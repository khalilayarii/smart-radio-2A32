#include "sponsors.h"

sponsors::sponsors()
{
    matricule="";
    nom=" ";
    domaine="";
    montant=0;

}
sponsors::sponsors(QString matricule,QString nom,QString domaine,float montant){

this->matricule=matricule;
this->nom=nom;
this->domaine=domaine;
this->montant=montant;



}
bool sponsors::ajouter(){

    QSqlQuery query;
    QString montant_string=QString::number(montant);
    query.prepare("INSERT INTO SPONSORS(matricule,nom,domaine,montant) "
                  "VALUES (:matricule,:nom,:domaine,:montant)");
    query.bindValue(":matricule", matricule);
    query.bindValue(":nom", nom);
    query.bindValue(":domaine", domaine);
    query.bindValue(":montant", montant_string);

   return query.exec();

}
QSqlQueryModel* sponsors::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT matricule,nom,domaine,montant FROM SPONSORS");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("domaine"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant"));

    return model;
}
bool sponsors::supprimer(QString matricule)
{
    QSqlQuery query;

        query.prepare(" Delete from sponsors where matricule=:matricule");
        query.bindValue(":matricule", matricule);

      return  query.exec();
    }
bool sponsors ::modifier()
{
QSqlQuery query;
QString montant_string=QString::number(montant);

query.prepare("update sponsors set matricule= :matricule, domaine= :domaine,nom= :nom, montant= :montant where matricule=:matricule ");
query.bindValue(":matricule", matricule);
query.bindValue(":domaine",domaine);
query.bindValue(":nom",nom );
query.bindValue(":montant",montant_string);

return    query.exec();
}
QSqlQueryModel *sponsors::rechercher (QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM sponsors WHERE matricule LIKE'"+rech+"%'");
    return model;


}

QSqlQueryModel *sponsors::recherchernom(QString nom)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM sponsors WHERE nom LIKE'"+nom+"%'");
    return model;


}

QSqlQueryModel * sponsors::affichertriAZ()
{   QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("SELECT * FROM sponsors order by nom Asc");
return model;
}

QSqlQueryModel * sponsors::affichertriZA()
{   QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("SELECT * FROM sponsors order by nom DESC");
return model;
}
QStringList sponsors::listeadresses(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from sponsors");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int sponsors::calcul_adresses(QString adresse,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from sponsors  WHERE "+val+"=:adresse");
     query.bindValue(":adresse", adresse );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}
