#pragma once
#include "Dbconn.h"
#include "articolo.h"

class ArticoloDao
{
public:
	ArticoloDao();
	virtual ~ArticoloDao();

	ListaArticoli all();
	void save(Articolo& articolo);
	Articolo perCodice(int codice);
	Articolo perBarcode(std::wstring barcode);
protected:
	Articolo fromResultset(const mariadb::result_set_ref rs);
	std::string m_Query;
	static ListaArticoli m_CachedListaArticoli;
};