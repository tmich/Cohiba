#pragma once
#include "articolo.h"

class VoceMagazzino
{
public:
	friend class Magazzino;
	VoceMagazzino(const Articolo&, int qta);
	virtual ~VoceMagazzino() = default;

	void setQta(int qta) { m_Qta = qta; }
	int getQta() const { return m_Qta; }

	int getSoglia() const { return m_Soglia; }
	void setSoglia(int soglia) { m_Soglia = soglia; }
	Articolo getArticolo() const { return m_Articolo; }

	double valore() const;
protected:
	Articolo m_Articolo;
	int m_Id;
	int m_Qta;
	int m_Soglia;
};

class ListaVociMagazzino
{
public:
	ListaVociMagazzino();
	virtual ~ListaVociMagazzino();

	std::vector<VoceMagazzino>::iterator begin();
	std::vector<VoceMagazzino>::iterator end();

	VoceMagazzino& operator[](const Articolo&);
	size_t size() const;
	void push_back(VoceMagazzino&);
protected:
	std::vector<VoceMagazzino> m_vect;
};

class Magazzino
{
public:
	Magazzino();
	virtual ~Magazzino();

	ListaVociMagazzino getVoci() const;

	void carica(const Articolo&, int qta);
	void scarica(const Articolo&, int qta);
protected:
	void dbUpdate(VoceMagazzino&);
	void dbInsert(VoceMagazzino&);
	ListaVociMagazzino m_voci;
};