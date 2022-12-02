#include "personels.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include<QMessageBox>

personels::personels()
{
    cin=0; nom="";
    prenom="";
}
personels::personels(int cin, QString nom , QString prenom, QString role,int etat)
{this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->role=role;
    this->etat=etat;


}

int personels::getcin(){return cin;}
QString personels::getnom(){return nom;}
QString personels::getprenom(){return prenom;}


void personels::setcin(int cin ){this->cin=cin;}
void personels::setnom(QString nom){this->nom=nom;}
void personels::setprenom(QString prenom){this->prenom=prenom;}

bool personels::ajouter()


{
    QSqlQuery query;
        QString res= QString::number (cin) ;
        query.prepare ("INSERT INTO PERSONELS (CIN, NOM, PRENOM,role,etat_conge) "
                       "VALUES (:cin,:nom,:prenom,:role,0)");
        query.bindValue(":cin",res);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":role",role);

        return query.exec () ;


}
QSqlQueryModel * personels::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM personels");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("role"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));



    return model;
}




bool personels::supprimer(int cin)
{
    QSqlQuery query;
      QString res =QString::number(cin);
    query.prepare(" Delete from personels where cin=:cin");
    query.bindValue(":cin", res);

  return  query.exec();
}


bool personels::modifier()
{
QSqlQuery query;
QString res= QString::number(cin);
query.prepare("update personels set cin= :cin, nom= :nom, prenom= :prenom, role=:role where cin = :cin");
query.bindValue(":cin", res);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom );
query.bindValue(":role",role);

return    query.exec();
}


QSqlQueryModel *personels::trie_cin()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM personels ORDER BY cin ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("role"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));


return model;
}
QStringList personels::listeadresses(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from personels");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int personels::calcul_adresses(QString adresse,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from personels  WHERE "+val+"=:adresse");
     query.bindValue(":adresse", adresse );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}

QSqlQueryModel *personels::rechercher(QString cin)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM PERSONELS WHERE CIN LIKE'%"+cin+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));

  return model;
}


