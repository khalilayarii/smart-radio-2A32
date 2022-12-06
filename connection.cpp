





#include "connection.h"
//test tutoriel
connection::connection()
{

}

bool connection::createconnect()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("system");//inserer mot de passe de cet utilisateur

return db.open();






    }
