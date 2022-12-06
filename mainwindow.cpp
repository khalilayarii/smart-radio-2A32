#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personels.h"
#include "connection.h"
#include "conge.h"
#include "arduino.h"
#include "finance.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
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
#include<QIntValidator>
#include <QWidget>
#include "sponsors.h"
#include "invite.h"
#include <QSqlQueryModel>
#include "logistique.h"
#include "smtp.h"
//************************

#include <string>
#include<QMessageBox>
#include <QIntValidator>
#include <QPixmap>
#include "QtWidgets"
#include <QTextEdit>
#include <QtDebug>
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>
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
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator(new QIntValidator(0,99999999, this));
    ui->le_cin_supp->setValidator(new QIntValidator(0,99999999,this));

    ui->tab_personels->setModel(p.afficher());
    //********f**************
    ui->le_id->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_id_supp->setValidator(new QIntValidator(0,99999999,this));

    ui->tab_finance->setModel(f.afficher());

    ui->tab_personels->setModel(p.afficher());

//**************S***************************

    ui->tablespon->setModel(S.afficher());

//**********************************************************

    ui->tableinvite->setModel(i.afficher());


        ui->cin->setValidator( new QIntValidator( 100000,999999, this));
        ui->tableinvite->setModel(i.afficher());
//**********************EMISSION////////////////////////
        Emission E ;
            ui->tab_emission->setModel(E.afficher());
            //ui->tab_emission->setModel(E.tri());
//********Logistique**************
            ui->le_quantite->setValidator(new QIntValidator(0, 99999999, this));
            ui->le_quantite_supp->setValidator(new QIntValidator(0,99999999,this));
            ui->le_prix->setValidator(new QIntValidator(0, 99999999, this));
            ui->lineEdit_prix_2->setValidator(new QIntValidator(0,99999999,this));

            ui->tab_logistique->setModel(L.afficher());
            //for email tab
            connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
            connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));


    //***********************ARDUINO**************************


    int ret=Ard.connect_arduino(); // lancer la connexion à arduino
               switch(ret){
               case(0):qDebug()<< "arduino is available and connected to : "<< Ard.getarduino_port_name();
                   break;
               case(1):qDebug() << "arduino is available but not connected to :" <<Ard.getarduino_port_name();
                  break;
               case(-1):qDebug() << "arduino is not available";
               }
                QObject::connect(Ard.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
                //le slot update_label suite à la reception du signal readyRead (reception des données).
}






