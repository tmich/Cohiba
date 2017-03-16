#include "stdafx.h"
#include "CZeeGrid.h"

///*************** UTILS *********************///
std::string Utils::StringToUpper(std::string strToConvert)
{
	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

	return strToConvert;
}

std::wstring Utils::WstringToUpper(std::wstring strToConvert)
{
	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

	return strToConvert;
}

std::wstring Utils::StringToWstring(const std::string & inputString)
{
	// Make room for characters
	std::wstring destinationString(inputString.length(), L' ');

	// Copy string to wstring.
	std::copy(inputString.begin(), inputString.end(), destinationString.begin());
	return destinationString;
}

std::wstring Utils::s2ws(const std::string & s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

std::string Utils::ws2s(const std::wstring & ws)
{
	const std::string s(ws.begin(), ws.end());
	size_t sz = s.size();
	char * buff = new char[sz + 1]{ 0 };
	::strcpy_s(buff, sz + 1, s.c_str());

	return std::string{ buff };
}
///*************** UTILS *********************///

CZeeGrid::CZeeGrid()
	:CZeeGrid(0, 0)
{
}

CZeeGrid::CZeeGrid(unsigned int columns)
	: CZeeGrid(0, columns)
{
}

// construct a grid with specified rows and columns
CZeeGrid::CZeeGrid(unsigned int rows, unsigned int columns)
	: m_cols(columns), m_rows(rows), hgridmod{ nullptr }
{
	InitGrid();
}

CZeeGrid::~CZeeGrid()
{
	::SendMessage(m_hWnd, ZGM_EMPTYGRID, 0, 0);
}

void CZeeGrid::AppendRow()
{
	int cellIdx = ::SendMessage(m_hWnd, ZGM_APPENDROW, 0, 0);
	m_rows++;
}

void CZeeGrid::SetCellValue(unsigned int index, std::wstring text)
{
	std::string s = Utils::ws2s(text);
	SetCellValue(index, s);
}

void CZeeGrid::SetCellValue(unsigned int index, std::string text)
{
	::SendMessage(m_hWnd, ZGM_SETCELLTEXT, index, (LPARAM)text.c_str());
}

void CZeeGrid::SetCellValue(unsigned int index, int val)
{
	::SendMessage(m_hWnd, ZGM_SETCELLINT, index, (LPARAM)&val);
}

void CZeeGrid::SetCellValue(unsigned int index, double val)
{
	::SendMessage(m_hWnd, ZGM_SETCELLDOUBLE, index, (LPARAM)&val);
}

void CZeeGrid::Refresh()
{
	::SendMessage(m_hWnd, ZGM_REFRESHGRID, 0, 0);
}

void CZeeGrid::InitGrid()
{
	/*hgridmod = ::LoadLibrary(_T("zeegrid.dll"));
	if (!hgridmod)
	{
		::MessageBox(m_hWnd, _T("Unable to load ZeeGrid.DLL"), _T("Error"), MB_OK);
		::PostQuitMessage(0);
	}*/

	// The entry for the dialog's control in resource.rc must match this name.
	CString ClassName = _T("ZeeGrid");

	// Register the window class
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));

	if (!::GetClassInfo(GetApp().GetInstanceHandle(), ClassName, &wc))
	{
		wc.lpszClassName = ClassName;
		wc.lpfnWndProc = ::DefWindowProc;
		wc.hInstance = GetApp().GetInstanceHandle();
		::RegisterClass(&wc);
	}

	assert(::GetClassInfo(GetApp().GetInstanceHandle(), ClassName, &wc));
}

void CZeeGrid::OnInitialUpdate()
{
	::SendMessage(m_hWnd, ZGM_DIMGRID, m_cols, 0);
	
	// Add rows
	for (size_t i = 0; i < m_rows; i++)
		::SendMessage(m_hWnd, ZGM_APPENDROW, 0, 0);
}

LRESULT CZeeGrid::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CWnd::OnPaint(uMsg, wParam, lParam);
}

LRESULT CZeeGrid::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return WndProcDefault(uMsg, wParam, lParam);
}
