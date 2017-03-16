#pragma once

class SettingsDialog : public CDialog
{
public:
	SettingsDialog();
	virtual ~SettingsDialog();
private:
	virtual BOOL OnInitDialog() override;
	virtual void OnOK() override;
	virtual void Error(CString message) const;

	CEdit m_txtServer, m_txtUsername, m_txtPassword, m_txtDbname;
};