void MainWindow::update_label()
{
 data="";

while((Ard.getdata().size()<6))
{
    QString key;
data=Ard.read_from_arduino();

break;

}
if(data.toInt()!=0)
{int D=data.toInt();
    if(Ard.cherchercin(D)!=-1)
    {
        QMessageBox::information(nullptr, QObject::tr("cin exist"),
                    QObject::tr("ce personnel existe.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {  QMessageBox::critical(nullptr, QObject::tr("introuvlable"),
                             QObject::tr("perso introuvable.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}

 qDebug() << D ;
}





data="";
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
int etat=0;
  personels p (cin,nom,prenom,role,etat);

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

    int etat=0;
      personels p (cin,nom,prenom,role,etat);
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

void MainWindow::on_pushButtonp_11_clicked()
{
    QString type=ui->type_conge->currentText();
    int cin=ui->comboBoxp->currentText().toInt();
    int id=ui->idp_2->text().toInt();

    QString datd=ui->FromdateEdit->date().toString("dd/MM/yyyy");

    QString datf=ui->TodateEdit->date().toString("dd/MM/yyyy");
QString etat;

conge c(id,cin,type,datd,datf,etat);

    bool test=c.ajouter();
    if(test)
    {
        //actualiser pour l'affichage
        ui->conge->setModel(c.afficher());

                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("ajout effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButtonp_6_clicked()
{
    int cin=ui->comboBoxp->currentText().toInt();
    int cin2=ui->cinconge->text().toInt();

    bool test=co.modifier(cin2,1);
    if(test)
    {
        //actualiser pour l'affichage
        ui->conge->setModel(co.afficher());
        QSqlQuery query2;
        query2.prepare("update conge set etat=:etat  "
                      "where CIN_P =:CIN_P ");
        query2.bindValue(":CIN_P", cin2);
        query2.bindValue(":etat", "autorisé");

         query2.exec();
         if (query2.exec())
         {   ui->conge->setModel(co.afficher());
             ui->tab_personels->setModel(p.afficher());
             QMessageBox::information(nullptr, QObject::tr("database is open"),
                         QObject::tr("congeautorise.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tab_personels->setModel(p.afficher());
         }}
}

void MainWindow::on_comboBoxp_currentTextChanged(const QString &arg1)
{
    ui->widget->hide();

       QSqlQuery query;
         QMessageBox msgBox;
             int type;
             query.prepare("SELECT ETAT_CONGE FROM PERSONELS WHERE CIN LIKE'%"+arg1+"%'");
             query.exec();
             while(query.next())
           {

            type=query.value(0).toInt();
            }
             if (type==1)
             {  QMessageBox::critical(nullptr, QObject::tr("DEMANDE NON AUTORISE"),
            QObject::tr("L'EMPLOYE EST DEJA EN CONGE"), QMessageBox::Cancel); }
             else if (type==0)
             {
            msgBox.setText("REMPLIR LA FORMULAIRE DU CONGE " );
            msgBox.exec();

             ui->widget->show();


            }

}

void MainWindow::on_pushButtonp_7_clicked()
{
    int id_conge=ui->idp_2->text().toInt();
    int cin=ui->cinconge->text().toInt();

    bool test=co.modifier(cin,0);
       if (test)
    {   QSqlQuery query;
       query.prepare("update conge set etat=:etat  "
                     "where ID_CONGE =:ID_CONGE ");
       query.bindValue(":ID_CONGE", id_conge);
       query.bindValue(":etat", "non autorisé");

        query.exec();
        if (query.exec())
        {   ui->conge->setModel(co.afficher());
            QMessageBox::critical(nullptr, QObject::tr("database is open"),
                        QObject::tr("conge non autorise.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->comboBoxp->setModel(p.afficher());
ui->tab_personels->setModel(p.afficher());
        }}
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index==5){
        ui->comboBoxp->setModel(p.afficher());

    }
}
//*************************login******************************************************
void MainWindow::on_login_button_clicked()
{
  QSqlQuery query;
    QMessageBox msgBox;
        QString id =ui->id->text(), pw=ui->password->text(),type="";
        query.prepare("SELECT ROLE FROM EMPLOYE WHERE ID =:id AND PASSWORD =:password");
        query.bindValue(":id", id);
        query.bindValue(":password",pw);
        query.exec();

        while(query.next())
      {

       type=query.value(0).toString();
       }
        if (type=="") {  QMessageBox::critical(nullptr, QObject::tr("Echec d'authentification"),
       QObject::tr("Mot de passe ou nom d'utilisateur non-valide"), QMessageBox::Cancel); }
        else {
       msgBox.setText("Identifié comme employé  " +type);
       msgBox.exec();
       if (type== "finance")
        ui->stackedWidget->setCurrentIndex(1);
       else if (type== "personels")
           ui->stackedWidget->setCurrentIndex(2);

       else if (type=="sponsors")
          ui->stackedWidget->setCurrentIndex(3);
       else if (type=="invitee")
          ui->stackedWidget->setCurrentIndex(4);
       else if (type=="programme")
          ui->stackedWidget->setCurrentIndex(5);
       else if (type=="logistique")
          ui->stackedWidget->setCurrentIndex(6);


       }


}
//******************************************************finance*****************

void MainWindow::on_pb_ajouterF_clicked()
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

void MainWindow::on_pushButton_supprimerF_clicked()
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

void MainWindow::on_pushButton_updateF_clicked()
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

void MainWindow::on_pdf1_clicked()
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




void MainWindow::on_pushButton_trieF_clicked()
{
    ui->tab_finance->setModel(f.trie_id());
}

void MainWindow::on_lineEdit_textChangedF(const QString &arg1)
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



void MainWindow::on_calculatrice_2_clicked()
{

    c= new calculatrice(this);
    c->show();
}

//****************************************************************************************
void MainWindow::on_ajouterS_clicked()
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


void MainWindow::on_deleteS_2_clicked()
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



void MainWindow::on_updateS_clicked()
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



void MainWindow::on_pushButtonS_clicked()
{
    ui->tablespon->setModel(S.affichertriAZ());
}

void MainWindow::on_pushButtonS_2_clicked()
{
    ui->tablespon->setModel(S.affichertriZA());

}

void MainWindow::on_matriculeS_2_textChanged(const QString &arg1)
{
    ui->tablespon->setModel(S.rechercher(arg1));

}

void MainWindow::on_matriculeS_4_textChanged(const QString &arg1)
{
    ui->tablespon->setModel(S.recherchernom(arg1));

}






void MainWindow::on_PDFS_clicked()
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



//****************invite*************************************************
void MainWindow::on_ajouterI_clicked()
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


void MainWindow::on_daleteI_clicked()
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


void MainWindow::on_updateI_clicked()
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

void MainWindow::on_pdfI_clicked()
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





void MainWindow::on_pushButtonI_clicked()
{        ui->tableinvite->setModel(i.trie_cin());
}


//************************************************EMISSION**********************************


void MainWindow::on_pB_ajouter_clicked()
{
    int idemission=ui->lidemission->text().toInt();
   QString nom_emission=ui->lnom_emission->text();
     //QString nom_animateur=ui->lnom_animateur->text();
      int temps=ui->ltemps->text().toInt();
      int idinvite=ui->lidinvite->text().toInt();
      int jour=ui->ljour->text().toInt();
   Emission E(idemission,nom_emission,temps,idinvite,jour);

   bool test=E.ajouter();

     if(test)
   {
         ui->tab_emission->setModel(E.afficher());
      //   ui->tab_emission->setModel(E.tri());


       QMessageBox::information(nullptr, QObject::tr("database is open"),
                       QObject::tr("ajout successfully.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);}


       else
          { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                       QObject::tr("ajout failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);}

}
void MainWindow::on_detett_clicked()
{   Emission E;
    int idemission=ui->lineEdit_29->text().toInt();


     //QString nom_animateur=ui->lnom_animateur->text();


     bool test=E.detett(idemission)  ;
    QMessageBox msgBox;

    if (test)
    {

        ui->tab_emission->setModel(E.afficher());

       // ui->tab_emission->setModel(E.tri());

        QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Deleted successfully.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}


        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Delete failed \n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}

}


void MainWindow::on_modiferE_clicked()
{
    int idemission=ui->lidemission->text().toInt();
   QString nom_emission=ui->lnom_emission->text();
     //QString nom_animateur=ui->lnom_animateur->text();
      int temps=ui->ltemps->text().toInt();
      int idinvite=ui->lidinvite->text().toInt();
      int jour=ui->ljour->text().toInt();
    Emission E(idemission,nom_emission,temps,idinvite,jour);
    QMessageBox msgBox;

    if (E.modifer(idemission,nom_emission,temps,idinvite,jour))
    {          ui->tab_emission->setModel(E.afficher());
      //  ui->tab_emission->setModel(E.tri());

        QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("UPDATE successfully.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}


        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("UPDATE failed \n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}

}




void MainWindow::on_pdfE_clicked()
{

    QPdfWriter pdf("D:/2A/projet c++/Emission.pdf");

       QPainter painter(&pdf);
       int i = 4000;
              painter.setPen(Qt::blue);
              painter.setFont(QFont("Time New Roman", 25));
              painter.drawText(3000,1400,"Liste Des Emission");
              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 15));
              painter.drawRect(100,100,9400,2500);
              painter.drawRect(100,3000,9400,500);
              painter.setFont(QFont("Time New Roman", 9));
              painter.drawText(500,3300,"idemission");
              painter.drawText(2000,3300,"nom_emission");
              painter.drawText(3500,3300,"temps");
              painter.drawText(5000,3300,"idinvite");
              painter.drawText(6500,3300,"jour");

              painter.drawRect(100,3000,9400,9000);

              QSqlQuery query;
              query.prepare("select * from Emission");
              query.exec();
              while (query.next())
              {
                  painter.drawText(500,i,query.value(0).toString());
                  painter.drawText(2000,i,query.value(1).toString());
                  painter.drawText(3500,i,query.value(2).toString());
                  painter.drawText(5000,i,query.value(3).toString());
                  painter.drawText(6500,i,query.value(4).toString());
                 i = i + 350;
              }
              QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_rechercheE_clicked()
{
    int idemission=ui->lidemission1->text().toInt();
        QSqlQueryModel *verif=E.recherche(idemission);
                     if (verif!=nullptr)
                     {
                         ui->tab_chercher->setModel((verif));
                         QMessageBox::information(this, QObject::tr("recherche faire!"),
                         QObject::tr("recherche faire!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
           }
                     else

                         QMessageBox::information(this, QObject::tr("recherche faile!"),
                         QObject::tr("recherche faile!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_actionplay_clicked()
{
    player= new QMediaPlayer ;
    vw=new QVideoWidget;

    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");

    vw->setGeometry(100,100,300,400);

    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(filename));
    //player->setMedia(QUrl::fromLocalFile("/C:/Users/malek jendoubi/Downloads/video final.mp4"));
    vw->show();
    player->play();
}

void MainWindow::on_actionstop_clicked()
{ player->stop();
    vw->close();

}

void MainWindow::on_Lid_clicked()
{
     Emission E;

     QMessageBox msgBox;


          ui->tab_tri->setModel(E.tri());
    /* QMessageBox::information(nullptr, QObject::tr("database is open"),
                     QObject::tr("tri successfully.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);*/



}

void MainWindow::on_lduree1_clicked()
{
    Emission E;

    QMessageBox msgBox;

     ui->tab_tri->setModel(E.tri2());
     /*  QMessageBox::information(nullptr, QObject::tr("database is open"),
                       QObject::tr("tri successfully.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);*/
}





void MainWindow::on_ltriidinvite_clicked()
{
    Emission E;

    QMessageBox msgBox;

     ui->tab_tri->setModel(E.tri3());
  /*  QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("tri successfully.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);*/

}







//***********************************DECONEXION***********************************





void MainWindow::on_deconnexion_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_deconnexion_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_deconnexion_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_deconnexion_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_deconnexion_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_deconnexion_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
//****************************close//*************************
void MainWindow::on_quit_clicked()
{
    close();
}void MainWindow::on_quit_2_clicked()
{
    close();
}
void MainWindow::on_quit_3_clicked()
{
    close();
}
void MainWindow::on_quit_4_clicked()
{
    close();

}
void MainWindow::on_quit_5_clicked()
{
    close();
}
void MainWindow::on_quit_6_clicked()
{
    close();
}
//************************logistique*******************
void MainWindow::on_pb_ajouterL_clicked()
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

void MainWindow::on_pushButton_supprimerL_clicked()
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

void MainWindow::on_pushButton_updateL_clicked()
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



void MainWindow::on_pushButton_trieL_clicked()
{
    ui->tab_logistique->setModel(L.trie());

}

void MainWindow::on_pushButton_imprimerL_clicked()
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




//*********************Menu***************************************************

void MainWindow::on_finance_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_personels_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}void MainWindow::on_sponsors_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}void MainWindow::on_programme_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}void MainWindow::on_invitee_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}void MainWindow::on_logistique_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}



void MainWindow::on_quitterprincipale_clicked()
{
    close();
}
//************************mailing***////

void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("ines.gharbi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("ines.gharbi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("ines.gharbi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void  MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}


void MainWindow::on_login_button_3_clicked()
{
 close ();
}

void MainWindow::on_Mouvement_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);

}
void MainWindow::updatee_label()
{
    data=Ard.read_from_arduino();
ui->label_13->setText("Mouvement non détecté");
    if(data=="1")

      {

        ui->label_13->setText("Mouvement détecté !!"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher Mouvement détecté


    //QMessageBox::warning(this,"Détection du mouvement","Mouvement détecté !!");
    }

    //else if (data=="0")

}
