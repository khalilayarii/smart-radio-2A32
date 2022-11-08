#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logistique.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_quantite->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_quantite_supp->setValidator(new QIntValidator(0,99999999,this));
    ui->le_prix->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_prix_2->setValidator(new QIntValidator(0,99999999,this));
    ui->tab_logistique->setModel(L.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int quantite=ui->le_quantite->text().toInt();
    QString type=ui->le_type->text();
    QString reference=ui->le_reference->text();
    int prix=ui->le_prix->text().toInt();
    QString etat=ui->le_etat->text();
    Logistique L(quantite,type,reference,prix,etat);

    bool test=L.ajouter();
    if (test)
    {
        //actualiser pour l'affichage
        ui->tab_logistique->setModel(L.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK") , QObject::tr("Ajout effectué\n"
                                                                     "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n"
                                                                           "Click Cancel to exit"), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimer_clicked()
{

    Logistique L;
    int quantite =ui->le_quantite_supp->text().toInt();
    bool test=L.supprimer(quantite);
            QMessageBox msgBox;

        if(test){
            //actualiser pour l'affichage
            ui->tab_logistique->setModel(L.afficher());
                 msgBox.setText("suppression reussite");
                    ui->tab_logistique->setModel(L.afficher());
                }
                else
                    msgBox.setText("echec de suppression");
                    msgBox.exec();

}

void MainWindow::on_pushButton_update_clicked()
{
    int quantite=ui->lineEdit_quantite_2->text().toInt();

    QString type=ui->lineEdit_type_2->text();

    QString reference=ui->lineEdit_reference_2->text();

    int prix=ui->lineEdit_prix_2->text().toInt();

   QString etat=ui->lineEdit_etat_2->text();

    Logistique L1(quantite,type,reference,prix,etat);

    bool test=L1.modifier();
    if(test)
    {
        //actualiser pour l'affichage
        ui->tab_logistique->setModel(L.afficher());
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("modification effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("modification non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
