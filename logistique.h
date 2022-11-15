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
    Logistique(int, QString, int, int, QString);

    //getters
    int getquantite();
    QString gettype();
    int getreference();
    int getprix();
    QString getetat();

    //setters
    void setquantite(int);
    void settype(QString);
    void setreference(int);
    void setprix(int n);
    void setetat(QString n);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trie_NOM();
    QSqlQueryModel* trie();
    QSqlQueryModel* trieprix();
    QStringList listeprix(QString var);
    int calcul_prix(QString adresse,QString val);
    QStringList calcul_prix5(QString var);
    int alerte(int ref);




    QSqlQueryModel *rechercher(QString id);
private:
    int quantite;
    QString type;
  int  reference;
  int prix;
  QString etat;

};
#endif // LOGISTIQUE_H
