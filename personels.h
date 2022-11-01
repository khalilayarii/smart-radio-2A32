#ifndef PERSONELS_H
#define PERSONELS_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>

#include <QString>
class Personels
{
public:
    Personels();
    Personels(int,QString,QString,QString,int);
    int getCIN();
    int getnumero();
    QString getnom();
    QString getprenom();
    QString getadresse();
    void setCIN(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setnumero(int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer (int);
private:
    int CIN,numero;
    QString nom,prenom, adresse;
};

#endif // PERSONELS_H
