#include "stdafx.h"
#include "dlgordine.h"
#include "resource.h"

OrdineDialog::OrdineDialog()
	: CDialog{ IDD_ORDINE }
{
}

OrdineDialog::~OrdineDialog()
{
}

BOOL OrdineDialog::OnInitDialog()
{
	// Attach the custom control to a CWnd object
	m_Grid.AttachDlgItem(IDC_ORDGRID, *this);
	return 0;
}
