#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include <QtWidgets>
#include <QtCore>
#include "helper/cpuwatcher.h"
#include "model/processinfo.h"
#include "helper/processmanager.h"

#define PROCESS_COLUMNS 1

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    unsigned numCPU;
    QTimer * updateTimer;
    CpuWatcher watcher;
    QList<QProgressBar*> bars;
    QList<ProcessInfo> processList;
    int selectedItem;
    QList<QString> header = {"CPU", "PID", "PPID", "CPU%", "MEM%", "TIME", "NAME"};

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonFilter_clicked();

    void on_lineEditFilter_editingFinished();

    void updateCpuUsage();

    void updateProcessList();

private:
    Ui::MainWindow *ui;

    void addRoot(const ProcessInfo & process);

    void createProgressBarLayout(unsigned qnt);
};

#endif // MAINWINDOW_H
