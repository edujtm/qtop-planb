#include "controller/mainwindow.h"
#include <QApplication>
#include "helper/cpuwatcher.h"
#include "helper/processmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
