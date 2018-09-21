#include "cpuwatcher.h"
#include <thread>

CpuWatcher::CpuWatcher()
{
    numCores = std::thread::hardware_concurrency();

    now = QList<CpuData>();
    previous = QList<CpuData>();

    // Inicializa o vetor com os tempos de memoria atuais
    for (unsigned i = 0; i <= numCores; ++i) {
        QString cpuline = readCpuLine(i);
        now.append(parseCpuUsage(cpuline));
        previous.append(CpuData());
    }

    // Faz outra leitura dos valores de memoria e passa os
    // valores de previous para now
    updateTimes();
}

/*
 * Utilizado para atualizar a porcentagem de uso da memoria
 * para o processador dado por cpuno. O valor 0 retorna o valor
 * de uso total da cpu, enquanto os valores de [1, numCores]
 * retornam o valor de uso de cada nucleo.
 *
 * Caso seja especificado um valor invalido, a funcao retorna -1.
 */
int CpuWatcher::getCpuUsage(unsigned cpuno) {
    if (cpuno > numCores) return -1;

    CpuData actualData = now[cpuno];
    CpuData previousData = previous[cpuno];

    unsigned prevIdle, prevNonIdle, prevTotal, idle, nonIdle, total, totald, idled;

    prevIdle = getIdleTime(previousData);
    idle = getIdleTime(actualData);

    prevNonIdle = getNonIdleTime(previousData);
    nonIdle = getNonIdleTime(actualData);

    prevTotal = prevIdle + prevNonIdle;
    total = idle + nonIdle;
    //qDebug() << "totals: " << total << " " << prevTotal;

    totald = total - prevTotal;
    idled = idle - prevIdle;

    unsigned div = (totald != 0 ? totald : 1);
    int result = static_cast<int>((100 * (totald - idled))/ div);

    return result;
}

/*
 * Recebe uma linha de texto do arquivo /proc/status que possui informações
 * da cpu. Retorna um objeto contendo as informações referentes ao uso da
 * cpu em seus diferentes estados.
 */
CpuWatcher::CpuData CpuWatcher::parseCpuUsage(QString cpuline) {
    QTextStream textLine(&cpuline);
    QString ignore;

    textLine >> ignore;

    CpuData result;
    for (int i = 0; i < result.NUM_CPU_STATES; ++i) {
        textLine >> result.times[i];
    }
    return result;
}

QString CpuWatcher::readCpuLine(unsigned cpuno) const {

    QFile cpuStatFile(FILE);
    if (!cpuStatFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Could not open file for reading cpu percentage";
    }

    const QString STR_CPU("cpu");
    const int LEN_STR_CPU = STR_CPU.size();

    QTextStream in(&cpuStatFile);
    QString cpuTotal = in.readLine();
    if (cpuno == 0) return cpuTotal;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith(STR_CPU)) {
               int coreno = line[LEN_STR_CPU].digitValue();
               if (coreno == -1) qDebug() << "Erro ao ler valor da cpu";

               // A linha corresponde às informações de cpuno
               if (coreno + 1 == cpuno) return line;
        }
    }
    return QString("");
}

unsigned CpuWatcher::getIdleTime(const CpuData & data) {
   unsigned long result = data.times[CpuIndex::IDLE] + data.times[CpuIndex::IOWAIT];
   return result;
}

unsigned CpuWatcher::getNonIdleTime(const CpuData & data) {
    QList<CpuIndex> indexes = {CpuIndex::USER, CpuIndex::NICE, CpuIndex::SYSTEM, CpuIndex::IRQ, CpuIndex::SOFTIRQ, CpuIndex::STEAL};
   unsigned result = 0;
   for (CpuIndex index : indexes) {
       result += data.times[index];
   }
   return result;
}

/*
 * Atualiza os valores de previous com os valores de now
 * e faz uma nova leitura na memória para obter valores em tempo real
 * do uso da memória.
 */
void CpuWatcher::updateTimes() {
    for (unsigned i = 0; i <= numCores; ++i) {
        for (int j = 0; j < 10; ++j) {
            previous[i].times[j] = now[i].times[j];
        }
        QString cpuline = readCpuLine(i);
        now[i] = parseCpuUsage(cpuline);
    }
}
