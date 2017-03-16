#pragma once

class DbSettings
{
public:
	DbSettings(CString keyName= _T("Software\\GestionaleM2\\Cohiba\\DB Settings"));
	virtual ~DbSettings();
	
	bool LoadFromRegistry();
	bool Exists();
	bool Create();
	bool Save();

	void SetServer(CString server);
	void SetUsername(CString username);
	void SetPassword(CString password);
	void SetDbname(CString dbname);

	CString GetServer() const { return m_Server; }
	CString GetUsername() const { return m_Username; }
	CString GetPassword() const { return m_Password; }
	CString GetDbname() const { return m_Dbname; }
protected:
	CString m_Server, m_Username, m_Password, m_Dbname, m_strKeyName;
};