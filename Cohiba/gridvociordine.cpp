#include "stdafx.h"
#include "gridvociordine.h"

GridVociOrdine::GridVociOrdine()
	:CZeeGrid{ 6 }
{
}

void GridVociOrdine::OnInitialUpdate()
{
	// font
	SendMessage(ZGM_SETDEFAULTFONT, 4, 0);

	// colonne
	SendMessage(ZGM_DIMGRID, m_cols, 0);

	// prealloco le righe
	SendMessage(ZGM_ALLOCATEROWS, m_ordine.getVoci().size(), 0);

	// nascondo il numero di riga
	SendMessage(ZGM_SHOWROWNUMBERS, false, 0);

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
	SetCellValue(idx++, _T("N°"));
	SetCellValue(idx++, _T("COSTO UN"));
	SetCellValue(idx++, _T("KG"));
	SetCellValue(idx++, _T("TOT"));

	// larghezza colonne
	SendMessage(ZGM_SETCOLWIDTH, 1, 80);
	SendMessage(ZGM_SETCOLWIDTH, 2, 670);
	SendMessage(ZGM_SETCOLWIDTH, 3, 65);
	SendMessage(ZGM_SETCOLWIDTH, 4, 100);
	SendMessage(ZGM_SETCOLWIDTH, 5, 120);
	SendMessage(ZGM_SETCOLWIDTH, 6, 100);

	 // colori personalizzati
	SendMessage(ZGM_SETCOLOR, 20, (LPARAM)((DWORD)(RGB(220, 220, 220))));

	// dati
	Update();
}

void GridVociOrdine::SetOrdine(const Ordine& ordine)
{
	m_ordine = ordine;
}

bool GridVociOrdine::HasVoceAt(size_t rowIndex)
{
	return m_ordine.getVoci().size() >= rowIndex;
}

VoceOrdine GridVociOrdine::GetVoceAt(size_t rowIndex)
{
	int index = SendMessage(ZGM_GETITEMDATA, rowIndex * m_cols + 1, 0);
	return m_ordine.getVoci()[index];
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
	for (size_t i = 0; i < m_ordine.getVoci().size(); i++)
	{
		VoceOrdine vo = m_ordine.getVoci()[i];
		SendMessage(ZGM_SETITEMDATA, idx, i);
		SetCellValue(idx++, vo.getCodice());
		SetCellValue(idx++, vo.toString());
		
		// NUM CONFEZIONI
		SendMessage(ZGM_SETCELLNUMPRECISION, idx, 0);
		SetCellValue(idx++, vo.getNumConfezioni());
		
		SetCellValue(idx++, vo.getPrezzoConfezione());
		
		// PESO IN KG (DA ORDINARE)
		//SendMessage(ZGM_SETCELLBCOLOR, idx, 3);
		SendMessage(ZGM_SETCELLNUMPRECISION, idx, 3);	
		SetCellValue(idx++, vo.getPesoKG());	

		SetCellValue(idx++, vo.getPrezzoTotale());
	}

	// Aggiungo righe a buffo
	for (int r = 0; r < 10; r++)
	{
		AppendRow();
	}

	//// Riga Totale	
	//idx = AppendRow();
	//FormatCell(idx, 20); SetCellValue(idx++, "");
	//FormatCell(idx, 20, 0, 5); SetCellValue(idx++, "TOTALI");
	//SendMessage(ZGM_SETCELLJUSTIFY, idx - 1, 7);
	//FormatCell(idx, 20, 0, 5); SetCellValue(idx++, m_ordine.getTotaleConfezioni());	// num_confezioni
	//FormatCell(idx, 20, 0, 5); SetCellValue(idx++, "");
	//SendMessage(ZGM_SETCELLNUMPRECISION, idx, 3); 
	//FormatCell(idx, 20, 0, 5); SetCellValue(idx++, m_ordine.getPesoTotale());	// KG tot
	//FormatCell(idx, 20, 0, 5); SetCellValue(idx++, m_ordine.getPrezzoTotale());		// prezzo tot

	//// Riga Aggio
	//idx = AppendRow();
	//FormatCell(idx, 20); SetCellValue(idx++, "");
	//FormatCell(idx, 20); SetCellValue(idx++, "");
	//FormatCell(idx, 20); SetCellValue(idx++, "");
	//FormatCell(idx, 20); SetCellValue(idx++, "");
	//FormatCell(idx, 20, 0, 5); SetCellValue(idx++, "Aggio");
	//SendMessage(ZGM_SETCELLJUSTIFY, idx - 1, 7);
	//FormatCell(idx, 20, 0, 5); SetCellValue(idx, m_ordine.getAggioTotale());		// Aggio totale

	SendMessage(ZGM_SETTOPROW, top, 0);
}

void GridVociOrdine::FormatCell(int cellIndex, int bgColor, int fgColor, int font) const
{
	SendMessage(ZGM_SETCELLBCOLOR, cellIndex, bgColor);
	SendMessage(ZGM_SETCELLFCOLOR, cellIndex, fgColor);
	SendMessage(ZGM_SETCELLFONT, cellIndex, font);
}
