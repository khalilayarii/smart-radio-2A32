#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "programme.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_programme->setModel(P.afficher())

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ajouter_clicked()
{
  QString nomE=ui->le_nomE->text();
  QString nomA=ui->le_nomA->text();
  QString nomE=ui->le_date->text();
  QString nomE=ui->le_typeE->text();
  programme P(nomA,nomE,date,typeE);

}
