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

    void on_pushButton_trie_clicked();

    void on_pushButton_imprimer_clicked();


    void on_le_recherche_textChanged(const QString &arg1);

   // void on_pushButton_clicked();

   // void on_pushButton_trieprix_clicked();

  //  void on_pushButton_triequantite_clicked();

   // void on_pushButton_trieprix_clicked(bool checked);

    //void on_pushButton_trieprix_pressed();

void on_alerte_clicked();

    void on_stat_clicked();

    void on_excel_clicked();

private:
    Ui::MainWindow *ui;
    Logistique L;
};

#endif // MAINWINDOW_H
