#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QtCore>

namespace ProcessManager {

    void readProcesses(const QString & filter = nullptr);
    int getCpuPercentage(int coreno);
    void killProcess(int pid);
}

#endif // PROCESSMANAGER_H
