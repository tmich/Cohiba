#include "stdafx.h"
#include "App.h"
#include "gui.h"

CFrameApp::CFrameApp()
{
}

CFrameApp::~CFrameApp()
{
	// unload ZeeGrid.dll
	::FreeLibrary(hgridmod);
}

BOOL CFrameApp::InitInstance()
{
	//Create the Frame Window
	if (m_Frame.Create() == 0)
	{
		// We get here if the Frame creation fails

		::MessageBox(NULL, _T("Failed to create Frame window"), _T("ERROR"), MB_ICONERROR);
		return FALSE; // returning FALSE ends the application
	}

	// load ZeeGrid.dll
	hgridmod = ::LoadLibrary(_T("zeegrid.dll"));
	if (!hgridmod)
	{
		guiutils::Error(_T("Unable to load zeegrid.dll"), m_Frame);
		::PostQuitMessage(0);
	}

	return TRUE;
}
