#pragma once
#include <memory>
#include "View.h"

class CMainFrame : public CFrame
{
public:
	CMainFrame();
	virtual ~CMainFrame();

	BOOL			OnFileExit();
	BOOL			OnFileOpen();
	BOOL			OnFilePrint();
	BOOL			OnFileSave();

protected:
	virtual BOOL	OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual int		OnCreate(CREATESTRUCT& cs) override;
	virtual void	OnInitialUpdate() override;
	virtual LRESULT OnNotify(WPARAM wParam, LPARAM lParam) override;
	virtual void	PreCreate(CREATESTRUCT& cs) override;
	virtual void	SetupToolBar() override;
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual BOOL	LoadRegistrySettings(LPCTSTR szKeyName) override;
	virtual BOOL	SaveRegistrySettings() override;
	virtual void	OnClose() override;
	
	virtual BOOL	OnArticoli();
	virtual BOOL	OnCaricoMagazzino();
	virtual BOOL	OnNuovoOrdine();

private:
	CString m_Title, m_strKeyName;
	std::unique_ptr<CView> m_View;
};