#ifndef INVITE_H
#define INVITE_H

#include <QString>
class invite
{
public:
    invite();
    invite(int cin,QString nom,QString prenom,int age,QString adress);
    int getcin();
    int getage();
    QString getnom();
    QString getprenom();
    QString getadress();
    void setcin(int cin);
    void setage(int age);
    void setnom(QString nom);
    void setprenom(QString prenom);
    void setadress(QString adress);
    bool ajouter();
private:
    int cin,age;
    QString nom,prenom,adress;
};

#endif // INVITE_H
