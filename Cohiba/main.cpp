// Cohiba.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <vld.h>
#include "App.h"


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		// Start Win32++
		CFrameApp theApp;

		// Run the application and the message loop
		return theApp.Run();

		::PostQuitMessage(0);
	}

	// catch all unhandled CException types
	catch (const CException &e)
	{
		// Display the exception and quit
		MessageBox(NULL, e.GetText(), A2T(e.what()), MB_ICONERROR);

		return -1;
	}
}
