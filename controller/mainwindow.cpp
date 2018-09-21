#include "mainwindow.h"
#include "ui_mainwindow.h"

//  ------- CONSTRUCTORS --------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    numCPU = std::thread::hardware_concurrency();
    processList = ProcessManager::readProcesses();

    ui->setupUi(this);
    ui->lineEditFilter->hide();
    ui->treeWidgetProcessView->setColumnCount(PROCESS_COLUMNS);
    ui->treeWidgetProcessView->setHeaderLabel(header[1]);

    createProgressBarLayout(numCPU);

    updateCpuUsage();

    updateTimer = new QTimer;
    updateTimer->setInterval(3000);
    updateTimer->start();

    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateCpuUsage()));
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateProcessList()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//  -------- HELPERS -------

/*
 * Cria o layout para as barras de usagem de cpu dinamicamente de acordo
 * com a quantidade de nucleos de cpu do computador
 */
void MainWindow::createProgressBarLayout(unsigned qnt) {
    for (unsigned i = 0; i < qnt; ++i) {
        QHBoxLayout * row = new QHBoxLayout;
        QLabel * cpuLabel = new QLabel("CPU " + QString::number(i+1));
        QProgressBar * cpuProgressBar = new QProgressBar;
        bars.append(cpuProgressBar);

        cpuProgressBar->setObjectName("CpuProgress" + QString::number(i+1));

        cpuProgressBar->setValue(24);

        row->addWidget(cpuLabel);
        row->addWidget(cpuProgressBar);
        ui->vboxCpuUsage->addLayout(row);
    }
}

void MainWindow::addRoot(const ProcessInfo & process) {
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidgetProcessView);
    item->setText(0, QString::number(process.pid));
    ui->treeWidgetProcessView->addTopLevelItem(item);
}


// -------- SLOTS --------


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
 * Atualiza as barra de progresso que representam o uso de memória pela cpu
 */
void MainWindow::updateCpuUsage() {
    watcher.updateTimes();
    for (unsigned i = 1; i <= numCPU; ++i) {
        int perc = watcher.getCpuUsage(i);
        bars[i-1]->setValue(perc);
        qDebug() << "teste";
    }
}

void MainWindow::updateProcessList() {

    QModelIndex itemIdx = ui->treeWidgetProcessView->currentIndex();
    // Trying to avoid nullptr for itemIdx after clearing treeWidgetProcessView
    QPair<int, int> pos;
    if (itemIdx.isValid()) {
        pos.first = itemIdx.row();
        pos.second = itemIdx.column();
    } else {
        pos.first = 0;
        pos.second = 0;
    }

    qDebug() << itemIdx.isValid();

    processList = ProcessManager::readProcesses();
    ui->treeWidgetProcessView->clear();
    for (ProcessInfo process : processList) {
        addRoot(process);
    }

    // The operating system will probably have at least one process running,
    // placed this line here just for ease of mind
    if (ui->treeWidgetProcessView->topLevelItemCount() == 0) return;

    // Keeps the selected item in place after treeWidgetProcessView is cleared
    // If the process list shrinks by having a process terminated, the last process
    // is the one selected
    if (pos.first > processList.size()) {
        int lastIdx = ui->treeWidgetProcessView->topLevelItemCount() - 1;
        QTreeWidgetItem * lastItem = ui->treeWidgetProcessView->topLevelItem(lastIdx);
        ui->treeWidgetProcessView->setCurrentItem(lastItem);
    } else {
        // The selected item jumps to the item above or below when the list changes
        // above if the terminated process has lower PID and vice-versa. Need to fix
        // that
        QTreeWidgetItem * selectedItem = ui->treeWidgetProcessView->topLevelItem(pos.first);
        ui->treeWidgetProcessView->setCurrentItem(selectedItem);
    }
}
