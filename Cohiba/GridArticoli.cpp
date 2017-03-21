#include "stdafx.h"
#include "GridArticoli.h"
#include <algorithm>
#include <exception>

const unsigned int GridArticoli::N_COLS = 5;

GridArticoli::GridArticoli()
	: CZeeGrid{ N_COLS }
{
}

GridArticoli::~GridArticoli()
{
}

void GridArticoli::SetArticoli(ListaArticoli & articoli)
{
	m_articoli = articoli;
}

Articolo GridArticoli::GetArticoloAt(int row)
{
	int id = SendMessage(ZGM_GETITEMDATA, row * N_COLS + 1, 0);
	/*auto it = std::find_if(m_articoli.begin(), m_articoli.end(), [id](const Articolo& art) 
	{
		return art.getId() == id;
	});
	
	return *it;
	*/
	return m_articoli[id];
}

int GridArticoli::FilterByNome(const std::wstring & descr)
{
	ListaArticoli matches;

	for (auto& art : m_articoli)
	{
		std::wstring artNome = art.getNome();
		if (artNome.find(descr.c_str()) != std::wstring::npos)
		{
			matches.append(art);
		}
	}

	Update(matches);

	return 0;
}

void GridArticoli::OnInitialUpdate()
{
	CZeeGrid::OnInitialUpdate();
	
	ShowWindow(0);

	GetParent().GetDC().DrawTextW(_T("Caricamento dati in corso..."), -1, GetClientRect(), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	// prealloco le righe
	SendMessage(ZGM_ALLOCATEROWS, m_articoli.size() + 1, 0);

	// mostro il numero di riga
	SendMessage(ZGM_SHOWROWNUMBERS, true, 0);

	// righe alternate
	SendMessage(ZGM_ALTERNATEROWCOLORS, true, 8);
	
	// intestazioni
	int idx = 1;
	SetCellValue(idx++, _T("CODICE"));
	SetCellValue(idx++, _T("NOME"));
	SetCellValue(idx++, _T("CONFEZIONE"));
	SetCellValue(idx++, _T("PREZZO KG"));
	SetCellValue(idx++, _T("BARCODE"));
	
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
	Update(m_articoli);
}

void GridArticoli::Update(ListaArticoli & articoli)
{
	//SendMessage(ZGM_EMPTYGRID, (WPARAM)TRUE, 0);
	EmptyGrid();

	// righe
	for (size_t i = 0; i <articoli.size(); i++)
	{
		int idx = AppendRow();
		Articolo a = articoli[i];
		SendMessage(ZGM_SETITEMDATA, idx, i);
		SetCellValue(idx++, a.getCodice());
		SetCellValue(idx++, a.getNome());
		SetCellValue(idx++, a.getConfezione());
		SetCellValue(idx++, a.getPrezzoKg());
		SetCellValue(idx++, a.getBarcode());
	}

	//auto size all columns
	::SendMessage(m_hWnd, ZGM_AUTOSIZE_ALL_COLUMNS, 0, 0);
}
