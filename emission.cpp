#include"emission.h"
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
#include <QObject>
#include <QDialog>
#include <QFrame>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <strstream>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QPdfWriter>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
Emission::Emission()
{
idemission=0;
nom_emission =" ";
//nom_animateur=" ";
temps=0;idinvite=0;jour=0 ;
}
Emission::Emission(int idemission ,QString nom_emission,int temps ,int idinvite ,int jour)

{   this->idemission=idemission;
  this->nom_emission=nom_emission;
 // this->nom_animateur=nom_animateur;
   this->temps=temps;
    this->idinvite=idinvite ;
    this->jour=jour;
}
int Emission::getidemission(){return idemission;}
QString Emission::getnom_emission(){return nom_emission;}
//QString Emission::getnom_animateur(){return nom_animateur;}
int Emission::gettemps(){return temps;}
int Emission::getidinvite(){return idinvite;}
int Emission::getjour(){return jour;}
void Emission::setidemission(int idemission){this->idemission=idemission;}
void Emission::setnom_emission(QString nom_emission){this->nom_emission=nom_emission;}
//void Emission::setnom_animateur(QString nom_animateur){this->nom_animateur=nom_animateur;}
void Emission::settemps(int temps){this->temps=temps;}
void Emission::setidinvite(int idinvite ){this->idinvite=idinvite;}
void Emission::setjour(int jour ){this->jour=jour;}

bool Emission::ajouter()
{
    //bool test=true;

    QSqlQuery query;


    QString idemission_string=QString::number(idemission);
    QString temps_string=QString::number(temps);
    QString idinvite_string=QString::number(idinvite);
    QString jour_string=QString::number(jour);
          query.prepare("INSERT INTO EMISSION (IDEMISSION,NOM_EMISSION,TEMPS,IDINVITE,jour) "
                        "VALUES (:idemission,:nom_emission,:temps,:idinvite,:jour)");

         query.bindValue(":idemission", idemission_string);
          query.bindValue(":nom_emission", nom_emission);
          //query.bindValue(":nom_animateur", nom_animateur);
          query.bindValue(":temps", temps_string);
          query.bindValue(":idinvite", idinvite_string);
          query.bindValue(":jour", jour_string);
     return query.exec();
}



QSqlQueryModel* Emission::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM EMISSION");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("idemission"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom_emission"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("temps"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("idinvite"));
          model->setHeaderData(4,Qt::Horizontal,QObject::tr("jour"));
    return model;
}
bool Emission::detett(int idemission )
{ QSqlQuery query;
   // QString nom_emission_string=QString::number(NOM_EMISSION);
    QString idemission_string=QString::number(idemission);

    query.prepare("Delete from EMISSION where idemission= :idemission ");
     query.bindValue(":idemission", idemission_string);
    return query.exec();

}

bool Emission::modifer(int idemission ,QString nom_emission,int temps ,int idinvite ,int jour)
{ QSqlQuery query;
    QString idemission_string=QString::number(idemission);
    QString temps_string=QString::number(temps);
    QString idinvite_string=QString::number(idinvite);
    QString jour_string=QString::number(jour);
    query.prepare("UPDATE EMISSION SET IDEMISSION= :IDEMISSION,NOM_EMISSION = :NOM_EMISSION,TEMPS = :TEMPS,IDINVITE = :IDINVITE,jour = :jour WHERE IDEMISSION=:IDEMISSION");

    query.bindValue(":IDEMISSION", idemission_string);
    query.bindValue(":NOM_EMISSION", nom_emission);
    query.bindValue(":TEMPS", temps_string);
    query.bindValue(":IDINVITE", idinvite_string);
    query.bindValue(":jour", jour_string);
    return query.exec();}
    QSqlQueryModel * Emission::recherche(int idemission)
     {
         QSqlQuery query;
         QString idemission_string=QString::number(idemission);

         query.prepare("select * from Emission where idemission=:idemission");
         query.bindValue(":idemission",idemission_string);
         query.exec();
         QSqlQueryModel *model= new QSqlQueryModel;
         model->setQuery(query);


        return model;
}/*
    QSqlQueryModel * Emission::tri()
    {
        QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery(" select * from Emission where idemission=:idemission" );
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("idemission"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_emission"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("temps"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("idinvite"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("jour"));


     return model;

    }*/
    QSqlQueryModel *Emission::tri() // m sghir lel kbir
    {
              QSqlQuery * q = new  QSqlQuery ();
                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("SELECT * FROM Emission order by idemission ");
                     q->exec();
                     model->setQuery(*q);
                     return model;
    }
    QSqlQueryModel *Emission::tri2() // m sghir lel kbir
    {
              QSqlQuery * q = new  QSqlQuery ();
                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("SELECT * FROM Emission order by temps ");
                     q->exec();
                     model->setQuery(*q);
                     return model;
    }
    QSqlQueryModel *Emission::tri3() // m sghir lel kbir
    {
              QSqlQuery * q = new  QSqlQuery ();
                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("SELECT * FROM Emission order by idinvite ");
                     q->exec();
                     model->setQuery(*q);
                     return model;
    }



