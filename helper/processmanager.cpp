#include "processmanager.h"
#include "thread"

#include <QtCore>
#include <QDebug>
#include <sys/types.h>
#include <signal.h>

/*
 * Namespace criado com o objetivo de fazer a leitura das informações dos processos
 * no sistema operacional. Os metodos que envolvem alterar informações dos processos
 * no sistema operacional e.g. kill, nice, etc. ficam aqui.
 */

namespace ProcessManager {

    const QString base = "/proc/";

    QList<ProcessInfo> readProcesses(const QString & filter) {
        QDir systemDir(base);
        QList<ProcessInfo> result;
        if (systemDir.exists()) {
            QDirIterator it(systemDir, QDirIterator::NoIteratorFlags);

            while (it.hasNext()) {
                // Busca apenas pelas pastas que representam process IDs
                QRegExp numeric("\\d+");
                if (numeric.exactMatch(it.fileName())) {
                    //qDebug() << it.fileName();

                    ProcessInfo process;
                    bool sucessful;
                    process.pid = it.fileName().toInt(&sucessful);
                    if (sucessful) {
                        result.append(process);
                    }
                    //qDebug() << it.filePath();
                    /*
                     ProcessInfo mProcess = createProcessInfo(it.filePath());

                    // Se houver erro, o processo não possuirá nome
                    //if (mProcess.name != "") {
                        result.append(mProcess);
                    }
                    */
                }
                it.next();
            }
        }
        return result;
    }

    ProcessInfo createProcessInfo(QString pidpath) {
        QDir processDir(pidpath);

        // Como as pastas são volateis, pode ser que o processo acabe antes desta instrução
        if (!processDir.exists()) return ProcessInfo();
        ProcessInfo result;

        parseStatusFile(pidpath, result);

        QDirIterator it(processDir, QDirIterator::NoIteratorFlags);
        // TODO iterar pelas pastas em /proc/$PID para encontrar as informações do processo
        while (it.hasNext()) {
            it.next();
        }

    }

    void parseStatusFile(const QString & pidpath, ProcessInfo & result) {
        QFile statusFile(pidpath + "/status");

        if (!statusFile.open(QFile::ReadOnly | QFile::Text)) return;

        QTextStream in(&statusFile);
        const QString NAME_STR("name");


        while(!in.atEnd()) {
            // TODO Parse pid status text stream
        }

    }

    void killProcess(int pid) {
        kill(pid, SIGKILL);
    }
}
