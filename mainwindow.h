#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "conge.h"
#include "arduino.h"
#include <QMainWindow>
#include <personels.h>
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
#include <QMainWindow>
#include <finance.h>
#include <exportexcelobject.h>
#include <QAbstractButton>
#include <QKeyEvent>
#include "calculatrice.h"
#include "sponsors.h"
#include <QMainWindow>
#include  <QPrinter>
#include  <QTextDocument>
#include "invite.h"
//***********
#include <QMainWindow>
#include <QIntValidator>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <QtPrintSupport/QPrintDialog>
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
//********************
#include "emission.h"
#include <QMainWindow>
#include <QTextStream>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
//*******************
#include "logistique.h"
//*********************************
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pushButton_supprimer_clicked();
    void on_login_button_clicked();

    void on_pushButton_update_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_trie_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButtonp_11_clicked();

    void on_pushButtonp_6_clicked();

    void on_comboBoxp_currentTextChanged(const QString &arg1);

    void on_pushButtonp_7_clicked();

    void on_tabWidget_tabBarClicked(int index);
void update_label();
//************************************finance************************
void on_pb_ajouterF_clicked();
void on_pushButton_supprimerF_clicked();
void on_pushButton_updateF_clicked();
void on_pdf1_clicked();

void on_pushButton_trieF_clicked();
void on_lineEdit_textChangedF(const QString &arg1);
void on_excel_clicked();
void on_calculatrice_2_clicked();

//**************************************sponsors****************************
void on_ajouterS_clicked();

void on_updateS_clicked();

void on_deleteS_2_clicked();

void on_pushButtonS_clicked();

void on_pushButtonS_2_clicked();

void on_matriculeS_2_textChanged(const QString &arg1);

void on_matriculeS_4_textChanged(const QString &arg1);


void on_PDFS_clicked();
//*********************************I*************************
void on_ajouterI_clicked();

void on_daleteI_clicked();

void on_updateI_clicked();

void on_tri1_clicked();

void on_tri2_clicked();

void on_cinn_textChanged(const QString &arg1);
void on_nomm_textChanged(const QString &arg1);
void on_pdfI_clicked();
void on_pushButtonI_clicked();
//****************************emission*************************

void on_pB_ajouter_clicked();
void on_detett_clicked();
void on_modiferE_clicked();
void on_pdfE_clicked();
void on_rechercheE_clicked();
void on_actionplay_clicked();
void on_actionstop_clicked();

void on_Lid_clicked();

void on_lduree1_clicked();

void on_ltriidinvite_clicked();

//***************DECONX/***************
void on_deconnexion_clicked();
void on_deconnexion_2_clicked();
void on_deconnexion_3_clicked();
void on_deconnexion_4_clicked();
void on_deconnexion_5_clicked();
void on_deconnexion_6_clicked();
//****************************************
void on_quit_clicked();
void on_quit_2_clicked();
void on_quit_3_clicked();
void on_quit_4_clicked();
void on_quit_5_clicked();
void on_quit_6_clicked();



//********************************
void on_pb_ajouterL_clicked();

void on_pushButton_supprimerL_clicked();

void on_pushButton_updateL_clicked();

void on_pushButton_trieL_clicked();

void on_pushButton_imprimerL_clicked();
void on_le_recherche_textChanged(const QString &arg1);
void on_alerte_clicked();
//*************************************************

void on_finance_clicked();
void on_personels_clicked();
void on_sponsors_clicked();
void on_programme_clicked();
void on_invitee_clicked();
void on_logistique_clicked();



void on_quitterprincipale_clicked();
//**************

void sendMail();
void mailSent(QString status);
void browse();


void on_login_button_3_clicked();

void on_Mouvement_clicked();
void updatee_label();


private:
    Ui::MainWindow *ui;
 conge co;
    personels p ;
    Arduino Ard;
        QByteArray data;
//**********************f******************
        Finance f;
      calculatrice *c;
      //******************************
      sponsors S;

//****************************************
      invite i;
//*************************************
      Logistique L;

      QStringList files;

      Emission E;
      QMediaPlayer* player;
      QVideoWidget* vw;
};

#endif // MAINWINDOW_H
