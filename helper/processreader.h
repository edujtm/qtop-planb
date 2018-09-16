#ifndef PROCESSREADER_H
#define PROCESSREADER_H

#include <QtCore>
#include "model/processinfo.h"

/*
 * Classe criada com o objetivo de fazer a leitura das informações dos processos
 * no sistema operacional. Os metodos que envolvem alterar informações dos processos
 * no sistema operacional e.g. kill, nice, etc. ficam aqui.
 */

class ProcessReader
{
public:
    ProcessReader();
    // QList<ProcessInfo> & readProcesses(const QString & filter = nullptr);
};

#endif // PROCESSREADER_H
