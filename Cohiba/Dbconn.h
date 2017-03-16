#pragma once
#include <mariadb++\connection.hpp>
#include <mariadb++\result_set.hpp>

class MyConnectionProvider
{
public:
	MyConnectionProvider();
	MyConnectionProvider(std::string server, std::string username, std::string password, std::string dbname);
	virtual ~MyConnectionProvider();
	mariadb::connection_ref connect();
protected:
	mariadb::connection_ref cnn;
	std::string m_Server, m_Username, m_Password, m_Dbname;
};