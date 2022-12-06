#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "invite.h"
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
#include "arduino.h"

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
    void on_ajouter_clicked();

    void on_dalete_clicked();

    void on_update_clicked();

    void on_tri1_clicked();

    void on_tri2_clicked();

    void on_cinn_textChanged(const QString &arg1);

    void on_nomm_textChanged(const QString &arg1);

    void on_pdf_clicked();

    void on_stat_clicked();

 void affichageinvite(QString id);
 void on_pushButton_clicked();

 void on_tableinvite_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    invite i;
    Arduino A;
};
#endif // MAINWINDOW_H
