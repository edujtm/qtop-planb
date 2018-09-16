#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    numCPU = std::thread::hardware_concurrency();

    ui->setupUi(this);
    ui->lineEditFilter->hide();



    createProgressBarLayout(numCPU);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Private slot que auxilia a gui a esconder a barra de filtragem/pesquisa
 */
void MainWindow::on_pushButtonFilter_clicked()
{
    ui->lineEditFilter->show();
}

/*
* Private slot que roda quando o usuario termina de digitar o filtro para
* os processos.
*/
void MainWindow::on_lineEditFilter_editingFinished()
{
    // TODO filtrar os processos pelo valor do lineEdit
    ui->lineEditFilter->hide();
}

/*
 * Cria o layout para as barras de usagem de cpu dinamicamente de acordo
 * com a quantidade de nucleos de cpu do computador
 */
void MainWindow::createProgressBarLayout(unsigned qnt) {
    for (unsigned i = 0; i < qnt; ++i) {
        QHBoxLayout * row = new QHBoxLayout;
        QLabel * cpuLabel = new QLabel(QString::number(i));
        QProgressBar * cpuProgressBar = new QProgressBar;

        cpuProgressBar->setValue(24);
        // CpuReader::queryCpuUsageValues();

        row->addWidget(cpuLabel);
        row->addWidget(cpuProgressBar);
        ui->vboxCpuUsage->addLayout(row);
    }
}
