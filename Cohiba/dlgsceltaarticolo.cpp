#include "stdafx.h"
#include "dlgsceltaarticolo.h"
#include "artdao.h"
#include "resource.h"

SceltaArticoloDialog::SceltaArticoloDialog()
	: CDialog{ IDD_SCELTAART }, m_Scelta{ nullptr }, m_bScelta{ false }
{
}

SceltaArticoloDialog::~SceltaArticoloDialog()
{
}

Articolo * SceltaArticoloDialog::GetArticolo()
{
	return m_Scelta.release();
}

bool SceltaArticoloDialog::Ok()
{
	return m_bScelta;
}

//Articolo * SceltaArticoloDialog::GetScelta()
//{
//	return m_pArticoloScelto;
//}

//bool SceltaArticoloDialog::GetScelta(Articolo &art)
//{
//	if(m_bScelta)
//		art = *m_Scelta;
//
//	return m_bScelta;
//}

BOOL SceltaArticoloDialog::OnInitDialog()
{
	// title
	CString m_title;
	m_title.LoadStringW(IDS_SCELTAART);
	this->SetWindowTextW(m_title);

	AttachItem(IDC_BTNCERCAART, m_btnCerca);
	AttachItem(IDC_ARTCERCA, m_txtCerca);
	// Attach the custom control to a CWnd object
	m_Grid.AttachDlgItem(IDC_CUSTOM1, *this);

	m_Resizer.Initialize(*this, CRect(0, 0, 300, 200));
	m_Resizer.AddChild(m_txtCerca, topleft, 0);
	m_Resizer.AddChild(m_btnCerca, topleft, 0);
	m_Resizer.AddChild(m_Grid, topleft, 0);

	// aggiorno i dati
	ArticoloDao artdao;
	m_articoli = artdao.all();
	m_Grid.SetArticoli(m_articoli);
	m_Grid.Update();

	return 0;
}

INT_PTR SceltaArticoloDialog::DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

void SceltaArticoloDialog::OnClose()
{
}

BOOL SceltaArticoloDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BTNCERCAART:	OnCerca();	return TRUE;
	case IDC_CUSTOM1:
	{
		switch (HIWORD(wParam))
		{
		case ZGN_DOUBLECLICKREADONLY:	OnGridDblClick();	return TRUE;
		}
	}
	break;
	}

	return 0;
}

void SceltaArticoloDialog::OnCerca()
{
	CString search = m_txtCerca.GetWindowTextW();
	search.MakeUpper();
	RicercaArticoli ricerca{ m_articoli };
	m_Grid.SetArticoli(ricerca.perNome(search.c_str()));
	m_Grid.Update();
}

void SceltaArticoloDialog::OnGridDblClick()
{
	int cellIndex = m_Grid.GetSelectedCellIndex();
	if (cellIndex >= 0)
	{
		int rowIndex = m_Grid.GetRowIndex(cellIndex);
		//m_pArticoloScelto = new Articolo{ m_Grid.GetArticoloAt(rowIndex) };
		
		m_Scelta = std::make_unique<Articolo>(m_Grid.GetArticoloAt(rowIndex));
		m_bScelta = true;
		EndDialog(IDOK);
	}
}


/******* SceltaArticolo **********/

SceltaArticolo::SceltaArticolo()
{
}

SceltaArticolo::~SceltaArticolo()
{
}

Articolo * SceltaArticolo::scegli()
{
	INT_PTR resp = dlg.DoModal();

	if (resp == IDOK)
	{
		if (dlg.Ok())
		{
			auto p = dlg.GetArticolo();
			return p;
		}
	}

	return nullptr;
}
