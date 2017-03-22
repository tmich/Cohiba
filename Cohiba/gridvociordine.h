#pragma once
#include "CZeeGrid.h"
#include "ordine.h"

class GridVociOrdine : public CZeeGrid
{
public:
	GridVociOrdine();
	virtual ~GridVociOrdine();
	void OnInitialUpdate() override;
	void SetVoci(ListaVociOrdine voci);
	void Update();
protected:
	ListaVociOrdine m_voci;
};