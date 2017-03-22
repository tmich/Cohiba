#include "stdafx.h"
#include "resource.h"
#include "mainfrm.h"
#include "Dbconn.h"
#include "dbsettings.h"
#include <mariadb++\exceptions.hpp>
#include "View.h"
#include "DlgArticoli.h"
#include "dlgsettings.h"
#include "dlgordine.h"


CMainFrame::CMainFrame()
	:m_strKeyName{ _T("GestionaleM2\\Cohiba") },
	m_View{ new CView }
{
	// Constructor for CMainFrame. Its called after CFrame's constructor

	//Set m_View as the view window of the frame
	SetView(*m_View);

	// Set the registry key name, and load the initial window position
	// Use a registry key name like "CompanyName\\Application"
	LoadRegistrySettings(m_strKeyName);
}

CMainFrame::~CMainFrame()
{
	// Destructor for CMainFrame.
	m_View.release();
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// OnCommand responds to menu and and toolbar input

	UNREFERENCED_PARAMETER(lParam);

	switch (LOWORD(wParam))
	{
	case IDM_TABELLE_ARTICOLI:  return OnArticoli();
	case IDM_MAGAZZINO_CARICO:	return OnCaricoMagazzino();
	case IDM_NUOVOORDINE:		return OnNuovoOrdine();
	case IDM_EXIT:				return OnFileExit();
	case IDW_VIEW_STATUSBAR:	return OnViewStatusBar();
	case IDW_VIEW_TOOLBAR:		return OnViewToolBar();
	case IDM_ABOUT:				return OnHelp();
	}

	return FALSE;
}

int CMainFrame::OnCreate(CREATESTRUCT& cs)
{
	// OnCreate controls the way the frame is created.
	// Overriding CFrame::OnCreate is optional.
	// The default for the following variables is TRUE

	// SetUseIndicatorStatus(FALSE);	// Don't show keyboard indicators in the StatusBar
	// SetUseMenuStatus(FALSE);			// Don't show menu descriptions in the StatusBar
	// SetUseReBar(FALSE);				// Don't use a ReBar
	SetUseThemes(FALSE);				// Don't use themes
	SetUseToolBar(FALSE);				// Don't use a ToolBar

	// call the base class function
	return CFrame::OnCreate(cs);
}

BOOL CMainFrame::OnFileExit()
{
	// Issue a close request to the frame
	PostMessage(WM_CLOSE);
	return TRUE;
}

void CMainFrame::OnInitialUpdate()
{
	// Titolo
	m_Title.LoadStringW(IDS_APP_TITLE);
	SetTitle(m_Title);

	// provo la connessione al database
	try
	{
		MyConnectionProvider provider;
		auto conn = provider.connect();
	}
	catch (const mariadb::exception::connection& cnex)
	{
		TRACE(cnex.what());
		this->Error(cnex.what());
		SettingsDialog dlgs;
		dlgs.DoModal(*this);
	}
	catch (const CWinException& winexc)
	{
		TRACE(winexc.what());
		this->Error(_T("Non sono riuscito a leggere il registro di sistema"));
	}

	// a tutto schermo
	ShowWindow(SW_MAXIMIZE);

	TRACE("Frame created\n");
}

BOOL CMainFrame::OnFileOpen()
{
	CFileDialog FileDlg(TRUE);

	// Bring up the file open dialog retrieve the selected filename
	if (FileDlg.DoModal(*this) == IDOK)
	{
		//GetDoc().FileLoad(FileDlg.GetPathName());
	}

	return TRUE;
}

BOOL CMainFrame::OnFileSave()
{
	CFileDialog FileDlg(FALSE);

	// Bring up the file save dialog retrieve the selected filename
	if (FileDlg.DoModal(*this) == IDOK)
	{
		//GetDoc().FileStore(FileDlg.GetPathName());
	}

	return TRUE;
}

BOOL CMainFrame::OnFilePrint()
{
	// Bring up a dialog to choose the printer
	CPrintDialog Printdlg;

	try
	{
		INT_PTR Res = Printdlg.DoModal(*this);

		// Retrieve the printer DC
		// CDC dcPrinter = Printdlg.GetPrinterDC();

		// TODO:
		// Add your own code here. Refer to the tutorial for additional information

		return (Res == IDOK);	// boolean expression
	}

	catch (const CException& /* e */)
	{
		// No default printer
		MessageBox(_T("Unable to display print dialog"), _T("Print Failed"), MB_OK);
		return FALSE;
	}
}

LRESULT CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam)
{
	// Process notification messages sent by child windows
	//	switch(((LPNMHDR)lParam)->code)
	//	{
	//		Add case statements for each notification message here
	//	}

	// Some notifications should return a value when handled
	return CFrame::OnNotify(wParam, lParam);
}

