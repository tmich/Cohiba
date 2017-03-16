#include "stdafx.h"
#include "DlgArticoli.h"
#include "resource.h"

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

	// Attach the custom control to a CWnd object
	m_Grid.AttachDlgItem(IDC_CUSTOM1, *this);
	
	m_Resizer.Initialize(*this, CRect(0, 0, 300, 200));
	m_Resizer.AddChild(m_Grid, bottomleft, RD_STRETCH_WIDTH | RD_STRETCH_HEIGHT);
	
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

DlgArticoli::~DlgArticoli()
{
	
}
