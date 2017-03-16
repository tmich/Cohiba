#include "stdafx.h"
#include "dbconn.h"
#include "dbsettings.h"
#include <mariadb++\exceptions.hpp>

MyConnectionProvider::MyConnectionProvider()
{
	// leggo le impostazioni di connessione dal registro di sistema
	try
	{
		DbSettings dbsett;
		if (!dbsett.Exists())
			dbsett.Create();

		if (dbsett.LoadFromRegistry())
		{
			wc_to_mb srv{ dbsett.GetServer().c_str() };
			wc_to_mb usr{ dbsett.GetUsername().c_str() };
			wc_to_mb pwd{ dbsett.GetPassword().c_str() };
			wc_to_mb db{ dbsett.GetDbname().c_str() };

			m_Server = srv.asStdString();
			m_Username = usr.asStdString();
			m_Password = pwd.asStdString();
			m_Dbname = db.asStdString();
		}
	}
	catch (const std::exception&)
	{
		throw;
	}

	mariadb::account_ref acc{ mariadb::account::create(m_Server.c_str(),m_Username.c_str(),m_Password.c_str(),m_Dbname.c_str()) };
	cnn = mariadb::connection::create(acc);
}

MyConnectionProvider::MyConnectionProvider(std::string server, std::string username, std::string password, std::string dbname)
	: m_Server{ server }, m_Username{ username }, m_Password{ password }, m_Dbname{ dbname }
{
	mariadb::account_ref acc{ mariadb::account::create(m_Server.c_str(),m_Username.c_str(),m_Password.c_str(),m_Dbname.c_str()) };
	cnn = mariadb::connection::create(acc);
}

MyConnectionProvider::~MyConnectionProvider()
{
	if (cnn != nullptr)
	{
		if (cnn->connected())
			cnn->disconnect();
	}
}

mariadb::connection_ref MyConnectionProvider::connect()
{
	if (cnn == nullptr)
		throw mariadb::exception::connection(999, "Impossibile stabilire una connessione");

	cnn->connect();
	return cnn;
}
