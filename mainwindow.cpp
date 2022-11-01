#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personels.h"
#include<QMessageBox>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->CIN->setValidator(new QIntValidator(0, 99999999, this));
    ui->tab_personels->setModel(p.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int CIN=ui->CIN->text().toInt() ;
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString adresse=ui->le_adresse->text();
    int numero=ui->le_num->text().toInt() ;

   Personels p(CIN,nom,prenom,adresse,numero);

   bool test=p.ajouter();

   if (test)
   {

        ui->tab_personels->setModel(p.afficher());


       QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("ajout effectué\n"
                                            "click cancel to exit."), QMessageBox::Cancel);
 ui->tab_personels->setModel(p.afficher());
   }
   else {QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);}


   }


void MainWindow::on_pb_supprimer_clicked()
{
 Personels p1; p1.setCIN(ui->le_CINsup->text().toInt());
 bool test=p1.supprimer(p1.getCIN());

if (test)
 { QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("suppression effectué\n"
                                        "click cancel to exit."), QMessageBox::Cancel);

    ui->tab_personels->setModel(p.afficher());}

else QMessageBox::critical(nullptr, QObject::tr("not ok"),
                          QObject::tr("suppression non effectué.\n"
                                      "Click Cancel to exit."),QMessageBox::Cancel);

}
