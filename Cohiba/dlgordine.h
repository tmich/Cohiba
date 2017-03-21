#pragma once
#include "GridOrdine.h"

class OrdineDialog : public CDialog
{
public:
	OrdineDialog();
	virtual ~OrdineDialog();
private:
	BOOL OnInitDialog() override;
	GridOrdine m_Grid;
};