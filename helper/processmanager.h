#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QtCore>
#include <exception>
#include "model/processinfo.h"

namespace ProcessManager {

    QList<ProcessInfo> readProcesses(const QString & filter = nullptr);
    ProcessInfo createProcessInfo(const QString & pidpath);
    void parseStatusFile(const QString & pidpath, ProcessInfo & process);

    void killProcess(int pid);
}

#endif // PROCESSMANAGER_H
