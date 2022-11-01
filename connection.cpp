#include "connection.h"

Connection::Connection(){}


bool Connection::createconnect()
{
 db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("test-bd");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("28695683");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
return true;
}
void Connection::closeconnect(){db.close(); }






