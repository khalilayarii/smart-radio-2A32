#include "logistique.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include<QMessageBox>
#include<QSystemTrayIcon>
#include <QSoundEffect>


Logistique::Logistique()
{
    quantite=0; type=""; reference=0 ;
    prix=0; etat="";
}
Logistique::Logistique(int quantite, QString type, int reference, int prix, QString etat)
{this->quantite=quantite; this->type=type; this->reference=reference; this->prix=prix; this->etat=etat;}
int Logistique:: getquantite() {return quantite;}
QString Logistique::gettype() {return type;}
int Logistique::getreference(){return reference;}
int Logistique:: getprix() {return prix;}
QString Logistique::getetat() {return etat;}
void Logistique::setquantite (int quantite) {this->quantite=quantite;}
void Logistique::settype (QString type) {this->type=type;}
void Logistique::setreference(int reference) {this->reference=reference;}
void Logistique::setprix (int prix) {this->prix=prix;}
void Logistique::setetat (QString etat) {this->etat=etat;}
bool Logistique::ajouter()
{
    QSqlQuery query;
    QString quantite_string= QString::number (quantite) ;
    QString prix_string= QString::number (prix) ;
    QString reference_string= QString::number (reference) ;
    query.prepare ("INSERT INTO logistique (quantite, type, reference, prix, etat) "
                   "VALUES (:quantite, :type, :reference, :prix, :etat)");
    query.bindValue(0,quantite_string);
    query.bindValue(1,type);
    query.bindValue(2,reference_string);
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




bool Logistique::supprimer(int reference)
{
    QSqlQuery query;
      QString res =QString::number(reference);
    query.prepare(" Delete from logistique where reference=:reference");
    query.bindValue(":reference", res);

  return  query.exec();
}


bool Logistique::modifier()
{
QSqlQuery query;
QString res= QString::number(reference);
query.prepare("update Logistique set quantite= :quantite, type= :type, reference= :reference, prix= :prix, etat= :etat where reference = :reference ");
query.bindValue(":reference", res);
query.bindValue(":type",type);
query.bindValue(":quantite",quantite );
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
QSqlQueryModel* Logistique::trie()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("SELECT quantite, type, reference, prix, etat from logistique ORDER BY QUANTITE asc");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("quantite"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("reference"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("etat"));


    return model;
}

QSqlQueryModel* Logistique::trieprix()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("SELECT quantite, type, reference, prix, etat from logistique ORDER BY PRIX asc");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("quantite"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("reference"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("etat"));


    return model;
}
QSqlQueryModel *Logistique::rechercher(QString id)
{

    QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM logistique WHERE type LIKE'%"+id+"%'");
        return model;
}


    int Logistique::calcul_prix(QString adresse,QString val)
    {
        QSqlQuery query;
         query.prepare("select  * from logistique  WHERE "+val+"=:prix");
         query.bindValue(":prix", adresse );
         query.exec();
         int total=0;
         while(query.next())
         {
           total++;
         }
         return total;
    }
    QStringList Logistique::listeprix(QString var){
        QSqlQuery query;
        query.prepare("select DISTINCT("+var+") from logistique");
        query.exec();
        QStringList list;
        while(query.next())
        {
            list.append(query.value(0).toString());
        }

        return list;
    }
    int Logistique::alerte(int ref)
    {

        QSqlQuery query;
        QString res=QString::number(ref);

        query.prepare("select quantite from logistique where reference= :ref");
        query.bindValue(":id", res);

         if (query.exec())
                             {
                                 while(query.next())
                                 {
                                   int e=query.value(0).toInt();


           if(e<5)
            {



                    query.prepare("update logistique set quantite=quantite+:quantite   where reference = :ref");
                    query.bindValue(":id", res);
                    query.bindValue(":quantite",5 );
    query.exec();
                    return 1;
}
           else
  {
 return 2;
    }

}}}


