#pragma once

class CView : public CDialog
{
public:
	CView();
	CView(UINT nResID);
	virtual ~CView() {}
	virtual bool ConfermaChiusura() const;

protected:
	virtual void OnDraw(CDC& dc) override;
	virtual void OnInitialUpdate() override;
	virtual void PreCreate(CREATESTRUCT& cs) override;
	virtual void PreRegisterClass(WNDCLASS& wc) override;
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual bool IsSaved() const { return m_Saved; }

	bool m_Saved;
};