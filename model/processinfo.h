#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include <QtCore>

/*
 * Classe Criada para representar as informações relacionada a cada processo da cpu.
 *
*/

struct ProcessInfo
{ 
    long long pid;
    long long parentpid;
    int cpuNumber;
    int cpuPercentage;
    int memoryPercentage;
    long long timeAliveMs;
    QString name;

    ProcessInfo();
    ProcessInfo(long long pid, long long ppid, int cpuno, int cpuper, int memper, long long timealivems, QString name);

    //  ------- Acessors --------
    QString getTextCpuPercentage() const;
    QString getTextMemoryPercentage() const;
    QString getTextTimeAlive() const;
    QList<QString> getHeader() const;
private:
    QList<QString> header = {"CPU", "PID", "PPID", "CPU%", "MEM%", "TIME", "NAME"};
};

#endif // PROCESSINFO_H
