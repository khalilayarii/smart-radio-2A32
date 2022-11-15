#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personels.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
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
#include <QPrinter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_cin_supp->setValidator(new QIntValidator(0,99999999,this));

    ui->tab_personels->setModel(p.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int cin=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString role=ui->comboBox->currentText();

  personels p (cin,nom,prenom,role);

    bool test=p.ajouter();
    if (test)
    {
        //actualiser pour l'affichage
        ui->tab_personels->setModel(p.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK") , QObject::tr("Ajout effectuÃ©\n"
                                                                     "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Ajout non effectuÃ©\n"
                                                                           "Click Cancel to exit"), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimer_clicked()
{

   personels p;
    int cin =ui->le_cin_supp->text().toInt();
    bool test=p.supprimer(cin);
            QMessageBox msgBox;

        if(test){
            //actualiser pour l'affichage
            ui->tab_personels->setModel(p.afficher());
                 msgBox.setText("suppression reussit");
                    ui->tab_personels->setModel(p.afficher());
                }
                else
                    msgBox.setText("echec de suppression");
                    msgBox.exec();

}

void MainWindow::on_pushButton_update_clicked()
{
    int cin=ui->lineEdit_cin_2->text().toInt();
    QString nom=ui->lineEdit_nom_2->text();


    QString prenom=ui->lineEdit_prenom_2->text();

    QString role=ui->comboBox_4->currentText();

   personels p(cin,nom,prenom,role);

    bool test=p.modifier();
    if(test)
    {
        //actualiser pour l'affichage
        ui->tab_personels->setModel(p.afficher());
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("modification effectue.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("modification non effectuÃ©.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_clicked()
{
    QPieSeries *series = new QPieSeries();


        QStringList list=p.listeadresses("role");



        for (int i =0; i< list.size();i++)
        {
            series->append(list[i],p.calcul_adresses(list[i],"role"));

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
        ui->stat->setLayout(mainLayout);
  }


void MainWindow::on_pushButton_4_clicked()
{
    ui->tab_personels->setModel(p.afficher());
        QString strStream;
                                        QTextStream out(&strStream);

                                        const int rowCount = ui->tab_personels->model()->rowCount();
                                        const int columnCount = ui->tab_personels->model()->columnCount();

                                        out <<  "<html>\n"
                                            "<head>\n"
                                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                            <<  QString("<title>%1</title>\n").arg("strTitle")
                                            <<  "</head>\n"
                                            "<body bgcolor=#ffffff link=#5000A0>\n"

                                           //     "<align='right'> " << datefich << "</align>"
                                            "<center> <H1>Liste des personels </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                        // headers
                                        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                        for (int column = 0; column < columnCount; column++)
                                            if (!ui->tab_personels->isColumnHidden(column))
                                                out << QString("<th>%1</th>").arg(ui->tab_personels->model()->headerData(column, Qt::Horizontal).toString());
                                        out << "</tr></thead>\n";

                                        // data table
                                        for (int row = 0; row < rowCount; row++) {
                                            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                            for (int column = 0; column < columnCount; column++) {
                                                if (!ui->tab_personels->isColumnHidden(column)) {
                                                    QString data = ui->tab_personels->model()->data(ui->tab_personels->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_pushButton_trie_clicked()
{
    ui->tab_personels->setModel(p.trie_cin());
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tab_personels->setModel(p.rechercher(arg1));
}
