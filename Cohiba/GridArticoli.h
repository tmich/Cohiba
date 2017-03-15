#pragma once
#include "CZeeGrid.h"

class GridArticoli : public CZeeGrid
{
public:
	GridArticoli();
	virtual ~GridArticoli();
protected:
	void OnInitialUpdate() override;
	unsigned const int N_COLS = 5;
};