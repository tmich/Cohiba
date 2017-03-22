#pragma once
#include <string>

namespace guiutils
{
	void Error(std::wstring message, HWND parent = 0);
	void Warning(std::wstring message, HWND parent = 0);
	void Notify(std::wstring message, HWND parent = 0);
}