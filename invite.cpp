#include "invite.h"
#include<QSqlQuery>
#include<QtDebug>
invite::invite()
{
cin=0;  age=0 ; nom=" "; prenom=" "; adress=" ";
}

invite::invite(int cin,QString nom,QString prenom,int age,QString adress)
{this->cin=cin ;
    this->age=age;
    this->nom=nom;
    this->prenom=prenom;
    this->adress=adress;}


int invite::getcin(){return cin;}
int invite::getage(){return age;}
QString invite::getnom(){return nom;}
QString invite::getprenom(){return prenom;}
QString invite::getadress(){return adress;}
void invite::setcin(int cin){this->cin=cin;}
void invite::setage(int age){this->age=age;}
void invite::setnom(QString nom){this->nom=nom;}
void invite::setprenom(QString prenom){this->prenom=prenom;}
void invite::setadress(QString adress){this->adress=adress;}
bool invite::ajouter()
{
    QSqlQuery query;
    QString cin_string=QString::number(cin);
    QString age_string=QString::number(age);
    query.prepare("INSERT INTO INVITE(cin, nom, prenom, age, adress) "
                  "VALUES (:cin, :nom, :prenom,:age,:adress)");
    query.bindValue(":cin", cin_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":age", age_string);
    query.bindValue(":adress", adress);
    return query.exec();

}
