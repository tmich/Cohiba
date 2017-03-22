#pragma once
#include "gridvociordine.h"
#include "ordine.h"

class OrdineDialog : public CDialog
{
public:
	OrdineDialog();
	virtual ~OrdineDialog();
private:
	virtual void OnCercaArticolo();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	BOOL OnInitDialog() override;
	GridVociOrdine m_Grid;
	CButton m_btnCercaArt;
	CStatic m_Title;
	Ordine m_Ordine;
};