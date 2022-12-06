#include "invite.h"
#include "connection.h"
#include<QSqlQuery>
#include<QtDebug>

#include "mainwindow.h"

invite::invite()
{
cin=0;
nom=" ";
prenom=" ";
age=0 ;
adresse=" ";
}
invite::invite(int cin,QString nom,QString prenom,int age,QString adresse)
{

    this->cin=cin ;
    this->age=age;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;

}


int invite::getcin(){return cin;}
QString invite::getnom(){return nom;}
QString invite::getprenom(){return prenom;}
int invite::getage(){return age;}
QString invite::getadresse(){return adresse;}


void invite::setcin(int cin){this->cin=cin;}
void invite::setnom(QString nom){this->nom=nom;}
void invite::setprenom(QString prenom){this->prenom=prenom;}
void invite::setage(int age){this->age=age;}
void invite::setadresse(QString adresse){this->adresse=adresse;}



bool invite::ajouter(){

    QSqlQuery query;
    QString cin_string= QString::number (cin) ;
    QString age_string= QString::number (age) ;
    query.prepare ("INSERT INTO INVITEE (cin, nom, prenom, age, adresse) "
                   "VALUES (:cin, :nom, :prenom, :age, :adresse)");
    query.bindValue(0,cin_string);
    query.bindValue(1,nom);
    query.bindValue(2,prenom);
    query.bindValue(3,age_string);
    query.bindValue(4,adresse);
    return query.exec () ;







}
QSqlQueryModel * invite::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM INVITEE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));

    return model;
}
bool invite::supprimer(int cin)
{
    QSqlQuery query;
      QString res =QString::number(cin);
    query.prepare(" Delete from INVITEE where cin=:cin");
    query.bindValue(":cin", res);

  return  query.exec();
}
bool invite::modifier()
{
QSqlQuery query;
QString res= QString::number(cin);
query.prepare("update INVITEE set cin= :cin, nom= :nom, prenom= :prenom, age= :age, adresse= :adresse where cin = :cin ");
query.bindValue(":cin", res);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom );
query.bindValue(":age",age);
query.bindValue(":adresse",adresse);
return    query.exec();
}
QSqlQueryModel *invite::rechercher(QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM INVITEE WHERE CIN LIKE'%"+rech+"%'");
    return model;


}

QSqlQueryModel *invite::recherchernom(QString nom)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM INVITEE WHERE nom LIKE'%"+nom+"%'");
    return model;


}

QSqlQueryModel * invite::affichertriAZ()
{   QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("SELECT * FROM INVITEE order by prenom Asc");
return model;
}

QSqlQueryModel * invite::affichertriZA()
{   QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("SELECT * FROM INVITEE order by prenom DESC");
return model;
}

QStringList invite::listeadresses(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from INVITEE");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int invite::calcul_adresses(QString adresse,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from INVITEE  WHERE "+val+"=:adresse");
     query.bindValue(":adresse", adresse );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}

