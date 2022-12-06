#ifndef FINANCE_H
#define FINANCE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Finance
{
public:
    //constructeurs
    Finance();
    Finance(int id,int dates , QString operations );
     //getters
    int getid();
    int getdates();
    QString getoperations();
 //setters
    void setid(int);
    void setdates(int);
    void setoperations(QString);


    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel *rechercher(QString rech);
    QSqlQueryModel *trie_id();
    int calcul_adresses(QString adresse,QString var);
    QStringList listeadresses(QString val);

private:
    int id,dates;
    QString operations ;

};


#endif // FINANCE_H
