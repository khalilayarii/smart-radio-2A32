#include "connection.h"
#include <QSqlDatabase>


//TEST Tutorial git





Connection::Connection()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
}

bool Connection::createconnect()
{bool test=false;
db.setDatabaseName("smart-radio");
db.setUserName("khalil");//inserer nom de l'utilisateur
db.setPassword("khalil");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
