#pragma once
#include "gridvociordine.h"
#include "ordine.h"

class OrdineDialog : public CDialog
{
public:
	OrdineDialog();
	virtual ~OrdineDialog();
private:
	void ModificaVoce(VoceOrdine& voce);
	void OnAggiungiVoce();
	virtual void OnCercaArticolo();
	void OnCodiceArticolo();
	void OnQtaConfezioni();
	void OnGridDblClick();
	void VoceAggiunta();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual BOOL DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	BOOL OnInitDialog() override;
	GridVociOrdine m_Grid;
	CButton m_btnCercaArt;
	CStatic m_Title, m_Totale;
	Ordine m_Ordine;
	CEdit m_txtCodArt, m_txtDescArt, m_txtBarcode, m_txtKG, m_txtNumConfezioni;
	CButton m_btnAddVoce;
	std::unique_ptr<VoceOrdine> m_VoceDaModificare;
	CFont titleFont;
};