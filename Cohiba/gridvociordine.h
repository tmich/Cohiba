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
	bool HasVoceAt(size_t rowIndex);
	VoceOrdine GetVoceAt(size_t rowIndex);
	void Update();
protected:
	ListaVociOrdine m_voci;
};