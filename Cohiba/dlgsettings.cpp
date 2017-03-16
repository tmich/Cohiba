#include "stdafx.h"
#include "dlgsettings.h"
#include "resource.h"
#include "dbsettings.h"
#include "ipaddress.h"
#include "Dbconn.h"
#include "wc_to_mb.h"
#include <mariadb++\exceptions.hpp>

SettingsDialog::SettingsDialog()
	: CDialog{ IDD_SETTINGS }
{
}

SettingsDialog::~SettingsDialog()
{
}

BOOL SettingsDialog::OnInitDialog()
{
	//m_txtServer, m_txtUsername, m_txtPassword, m_txtDbname;

	AttachItem(IDC_DBADDRESS, m_txtServer);
	AttachItem(IDC_DBUSERNAME, m_txtUsername);
	AttachItem(IDC_DBPASSWORD, m_txtPassword);

	DbSettings dbsett;
	if (dbsett.Exists())
	{
		dbsett.LoadFromRegistry();
		IpAddress ip{ dbsett.GetServer().c_str() };
		m_txtServer.SetWindowTextW(ip.str().c_str());
		m_txtUsername.SetWindowTextW(dbsett.GetUsername().c_str());
		m_txtPassword.SetWindowTextW(dbsett.GetPassword().c_str());
	}

	return 0;
}

void SettingsDialog::Error(CString message) const
{
	this->MessageBox(message.c_str(), _T("Errore"), MB_ICONERROR | MB_OK);
}

void SettingsDialog::OnOK()
{
	DbSettings dbsett;
	if (dbsett.Exists())
		dbsett.LoadFromRegistry();

	CString srv = m_txtServer.GetWindowTextW();
	CString usr = m_txtUsername.GetWindowTextW();
	CString pwd = m_txtPassword.GetWindowTextW();
	CString db = dbsett.GetDbname();

	wc_to_mb w1{ srv.c_str() };
	wc_to_mb w2{ usr.c_str() };
	wc_to_mb w3{ pwd.c_str() };
	wc_to_mb w4{ db.c_str() };

	try
	{
		MyConnectionProvider provider{ w1.asStdString(), w2.asStdString(), w3.asStdString(), w4.asStdString() };
		auto cnn = provider.connect();

		dbsett.SetServer(srv);
		dbsett.SetUsername(usr);
		dbsett.SetPassword(pwd);
		dbsett.SetDbname(db);
		dbsett.Save();

		CDialog::OnOK();
	}
	catch (const mariadb::exception::connection& cnex)
	{
		this->Error(cnex.what());
	}
}
