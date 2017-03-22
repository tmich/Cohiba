#pragma once
#include "zeegrid.h"
#include <string>

namespace Utils
{
	std::string StringToUpper(std::string strToConvert);
	std::wstring WstringToUpper(std::wstring strToConvert);
	std::wstring StringToWstring(const std::string &inputString);
	std::wstring s2ws(const std::string& s);
	std::string ws2s(const std::wstring& ws);
};

class CZeeGrid : public CWnd
{
public:
	CZeeGrid();
	CZeeGrid(unsigned int columns);
	CZeeGrid(unsigned int rows, unsigned int columns);
	~CZeeGrid();

	int AppendRow();
	unsigned int RowCount() const { return m_rows; }
	void SetCellValue(unsigned int index, std::wstring);
	void SetCellValue(unsigned int index, std::string);
	void SetCellValue(unsigned int index, int);
	void SetCellValue(unsigned int index, double);
	
	void SelectFirstCellAt(int rowIndex) const;
	int GetSelectedCellIndex() const;
	int GetRowIndex(int cellIndex) const;
	std::string GetCellText(int cellIndex) const;
	std::wstring GetCellTextW(int cellIndex) const;
	void EmptyGrid();
	void Refresh();
protected:
	void InitGrid();
	void OnInitialUpdate() override;
	//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	unsigned int m_cols;
	unsigned int m_rows;
	HMODULE hgridmod;
};

