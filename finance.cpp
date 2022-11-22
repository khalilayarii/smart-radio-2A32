#include "finance.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include<QMessageBox>

Finance::Finance()
{
    id=0; operations="";
    dates=0;
}
Finance::Finance(int id, int dates, QString operations)
{this->id=id;
    this->dates=dates;
    this->operations=operations;
}

int Finance::getid(){return id;}
int Finance::getdates(){return dates;}
QString Finance::getoperations(){return operations;}


void Finance::setid(int id ){this->id=id;}
void Finance::setdates(int date){this->dates=dates;}
void Finance::setoperations(QString operations){this->operations=operations;}

bool Finance::ajouter()


{
    QSqlQuery query;
        QString res= QString::number (id) ;
        query.prepare ("INSERT INTO FINANCE (ID, OPERATIONS, DATES) "
                       "VALUES (:id,:operations,:dates)");
        query.bindValue(":id",res);
        query.bindValue(":operations",operations);
        query.bindValue(":dates",dates);

        return query.exec () ;


}
QSqlQueryModel * Finance::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM Finance");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("operations"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("dates"));


    return model;
}




bool Finance::supprimer(int id)
{
    QSqlQuery query;
      QString res =QString::number(id);
    query.prepare(" Delete from FINANCE where id=:id");
    query.bindValue(":id", res);

  return  query.exec();
}


bool Finance::modifier()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("update FINANCE set id= :id, dates= :dates, operations= :operations where id = :id ");
query.bindValue(":id", res);
query.bindValue(":dates",dates);
query.bindValue(":operations",operations );
return    query.exec();
}

QSqlQueryModel *Finance::rechercher(QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM FINANCE WHERE ID LIKE'%"+rech+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("dates"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("operations"));
    return model;


}





QSqlQueryModel *Finance::trie_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM FINANCE ORDER BY id ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("dates"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("operations"));

return model;
}
QStringList Finance::listeadresses(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from FINANCE");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int     Finance::calcul_adresses(QString adresse,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from FINANCE  WHERE "+val+"=:adresse");
     query.bindValue(":adresse", adresse );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}
