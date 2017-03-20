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
private:
	GridArticoli m_Grid;
	CResizer m_Resizer;
	CEdit m_Edit1;
};