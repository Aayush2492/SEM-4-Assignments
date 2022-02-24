#include "Process.h"

Process::Process()
{
    this->waiting_time = 0;
}

Process::Process(int pid, int processing_time, int period, int repeats)
{
    this->pid = pid;
    this->processing_time = processing_time;
    this->period = period;
    this->repeats = repeats;
    this->waiting_time = 0;
}