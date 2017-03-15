#pragma once

class CView : public CWnd
{
public:
	CView();
	virtual ~CView() {}


protected:
	virtual void OnDraw(CDC& dc);
	virtual void OnInitialUpdate();
	virtual void PreCreate(CREATESTRUCT& cs);
	virtual void PreRegisterClass(WNDCLASS& wc);
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};