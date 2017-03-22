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
};