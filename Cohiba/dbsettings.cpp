#include "stdafx.h"
#include "dbsettings.h"

DbSettings::DbSettings(CString keyName)
	: m_strKeyName{ keyName }
{
}

DbSettings::~DbSettings()
{
}

bool DbSettings::LoadFromRegistry()
{
	TCHAR szServer[201] = { 0 };
	TCHAR szNome[201] = { 0 };
	TCHAR szUsername[201] = { 0 };
	TCHAR szPswd[201] = { 0 };
	ULONG usz = 200;
	CRegKey Key;

	//auto err = Key.Open(HKEY_CURRENT_USER, m_strKeyName, KEY_READ);
	
	if (ERROR_SUCCESS == Key.Open(HKEY_CURRENT_USER, m_strKeyName, KEY_READ))
	{
		// se esiste la chiave, leggo le informazioni
		try
		{
			if (ERROR_SUCCESS != Key.QueryStringValue(_T("Server"), szServer, &usz))
				throw CWinException(_T("QueryStringValue Failed"));
			m_Server.Assign(szServer, usz);

			if (ERROR_SUCCESS != Key.QueryStringValue(_T("Nome"), szNome, &usz))
				throw CWinException(_T("QueryStringValue Failed"));
			m_Dbname.Assign(szNome, usz);

			if (ERROR_SUCCESS != Key.QueryStringValue(_T("Username"), szUsername, &usz))
				throw CWinException(_T("QueryStringValue Failed"));
			m_Username.Assign(szUsername, usz);

			if (ERROR_SUCCESS != Key.QueryStringValue(_T("Password"), szPswd, &usz))
				throw CWinException(_T("QueryStringValue Failed"));
			m_Password.Assign(szPswd, usz);

			return true;
		}
		catch (const CWinException& winexc)
		{
			TRACE(winexc.what());
			throw;
		}
	}
	return false;
}

bool DbSettings::Exists()
{
	CRegKey Key;
	//m_strKeyName = _T("Software\\Emme\\Cohiba\\DB Settings");
	return (ERROR_SUCCESS == Key.Open(HKEY_CURRENT_USER, m_strKeyName, KEY_READ));
}

bool DbSettings::Create()
{
	try
	{
		CRegKey Key;

		// Creo la chiave...
		LONG lRet = Key.Create(HKEY_CURRENT_USER, m_strKeyName);
		if (ERROR_SUCCESS != lRet)
			throw CWinException(_T("RegCreateKeyEx failed"));

		// ...la apro...
		if (ERROR_SUCCESS != Key.Open(HKEY_CURRENT_USER, m_strKeyName))
			throw CWinException(_T("RegOpenKeyEx failed"));

		// ... e ci scrivo i valori di default
		if (ERROR_SUCCESS != Key.SetStringValue(_T("Server"), _T("127.0.0.1")))
			throw CWinException(_T("RegSetValueEx failed"));
		if (ERROR_SUCCESS != Key.SetStringValue(_T("Nome"), _T("tabacchi")))
			throw CWinException(_T("RegSetValueEx failed"));
		if (ERROR_SUCCESS != Key.SetStringValue(_T("Username"), _T("pippo")))
			throw CWinException(_T("RegSetValueEx failed"));
		if (ERROR_SUCCESS != Key.SetStringValue(_T("Password"), _T("pluto")))
			throw CWinException(_T("RegSetValueEx failed"));

		if (ERROR_SUCCESS != Key.Create(HKEY_CURRENT_USER, m_strKeyName))
			throw CWinException(_T("RegCreateKeyEx failed"));

		return true;
	}
	catch (const CWinException& winexc)
	{
		TRACE(winexc.what());
		throw;
	}

	return false;
}

bool DbSettings::Save()
{
	try
	{
		CRegKey Key;
		
		if (ERROR_SUCCESS != Key.Open(HKEY_CURRENT_USER, m_strKeyName))
			throw CWinException(_T("RegOpenKeyEx failed"));
		
		if (ERROR_SUCCESS != Key.SetStringValue(_T("Server"), m_Server))
			throw CWinException(_T("RegSetValueEx failed"));
		if (ERROR_SUCCESS != Key.SetStringValue(_T("Nome"), m_Dbname))
			throw CWinException(_T("RegSetValueEx failed"));
		if (ERROR_SUCCESS != Key.SetStringValue(_T("Username"), m_Username))
			throw CWinException(_T("RegSetValueEx failed"));
		if (ERROR_SUCCESS != Key.SetStringValue(_T("Password"), m_Password))
			throw CWinException(_T("RegSetValueEx failed"));
	}
	catch (const std::exception&)
	{

	}
	return false;
}

void DbSettings::SetServer(CString server)
{
	m_Server = server;
}

void DbSettings::SetUsername(CString username)
{
	m_Username = username;
}

void DbSettings::SetPassword(CString password)
{
	m_Password = password;
}

void DbSettings::SetDbname(CString dbname)
{
	m_Dbname = dbname;
}
