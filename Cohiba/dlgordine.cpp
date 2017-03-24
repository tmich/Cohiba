#include "stdafx.h"
#include "dlgordine.h"
#include "resource.h"
#include "dlgsceltaarticolo.h"
#include "artdao.h"
#include "gui.h"

OrdineDialog::OrdineDialog()
	: CDialog{ IDD_ORDINE }
{
}

OrdineDialog::~OrdineDialog()
{
}

void OrdineDialog::AggiornaTotali()
{
	double totLordo = m_Ordine.getPrezzoTotale();
	double totAggio = m_Ordine.getAggioTotale();
	double totNetto = totLordo - totAggio;
	m_txtTotKG.SetWindowTextW(stringutils::to_wstring(m_Ordine.getPesoTotale(), 3).c_str());
	m_txtTotLordo.SetWindowTextW(stringutils::to_wstring(totLordo).c_str());
	m_txtTotAggio.SetWindowTextW(stringutils::to_wstring(totAggio).c_str());
	m_txtTotNetto.SetWindowTextW(stringutils::to_wstring(totNetto).c_str());
}

void OrdineDialog::ModificaVoce(VoceOrdine & voce)
{
	m_VoceDaModificare = std::make_unique<VoceOrdine>(voce);
	UnitaMisura um = m_VoceDaModificare->getArticolo().getUnitaMisura();
	m_txtCodArt.SetWindowTextW(std::to_wstring(voce.getCodice()).c_str());
	m_txtDescArt.SetWindowTextW(voce.toString().c_str());
	m_txtBarcode.SetWindowTextW(voce.getBarcode().c_str());
	m_txtKG.SetWindowTextW(stringutils::to_wstring(voce.getPesoKG(), 3).c_str());
	if(m_VoceDaModificare->getNumConfezioni() > 0)
		m_txtNumConfezioni.SetWindowTextW(stringutils::to_wstring(m_VoceDaModificare->getNumConfezioni(), 0).c_str());
	m_btnAddVoce.EnableWindow(true);
	m_btnAddVoce.SendMessageW(DM_SETDEFID, IDC_BTNADDVOCE, 0);
	m_txtNumConfezioni.SetFocus();

	//m_txtKG.SetReadOnly(um == UnitaMisura::PEZZI);
	//m_txtNumConfezioni.SetReadOnly(um == UnitaMisura::GRAMMI);
}

void OrdineDialog::OnAggiungiVoce()
{
	if (m_VoceDaModificare.get() == nullptr)
	{
		return;
	}

	try
	{
		OnQtaConfezioni();
		CString snum{ m_txtNumConfezioni.GetWindowTextW() };
		int numConf = 1;
		numConf = std::stoi(snum.c_str());
		m_VoceDaModificare->setNumConfezioni(numConf);
		m_Ordine.aggiungi(*m_VoceDaModificare);
		m_Grid.SetOrdine(m_Ordine);
		m_Grid.Update();

		AggiornaTotali();
		VoceAggiunta();
	}
	catch (const std::invalid_argument&)
	{
		m_txtNumConfezioni.SetFocus();
	}
}

void OrdineDialog::OnEliminaVoce()
{
	if (m_VoceDaModificare.get() == nullptr)
	{
		return;
	}

	m_Ordine.rimuovi(*m_VoceDaModificare);
	//m_Ordine.aggiungi(*m_VoceDaModificare);
	m_Grid.SetOrdine(m_Ordine);
	m_Grid.Update();

	AggiornaTotali();
	VoceAggiunta();
}

void OrdineDialog::OnCercaArticolo()
{
	Articolo * m_art{ nullptr };
	SceltaArticolo scelta;
	m_art = scelta.scegli();

	if (m_art != nullptr)
	{
		VoceOrdine vo{ *m_art, 1 };
		ModificaVoce(vo);
	}
	delete m_art;
}

void OrdineDialog::OnCodiceArticolo()
{
	std::wstring codart = m_txtCodArt.GetWindowTextW();
	try
	{
		int codice = std::stoi(codart);
	
		ArticoloDao artdao;
		Articolo art = artdao.perCodice(codice);
		VoceOrdine vo{ art, 0 };
		ModificaVoce(vo);
	}
	catch (const std::out_of_range&)
	{
		// numero troppo grande
	}
	catch (const std::invalid_argument&)
	{
		// non è un numero
	}
	catch (const std::exception&)
	{
		//	non trovato
		VoceAggiunta();
	}
}

void OrdineDialog::OnBarcode()
{
	std::wstring barcode = m_txtBarcode.GetWindowTextW();
	if (barcode.size() > 0)
	{
		try
		{
			ArticoloDao artdao;
			Articolo art = artdao.perBarcode(barcode);
			VoceOrdine vo{ art, 0 };
			ModificaVoce(vo);
		}
		catch (const std::exception&)
		{
			//	non trovato
			VoceAggiunta();
		}
	}
}

