#pragma once
#include "GridArticoli.h"

class DlgArticoli : public CDialog
{
public:
	DlgArticoli();
	virtual ~DlgArticoli();
protected:
	BOOL OnInitDialog() override;
private:
	GridArticoli m_Grid;
};