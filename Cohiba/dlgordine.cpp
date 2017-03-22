#include "stdafx.h"
#include "dlgordine.h"
#include "resource.h"
#include "dlgsceltaarticolo.h"
#include "gui.h"

OrdineDialog::OrdineDialog()
	: CDialog{ IDD_ORDINE }
{
}

OrdineDialog::~OrdineDialog()
{
}

void OrdineDialog::OnCercaArticolo()
{
	SceltaArticoloDialog dlg;
	INT_PTR resp = dlg.DoModal(*this);
	
	if (resp == IDOK)
	{
		Articolo a = dlg.GetScelta();
		VoceOrdine vo{ a, 1 };
		m_Ordine.aggiungi(vo);
		m_Grid.SetVoci(m_Ordine.getVoci());
		m_Grid.Update();
	}
}

BOOL OrdineDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BTNCERCAART:
		OnCercaArticolo();
		break;
	}
	return 0;
}

BOOL OrdineDialog::OnInitDialog()
{
	AttachItem(IDC_NORDTITL, m_Title);
	AttachItem(IDC_BTNCERCAART, m_btnCercaArt);
	// Attach the custom control to a CWnd object
	m_Grid.AttachDlgItem(IDC_ORDGRID, *this);

	CString title;
	title.LoadStringW(IDS_NUOVOORD);
	m_Title.SetWindowTextW(title);
	CFont titleFont = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Microsoft Sans Serif"));
	m_Title.SetFont(titleFont);
	return 0;
}
