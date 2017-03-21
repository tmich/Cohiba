#include "stdafx.h"
#include "DlgArticoli.h"
#include "resource.h"
#include "articolo.h"
#include "Dbconn.h"

DlgArticoli::DlgArticoli()
	: CDialog{ IDD_ARTICOLI }
{
}

BOOL DlgArticoli::OnInitDialog()
{
	// title
	CString m_title;
	m_title.LoadStringW(IDS_ARTICOLI);
	this->SetWindowTextW(m_title);

	AttachItem(IDC_ARTDES, m_txtDescr);
	AttachItem(IDC_ARTCODE, m_txtCodice);
	AttachItem(IDC_ARTBARCODE, m_txtBarcode);
	AttachItem(IDC_ARTCERCA, m_txtCerca);
	AttachItem(IDC_BTNCERCAART, m_btnCerca);
	AttachItem(IDC_GROUPBOX1, m_groupbox);

	// Attach the custom control to a CWnd object
	m_Grid.AttachDlgItem(IDC_CUSTOM1, *this);
	
	m_Resizer.Initialize(*this, CRect(0, 0, 300, 200));
	m_Resizer.AddChild(m_txtCerca, topleft, 0);
	m_Resizer.AddChild(m_btnCerca, topleft, 0);
	m_Resizer.AddChild(m_Grid, topleft, RD_STRETCH_WIDTH);
	m_Resizer.AddChild(m_groupbox, topleft, RD_STRETCH_HEIGHT);
	m_Resizer.AddChild(m_txtCodice, topleft, 0);
	m_Resizer.AddChild(m_txtDescr, topleft, 0);
	m_Resizer.AddChild(m_txtBarcode, topleft, 0);

	// query
	ListaArticoli articoli;
	MyConnectionProvider myconn;
	auto cnn = myconn.connect();
	mariadb::statement_ref stmt = cnn->create_statement("select id, codice, nome, confezione, prezzo_kg, barcode from articolo order by nome;");
	mariadb::result_set_ref rs = stmt->query();

	// righe
	while (rs->next())
	{
		int id = rs->get_unsigned32("id");
		int codice = rs->get_unsigned32("codice");
		std::wstring nome{ rs->get_wstring("nome") };
		std::wstring conf{ rs->get_wstring("confezione") };
		std::string s_przkg = rs->get_string("prezzo_kg");
		mariadb::decimal prezzo_kg{ s_przkg.c_str() };

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
		art.setPrezzoKg(prezzo_kg.double128());
		art.setBarcode(bcod);

		articoli.append(art);
	}

	cnn->disconnect();
	
	m_Grid.SetArticoli(articoli);
	//m_Grid.Update();

	// a tutto schermo
	ShowWindow(SW_MAXIMIZE);

	return 0;
}

INT_PTR DlgArticoli::DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Pass resizing messages on to the resizer
	m_Resizer.HandleMessage(uMsg, wParam, lParam);

	//  switch (uMsg)
	//  {
	//      Additional messages to be handled go here
	//  }

	// Pass unhandled messages on to parent DialogProc
	return DialogProcDefault(uMsg, wParam, lParam);
}

BOOL DlgArticoli::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_CUSTOM1:
	{
		switch (HIWORD(wParam))
		{
		case ZGN_CURSORCELLCHANGED:
			OnCellSelected();
			break;
		case ZGN_ROWSELECTED:
			OnRowSelected();
			break;
		case ZGN_F8:
			TRACE("ZGN_F8\n");
			break;
		case ZGN_GOTFOCUS:
			TRACE("ZGN_GOTFOCUS\n");
			break;
		case ZGN_LOSTFOCUS:
			TRACE("ZGN_LOSTFOCUS\n");
			break;
		}
	}
	break;
	case IDC_BTNCERCAART:
	{
		CString search = m_txtCerca.GetWindowTextW();
		m_Grid.FilterByNome(search.c_str());
	}
	break;
	default:
		break;
	}
	return 0;
}

void DlgArticoli::OnRowSelected()
{
	int rowIndex = m_Grid.SendMessageW(ZGM_GETSELECTEDROW, 0, 0);
	
	if (rowIndex >= 0)
	{
		m_Grid.SelectFirstCellAt(rowIndex);
		Articolo art = m_Grid.GetArticoloAt(rowIndex);
		ShowArticolo(art);
	}
}

void DlgArticoli::OnCellSelected()
{
	int cursorIndex = m_Grid.GetSelectedCellIndex();

	if (cursorIndex >= 0)
	{
		int rowIndex = m_Grid.GetRowIndex(cursorIndex);
		Articolo art = m_Grid.GetArticoloAt(rowIndex);
		ShowArticolo(art);
	}
}

void DlgArticoli::ShowArticolo(const Articolo & art)
{
	m_txtCodice.SetWindowTextW(std::to_wstring(art.getCodice()).c_str());
	m_txtBarcode.SetWindowTextW(art.getBarcode().c_str());
	m_txtDescr.SetWindowTextW(art.getNome().c_str());
}

DlgArticoli::~DlgArticoli()
{
	
}
