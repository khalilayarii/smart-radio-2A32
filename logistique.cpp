#include "logistique.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include<QMessageBox>

Logistique::Logistique()
{
    quantite=0; type=""; reference="" ;
    prix=0; etat="";
}
Logistique::Logistique(int quantite, QString type, QString reference, int prix, QString etat)
{this->quantite=quantite; this->type=type; this->reference=reference; this->prix=prix; this->etat=etat;}
int Logistique:: getquantite() {return quantite;}
QString Logistique::gettype() {return type;}
QString Logistique::getreference(){return reference;}
int Logistique:: getprix() {return prix;}
QString Logistique::getetat() {return etat;}
void Logistique::setquantite (int quantite) {this->quantite=quantite;}
void Logistique::settype (QString type) {this->type=type;}
void Logistique::setreference(QString reference) {this->reference=reference;}
void Logistique::setprix (int prix) {this->prix=prix;}
void Logistique::setetat (QString etat) {this->etat=etat;}
bool Logistique::ajouter()
{
    QSqlQuery query;
    QString quantite_string= QString::number (quantite) ;
    QString prix_string= QString::number (prix) ;
    query.prepare ("INSERT INTO logistique (quantite, type, reference, prix, etat) "
                   "VALUES (:quantite, :type, :reference, :prix, :etat)");
    query.bindValue(0,quantite_string);
    query.bindValue(1,type);
    query.bindValue(2,reference);
    query.bindValue(3,prix_string);
    query.bindValue(4,etat);
    return query.exec () ;

}
QSqlQueryModel * Logistique::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM logistique");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("reference"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("etat"));

    return model;
}




bool Logistique::supprimer(int quantite)
{
    QSqlQuery query;
      QString res =QString::number(quantite);
    query.prepare(" Delete from logistique where quantite=:quantite");
    query.bindValue(":quantite", res);

  return  query.exec();
}


bool Logistique::modifier()
{
QSqlQuery query;
QString res= QString::number(quantite);
query.prepare("update Logistique set quantite= :quantite, type= :type, reference= :reference, prix= :prix, etat= :etat where quantite = :quantite ");
query.bindValue(":quantite", res);
query.bindValue(":type",type);
query.bindValue(":reference",reference );
query.bindValue(":prix",prix);
query.bindValue(":etat",etat);
return    query.exec();
}


QSqlQueryModel * Logistique::trie_NOM()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Logistique ORDER BY type ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("quantite"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("reference"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("prix"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("etat"));
    return model;
}
