#include "Event.h"

Event::Event(Process *p, int arrival_time, int deadline)
{
    this->p = p;
    this->arrival_time = arrival_time;
    this->deadline = deadline;
    // this->priority = 1.0 / this->p->period;
    this->cpu_time = 0;
}

double Event::get_priority(bool is_rms) const
{
    if (is_rms)
    {
        return 1.0 / this->p->period;
    }
    else // Earliest Deadline First
    {
        // Earliest deadline has highest priority
        return (1.0 / deadline);
    }
}