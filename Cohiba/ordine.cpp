#include "stdafx.h"
#include "ordine.h"

//VoceOrdine::VoceOrdine()
//	: m_qta{ 0 }
//{
//}

VoceOrdine::VoceOrdine(Articolo art, int confezioni)
	: m_articolo{ art }, m_confezioni{ confezioni }
{
}

VoceOrdine::~VoceOrdine()
{
}

//void VoceOrdine::setQtaKG(double qta)
//{
//	m_qtaKG = qta;
//}

double VoceOrdine::getPrezzoConfezione() const
{
	return m_articolo.getPrezzoConfezione();
}

double VoceOrdine::getPrezzoTotale() const
{
	//return m_articolo.getPrezzoKg() * getPesoKG();
	return m_articolo.getPrezzoConfezione() * m_confezioni;
}

void VoceOrdine::setNumConfezioni(int num_confezioni)
{
	m_confezioni = num_confezioni;
}

int VoceOrdine::getNumConfezioni() const
{
	return m_confezioni;
}

double VoceOrdine::getPesoKG() const
{
	// per sapere il peso totale, devo moltiplicare il peso singolo dell'articolo per il numero delle confezioni da ordinare
	double peso_un = m_articolo.getPesoUnitario();
	double peso_tot = peso_un * m_confezioni;
	return peso_tot;
}

double VoceOrdine::getAggio() const
{
	return (getPrezzoTotale() / 100) * m_articolo.getPercentualeAggio();
}

std::wstring VoceOrdine::toString() const
{
	return getNome() + _T(" ") + getConfezione();
}

VoceOrdine VoceOrdine::operator=(const VoceOrdine & rhs)
{
	m_articolo = rhs.m_articolo;
	m_confezioni = rhs.m_confezioni;
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

void Ordine::rimuovi(const VoceOrdine & voce)
{
	auto it = std::find(m_voci.begin(), m_voci.end(), voce);
	if (it != m_voci.end())
	{
		m_voci.erase(it, it + 1);
	}
}

double Ordine::getPrezzoTotale() const
{
	double tot = 0.0;
	for (auto const& vo : m_voci)
		tot += vo.getPrezzoTotale();

	return tot;
}

ListaVociOrdine Ordine::getVoci() const
{
	return m_voci;
}

int Ordine::getTotaleConfezioni() const
{
	int tot = 0;
	for (auto const& vo : m_voci)
		tot += vo.getNumConfezioni();

	return tot;
}

double Ordine::getPesoTotale() const
{
	double tot = 0.0;
	for (auto const& vo : m_voci)
		tot += vo.getPesoKG();

	return tot;
}

double Ordine::getAggioTotale() const
{
	double aggio = 0.0;
	for (auto const& vo : m_voci)
		aggio += vo.getAggio();

	return aggio;
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
