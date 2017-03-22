#pragma once
#include <memory>

class CMainFrame : public CFrame
{
public:
	CMainFrame();
	virtual ~CMainFrame();

	BOOL			OnFileExit();
	BOOL			OnFileOpen();
	BOOL			OnFilePrint();
	BOOL			OnFileSave();
	virtual void	Error(CString message) const;

protected:
	virtual BOOL	OnCommand(WPARAM wParam, LPARAM lParam);
	virtual int		OnCreate(CREATESTRUCT& cs);
	virtual void	OnInitialUpdate();
	virtual LRESULT OnNotify(WPARAM wParam, LPARAM lParam);
	virtual void	PreCreate(CREATESTRUCT& cs);
	virtual void	SetupToolBar();
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL	LoadRegistrySettings(LPCTSTR szKeyName) override;
	virtual BOOL	SaveRegistrySettings() override;
	
	virtual BOOL	OnArticoli();
	virtual BOOL	OnCaricoMagazzino();
	virtual BOOL	OnNuovoOrdine();

private:
	//CView m_View;
	CString m_Title, m_strKeyName;
	//std::unique_ptr<OrdineDialog> odlg;
	std::unique_ptr<CWnd> m_View;
};