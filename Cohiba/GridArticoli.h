#pragma once
#include "CZeeGrid.h"
#include "articolo.h"

class GridArticoli : public CZeeGrid
{
public:
	GridArticoli();
	virtual ~GridArticoli();
	
	std::string GetNome(int row);
	Articolo GetArticolo(int row);
protected:
	void OnInitialUpdate() override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	unsigned const int N_COLS = 5;
	int m_RowSelected = -1;
};