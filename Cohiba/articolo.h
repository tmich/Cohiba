#pragma once

enum UnitaMisura
{
	GRAMMI,
	PEZZI
};

class Articolo
{
	Articolo();
public:
	Articolo(int id, int codice, std::wstring nome, double prezzoKg, double prezzoConfezione, std::wstring confezione,
		std::string unitaMisura, double qtaPerConfezione, int categoria, std::wstring barcode);
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

	std::wstring getCategoria() const;
	void setCategoria(int categoria) { m_cat = categoria; }

	double getPezziPerConfezione() const { return m_qta_conf; }
	int getPezziPerKg() const;
	double getKg(double pezzi) const;

	UnitaMisura getUnitaMisura() const;

	bool operator==(const Articolo&);
protected:
	int m_id;
	std::wstring m_nome;
	int m_codice;
	std::string m_unita_misura;
	double m_prezzo_kg, m_prezzo_conf, m_qta_conf;
	std::wstring m_confezione;
	std::wstring m_barcode;
	int m_cat;
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
	Articolo& operator [] (int i);
	void empty();
protected:
	std::vector<Articolo> m_vect;
};

class RicercaArticoli
{
public:
	RicercaArticoli(const ListaArticoli&);
	~RicercaArticoli();

	ListaArticoli perNome(const std::wstring& nome);
	ListaArticoli perCodice(const int codice);
	ListaArticoli perBarcode(const std::wstring& barcode);
protected:
	ListaArticoli m_Lista;
};

//class ConvertitoreUnita
//{
//public:
//	ConvertitoreUnita(const Articolo& art);
//	~ConvertitoreUnita();
//};