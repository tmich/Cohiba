#pragma once
#include "GridArticoli.h"

class DlgArticoli : public CDialog
{
public:
	DlgArticoli();
	virtual ~DlgArticoli();
protected:
	BOOL OnInitDialog() override;
	INT_PTR DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnRowSelected();
	virtual void OnCellSelected();
	virtual void ShowArticolo(const Articolo& art);
private:
	GridArticoli m_Grid;
	CResizer m_Resizer;
	CEdit m_txtDescr, m_txtCodice, m_txtBarcode, m_txtCerca;
	CButton m_btnCerca;
	CStatic m_groupbox;
};