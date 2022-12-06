#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sponsors.h"
#include <QUrl>
#include "arduino.h"
#include <QWidget>
#include <QVariant>
#include <QPdfWriter>
#include <QFileDialog>
#include  <QPrinter>
#include <QPainter>
#include <QtPrintSupport/QPrintDialog>
#include "statistique.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "windows.h"


MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //int ret=A.connect_arduino(); // lancer la connexion à arduino
   // switch(ret){
    //case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
      //  break;
    //case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
      // break;
    //case(-1):qDebug() << "arduino is not available";
    //}
    // QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).

    ui->tablespon->setModel(S.afficher());
   //map
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                        QCoreApplication::organizationName(), QCoreApplication::applicationName());

     ui->WebBrowser_2->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
}
void MainWindow::update_label()
{

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    QString matricule=ui->matricule->text();
    QString nom=ui->nom->text();
    QString domaine=ui->domaine->text();
    int montant=ui->montant->text().toInt();

  sponsors S(matricule,nom,domaine,montant);
  bool test=S.ajouter();
  if (test)
  {
      //actualiser pour l'affichage
       ui->tablespon->setModel(S.afficher());
      QMessageBox::information(nullptr, QObject::tr("OK") , QObject::tr("Ajout effectué\n"
                                                                   "Click Cancel to exit"), QMessageBox::Cancel);
  }
  else
      QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n"
                                                                         "Click Cancel to exit"), QMessageBox::Cancel);

}


void MainWindow::on_delete_2_clicked()
{sponsors S;
    QString  matricule=ui->sup_m->text();
    bool test=S.supprimer(matricule);
            QMessageBox msgBox;

        if(test){
            //actualiser pour l'affichage
            ui->tablespon->setModel(S.afficher());
                 msgBox.setText("suppression reussit");
                    ui->tablespon->setModel(S.afficher());
                }
                else
                    msgBox.setText("echec de suppression");
                    msgBox.exec();

}



void MainWindow::on_update_clicked()
{
    QString matricule=ui->matricule_3->text();
    QString nom=ui->nom_3->text();
    QString domaine=ui->domaine_3->text();
    int montant=ui->montant_3->text().toInt();



       sponsors  S1(matricule,nom,domaine,montant);

        bool test=S1.modifier();
        if(test)
        {
            //actualiser pour l'affichage
            ui->tablespon->setModel(S1.afficher());
                    QMessageBox::information(nullptr, QObject::tr("database is open"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("database is open"),
                        QObject::tr("modification non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }



void MainWindow::on_pushButton_clicked()
{
    ui->tablespon->setModel(S.affichertriAZ());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tablespon->setModel(S.affichertriZA());

}

void MainWindow::on_matricule_2_textChanged(const QString &arg1)
{
    ui->tablespon->setModel(S.rechercher(arg1));

}




void MainWindow::on_PDF_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                           "/home",
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);
               qDebug()<<dir;
               QPdfWriter pdf(dir+"/PdfList.pdf");
                                      QPainter painter(&pdf);
                                     int i = 4000;

                                     painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/21621/OneDrive/Bureau/radio.png"));
                                         //painter.drawText(900,650,"gestion sponsors");



                                          painter.setPen(Qt::blue);
                                          painter.setFont(QFont("Time New Roman", 25));
                                          painter.drawText(3000,1400,"Liste Des sponsors");
                                          painter.setPen(Qt::black);
                                          painter.setFont(QFont("Time New Roman", 15));
                                          painter.drawRect(100,100,9400,2500);
                                          painter.drawRect(100,3000,9400,500);
                                          painter.setFont(QFont("Time New Roman", 9));
                                          painter.drawText(300,3300,"matricule");
                                          painter.drawText(2300,3300,"nom");
                                          painter.drawText(4300,3300,"domaine");
                                          painter.drawText(6300,3300,"montant");
                                          //painter.drawText(7500,3300,"type");

                                        /*  painter.drawText(9500,3300,"Date Retour");
                                          painter.drawText(10500,3300,"Date Naissance");*/

                                          painter.drawRect(100,3000,9400,10700);


                                          QTextDocument previewDoc;
                                          QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");


                                          QTextCursor cursor(&previewDoc);



                                          QSqlQuery query;
                                          query.prepare("select * from sponsors");
                                          query.exec();
                                          while (query.next())
                                          {
                                              painter.drawText(300,i,query.value(0).toString());
                                              painter.drawText(2300,i,query.value(1).toString());
                                              painter.drawText(4300,i,query.value(2).toString());
                                              painter.drawText(6300,i,query.value(3).toString());
                                              painter.drawText(7500,i,query.value(4).toString());
                                             /* painter.drawText(8500,i,query.value(5).toString());
                                              painter.drawText(9500,i,query.value(6).toString());
                                              painter.drawText(10500,i,query.value(7).toString());*/




                                             i = i +500;
                                          }
                                          int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                              QMessageBox::Yes|QMessageBox::No);
                                              if (reponse == QMessageBox::Yes)
                                              {
                                                  QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                                  painter.end();
                                              }
                                              else
                                              {
                                                   painter.end();
     }

}



void MainWindow::on_STAT_clicked()
{

}

void MainWindow::on_pushButton_4_clicked()
{

    QSqlQuery query;
             QMessageBox msgBox;
                 QString id =ui->id->text(), pw=ui->pw->text(),type="";
                 query.prepare("SELECT nom FROM PERSONNELS WHERE IDENTIFIANT =:id AND MOT_DE_PASSE =:pwd");
                 query.bindValue(":id", id);
                 query.bindValue(":pwd", pw);
                 query.exec();
   
                 while(query.next())
               {
   
                type=query.value(0).toString();
                }
                 if (query.exec())
                 {              msgBox.setText("Identifié comme  " +type);
                     msgBox.exec();
   
                      ui->stackedWidget->setCurrentIndex(1);
                       A.write_to_arduino("2") ; 
    }
                 else { 
                      A.write_to_arduino("1") ; 
                     QMessageBox::critical(nullptr, QObject::tr("Echec d'authentification"),
                                              QObject::tr("Mot de passe ou nom d'utilisateur non-valide"), QMessageBox::Cancel);
                      
   
                }



}
