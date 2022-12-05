#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
    void on_pB_ajouter_clicked();
    void on_detett_clicked();
    void on_modifer_clicked();
    void on_pdf_clicked();
    void on_recherche_clicked();
    void on_actionplay_clicked();
    void on_actionstop_clicked();

    void on_Lid_clicked();

    void on_lduree1_clicked();

    void on_ltriidinvite_clicked();

    void on_statistique_clicked();

private:
    Ui::MainWindow *ui;
    Emission E;
    QMediaPlayer* player;
    QVideoWidget* vw;
};
#endif // MAINWINDOW_H
