#include "programme.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>


programme::programme()
{
 nomA=" ";
 nomE=" ";
 typeE=" ";
 date =" ";
}
programme::programme(QString nomA,QString nomE,QString typeE,QString date)
{this ->nomA=nomA;this ->nomE=nomE;this ->typeE=typeE;this ->date=date;}
QString programme:: getnomE(){return nomE;}
QString programme::getnomA(){return nomA;}
QString programme:: gettypeE(){return typeE;}
QString programme::getedate(){return date;}
void programme::setnomE(QString nomA){this ->nomA=nomA;}
void programme::setnomA(QString nomE){this ->nomE=nomE;}
void programme::settypeE(QString typeE){this ->typeE=typeE;}
void programme::setdate(QString date){this ->date=date;}
bool programme::ajouter()
{bool test=false;
    {
        QSqlQuery query;

    query.prepare("INSERT INTO Piste (nomE,nomA,typeE,date) "
                           "VALUES (:nomE,nomA,typeE,date)");
             query.bindValue(":nomE", nomE);
             query.bindValue(":nomA", nomA);
             query.bindValue(":typeE", typeE);
             query.bindValue(":date", date);

            return query.exec();
             QSqlQueryModel*programme::afficher

    }
}

