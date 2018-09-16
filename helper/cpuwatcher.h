#ifndef CPUWATCHER_H
#define CPUWATCHER_H

#include <QtCore>

/*
 *  Classe responsável por obter em tempo real a quantidade de cpu utilizada em cada
 *  nucleo de cpu. Necessária para manter o estado anterior da cpu e com isso calcular
 *  a variação no uso da cpu
 */

/*
 * Indices para os tempos no vetor em CpuData::times
 */
enum CpuIndex {
    USER, NICE, SYSTEM, IDLE, IOWAIT, IRQ, SOFTIRQ, STEAL, GUEST, GUEST_NICE
};

class CpuWatcher
{

    const QString FILE = "/proc/stat";


    struct CpuData {
        const int NUM_CPU_STATES = 10;

        size_t times[10];
    };

    unsigned numCores;
    QList<CpuData> previous;
public:
    CpuWatcher();
    int getCpuUsage(unsigned cpuno);

private:
    CpuData parseCpuUsage(QString cpuline);
    QString readCpuLine(unsigned cpuno) const;
    unsigned getIdleTime(const CpuData & data);
    unsigned getNonIdleTime(const CpuData & data);
};

#endif // CPUWATCHER_H
