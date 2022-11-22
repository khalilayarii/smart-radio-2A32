#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finance.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
#include <QSqlQuery>
#include <QDebug>
#include <QUrl>
#include <QPdfWriter>

#include <QUrlQuery>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_id_supp->setValidator(new QIntValidator(0,99999999,this));

    ui->tab_finance->setModel(f.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    int date=ui->le_dates->text().toInt();
    QString operations=ui->le_operations->text();
    Finance f (id,date,operations);

    bool test=f.ajouter();
    if (test)
    {
        //actualiser pour l'affichage
        ui->tab_finance->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK") , QObject::tr("Ajout effectué\n"
                                                                     "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n"
                                                                           "Click Cancel to exit"), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimer_clicked()
{

    Finance f;
    int id =ui->le_id_supp->text().toInt();
    bool test=f.supprimer(id);
            QMessageBox msgBox;

        if(test){
            //actualiser pour l'affichage
            ui->tab_finance->setModel(f.afficher());
                 msgBox.setText("suppression reussit");
                    ui->tab_finance->setModel(f.afficher());
                }
                else
                    msgBox.setText("echec de suppression");
                    msgBox.exec();

}

void MainWindow::on_pushButton_update_clicked()
{
    int id=ui->lineEdit_id_2->text().toInt();
  int date=ui->lineEdit_dates_2->text().toInt();
    QString operations=ui->lineEdit_operations_2->text();


   Finance f1(id,date,operations);

    bool test=f1.modifier();
    if(test)
    {
        //actualiser pour l'affichage
        ui->tab_finance->setModel(f.afficher());
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("modification effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("modification non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                               "/home",
                                                               QFileDialog::ShowDirsOnly
                                                               | QFileDialog::DontResolveSymlinks);
                   qDebug()<<dir;
                   QPdfWriter pdf(dir+"/PdfList.pdf");
                                          QPainter painter(&pdf);
                                         int i = 4000;

                                         painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Admin/Desktop/logo.png"));
                                             painter.drawText(900,650,"Gharbi Ines");

                                              //painter.drawPixmap(QRect(7600,100,2100,2700),QPixmap("C:/Users/Admin/Desktop/logo.png"));

                                              painter.setPen(Qt::blue);
                                              painter.setFont(QFont("Time New Roman", 25));
                                              painter.drawText(3000,1400,"finance");
                                              painter.setPen(Qt::black);
                                              painter.setFont(QFont("Time New Roman", 15));
                                              painter.drawRect(100,100,9400,2500);
                                              painter.drawRect(100,3000,9400,500);
                                              painter.setFont(QFont("Time New Roman", 9));
                                              painter.drawText(300,3300,"id");
                                              painter.drawText(2300,3300,"dates");
                                              painter.drawText(4300,3300,"operations");



                                              painter.drawRect(100,3000,9400,10700);


                                              QTextDocument previewDoc;
                                              QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");


                                              QTextCursor cursor(&previewDoc);



                                              QSqlQuery query;
                                              query.prepare("select * from finance");
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


void MainWindow::on_pushButton_clicked()
{
        QPieSeries *series = new QPieSeries();


            QStringList list=f.listeadresses("OPERATIONS");



            for (int i =0; i< list.size();i++)
            {
                series->append(list[i],f.calcul_adresses(list[i],"OPERATIONS"));

            }
            QPieSlice *slice = series->slices().at(1);
            slice->setLabelVisible();
            slice->setExploded();


            QtCharts::QChart *chart =new QtCharts::QChart();
            chart->addSeries(series);
            chart->setTitle("Statistiques");
            chart->setAnimationOptions(QChart::AllAnimations);
            QChartView *chartview=new QChartView(chart);
            QGridLayout *mainLayout=new QGridLayout();
            mainLayout->addWidget(chartview,0,0);
            ui->STAT->setLayout(mainLayout);

}

void MainWindow::on_pushButton_trie_clicked()
{
    ui->tab_finance->setModel(f.trie_id());
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tab_finance->setModel(f.rechercher(arg1));
}


void MainWindow::on_excel_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tab_finance);

    //colums to export
    obj.addField(0, "id", "char(20)");
    obj.addField(1, "dates", "char(20)");
    obj.addField(2, "operations", "char(20)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal));

    }

}



void MainWindow::on_pushButton_6_clicked()
{

    c= new calculatrice(this);
    c->show();
}

