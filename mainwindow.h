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

    void on_pushButton_update_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_trie_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButtonp_11_clicked();

    void on_pushButtonp_6_clicked();

    void on_comboBoxp_currentTextChanged(const QString &arg1);

    void on_pushButtonp_7_clicked();

    void on_tabWidget_tabBarClicked(int index);
void update_label();




private:
    Ui::MainWindow *ui;
 conge c;
    personels p ;
    Arduino Ard;
        QByteArray data;

};

#endif // MAINWINDOW_H
