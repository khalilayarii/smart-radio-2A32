#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{

db = QSqlDatabase::addDatabase("QODBC");
 bool test=false;
db.setDatabaseName("mybase");
db.setUserName("roube");//inserer nom de l'utilisateur
db.setPassword("roube");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
 return  test;
}
 void Connection::closeconnection(){db.close();}
