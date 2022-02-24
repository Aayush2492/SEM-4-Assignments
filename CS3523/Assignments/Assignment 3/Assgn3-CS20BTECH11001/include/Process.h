#ifndef _PROCESS_H_
#define _PROCESS_H_
class Process
{
public:
    int pid;
    int processing_time;
    int period;
    int repeats;
    int waiting_time;

    Process();
    Process(int, int, int, int);
};
#endif