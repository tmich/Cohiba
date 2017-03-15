#pragma once
#include "Mainfrm.h"

class CFrameApp : public CWinApp
{
public:
	CFrameApp();
	virtual ~CFrameApp();
	virtual BOOL InitInstance();
	CMainFrame& GetMainFrame() { return m_Frame; }
private:
	CMainFrame m_Frame;
};


// a useful function that returns a reference to the CFrameApp object
inline CFrameApp& GetFrameApp() { return static_cast<CFrameApp&>(GetApp()); }