#include "stdafx.h"
#include "artdao.h"
#include "wc_to_mb.h"

ArticoloDao::ArticoloDao()
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
	const char * qry = "select id, codice, nome, confezione, prezzo_kg, barcode, categoria_id from articolo where cancellato=0;";
	mariadb::statement_ref stmt = conn->create_statement(qry);
	mariadb::result_set_ref rs = stmt->query();

	// righe
	while (rs->next())
	{
		int id = rs->get_unsigned32("id");
		int codice = rs->get_unsigned32("codice");
		std::wstring nome{ rs->get_wstring("nome") };
		std::wstring conf{ rs->get_wstring("confezione") };
		std::string s_przkg = rs->get_string("prezzo_kg");
		double prezzo_kg{ stringutils::to_double(s_przkg.c_str()) };
		int cat = rs->get_unsigned32("categoria_id");

		std::wstring bcod;
		if (!rs->is_null("barcode"))
		{
			bcod = rs->get_wstring("barcode");
		}

		Articolo art;
		art.setId(id);
		art.setNome(nome);
		art.setCodice(codice);
		art.setConfezione(conf);
		art.setPrezzoKg(prezzo_kg);
		art.setBarcode(bcod);
		art.setCategoria(cat);

		m_articoli.append(art);
	}

	return m_articoli;
}

void ArticoloDao::save(Articolo & articolo)
{
	std::string qry;
	if (articolo.getId() == 0)
	{
		;
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
