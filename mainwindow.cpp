#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logistique.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
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
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QtCharts>
#include <QSqlQuery>
#include <exportexcelobject.h>

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
    int reference=ui->le_reference->text().toInt();
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
    int reference =ui->le_quantite_supp->text().toInt();
    bool test=L.supprimer(reference);
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

    int reference=ui->lineEdit_reference_2->text().toInt();

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



void MainWindow::on_pushButton_trie_clicked()
{
    ui->tab_logistique->setModel(L.trie());

}

void MainWindow::on_pushButton_imprimer_clicked()
{
    QString strStream;
                                    QTextStream out(&strStream);

                                    const int rowCount = ui->tab_logistique->model()->rowCount();
                                    const int columnCount = ui->tab_logistique->model()->columnCount();

                                    out <<  "<html>\n"
                                        "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>listes des logistique </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tab_logistique->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tab_logistique->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tab_logistique->isColumnHidden(column)) {
                                                QString data = ui->tab_logistique->model()->data(ui->tab_logistique->model()->index(row, column)).toString().simplified();
                                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                            }
                                        }
                                        out << "</tr>\n";
                                    }
                                    out <<  "</table> </center>\n"
                                        "</body>\n"
                                        "</html>\n";

                              QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                               QPrinter printer (QPrinter::PrinterResolution);
                                printer.setOutputFormat(QPrinter::PdfFormat);
                               printer.setPaperSize(QPrinter::A4);
                              printer.setOutputFileName(fileName);

                               QTextDocument doc;
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);
}


void MainWindow::on_le_recherche_textChanged(const QString &arg1)
{
    ui->tab_logistique->setModel(L.rechercher(arg1));
}


/*void MainWindow::on_pushButton_trieprix_clicked()
{
    ui->tab_logistique->setModel(L.trieprix());
}



*/
void MainWindow::on_alerte_clicked()
{Logistique L;
    int reference =ui->ee->text().toInt();
   int test=L.supprimer(reference);
   if (test==1)
    {


                QMessageBox::critical(nullptr, QObject::tr("database is open"),
                            QObject::tr("stock est verifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->lii->addItem("stock presque nulle");
   }
    else if(test==2) {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("stock est verifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
   ui->lii->addItem("stock suffisant");}

    }










void MainWindow::on_stat_clicked()
{

        QPieSeries *series = new QPieSeries();


            QStringList list=L.listeprix("prix");



            for (int i =0; i< list.size();i++)
            {
                series->append(list[i],L.calcul_prix(list[i],"prix"));

            }
            QPieSlice *slice = series->slices().at(1);
            slice->setLabelVisible();
            slice->setExploded();


            QtCharts::QChart *chart =new QtCharts::QChart();
            chart->addSeries(series);
            chart->setTitle("Statistiques des prix");
            chart->setAnimationOptions(QChart::AllAnimations);
            QChartView *chartview=new QChartView(chart);
            QGridLayout *mainLayout=new QGridLayout();
            mainLayout->addWidget(chartview,0,0);
            ui->stat->setLayout(mainLayout);

    }



void MainWindow::on_excel_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tab_logistique);

    //colums to export
    obj.addField(0, "reference", "char(20)");
    obj.addField(1, "nom", "char(20)");
    obj.addField(2, "prenom", "char(20)");
    obj.addField(3, "destination", "char(20)");
    obj.addField(4, "date de depart", "char(20)");
    obj.addField(5, "pilote", "char(20)");
    obj.addField(5, "avion", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal));

    }

}
