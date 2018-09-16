#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include <QtWidgets>
#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    unsigned numCPU;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonFilter_clicked();

    void on_lineEditFilter_editingFinished();

private:
    Ui::MainWindow *ui;

    void createProgressBarLayout(unsigned qnt);
};

#endif // MAINWINDOW_H
