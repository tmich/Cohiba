#include "stdafx.h"
#include "GridArticoli.h"
#include "Dbconn.h"

GridArticoli::GridArticoli()
	: CZeeGrid{ 5 }
{
}

GridArticoli::~GridArticoli()
{
}

void GridArticoli::OnInitialUpdate()
{
	int idx = 1;
	CZeeGrid::OnInitialUpdate();

	MyConnection myconn;
	auto cnn = myconn.connect();
	//mariadb::result_set_ref rs = cnn->query("select id, codice, nome, confezione, prezzo_kg from articolo limit 30;");
	mariadb::statement_ref stmt = cnn->create_statement("select id, codice, nome, confezione, prezzo_kg from articolo;");
	mariadb::result_set_ref rs = stmt->query();

	// intestazioni
	::SendMessage(m_hWnd, ZGM_SETCELLTEXT, idx++, (LPARAM)"ID");
	::SendMessage(m_hWnd, ZGM_SETCELLTEXT, idx++, (LPARAM)"CODICE");
	::SendMessage(m_hWnd, ZGM_SETCELLTEXT, idx++, (LPARAM)"NOME");
	::SendMessage(m_hWnd, ZGM_SETCELLTEXT, idx++, (LPARAM)"CONFEZIONE");
	::SendMessage(m_hWnd, ZGM_SETCELLTEXT, idx++, (LPARAM)"PREZZO KG");
	
	// righe
	while(rs->next())
	{
		int id = rs->get_unsigned32("id");
		int codice = rs->get_unsigned32("codice");

		std::wstring nome{ rs->get_wstring("nome") };
		std::wstring conf{ rs->get_wstring("confezione") };
		std::string s_przkg = rs->get_string("prezzo_kg");
		mariadb::decimal prezzo_kg{ s_przkg.c_str() };
		AppendRow();
		
		SetCellValue(idx++, id);
		SetCellValue(idx++, codice);
		SetCellValue(idx++, nome);
		SetCellValue(idx++, conf);
		SetCellValue(idx++, prezzo_kg.str());
	}

	cnn->disconnect();
}