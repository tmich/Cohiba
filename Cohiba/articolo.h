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
	
	double getPrezzoKg() const { return m_prezzo_kg; }
	void setPrezzoKg(double prezzo_kg) { m_prezzo_kg = prezzo_kg; }
	
	std::wstring getConfezione() const { return m_confezione; }
	void setConfezione(std::wstring confezione) { m_confezione = confezione; }
protected:
	int m_id;
	std::wstring m_nome;
	double m_prezzo_kg;
	std::wstring m_confezione;
};