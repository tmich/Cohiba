#include "stdafx.h"
#include "gui.h"
#include "resource.h"
#include <wxx_cstring.h>

void guiutils::Error(std::wstring message, HWND parent)
{
	CString apptitle;
	apptitle.LoadStringW(IDS_APP_TITLE);
	MessageBox(parent, message.c_str(), apptitle.c_str(), MB_ICONERROR);
}

void guiutils::Warning(std::wstring message, HWND parent)
{
	CString apptitle;
	apptitle.LoadStringW(IDS_APP_TITLE);
	MessageBox(parent, message.c_str(), apptitle.c_str(), MB_ICONEXCLAMATION);
}

void guiutils::Notify(std::wstring message, HWND parent)
{
	CString apptitle;
	apptitle.LoadStringW(IDS_APP_TITLE);
	MessageBox(parent, message.c_str(), apptitle.c_str(), MB_ICONASTERISK);
}

int guiutils::Confirm(std::wstring message, HWND parent)
{
	CString apptitle;
	apptitle.LoadStringW(IDS_APP_TITLE);
	return MessageBox(parent, message.c_str(), apptitle.c_str(), MB_YESNO | MB_ICONQUESTION);
}
