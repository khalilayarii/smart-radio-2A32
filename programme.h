#ifndef PROGRAMME_H
#define PROGRAMME_H
#include <QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>


#include<QString>
class programme
{
public:
    programme();
    programme(QString,QString,QString,QString);
    QString getnomE();
    QString getnomA();
    QString gettypeE();
    QString getedate();
    void setnomE(QString);
    void setnomA(QString);
    void settypeE(QString);
    void setdate(QString);
    bool ajouter();
    QSqlQueryModel * afficher();
        bool supprimer (int);


private:
    QString  nomE,nomA,typeE,date;

};


#endif // PROGRAMME_H
