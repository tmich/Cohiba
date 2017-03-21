#pragma once
#include "CZeeGrid.h"

class GridOrdine : public CZeeGrid
{
public:
	GridOrdine();
	virtual ~GridOrdine();
protected:
	static const size_t N_COLS;
};