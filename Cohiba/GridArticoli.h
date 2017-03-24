#pragma once
#include "CZeeGrid.h"
#include "articolo.h"

class GridArticoli : public CZeeGrid
{
public:
	GridArticoli();
	virtual ~GridArticoli();
	
	void SetArticoli(ListaArticoli& articoli);
	Articolo& GetArticoloAt(int rowIndex);
	void Update();
protected:
	const int MAX = 100;
	void OnInitialUpdate() override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	
	ListaArticoli m_articoli;
};