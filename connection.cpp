#include "connection.h"

//Test Tutoriel Git
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("khalil");//inserer nom de l'utilisateur
db.setPassword("khalil");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
