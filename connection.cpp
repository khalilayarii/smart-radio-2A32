#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
db=QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("99191060dhia");//inserer mot de passe de cet utilisateur

if (db.open())
    return true;
        return false;
}
void Connection::closeconnect()
{db.close();}
