#ifndef _EVENT_H_
#define _EVENT_H_

#include "Process.h"

class Event
{
public:
    Process *p;
    int arrival_time;
    int deadline;
    // double priority;
    int cpu_time;

    Event(Process *, int, int);
    double get_priority(bool) const;
};
#endif