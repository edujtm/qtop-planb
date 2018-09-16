#include "processmanager.h"
#include <QtCore>
#include <QDebug>

/*
 * Namespace criado com o objetivo de fazer a leitura das informações dos processos
 * no sistema operacional. Os metodos que envolvem alterar informações dos processos
 * no sistema operacional e.g. kill, nice, etc. ficam aqui.
 */

namespace ProcessManager {

    const QString base = "/proc/";

    void readProcesses(const QString & filter) {
        QDir processDir(base);

        if (processDir.exists()) {
            QDirIterator it(processDir, QDirIterator::NoIteratorFlags);

            while (it.hasNext()) {
                // Busca apenas pelas pastas que representam process IDs
                QRegExp numeric("\\d+");
                if (numeric.exactMatch(it.fileName())) {
                    qDebug() << it.fileName();
                }
                it.next();
            }
        }
    }

    int getCpuPercentage(int coreno) {
        return 0;
    }

    void killProcess(int pid) {

    }
}
