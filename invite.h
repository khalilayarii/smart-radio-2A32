#ifndef INVITE_H
#define INVITE_H
#include "connection.h"


class invite
{
public:
    invite();
    invite(int cin,QString nom,QString prenom,int age,QString adresse);


    //getters
    int getcin();
    QString getnom();
    QString getprenom();
    int getage();
    QString getadresse();


    //setters
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setage(int age);
    void setadresse(QString);

    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    bool ajouter();
    QSqlQueryModel *rechercher(QString rech);
    QSqlQueryModel *recherchernom(QString nom);
    QSqlQueryModel *affichertriAZ();
    QSqlQueryModel *affichertriZA();
    QStringList listeadresses(QString val);
    int calcul_adresses(QString adresse,QString var);









private:

    int cin;
    QString nom;
    QString prenom;
    int age;
    QString adresse;

};

#endif // INVITE_H
