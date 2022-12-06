#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{
 db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("test-bd");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("28695683");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
return true;
}
void connection::closeconnect()
{db.close(); }
