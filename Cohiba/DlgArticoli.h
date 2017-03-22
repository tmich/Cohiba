#pragma once
#include "GridArticoli.h"
#include <memory>

class DlgArticoli : public CDialog
{
public:
	DlgArticoli();
	virtual ~DlgArticoli();
protected:
	BOOL OnInitDialog() override;
	INT_PTR DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual void OnClose() override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual void OnRowSelected();
	virtual void OnCellSelected();
	virtual void UpdateArticolo();
	virtual void OnCercaPerNome();
	virtual void OnSalvaArticolo();
private:
	GridArticoli m_Grid;
	ListaArticoli m_articoli;
	CResizer m_Resizer;
	CEdit m_txtDescr, m_txtCodice, m_txtBarcode, m_txtCerca, m_txtPrezzoKg, m_txtCategoria, m_txtConfezione;
	CButton m_btnCerca, m_btnSalva;
	CStatic m_groupbox;
	std::unique_ptr<Articolo> m_artmod;
};