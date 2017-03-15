#include "stdafx.h"
#include "DlgArticoli.h"
#include "resource.h"

DlgArticoli::DlgArticoli()
	: CDialog{ IDD_DIALOG1 }
{
}

BOOL DlgArticoli::OnInitDialog()
{
	// Attach the custom control to a CWnd object
	m_Grid.AttachDlgItem(IDC_CUSTOM1, *this);
	
	return 0;
}

DlgArticoli::~DlgArticoli()
{
}
