#ifndef EMISSION_H
#define EMISSION_H
#include<QString>
#include <QSqlQuery>

#include <QDebug>
#include <QDate>
#include <QString>
#include <QSqlQueryModel>
#include <QObject>
class Emission
{
public:
    Emission();
    Emission(int,QString,int,int,int);

    int getidemission();
    QString getnom_emission();
   // QString getnom_animateur();
    int gettemps();
   int getidinvite();
    int getjour();
    void setidemission(int);
    void setnom_emission(QString);
   // void setnom_animateur(QString);
    void settemps(int) ;
    void setidinvite(int) ;
    void setjour(int);
    bool ajouter();
    QSqlQueryModel* afficher();
  bool detett(int idemission );
  bool modifer(int idemission ,QString nom_emission,int temps ,int idinvite ,int jour);
  QSqlQueryModel * recherche(int idemission );
      QSqlQueryModel * tri();
      QSqlQueryModel * tri2();
      QSqlQueryModel * tri3();

    private:
   int idemission ;
    QString nom_emission;
    int  temps,idinvite,jour ;
};

#endif // EMISSION_H
