#ifndef CONNECTION_H
#define CONNECTION_H
//tester tuto git
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>
#include <QSqlQueryModel>
#include<QMessageBox>

class connection
{
    QSqlDatabase db;
public:
    connection();
    bool createconnect();
    void closeconnect();

};

#endif // CONNECTION_H
