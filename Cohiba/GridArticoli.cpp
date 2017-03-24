#include "stdafx.h"
#include "GridArticoli.h"
#include <algorithm>
#include <exception>

GridArticoli::GridArticoli()
	: CZeeGrid{ 5 }
{
}

GridArticoli::~GridArticoli()
{
}

void GridArticoli::SetArticoli(ListaArticoli & articoli)
{
	m_articoli = articoli;
}

Articolo& GridArticoli::GetArticoloAt(int row)
{
	int index = SendMessage(ZGM_GETITEMDATA, row * m_cols + 1, 0);

	return m_articoli[index];
}

void GridArticoli::OnInitialUpdate()
{
	// colonne
	SendMessage(ZGM_DIMGRID, m_cols, 0);
	
	ShowWindow(0);
	TRACE("Caricamento dati in corso...");
	GetParent().GetDC().DrawTextW(_T("Caricamento dati in corso..."), -1, GetClientRect(), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	// prealloco le righe
	SendMessage(ZGM_ALLOCATEROWS, m_articoli.size() + 1, 0);

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
	SetCellValue(idx++, _T("CU"));
	SetCellValue(idx++, _T("CONFEZIONE"));
	SetCellValue(idx++, _T("CATEGORIA"));
	
	// dati
	Update();

	ShowWindow(1);
}

BOOL GridArticoli::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return CZeeGrid::OnCommand(wParam, lParam);
}

void GridArticoli::Update()
{
	int top = SendMessage(ZGM_GETTOPROW, 0, 0);

	EmptyGrid();

	int idx = AppendRow();

	// righe
	for (size_t i = 0; i < m_articoli.size(); i++)
	{	
		// massimo...
		if (i == MAX)
			break;

		Articolo a = m_articoli[i];
		SendMessage(ZGM_SETITEMDATA, idx, i);
		SetCellValue(idx++, a.getCodice());
		//SetCellValue(idx++, a.getBarcode());
		SetCellValue(idx++, a.getNome());
		SetCellValue(idx++, a.getPrezzoConfezione());
		SetCellValue(idx++, a.getConfezione());
		SetCellValue(idx++, a.getCategoria());
	}

	SendMessage(ZGM_AUTOSIZECOLUMN, 2, 0);	// nome
	SendMessage(ZGM_SETTOPROW, top, 0);
}
