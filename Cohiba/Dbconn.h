#pragma once
#include <mariadb++\connection.hpp>
#include <mariadb++\result_set.hpp>

class MyConnection
{
public:
	MyConnection();
	virtual ~MyConnection();
	mariadb::connection_ref connect();
protected:
	mariadb::connection_ref cnn;
};