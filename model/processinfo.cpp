#include "processinfo.h"

ProcessInfo::ProcessInfo()
{

}

long long ProcessInfo::getPid() const
{
    return pid;
}

void ProcessInfo::setPid(long long value)
{
    pid = value;
}

