#ifndef LOGISTIQUE_H
#define LOGISTIQUE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Logistique
{
public:
    //constructeurs
    Logistique();
    Logistique(int, QString, QString, int, QString);

    //getters
    int getquantite();
    QString gettype();
    QString getreference();
    int getprix();
    QString getetat();

    //setters
    void setquantite(int);
    void settype(QString);
    void setreference(QString);
    void setprix(int n);
    void setetat(QString n);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trie_NOM();
private:
    int quantite, prix;
    QString type, reference, etat;
};

#endif // LOGISTIQUE_H
