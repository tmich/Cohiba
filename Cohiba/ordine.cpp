#include "stdafx.h"
#include "ordine.h"

//VoceOrdine::VoceOrdine()
//	: m_qta{ 0 }
//{
//}

VoceOrdine::VoceOrdine(Articolo art, double qta)
	: m_articolo{ art }, m_qtaKG{ qta }
{
}

VoceOrdine::~VoceOrdine()
{
}

void VoceOrdine::setQtaKG(double qta)
{
	m_qtaKG = qta;
}

double VoceOrdine::getPrezzoTotKg() const
{
	return m_articolo.getPrezzoKg() * m_qtaKG;
}

double VoceOrdine::getNumConfezioni() const
{
	double pezziTotali = m_qtaKG * m_articolo.getPezziPerKg();
	double confezioni = pezziTotali / m_articolo.getPezziPerConfezione();
	//int num = (int)((m_articolo.getPezziPerKg() * m_qtaKG) / m_articolo.getPezziPerConfezione());
	return confezioni;
}

VoceOrdine VoceOrdine::operator=(const VoceOrdine & rhs)
{
	m_articolo = rhs.m_articolo;
	m_qtaKG = rhs.m_qtaKG;

	return *this;
}

bool VoceOrdine::operator==(const VoceOrdine & rhs)
{
	return m_articolo == rhs.m_articolo;
}

Ordine::Ordine()
{
}

void Ordine::aggiungi(const VoceOrdine & voce)
{
	auto it = std::find(m_voci.begin(), m_voci.end(), voce);

	if (it == m_voci.end())
	{
		m_voci.push_back(voce);
	}
	else
	{
		*it = voce;
	}
}

double Ordine::getPrezzoTotale() const
{
	double tot = 0.0;
	for (auto const& vo : m_voci)
		tot += vo.getPrezzoTotKg();

	return tot;
}

ListaVociOrdine Ordine::getVoci() const
{
	return m_voci;
}

ListaVociOrdine::ListaVociOrdine(std::vector<VoceOrdine> voci)
	: m_vect{ voci }
{
}

ListaVociOrdine ListaVociOrdine::operator=(const std::vector<VoceOrdine> voci)
{
	m_vect = voci;
	return *this;
}

ListaVociOrdine ListaVociOrdine::operator=(const ListaVociOrdine & lista)
{
	m_vect.erase(m_vect.begin(), m_vect.end());
	m_vect.clear();
	m_vect.assign(lista.m_vect.begin(), lista.m_vect.end());
	return *this;
}

std::vector<VoceOrdine>::const_iterator ListaVociOrdine::begin()
{
	return m_vect.begin();
}

std::vector<VoceOrdine>::const_iterator ListaVociOrdine::end()
{
	return m_vect.end();
}

VoceOrdine & ListaVociOrdine::operator[](int i)
{
	return m_vect[i];
}

size_t ListaVociOrdine::size() const
{
	return m_vect.size();
}
