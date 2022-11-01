#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invite.h"
#include<QMessageBox>
#include<QIntValidator>
#include "connection.h"
#include <QApplication>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_clicked()
{
    //recuperation des information saisis dans les 6 champs
   int cin=ui->cin->text().toInt();
   QString nom=ui->nom->text();
   QString prenom=ui->prenom->text();
   int age=ui->age->text().toInt();
   QString adress=ui->adress->text();

invite I(cin,nom,prenom,age,adress);
 bool test=I.ajouter();
 if (test)
 {

     QMessageBox::information(nullptr, QObject::tr("OK") , QObject::tr("Ajout effectué\n"
                                                                  "Click Cancel to exit"), QMessageBox::Cancel);
 }
 else
     QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n"
                                                                        "Click Cancel to exit"), QMessageBox::Cancel);


}
