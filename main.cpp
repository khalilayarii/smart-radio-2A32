#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QInputDialog>
#include <QFrame>
#include <QDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //debut config langue
        QTranslator T;
        QStringList langue;
        langue<<"English"<<"Francais";
        const QString languel=QInputDialog::getItem(NULL,"Langue","Selectionner langue",langue);
        if(languel=="English")
            T.load(":/english.qm");
        if(languel!="Francais")
                     a.installTranslator(&T);
                                //fin config langue
    Connection c;
    bool test=c.createconnect();
    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
