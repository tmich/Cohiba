#include "stdafx.h"
#include "artdao.h"
#include "wc_to_mb.h"

ArticoloDao::ArticoloDao()
	: m_Query{ "SELECT id, codice, nome, confezione, prezzo_kg, prezzo_confezione, unita_misura, qta, categoria_id, barcode from articolo where cancellato=0 " }
{
}

ArticoloDao::~ArticoloDao()
{
}

ListaArticoli ArticoloDao::all()
{
	ListaArticoli m_articoli;
	
	MyConnectionProvider myconn;
	mariadb::connection_ref conn = myconn.connect();
	mariadb::statement_ref stmt = conn->create_statement(m_Query.c_str());
	mariadb::result_set_ref rs = stmt->query();

	// righe
	while (rs->next())
	{
		Articolo art = fromResultset(rs);
		m_articoli.append(art);
	}

	return m_articoli;
}

void ArticoloDao::save(Articolo & articolo)
{
	std::string qry;
	if (articolo.getId() == 0)
	{
		;	// TODO: INSERT
	}
	else
	{
		qry = "update articolo set codice = ?, nome = ?, confezione = ?, prezzo_kg = ?, barcode = ? where id=?;";

	}

	MyConnectionProvider myconn;
	mariadb::connection_ref conn = myconn.connect();
	mariadb::statement_ref stmt = conn->create_statement(qry.c_str());
	stmt->set_unsigned32(0, articolo.getCodice());
	stmt->set_wstring(1, articolo.getNome());
	stmt->set_wstring(2, articolo.getConfezione());
	stmt->set_decimal(3, mariadb::decimal(std::to_string(articolo.getPrezzoKg()).c_str()));
	stmt->set_wstring(4, articolo.getBarcode());
	stmt->set_unsigned32(5, articolo.getId());
	auto rows_affected = stmt->execute();
}

Articolo ArticoloDao::perCodice(int codice)
{
	std::string query = m_Query + " and codice=?;";
	MyConnectionProvider myconn;
	mariadb::connection_ref conn = myconn.connect();
	mariadb::statement_ref stmt = conn->create_statement(query.c_str());
	stmt->set_unsigned32(0, codice);
	mariadb::result_set_ref rs = stmt->query();
	if (rs->row_count() == 0)
	{
		throw std::exception("non trovato");
	}
	else
	{
		rs->next();
		return fromResultset(rs);
	}
}

Articolo ArticoloDao::fromResultset(mariadb::result_set_ref rs)
{
	int id = rs->get_unsigned32("id");
	int codice = rs->get_unsigned32("codice");
	std::wstring nome{ rs->get_wstring("nome") };
	std::wstring conf{ rs->get_wstring("confezione") };
	std::string s_przkg = rs->get_string("prezzo_kg");
	double prezzo_kg{ stringutils::to_double(s_przkg) };
	std::string s_przconf = rs->get_string("prezzo_confezione");
	double prezzo_confezione{ stringutils::to_double(s_przconf) };
	std::string um = rs->get_string("unita_misura");
	std::string s_qta = rs->get_string("qta");
	double qta = stringutils::to_double(s_qta);
	int cat = rs->get_unsigned32("categoria_id");
	std::wstring bcod;
	if (!rs->is_null("barcode"))
	{
		bcod = rs->get_wstring("barcode");
	}

	return Articolo(id, codice, nome, prezzo_kg, prezzo_confezione, conf, um, qta, cat, bcod);
}
