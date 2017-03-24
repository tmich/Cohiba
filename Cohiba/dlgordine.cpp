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

void OrdineDialog::ModificaVoce(VoceOrdine & voce)
{
	m_VoceDaModificare = std::make_unique<VoceOrdine>(voce);
	UnitaMisura um = m_VoceDaModificare->getArticolo().getUnitaMisura();
	m_txtCodArt.SetWindowTextW(std::to_wstring(voce.getCodice()).c_str());
	m_txtDescArt.SetWindowTextW(voce.getNome().c_str());
	m_txtBarcode.SetWindowTextW(voce.getBarcode().c_str());
	m_txtKG.SetWindowTextW(stringutils::to_wstring(voce.getQtaKG(), 3).c_str());
	m_txtNumConfezioni.SetWindowTextW(stringutils::to_wstring(m_VoceDaModificare->getNumConfezioni(), 0).c_str());
	m_btnAddVoce.EnableWindow(true);
	m_btnAddVoce.SendMessageW(DM_SETDEFID, IDC_BTNADDVOCE, 0);

	m_txtKG.SetReadOnly(um == UnitaMisura::PEZZI);
	m_txtNumConfezioni.SetReadOnly(um == UnitaMisura::GRAMMI);
}

void OrdineDialog::OnAggiungiVoce()
{
	if (m_VoceDaModificare.get() == nullptr)
	{
		return;
	}

	OnQtaConfezioni();

	double qtaKG = stringutils::to_double(m_txtKG.GetWindowTextW().c_str());
	if (qtaKG == 0)
		qtaKG = 1;
	m_VoceDaModificare->setQtaKG(qtaKG);
	m_Ordine.aggiungi(*m_VoceDaModificare);
	m_Grid.SetVoci(m_Ordine.getVoci());
	m_Grid.Update();
	m_Totale.SetWindowTextW(stringutils::to_wstring(m_Ordine.getPrezzoTotale()).c_str());

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
	/*double qta = 1.00;
	if (m_txtKG.GetWindowTextW().GetLength() > 0)
	{
		qta = stringutils::to_double(m_txtKG.GetWindowTextW().c_str());
	}*/

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

void OrdineDialog::OnQtaConfezioni()
{
	// dalle confezioni al peso...
	if (m_VoceDaModificare.get() != nullptr)
	{
		CString s_num = m_txtNumConfezioni.GetWindowTextW();
		double numConfezioni = stringutils::to_double(s_num.c_str());
		Articolo a = m_VoceDaModificare->getArticolo();
		double pezziPerConfezione = a.getPezziPerConfezione();
		double kg = a.getKg(pezziPerConfezione * numConfezioni);
		m_txtKG.SetWindowTextW(stringutils::to_wstring(kg, 3).c_str());
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
}

BOOL OrdineDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BTNCERCAART:
		OnCercaArticolo();
		break;
	case IDC_BTNADDVOCE:
		OnAggiungiVoce();
		break;
	case IDC_ORDCODART:
		if (HIWORD(wParam) == EN_KILLFOCUS)	OnCodiceArticolo();	return TRUE;
		break;
	case IDC_ORDGRID:
		if (HIWORD(wParam) == ZGN_DOUBLECLICKREADONLY)	OnGridDblClick();	return TRUE;
		break;
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
	AttachItem(IDC_ORDTOTALE, m_Totale);
	AttachItem(IDC_ORDQTACONF, m_txtNumConfezioni);

	// Attach the custom control to a CWnd object
	m_Grid.AttachDlgItem(IDC_ORDGRID, *this);

	// Create font
	titleFont = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Microsoft Sans Serif"));

	CString title;
	title.LoadStringW(IDS_NUOVOORD);
	m_Title.SetWindowTextW(title);
	m_Title.SetFont(titleFont);
	m_Totale.SetFont(titleFont);
	m_Totale.SetWindowTextW(stringutils::to_wstring(m_Ordine.getPrezzoTotale()).c_str());

	m_txtCodArt.SetFocus();
	return 0;
}