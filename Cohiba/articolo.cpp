#include "stdafx.h"
#include "articolo.h"

Articolo::Articolo()
{
}

Articolo::~Articolo()
{
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

const Articolo & ListaArticoli::operator[](int i) const
{
	return m_vect[i];
}

void ListaArticoli::empty()
{
	m_vect.erase(m_vect.begin(), m_vect.end());
	m_vect.clear();
}
