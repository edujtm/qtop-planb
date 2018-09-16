#include "processinfo.h"

ProcessInfo::ProcessInfo() { }

ProcessInfo::ProcessInfo(long long pid, long long ppid, int cpuno, int cpuper, int memper, long long timealivems, QString name)
    : pid{pid}, parentpid{ppid}, cpuNumber{cpuno}, cpuPercentage{cpuper}, memoryPercentage{memper},
    timeAliveMs{timealivems}, name{name} { }

QString ProcessInfo::getTextCpuPercentage() const {
    double perc = cpuPercentage / 100.0;
    return QString::number(perc, 'g', 2);
}

QString ProcessInfo::getTextMemoryPercentage() const {
    double perc = memoryPercentage / 100.0;
    return QString::number(perc, 'g', 2);
}

QString ProcessInfo::getTextTimeAlive() const {
    long long seconds, minutes, hours;
    int restSeconds, restMinutes;

    seconds = timeAliveMs / 1000;
    minutes = seconds / 60;
    hours = minutes / 60;

    restSeconds = seconds % 60;
    restMinutes = minutes % 60;

    QString result = QString::number(hours) + ":" + QString::number(restMinutes) + ":" + QString::number(restSeconds);
    return result;
}

QList<QString> ProcessInfo::getHeader() const {
    return header;
}