void OrdineDialog::OnQtaConfezioni()
{
	// dalle confezioni al peso...
	if (m_VoceDaModificare.get() != nullptr)
	{
		CString s_num = m_txtNumConfezioni.GetWindowTextW();
		int numConfezioni = 0;
		try
		{
			numConfezioni = std::stoi(s_num.c_str());
			m_VoceDaModificare->setNumConfezioni(numConfezioni);
			double kg = m_VoceDaModificare->getPesoKG();
			m_txtKG.SetWindowTextW(stringutils::to_wstring(kg, 3).c_str());
		}
		catch (std::invalid_argument&)
		{
			throw;
		}
	}
}

void OrdineDialog::OnGridDblClick()
{
	int cellIndex = m_Grid.GetSelectedCellIndex();
	
	if (cellIndex >= 0)
	{
		size_t RigaSelezionata = m_Grid.GetRowIndex(cellIndex);
		if (m_Grid.HasVoceAt(RigaSelezionata))
		{
			VoceOrdine vo = m_Grid.GetVoceAt(RigaSelezionata);
			m_btnDelVoce.EnableWindow(true);
			ModificaVoce(vo);
		}
	}
}

void OrdineDialog::VoceAggiunta()
{
	m_txtCodArt.SetWindowTextW(_T(""));
	m_txtDescArt.SetWindowTextW(_T(""));
	m_txtBarcode.SetWindowTextW(_T(""));
	m_txtKG.SetWindowTextW(_T(""));
	m_txtNumConfezioni.SetWindowTextW(_T(""));
	m_txtCodArt.SetFocus();
	m_VoceDaModificare.release();
	m_btnAddVoce.EnableWindow(false);
	m_btnDelVoce.EnableWindow(false);
}

BOOL OrdineDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BTNCERCAART:
		OnCercaArticolo();	break;
	case IDC_BTNADDVOCE:
		OnAggiungiVoce();	break;
	case IDC_BTNDELDVOCE:
		OnEliminaVoce();	break;
	case IDC_ORDCODART:
		if (HIWORD(wParam) == EN_KILLFOCUS)	OnCodiceArticolo();	return TRUE;
	case IDC_ORDBARCODE:
		if (HIWORD(wParam) == EN_KILLFOCUS)	OnBarcode();		return TRUE;
	case IDC_ORDGRID:
		if (HIWORD(wParam) == ZGN_DOUBLECLICKREADONLY)	OnGridDblClick();	return TRUE;
	case IDC_ORDQTACONF:
		if (HIWORD(wParam) == EN_KILLFOCUS)	OnQtaConfezioni();	return TRUE;
	}

	return 0;
}

BOOL OrdineDialog::DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case EN_KILLFOCUS:
		switch (LOWORD(wParam))
		{
		case IDC_ORDCODART:	
			OnCodiceArticolo(); 
			return TRUE;
		}
		break;
	}
	return DialogProcDefault(uMsg, wParam, lParam);
}

BOOL OrdineDialog::OnInitDialog()
{
	AttachItem(IDC_ORDCODART, m_txtCodArt);
	AttachItem(IDC_ORDBARCODE, m_txtBarcode);
	AttachItem(IDC_ORDDESCART, m_txtDescArt);
	AttachItem(IDC_ORDQTAART, m_txtKG);
	AttachItem(IDC_NORDTITL, m_Title);
	AttachItem(IDC_BTNCERCAART, m_btnCercaArt);
	AttachItem(IDC_BTNADDVOCE, m_btnAddVoce);
	AttachItem(IDC_BTNDELDVOCE, m_btnDelVoce);
	AttachItem(IDC_ORDQTACONF, m_txtNumConfezioni);
	AttachItem(IDC_ORDTOTKG, m_txtTotKG);
	AttachItem(IDC_ORDTOTLORDO, m_txtTotLordo);
	AttachItem(IDC_ORDTOTAGGIO, m_txtTotAggio);
	AttachItem(IDC_ORDTOTNETTO, m_txtTotNetto);

	// Attach the custom control to a CWnd object
	m_Grid.AttachDlgItem(IDC_ORDGRID, *this);

	// Create font
	titleFont = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Microsoft Sans Serif"));
		
	CString title;
	title.LoadStringW(IDS_NUOVOORD);
	m_Title.SetWindowTextW(title);
	m_Title.SetFont(titleFont);

	m_txtCodArt.SetFocus();
	return 0;
}


/********* CColorEdit ***********/
BOOL CColorEdit::OnEraseBkgnd(CDC & dc)
{
	dc.SetBkMode(TRANSPARENT);
	//dc.SetTextColor(RGB(0, 0, 0));
	//dc.SetBkColor(RGB(204, 155, 153));
	return true;
}

LRESULT CColorEdit::OnMessageReflect(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CTLCOLORSTATIC)
	{
		return (INT_PTR)CreateSolidBrush(RGB(150, 250, 50));
	}

	return 0L;
}
