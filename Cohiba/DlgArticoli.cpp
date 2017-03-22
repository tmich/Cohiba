#include "stdafx.h"
#include "DlgArticoli.h"
#include "resource.h"
#include "artdao.h"
#include "gui.h"

DlgArticoli::DlgArticoli()
	: CDialog{ IDD_ARTICOLI }, m_artmod{ nullptr }
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
	AttachItem(IDC_ARTPRZKG, m_txtPrezzoKg);
	AttachItem(IDC_ARTCAT, m_txtCategoria);
	AttachItem(IDC_ARTCONF, m_txtConfezione);
	AttachItem(IDC_BTNCERCAART, m_btnCerca);
	AttachItem(IDC_BTNSALVAART, m_btnSalva);
	AttachItem(IDC_GROUPBOX1, m_groupbox);
	
	// Attach the custom control to a CWnd object
	m_Grid.AttachDlgItem(IDC_CUSTOM1, *this);
	
	m_Resizer.Initialize(*this, CRect(0, 0, 300, 200));
	m_Resizer.AddChild(m_txtCerca, topleft, 0);
	m_Resizer.AddChild(m_btnCerca, topleft, 0);
	m_Resizer.AddChild(m_Grid, topleft, 0);
	m_Resizer.AddChild(m_groupbox, topleft, RD_STRETCH_HEIGHT);
	m_Resizer.AddChild(m_txtCodice, topleft, 0);
	m_Resizer.AddChild(m_txtDescr, topleft, 0);
	m_Resizer.AddChild(m_txtBarcode, topleft, 0);

	// aggiorno i dati
	ArticoloDao artdao;
	m_articoli = artdao.all();
	m_Grid.SetArticoli(m_articoli);
	m_Grid.Update();

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

void DlgArticoli::OnClose()
{
	m_Grid.EmptyGrid();
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
		}
	}
	break;
	case IDC_BTNCERCAART:
		OnCercaPerNome();
		break;
	case IDC_BTNSALVAART:
		OnSalvaArticolo();
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
		OnCellSelected();
	}
}

void DlgArticoli::OnCellSelected()
{
	int cursorIndex = m_Grid.GetSelectedCellIndex();

	if (cursorIndex >= 0)
	{
		int rowIndex = m_Grid.GetRowIndex(cursorIndex);
		Articolo& art = m_Grid.GetArticoloAt(rowIndex);

		m_artmod.release();
		m_artmod.reset(&art);
		UpdateArticolo();
	}
}

void DlgArticoli::UpdateArticolo()
{
	if (m_artmod != nullptr)
	{
		CString codice;
		codice.AppendFormat(_T("%d"), m_artmod->getCodice());
		m_txtCodice.SetWindowTextW(codice);
		m_txtBarcode.SetWindowTextW(m_artmod->getBarcode().c_str());
		m_txtDescr.SetWindowTextW(m_artmod->getNome().c_str());
		CString przkg;
		przkg.AppendFormat(_T("%.2f"), m_artmod->getPrezzoKg());
		m_txtPrezzoKg.SetWindowTextW(przkg);
		m_txtConfezione.SetWindowTextW(m_artmod->getConfezione().c_str());
		m_txtCategoria.SetWindowTextW(m_artmod->getCategoria().c_str());
		m_btnSalva.EnableWindow(true);
	}
	else
	{
		m_txtCodice.SetWindowTextW(_T(""));
		m_txtBarcode.SetWindowTextW(_T(""));
		m_txtDescr.SetWindowTextW(_T(""));
		m_txtPrezzoKg.SetWindowTextW(_T(""));
		m_txtConfezione.SetWindowTextW(_T(""));
		m_txtCategoria.SetWindowTextW(_T(""));
		m_btnSalva.EnableWindow(false);
	}
}

void DlgArticoli::OnCercaPerNome()
{
	CString search = m_txtCerca.GetWindowTextW();
	search.MakeUpper();
	RicercaArticoli ricerca{ m_articoli };
	m_Grid.SetArticoli(ricerca.perNome(search.c_str()));
	m_Grid.Update();

	m_artmod.release();
	UpdateArticolo();
}

void DlgArticoli::OnSalvaArticolo()
{
	if (m_artmod != nullptr)
	{
		try
		{
			m_artmod->setBarcode(m_txtBarcode.GetWindowTextW().c_str());
			std::wstring wsp = m_txtPrezzoKg.GetWindowTextW().c_str();
			double prezzoKg = stringutils::to_double(wsp);
			m_artmod->setPrezzoKg(prezzoKg);

			ArticoloDao artdao;
			artdao.save(*m_artmod);
			CString msg;
			msg.LoadStringW(IDS_OKARTSALVA);
			guiutils::Notify(msg.c_str(), *this);
			m_Grid.Update();
		}
		catch (const std::exception& exc)
		{
			TRACE(_T("ECCEZIONE DlgArticoli::OnSalvaArticolo"));
			mb_to_wc e{ exc.what() };
			guiutils::Warning(e.asStdWstring(), *this);
		}
	}
}

DlgArticoli::~DlgArticoli()
{
	m_artmod.release();
}
