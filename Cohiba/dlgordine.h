#pragma once
#include "gridvociordine.h"
#include "ordine.h"

class CColorEdit : public CEdit
{
protected:
	virtual BOOL OnEraseBkgnd(CDC& dc);
	virtual LRESULT OnMessageReflect(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

class OrdineDialog : public CDialog
{
public:
	OrdineDialog();
	virtual ~OrdineDialog();
private:
	void AggiornaTotali();
	void ModificaVoce(VoceOrdine& voce);
	void OnAggiungiVoce();
	void OnEliminaVoce();
	virtual void OnCercaArticolo();
	void OnCodiceArticolo();
	void OnBarcode();
	void OnQtaConfezioni();
	void OnGridDblClick();
	void VoceAggiunta();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual BOOL DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	BOOL OnInitDialog() override;
	GridVociOrdine m_Grid;
	CButton m_btnCercaArt, m_btnAddVoce, m_btnDelVoce;
	CStatic m_Title;
	Ordine m_Ordine;
	CEdit m_txtCodArt, m_txtDescArt, m_txtBarcode, m_txtKG, m_txtNumConfezioni;
	CColorEdit m_txtTotKG, m_txtTotLordo, m_txtTotAggio, m_txtTotNetto;
	std::unique_ptr<VoceOrdine> m_VoceDaModificare;
	CFont titleFont;
};