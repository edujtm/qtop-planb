#include "controller/mainwindow.h"
#include <QApplication>
#include "helper/processmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ProcessManager::readProcesses();

    return a.exec();
}
