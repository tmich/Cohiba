#include "stdafx.h"
#include "gridvociordine.h"

GridVociOrdine::GridVociOrdine()
	:CZeeGrid{ 7 }
{
}

void GridVociOrdine::OnInitialUpdate()
{
	// colonne
	SendMessage(ZGM_DIMGRID, m_cols, 0);

	// prealloco le righe
	SendMessage(ZGM_ALLOCATEROWS, m_voci.size() + 1, 0);

	// nascondo il numero di riga
	SendMessage(ZGM_SHOWROWNUMBERS, false, 0);

	// larghezza colonne
	SendMessage(ZGM_SETCOLWIDTH, 2, 200);
	SendMessage(ZGM_SETCOLWIDTH, 3, 80);
	SendMessage(ZGM_SETCOLWIDTH, 4, 300);
	SendMessage(ZGM_SETCOLWIDTH, 5, 80);

	// righe alternate
	SendMessage(ZGM_ALTERNATEROWCOLORS, true, 8);
	SendMessage(ZGM_ENABLETBMERGEROWS, false, 0);
	SendMessage(ZGM_ENABLETBROWNUMBERS, false, 0);
	SendMessage(ZGM_ENABLETBSEARCH, false, 0);
	SendMessage(ZGM_ENABLETBEDIT, false, 0);
	SendMessage(ZGM_SHOWTITLE, false, 0);

	// intestazioni
	int idx = 1;
	SetCellValue(idx++, _T("CODICE"));
	SetCellValue(idx++, _T("NOME"));
	SetCellValue(idx++, _T("CONFEZIONI"));
	SetCellValue(idx++, _T("QTA"));
	SetCellValue(idx++, _T("KG"));
	SetCellValue(idx++, _T("PREZZO UNIT"));
	SetCellValue(idx++, _T("TOTALE"));

	// dati
	Update();
}

void GridVociOrdine::SetVoci(ListaVociOrdine voci)
{
	m_voci = voci;
}

GridVociOrdine::~GridVociOrdine()
{
}

void GridVociOrdine::Update()
{
	int top = SendMessage(ZGM_GETTOPROW, 0, 0);

	EmptyGrid();

	int idx = AppendRow();

	// righe
	for (size_t i = 0; i < m_voci.size(); i++)
	{
		VoceOrdine vo = m_voci[i];
		SendMessage(ZGM_SETITEMDATA, idx, i);
		SetCellValue(idx++, vo.getCodice());
		SetCellValue(idx++, vo.getNome());
		SetCellValue(idx++, 1);
		SetCellValue(idx++, vo.getQta());
		SetCellValue(idx++, 1);
		SetCellValue(idx++, vo.getPrezzoUnitKg());
		SetCellValue(idx++, vo.getPrezzoTotKg());
	}

	SendMessage(ZGM_AUTOSIZECOLUMN, 2, 0);	// nome
	SendMessage(ZGM_SETTOPROW, top, 0);
}
