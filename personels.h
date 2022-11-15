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
   personels(int cin,QString nom , QString prenom, QString role );
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

};



#endif // PERSONELS_H
