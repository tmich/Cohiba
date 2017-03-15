#include "stdafx.h"
#include "dbconn.h"

MyConnection::MyConnection()
{
	mariadb::account_ref acc{ mariadb::account::create("192.168.56.101","scott","tiger","tabacchi") };
	cnn = mariadb::connection::create(acc);
}

MyConnection::~MyConnection()
{
	cnn->disconnect();
}

mariadb::connection_ref MyConnection::connect()
{
	cnn->connect();
	return cnn;
}
