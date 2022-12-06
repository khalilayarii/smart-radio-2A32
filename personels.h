#ifndef PERSONELS_H
#define PERSONELS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class personels
{
public:
    //constructeurs
   personels();
   personels(int cin,QString nom , QString prenom, QString role,int etat );
     //getters
    int getcin();
    QString getnom();
    QString getprenom();
 //setters
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel *rechercher(QString cin);
    QSqlQueryModel * trie_cin();
    QStringList listeadresses(QString val);
       int calcul_adresses(QString adresse,QString var);


private:
    int cin;
    QString nom ,prenom,role ;
    int etat;


};
class conge{
public:

    conge();
    conge(int,int,QString,QString,QString,QString);


    int Getid_conge() { return id_conge; }
    void Setid_conge(int val) { id_conge = val; }
    int Getcin_p() { return cin_p; }
    void Setcin_p(int val) { cin_p = val; }
    QString Gettype_conge() { return type_conge; }
    void Settype_conge(QString val) { type_conge = val; }
    QString GetDATE_D() { return DATE_D; }
    void SetDATE_D(QString val) { DATE_D = val; }
    QString GetDATE_F() { return DATE_F; }
    void SetDATE_F(QString val) { DATE_F = val; }
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id_conge);
    bool modifier(int cin,int etat);




private:
    int id_conge;
    int cin_p;
    QString type_conge;
    QString DATE_D;
    QString DATE_F;
    QString etat;

};


#endif // PERSONELS_H
