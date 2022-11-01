#include "personels.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include<QObject>
#include<QTableView>
#include <QSqlTableModel>
Personels::Personels()
{
 CIN= 0;
 numero= 0;
 nom="";
 prenom="";
 adresse="";
}
Personels::Personels(int CIN,QString adresse,QString nom,QString prenom,int numero)
{
    this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
     this->numero=numero;
}
int Personels::getCIN(){return CIN;}
int Personels::getnumero(){return numero;}
QString Personels::getnom(){return nom;}
QString Personels::getprenom(){return prenom;}
QString Personels::getadresse(){return adresse;}

void Personels::setCIN(int CIN){this->CIN=CIN;}
void Personels::setnom(QString nom){this->nom=nom;}
void Personels::setprenom(QString prenom){this->prenom=prenom;}
void Personels::setadresse(QString adresse){this->adresse=adresse;}
void Personels::setnumero(int numero){this->numero=numero;}

bool Personels::ajouter()
{ //bool test=true;

    QString CIN_strings = QString::number(CIN);
    QString numero_strings = QString::number(numero);

       QSqlQuery query;
          query.prepare("INSERT INTO PERSONENELS (CIN, nom, prenom,adresse,numero) ""VALUES (:CIN, :nom, :prenom, :adresse ,:numero)");
          query.bindValue(CIN, CIN_strings);
          query.bindValue(nom, nom);
          query.bindValue(prenom, prenom);
          query.bindValue(adresse, adresse);
          query.bindValue(numero, numero_strings);

         return  query.exec();

   //return  test;

}
bool Personels::supprimer(int CIN)
{

    QSqlQuery query;
       query.prepare("Delete from personels where CIN=:CIN" );

       query.bindValue(0,'CIN_');


      return  query.exec();





}
QSqlQueryModel* Personels::afficher()
{


    QSqlQueryModel* model= new QSqlQueryModel();
          model->setQuery("SELECT * FROM Personels");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));


    return model;
   }



