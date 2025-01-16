#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Réalité Virtuelle: TP7 Courrege");
    w.show();
    return a.exec();
}
