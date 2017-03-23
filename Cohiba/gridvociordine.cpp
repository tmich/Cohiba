#include "stdafx.h"
#include "gridvociordine.h"

GridVociOrdine::GridVociOrdine()
	:CZeeGrid{ 6 }
{
}

void GridVociOrdine::OnInitialUpdate()
{
	// colonne
	SendMessage(ZGM_DIMGRID, m_cols, 0);

	// prealloco le righe
	SendMessage(ZGM_ALLOCATEROWS, m_voci.size(), 0);

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
	SetCellValue(idx++, _T("CONF"));
	SetCellValue(idx++, _T("PREZZO KG"));
	SetCellValue(idx++, _T("KG"));
	SetCellValue(idx++, _T("TOTALE"));

	// larghezza colonne
	SendMessage(ZGM_SETCOLWIDTH, 1, 80);
	SendMessage(ZGM_SETCOLWIDTH, 2, 300);
	SendMessage(ZGM_SETCOLWIDTH, 3, 60);
	SendMessage(ZGM_SETCOLWIDTH, 4, 80);
	SendMessage(ZGM_SETCOLWIDTH, 5, 100);
	SendMessage(ZGM_SETCOLWIDTH, 6, 100);

	// dati
	Update();
}

void GridVociOrdine::SetVoci(ListaVociOrdine voci)
{
	m_voci = voci;
}

bool GridVociOrdine::HasVoceAt(size_t rowIndex)
{
	return m_voci.size() >= rowIndex;
}

VoceOrdine GridVociOrdine::GetVoceAt(size_t rowIndex)
{
	int index = SendMessage(ZGM_GETITEMDATA, rowIndex * m_cols + 1, 0);
	return m_voci[index];
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
		SendMessage(ZGM_SETCELLNUMPRECISION, idx, 0);	// NUM CONFEZIONI
		SetCellValue(idx++, vo.getNumConfezioni());
		SetCellValue(idx++, vo.getPrezzoUnitKg());
		SendMessage(ZGM_SETCELLBCOLOR, idx, 3);
		SetCellValue(idx++, vo.getQta());
		SetCellValue(idx++, vo.getPrezzoTotKg());
	}

	SendMessage(ZGM_SETTOPROW, top, 0);
}
