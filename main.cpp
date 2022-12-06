
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;
    //QTranslator guitranslator;
    QStringList languages;
    languages << "Français" << "English" << "Spanish" << "العربية" <<"Chinese";
    QString lang = QInputDialog::getItem(NULL ,"Choisir Votre Language","Language",languages);
    if (lang == "English")
    {
        t.load(":/translate/english.qm");
    }
    else if (lang == "Spanish")
    {
        t.load(":/translate/spanish.qm");
    }
    else if (lang == "العربية")
    {
        t.load(":/translate/arabic.qm");
    }
    else if (lang == "Chinese")
    {
        t.load(":/translate/chinese.qm");
    }
    if (lang != "Français")
    {
        a.installTranslator(&t);
    }
    connection c;
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    w.show();
    return a.exec();
}