void CMainFrame::PreCreate(CREATESTRUCT& cs)
{
	// This function is called before the frame is created.
	// It provides an opportunity to modify the various CREATESTRUCT
	// parameters used in the frame window's creation.

	// The WS_EX_LAYOUTRTL style requires Windows 2000 or above in targetver.h
	// cs.dwExStyle = WS_EX_LAYOUTRTL;		// Set Right-To-Left Window Layout

	// Call base clase to set defaults
	CFrame::PreCreate(cs);

	// cs.style &= ~WS_VISIBLE;	// Remove the WS_VISIBLE style. The frame will be initially hidden.
}

void CMainFrame::SetupToolBar()
{
	// Set the Resource IDs for the toolbar buttons
	//AddToolBarButton(IDM_FILE_NEW);
	//AddToolBarButton(IDM_FILE_OPEN);
	//AddToolBarButton(IDM_FILE_SAVE);

	//AddToolBarButton(0);						// Separator
	//AddToolBarButton(IDM_EDIT_CUT, FALSE);	// disabled button
	//AddToolBarButton(IDM_EDIT_COPY, FALSE);	// disabled button
	//AddToolBarButton(IDM_EDIT_PASTE, FALSE);	// disabled button

	//AddToolBarButton(0);						// Separator
	//AddToolBarButton(IDM_FILE_PRINT);

	//AddToolBarButton(0);						// Separator
	//AddToolBarButton(IDM_HELP_ABOUT);
}

LRESULT CMainFrame::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//	switch (uMsg)
	//	{
	//		Add case statements for each messages to be handled here
	//	}

	// pass unhandled messages on for default processing
	return WndProcDefault(uMsg, wParam, lParam);
}

BOOL CMainFrame::LoadRegistrySettings(LPCTSTR szKeyName)
{
	CFrame::LoadRegistrySettings(szKeyName);

	//// Leggo le impostazione del db
	//TCHAR szServer[201] = { 0 };
	//TCHAR szNome[201] = { 0 };
	//TCHAR szUsername[201] = { 0 };
	//TCHAR szPswd[201] = { 0 };
	//ULONG usz = 200;
	//CString KeyName = _T("Software\\") + m_strKeyName;
	//CString SubKey = KeyName + _T("\\Database");
	//CRegKey Key;

	//// se la chiave di registro non esiste: la creo...
	//if (ERROR_SUCCESS != Key.Open(HKEY_CURRENT_USER, SubKey, KEY_READ))
	//{
	//	if (ERROR_SUCCESS != Key.Create(HKEY_CURRENT_USER, SubKey))
	//		throw CWinException(_T("RegCreateKeyEx failed"));

	//	// ...la apro...
	//	if (ERROR_SUCCESS != Key.Open(HKEY_CURRENT_USER, SubKey))
	//		throw CWinException(_T("RegCreateKeyEx failed"));
	//	
	//	// ... e ci scrivo i valori di default
	//	if (ERROR_SUCCESS != Key.SetStringValue(_T("Server"), _T("127.0.0.1")))
	//		throw CWinException(_T("RegSetValueEx failed"));
	//	if (ERROR_SUCCESS != Key.SetStringValue(_T("Nome"), _T("tabacchi")))
	//		throw CWinException(_T("RegSetValueEx failed"));
	//	if (ERROR_SUCCESS != Key.SetStringValue(_T("Username"), _T("pippo")))
	//		throw CWinException(_T("RegSetValueEx failed"));
	//	if (ERROR_SUCCESS != Key.SetStringValue(_T("Password"), _T("pluto")))
	//		throw CWinException(_T("RegSetValueEx failed"));
	//}

	//if (ERROR_SUCCESS == Key.Open(HKEY_CURRENT_USER, SubKey, KEY_READ))
	//{
	//	// se esiste la chiave, leggo le informazioni
	//	if (ERROR_SUCCESS != Key.QueryStringValue(_T("Server"), szServer, &usz))
	//		throw CWinException(_T("QueryStringValue Failed"));
	//	if (ERROR_SUCCESS != Key.QueryStringValue(_T("Nome"), szNome, &usz))
	//		throw CWinException(_T("QueryStringValue Failed"));
	//	if (ERROR_SUCCESS != Key.QueryStringValue(_T("Username"), szUsername, &usz))
	//		throw CWinException(_T("QueryStringValue Failed"));
	//	if (ERROR_SUCCESS != Key.QueryStringValue(_T("Password"), szPswd, &usz))
	//		throw CWinException(_T("QueryStringValue Failed"));
	//}
	return 0;
}

BOOL CMainFrame::SaveRegistrySettings()
{
	CFrame::SaveRegistrySettings();
	return 0;
}

BOOL CMainFrame::OnArticoli()
{
	DlgArticoli dlgArticoli;
	dlgArticoli.DoModal(*this);
	return 0;
}

BOOL CMainFrame::OnCaricoMagazzino()
{
	m_View.release();
	m_View.reset(new CView);
	SetView(*m_View);
	return 0;
}

BOOL CMainFrame::OnNuovoOrdine()
{
	m_View.release();
	m_View.reset(new OrdineDialog);
	SetView(*m_View);
	return 0;
}

void CMainFrame::Error(CString message) const
{
	this->MessageBox(message.c_str(), _T("Errore"), MB_ICONERROR | MB_OK);
}
