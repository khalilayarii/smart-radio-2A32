#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <finance.h>
#include <exportexcelobject.h>
#include <QAbstractButton>
#include <QKeyEvent>
#include "calculatrice.h"
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

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_trie_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_excel_clicked();
     void on_pushButton_6_clicked();



private:
    Ui::MainWindow *ui;

    Finance f;


    calculatrice *c;

};

#endif // MAINWINDOW_H
