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
        int NUM_CPU_STATES;

        size_t times[10];

        CpuData() : NUM_CPU_STATES(10) {}

        bool operator==(const CpuData & other) const {
            for (int i = 0; i < NUM_CPU_STATES; ++i) {
                if (times[i] != other.times[i]) return false;
            }
            return true;
        }
    };

    unsigned numCores;
    QList<CpuData> previous;
    QList<CpuData> now;
    QTimer * updateTimer;

public:
    CpuWatcher();
    int getCpuUsage(unsigned cpuno);
    void updateTimes();

private:
    CpuData parseCpuUsage(QString cpuline);
    QString readCpuLine(unsigned cpuno) const;
    unsigned getIdleTime(const CpuData & data);
    unsigned getNonIdleTime(const CpuData & data);
};

#endif // CPUWATCHER_H
