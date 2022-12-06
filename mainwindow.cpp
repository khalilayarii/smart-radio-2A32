#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "invite.h"
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>
#include <QPainter>
#include<QMessageBox>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QCloseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include<QSystemTrayIcon>
#include<QPrinter>
#include<QLineSeries>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{        ui->tableinvite->setModel(i.afficher());

    int rete=A.connect_arduino(); // lancer la connexion à arduino+.

       switch(rete){
       case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_tableinvite_clicked(const QModelIndex &index)));

    ui->setupUi(this);
    ui->cin->setValidator( new QIntValidator( 100000,999999, this));
    ui->tableinvite->setModel(i.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::affichageinvite(QString id){

       QSqlQuery query;
       QByteArray message;
       QString ch;
       query.prepare("select nom from INVITEE where cin= "+id+"");
       if (query.exec())
                           {
                               while(query.next())
                               {
                                ch =query.value(0).toString();



                               }
                                message=ch.toUtf8();
                                A.write_to_arduino(message) ;


}}
void MainWindow::on_ajouter_clicked()
{


    int cin=ui->cin->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int age=ui->age->text().toInt();
    QString adresse=ui->adresse->text();
    invite i(cin,nom,prenom,age,adresse);

    bool test=i.ajouter();
    if (test)
    {
        //actualiser pour l'affichage
        ui->tableinvite->setModel(i.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK") , QObject::tr("Ajout effectué\n"
                                                                     "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n"
                                                                           "Click Cancel to exit"), QMessageBox::Cancel);



}


void MainWindow::on_dalete_clicked()
{
    invite i;
    int cin =ui->sup_cin->text().toInt();
    bool test=i.supprimer(cin);
            QMessageBox msgBox;

        if(test){
            //actualiser pour l'affichage
            ui->tableinvite->setModel(i.afficher());
                 msgBox.setText("Suppression effectué");
                    ui->tableinvite->setModel(i.afficher());
                }
                else
                    msgBox.setText("Suppression non effectué");
                    msgBox.exec();

}


void MainWindow::on_update_clicked()
{
    int cin=ui->cin_2->text().toInt();
    QString nom=ui->nom_2->text();
    QString prenom=ui->prenom_2->text();
    int age=ui->age_2->text().toInt();
    QString adresse=ui->adresse_2->text();
    invite i1(cin,nom,prenom,age,adresse);

    bool test=i1.modifier();
    if(test)
    {
        //actualiser pour l'affichage
        ui->tableinvite->setModel(i1.afficher());
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("MAJ effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("modification non effectué.\n"
                                "MAJ non effectué."), QMessageBox::Cancel);

}

void MainWindow::on_tri1_clicked()
{
    ui->tableinvite->setModel(i.affichertriAZ());

}

void MainWindow::on_tri2_clicked()
{
    ui->tableinvite->setModel(i.affichertriZA());

}

void MainWindow::on_cinn_textChanged(const QString &arg1)
{
    ui->tableinvite->setModel(i.rechercher(arg1));

}

void MainWindow::on_nomm_textChanged(const QString &nom)
{
    ui->tableinvite->setModel(i.recherchernom(nom));

}

void MainWindow::on_pdf_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                               "/home",
                                                               QFileDialog::ShowDirsOnly
                                                               | QFileDialog::DontResolveSymlinks);
                   qDebug()<<dir;
                   QPdfWriter pdf(dir+"/PdfList.pdf");
                                          QPainter painter(&pdf);
                                         int i = 4000;

                                         painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/saiid/OneDrive/Bureau/radio.png"));
                                             painter.drawText(900,650,"gestion invites");

                                              //painter.drawPixmap(QRect(7600,100,2100,2700),QPixmap("C:/Users/Admin/Desktop/logo.png"));

                                              painter.setPen(Qt::blue);
                                              painter.setFont(QFont("Time New Roman", 25));
                                              painter.drawText(3000,1400,"Liste Des invites");
                                              painter.setPen(Qt::black);
                                              painter.setFont(QFont("Time New Roman", 15));
                                              painter.drawRect(100,100,9400,2500);
                                              painter.drawRect(100,3000,9400,500);
                                              painter.setFont(QFont("Time New Roman", 9));
                                              painter.drawText(300,3300,"ID");
                                              painter.drawText(2300,3300,"Prenom");
                                              painter.drawText(4300,3300,"Nom");
                                              painter.drawText(6300,3300,"age");
                                              painter.drawText(7500,3300,"adresse");
                                             /* painter.drawText(8500,3300,"Date ");
                                              painter.drawText(9500,3300,"Date Retour");
                                              painter.drawText(10500,3300,"Date Naissance");*/

                                              painter.drawRect(100,3000,9400,10700);


                                              QTextDocument previewDoc;
                                              QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");


                                              QTextCursor cursor(&previewDoc);



                                              QSqlQuery query;
                                              query.prepare("select * from invite");
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


void MainWindow::on_stat_clicked()
{invite p;
    QPieSeries *series = new QPieSeries();


        QStringList list=p.listeadresses("age");



        for (int i =0; i< list.size();i++)
        {
            series->append(list[i],p.calcul_adresses(list[i],"age"));

        }
        QPieSlice *slice = series->slices().at(1);
        slice->setLabelVisible();
        slice->setExploded();


        QtCharts::QChart *chart =new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques par age ");
        chart->setAnimationOptions(QChart::AllAnimations);
        QChartView *chartview=new QChartView(chart);
        QGridLayout *mainLayout=new QGridLayout();
        mainLayout->addWidget(chartview,0,0);
        ui->statistiques->setLayout(mainLayout);

}


void MainWindow::on_pushButton_clicked()
{    QString id=ui->id_affiche->text();

    affichageinvite(id);
}

void MainWindow::on_tableinvite_clicked(const QModelIndex &index)
{
    QString val=ui->tableinvite->model()->data(index).toString();

    QSqlQuery query;
    QByteArray message,message1;
    QString ch,ch1;
    query.prepare("select nom from INVITEE where cin= "+val+"");
    if (query.exec())
                        {
                            while(query.next())
                            {
                             ch =query.value(0).toString();



                            }
                             message=ch.toUtf8();

               query.prepare("select  prenom from INVITEE where cin= "+val+"");
                             if (query.exec())
                                                 {
                                                     while(query.next())
                                                     {
                                                      ch1 =query.value(0).toString();



                                                     }
                                                      message=message1+""+ch1.toUtf8();
                                                      A.write_to_arduino(message);

}}}
