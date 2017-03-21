#pragma once

class Articolo
{
public:
	Articolo();
	virtual ~Articolo();

	int getId() const { return m_id; }
	void setId(int id) { m_id = id; }
	
	std::wstring getNome() const { return m_nome; }
	void setNome(std::wstring nome) { m_nome = nome; }
	
	int getCodice() const { return m_codice; }
	void setCodice(int codice) { m_codice = codice; }

	double getPrezzoKg() const { return m_prezzo_kg; }
	void setPrezzoKg(double prezzo_kg) { m_prezzo_kg = prezzo_kg; }
	
	std::wstring getConfezione() const { return m_confezione; }
	void setConfezione(std::wstring confezione) { m_confezione = confezione; }

	std::wstring getBarcode() const { return m_barcode; }
	void setBarcode(std::wstring barcode) { m_barcode = barcode; }
protected:
	int m_id;
	std::wstring m_nome;
	int m_codice;
	double m_prezzo_kg;
	std::wstring m_confezione;
	std::wstring m_barcode;
};

class ListaArticoli
{
public:
	ListaArticoli() {}
	ListaArticoli(std::vector<Articolo>);
	virtual ~ListaArticoli() {}

	ListaArticoli operator=(const std::vector<Articolo>);
	ListaArticoli operator=(const ListaArticoli&);

	void append(const Articolo& a);
	std::vector<Articolo>::const_iterator begin();
	std::vector<Articolo>::const_iterator end();
	size_t size() const;
	const Articolo& operator [] (int i) const;
	void empty();
protected:
	std::vector<Articolo> m_vect;
};