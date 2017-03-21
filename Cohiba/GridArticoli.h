#pragma once
#include "CZeeGrid.h"
#include "articolo.h"

class GridArticoli : public CZeeGrid
{
public:
	GridArticoli();
	virtual ~GridArticoli();
	
	void SetArticoli(ListaArticoli& articoli);
	Articolo GetArticoloAt(int rowIndex);
	int FilterByNome(const std::wstring& descr);
protected:
	void OnInitialUpdate() override;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	void Update();
	void Update(ListaArticoli& articoli);

	ListaArticoli m_articoli;
	const unsigned static int N_COLS;
	//int idx = 1;
	int m_RowSelected = -1;
};