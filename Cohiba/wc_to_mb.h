#pragma once
#include <string>

namespace stringutils
{
	std::wstring to_upper(std::wstring str);
	double to_double(std::wstring str);
	double to_double(std::string str);
}

class wc_to_mb
{
public:
	wc_to_mb(std::wstring);
	~wc_to_mb();

	std::string asStdString();
protected:
	std::wstring m_wcs;
	char * m_pmb;
};

class mb_to_wc
{
public:
	mb_to_wc(std::string);
	~mb_to_wc();

	std::wstring asStdWstring();
protected:
	std::string m_str;
	wchar_t * m_pws;
};