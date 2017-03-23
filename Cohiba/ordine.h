#pragma once
#include "articolo.h"

class VoceOrdine
{
public:
	//VoceOrdine();
	VoceOrdine(Articolo art, double qta);
	virtual ~VoceOrdine();

	std::wstring getNome() const { return m_articolo.getNome(); }
	int getCodice() const { return m_articolo.getCodice(); }
	double getPrezzoUnitKg() const { return m_articolo.getPrezzoKg(); }
	std::wstring getConfezione() const { return m_articolo.getConfezione(); }
	std::wstring getBarcode() const { return m_articolo.getBarcode(); }
	std::wstring getCategoria() const { return m_articolo.getCategoria(); }
	double getQta() const { return m_qta; }
	void setQta(double qta);
	double getPrezzoTotKg() const;
	double getNumConfezioni() const;

	VoceOrdine operator=(const VoceOrdine&);
	bool operator==(const VoceOrdine&);
protected:
	Articolo m_articolo;
	double m_qta;
};

class ListaVociOrdine
{
public:
	ListaVociOrdine() {};
	ListaVociOrdine(std::vector<VoceOrdine>);
	~ListaVociOrdine() {};

	ListaVociOrdine operator=(const std::vector<VoceOrdine>);
	ListaVociOrdine operator=(const ListaVociOrdine&);

	std::vector<VoceOrdine>::const_iterator begin();
	std::vector<VoceOrdine>::const_iterator end();
	VoceOrdine& operator [] (int i);
	size_t size() const;
protected:
	std::vector<VoceOrdine> m_vect;
};

class Ordine
{
public:
	Ordine();
	virtual ~Ordine() {};
	void aggiungi(const VoceOrdine& voce);
	double getPrezzoTotale() const;
	ListaVociOrdine getVoci() const;
protected:
	std::vector<VoceOrdine> m_voci;
};