#include "stdafx.h"
#include "articolo.h"
#include "wc_to_mb.h"

Articolo::Articolo()
	: m_id{ 0 }
{
}

Articolo::~Articolo()
{
}

std::wstring Articolo::getCategoria() const
{
	switch (m_cat)
	{
	case 1:
		return _T("Sigarette");
	case 2:
		return _T("Sigari");
	case 3:
		return _T("Sigaretti");
	case 4:
		return _T("Trinciati per sigarette");
	case 5:
		return _T("Tabacco da fiuto o da mastico");
	case 6:
		return _T("Tabacco da inalazione senza combustione");
	case 7:
		return _T("Trinciati per pipa");
	default:
		return _T("");
	}
}

ListaArticoli::ListaArticoli(std::vector<Articolo> articoli)
	: m_vect{ articoli }
{
}

ListaArticoli ListaArticoli::operator=(const std::vector<Articolo> articoli)
{
	m_vect = articoli;
	return *this;
}

ListaArticoli ListaArticoli::operator=(const ListaArticoli &lista)
{
	m_vect.erase(m_vect.begin(), m_vect.end());
	m_vect.clear();
	m_vect.assign(lista.m_vect.begin(), lista.m_vect.end());
	return *this;
}

void ListaArticoli::append(const Articolo & a)
{
	m_vect.push_back(a);
}

std::vector<Articolo>::const_iterator ListaArticoli::begin()
{
	return m_vect.begin();
}

std::vector<Articolo>::const_iterator ListaArticoli::end()
{
	return m_vect.end();
}

size_t ListaArticoli::size() const
{
	return m_vect.size();
}

Articolo & ListaArticoli::operator[](int i)
{
	return m_vect[i];
}

void ListaArticoli::empty()
{
	m_vect.erase(m_vect.begin(), m_vect.end());
	m_vect.clear();
}

RicercaArticoli::RicercaArticoli(const ListaArticoli& lst)
	: m_Lista{ lst }
{
}

RicercaArticoli::~RicercaArticoli()
{
}

ListaArticoli RicercaArticoli::perNome(const std::wstring & nome)
{
	ListaArticoli matches;

	for (const auto& art : m_Lista)
	{
		//std::wstring par = stringutils::to_upper(nome);
		std::wstring artNome = stringutils::to_upper(art.getNome());

		if (artNome.find(nome.c_str()) != std::wstring::npos)
		{
			matches.append(art);
		}
	}

	return matches;
}

ListaArticoli RicercaArticoli::perCodice(const int codice)
{
	ListaArticoli matches;

	for (const auto& art : m_Lista)
	{
		if (art.getCodice() == codice)
		{
			matches.append(art);
		}
	}

	return matches;
}

ListaArticoli RicercaArticoli::perBarcode(const std::wstring & barcode)
{
	ListaArticoli matches;

	for (const auto& art : m_Lista)
	{
		std::wstring artBarcode = art.getBarcode();
		if (artBarcode == barcode)
		{
			matches.append(art);
		}
	}

	return matches;
}
