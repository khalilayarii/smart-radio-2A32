#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <logistique.h>

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

private:
    Ui::MainWindow *ui;
    Logistique L;
};

#endif // MAINWINDOW_H
