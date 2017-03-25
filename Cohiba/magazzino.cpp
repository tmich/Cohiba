#include "stdafx.h"
#include "magazzino.h"
#include "Dbconn.h"
#include "artdao.h"
#include <algorithm>
#include <exception>

/************** Magazzino **************/
Magazzino::Magazzino()
{
	MyConnectionProvider connectionProvider;
	auto conn = connectionProvider.connect();
	auto rs = conn->query("select id, articolo_id, quantita, soglia from magazzino;");

	ArticoloDao artdao;
	while (rs->next())
	{
		int id = rs->get_unsigned32("id");
		int articolo_id = rs->get_unsigned32("articolo_id");
		int qta = rs->get_unsigned32("quantita");
		int soglia = rs->get_unsigned32("soglia");
		
		Articolo art = artdao.perId(id);
		VoceMagazzino vm{ art,qta };
		vm.m_Id = id;
		vm.setSoglia(soglia);

		m_voci.push_back(vm);
	}
}

Magazzino::~Magazzino()
{
}

ListaVociMagazzino Magazzino::getVoci() const
{
	return m_voci;
}

void Magazzino::carica(const Articolo & articolo, int qta)
{
	try
	{
		VoceMagazzino vm = m_voci[articolo];
		vm.setQta(qta);
		dbUpdate(vm);
	}
	catch (const std::exception&)
	{
		VoceMagazzino vm{ articolo,qta };
		m_voci.push_back(vm);
		dbInsert(vm);
	}
}

void Magazzino::scarica(const Articolo &, int qta)
{
}

void Magazzino::dbUpdate(VoceMagazzino & vm)
{
	MyConnectionProvider connectionProvider;
	auto conn = connectionProvider.connect();
	auto stmt = conn->create_statement("update magazzino set quantita=?, soglia=? where id=?;");
	stmt->set_unsigned32(0, vm.getQta());
	stmt->set_unsigned32(1, vm.getSoglia());
	stmt->set_unsigned32(2, vm.m_Id);
	stmt->execute();
}

void Magazzino::dbInsert(VoceMagazzino & vm)
{
	MyConnectionProvider connectionProvider;
	auto conn = connectionProvider.connect();
	auto stmt = conn->create_statement("insert into magazzino (articolo_id, quantita, soglia values(?,?,?);");
	stmt->set_unsigned32(0, vm.getArticolo().getId());
	stmt->set_unsigned32(1, vm.getQta());
	stmt->set_unsigned32(2, vm.getSoglia());
	stmt->execute();

	int lastId = conn->execute("select LAST_INSERT_ID();");
	vm.m_Id = lastId;
}

/************** ListaVociMagazzino **************/
ListaVociMagazzino::ListaVociMagazzino()
{
}

ListaVociMagazzino::~ListaVociMagazzino()
{
}

std::vector<VoceMagazzino>::iterator ListaVociMagazzino::begin()
{
	return m_vect.begin();
}

std::vector<VoceMagazzino>::iterator ListaVociMagazzino::end()
{
	return m_vect.end();
}

VoceMagazzino & ListaVociMagazzino::operator[](const Articolo & articolo)
{
	auto it = std::find_if(begin(), end(), [articolo](const VoceMagazzino& vm) 
	{
		return vm.getArticolo() == articolo; 
	});

	if (it != end())
		return *it;

	throw std::exception{ "non trovato" };
}

size_t ListaVociMagazzino::size() const
{
	return m_vect.size();
}

void ListaVociMagazzino::push_back(VoceMagazzino & vm)
{
	m_vect.push_back(vm);
}

/************** VoceMagazzino **************/

VoceMagazzino::VoceMagazzino(const Articolo & articolo, int qta)
	: m_Articolo{ articolo }, m_Qta{ qta }
{
}

double VoceMagazzino::valore() const
{
	return m_Qta * m_Articolo.getPrezzoConfezione();
}
