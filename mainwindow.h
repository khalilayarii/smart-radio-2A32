#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "sponsors.h"
#include <QMainWindow>
#include  <QPrinter>
#include  <QTextDocument>
#include <QFile>
#include <QFileDialog>
#include "arduino.h"

#include "statistique.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino

    void on_ajouter_clicked();

  //  void on_pushButton_2_clicked();

    void on_update_clicked();

    void on_delete_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_matricule_2_textChanged(const QString &arg1);

    void on_matricule_4_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_PDF_clicked();



    void on_STAT_clicked();

    void login_arduino();



private:
    Ui::MainWindow *ui;
    sponsors S;
    Arduino A;
    QByteArray alrt;
    QStringList files;
};
#endif // MAINWINDOW_H
