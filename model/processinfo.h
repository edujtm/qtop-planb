#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include <QtCore>

/*
 * Classe Criada para representar as informações relacionada a cada processo da cpu.
 *
*/

class ProcessInfo
{
    QList<QString> header = {"CPU", "PID", "PPID", "CPU%", "MEM%", "TIME", "NAME"};
    long long pid;
    long long parentpid;
    int cpuNumber;
    int cpuPercentage;
    int memoryPercentage;
    int timeAlive;
    QString name;
public:
    ProcessInfo();

    //  ------- Acessors --------
    QList<QPair<QString, QString>> & getAllProcessInfo() const;
    QString & getTextPid() const;
    QString & getTextPPid() const;
    QString & getTextCpuNumber() const;
    QString & getTextCpuPercentage() const;
    QString & getTextMemoryPercentage() const;
    QString & getTextTimeAlive() const;
    QString & getName() const;

    long long getPid() const;

    // ------ Mutators --------
    void setPid(long long value);
};

#endif // PROCESSINFO_H
