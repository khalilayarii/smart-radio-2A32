#include "conge.h"
#include "mainwindow.h"



conge::conge()
{
  id_conge=-1;
  cin_p=-1;
  type_conge=" ";
  DATE_D=" ";
  DATE_F=" ";
  etat="";

}
conge::conge(int id_conge,int cin_p,QString type_conge,QString DATE_D,QString DATE_F,QString etat){

    this->id_conge=id_conge;
    this->cin_p=cin_p;
    this->type_conge=type_conge;
    this->DATE_D=DATE_D;
    this->DATE_F=DATE_F;
    this->etat=etat;


}

bool conge::ajouter(){

    QSqlQuery query;
    QString Cin_p_string=QString::number(cin_p);
    QString id_string=QString::number(id_conge);
    query.prepare("INSERT INTO conge(ID_CONGE,CIN_P,TYPE_CONGE,DATE_D,DATE_F,etat) "
                  "VALUES (:ID_CONGE,:CIN_P,:TYPE_CONGE,:DATE_D,:DATE_F,:etat)");
    query.bindValue(":ID_CONGE", id_string);
    query.bindValue(":CIN_P", Cin_p_string);
    query.bindValue(":TYPE_CONGE", type_conge);
    query.bindValue(":DATE_D", DATE_D);
    query.bindValue(":DATE_F", DATE_F);
    query.bindValue(":etat", etat);


   return query.exec();

}

QSqlQueryModel* conge::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM conge");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CONGE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN_employe"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE_CONGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_fin"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));


    return model;
}
bool conge::supprimer(int id)
{int cinn;
    QSqlQuery query,query1;
    query.prepare(" select ID_CONGE from conge where ID_CONGE=:ID_CONGE");
    query.bindValue(":ID_CONGE", id);
    query.exec();
    while(query.next())
  {

   cinn=query.value(0).toInt();
   }
    if (cinn!=id) {  QMessageBox::critical(nullptr, QObject::tr("supp impossible"),
   QObject::tr("cin n'existe pas"), QMessageBox::Cancel); }
    else {
        query1.prepare(" Delete from perso where Cin=:Cin");
        query1.bindValue(":Cin", id);
        QMessageBox::critical(nullptr, QObject::tr("suppression reussit"),
           QObject::tr("suppression reussit"), QMessageBox::Cancel);


   }
    return  query1.exec();


}

bool conge::modifier(int cin,int etat)
{
QSqlQuery query;
query.prepare("update personels set etat_conge=:etat  "
              "where Cin = :Cin ");
query.bindValue(":Cin", cin);
query.bindValue(":etat", etat);

return    query.exec();
}
