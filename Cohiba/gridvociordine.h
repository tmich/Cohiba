#pragma once
#include "CZeeGrid.h"
#include "ordine.h"

class GridVociOrdine : public CZeeGrid
{
public:
	GridVociOrdine();
	virtual ~GridVociOrdine();
	void OnInitialUpdate() override;
	void SetOrdine(const Ordine& ordine);
	bool HasVoceAt(size_t rowIndex);
	VoceOrdine GetVoceAt(size_t rowIndex);
	void Update();
protected:
	void FormatCell(int cellIndex, int bgColor, int fgColor = 0, int font = 2) const;
	Ordine m_ordine;
};