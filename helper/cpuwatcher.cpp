#include "cpuwatcher.h"
#include <thread>

CpuWatcher::CpuWatcher()
{
    unsigned numCpu = std::thread::hardware_concurrency();

    previous = QList<CpuData>();

    for (unsigned i = 0; i <= numCpu; ++i) {
        QString cpuline = readCpuLine(i);
        previous.append(parseCpuUsage(cpuline));
    }
}

int CpuWatcher::getCpuUsage(unsigned cpuno) {
    if (cpuno > numCores) return -1;

    QString cpuTotal = readCpuLine(cpuno);
    CpuData now = parseCpuUsage(cpuTotal);
    CpuData previousData = previous[cpuno];

    unsigned prevIdle, prevNonIdle, prevTotal, idle, nonIdle, total, totald, idled;

    prevIdle = getIdleTime(previousData);
    idle = getIdleTime(now);

    prevNonIdle = getNonIdleTime(previousData);
    nonIdle = getNonIdleTime(now);

    prevTotal = prevIdle + prevNonIdle;
    total = idle + nonIdle;

    totald = total - prevTotal;
    idled = idle - prevIdle;

    int result = static_cast<int>(100 * ((totald - idled)/ totald));
    return result;
}


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
   return data.times[CpuIndex::IDLE] + data.times[CpuIndex::IOWAIT];
}

unsigned CpuWatcher::getNonIdleTime(const CpuData & data) {
    QList<CpuIndex> indexes = {CpuIndex::USER, CpuIndex::NICE, CpuIndex::SYSTEM, CpuIndex::IRQ, CpuIndex::SOFTIRQ, CpuIndex::STEAL};
   unsigned result = 0;
   for (CpuIndex index : indexes) {
       result += data.times[index];
   }
   return result;
}
