#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>

#include "Process.h"
#include "Event.h"

#define PUSH_HEAP(v, e, f) \
    v.push_back(e);        \
    push_heap(v.begin(), v.end(), f);
#define POP_HEAP(v, f)               \
    pop_heap(v.begin(), v.end(), f); \
    v.pop_back();
#define LIMIT 100
#define CONTEXT_SWITCH_TIME 0

bool is_rms;

using namespace std;

bool my_greater_func_at(const Event *a, const Event *b)
{
    return a->arrival_time > b->arrival_time;
}

bool my_greater_func_p(const Event *a, const Event *b)
{
    return a->get_priority(is_rms) < b->get_priority(is_rms);
}

int main(int argc, char **argv)
{
    char *inp_file_name;
    if (argc == 3)
    {
        inp_file_name = argv[2];
        string argv1 = argv[1];
        if (argv1 == "-rms")
        {
            is_rms = true;
        }
        else if (argv1 == "-edf")
        {
            is_rms = false;
        }
        else
        {
            cout << "Invalid argument. Use -rms or -edf" << endl;
            return 1;
        }
    }
    else
    {
        printf("Invalid number of arguments");
        return -1;
    }

    int n_proc;
    FILE *fp = fopen(inp_file_name, "r");
    char *op_file_name;
    if (is_rms)
        op_file_name = "RMS-Log.txt";
    else
        op_file_name = "EDF-Log.txt";

    FILE *f_writer = fopen(op_file_name, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fscanf(fp, "%d", &n_proc);
    Process p[n_proc];
    vector<Event *> events;
    for (int i = 0; i < n_proc; i++)
    {
        fscanf(fp, "%d,%d,%d,%d", &p[i].pid, &p[i].processing_time, &p[i].period, &p[i].repeats);
        p[i].processing_time *= 100;
        p[i].period *= 100;
        p[i].waiting_time = 0;
        fprintf(f_writer, "Process %d : Processing time = %d; Deadline = %d; Period = %d; Repeats: %d joined at time = 0\n", p[i].pid, p[i].processing_time, p[i].period, p[i].period, p[i].repeats);
        for (int j = 0; j < p[i].repeats; j++)
        {
            events.push_back(new Event(&p[i], p[i].period * j * 100, p[i].period * (j + 1) * 100));
        }
    }

    make_heap(events.begin(), events.end(), my_greater_func_at);
    Event *prev_executing = nullptr;
    vector<Event *> ready;
    int dead_miss = 0;
    bool flag = false;
    for (int i = 0; i <= LIMIT * 100 * 100 && (events.size() != 0 || ready.size() != 0 || prev_executing != nullptr); i += 100)
    {
        while (events.size() != 0 && events.front()->arrival_time <= i)
        {
            PUSH_HEAP(ready, events.front(), my_greater_func_p);
            POP_HEAP(events, my_greater_func_at);
        }

        if (ready.size() == 0 && prev_executing == nullptr && flag == false)
        {
            // For logging cpu wait
            flag = true;
        }
        if (prev_executing != nullptr)
        {
            // increasing cpu_time for successful execution
            prev_executing->cpu_time += 100;
        }

        if (prev_executing == nullptr)
        {
            // No process is currently executing so we pick out the front element from ready heap
            if (ready.size() != 0)
            {
                prev_executing = ready.front();
                POP_HEAP(ready, my_greater_func_p);
                if (i > prev_executing->deadline)
                {
                    i -= 100;
                    continue;
                }
                if (flag == true)
                {
                    flag = false;
                    fprintf(f_writer, "CPU waits until %d\n", i);
                }
                fprintf(f_writer, "At time %lf: Process %d starts execution\n", i / 100, prev_executing->p->pid);
                i += CONTEXT_SWITCH_TIME;
            }
        }
        else if (prev_executing->cpu_time >= prev_executing->p->processing_time)
        {
            // Event has successfully completion
            fprintf(f_writer, "At time %lf: Process %d completes execution\n", i / 100, prev_executing->p->pid);
            prev_executing->p->waiting_time += (i - prev_executing->arrival_time - prev_executing->p->processing_time);
            prev_executing = nullptr;
            i -= 100;
            i += CONTEXT_SWITCH_TIME;
        }
        else if (ready.size() != 0 && prev_executing->get_priority(is_rms) < ready.front()->get_priority(is_rms))
        {
            // Event has to be preempted
            int a = ((prev_executing->p->processing_time - prev_executing->cpu_time) % 5 == 0) ? prev_executing->p->processing_time - prev_executing->cpu_time : (prev_executing->p->processing_time - prev_executing->cpu_time - 1);
            fprintf(f_writer, "At time %lf: Process %d is preempted by process %d. Remaining processing time: %d\n", i / 100, prev_executing->p->pid, ready.front()->p->pid, a);
            Event *temp = prev_executing;
            PUSH_HEAP(ready, temp, my_greater_func_p);
            prev_executing->p->waiting_time += (i - prev_executing->arrival_time - prev_executing->cpu_time);
            prev_executing = nullptr;
            i -= 100;
            i += CONTEXT_SWITCH_TIME;
        }
        else
        {
            if (i >= prev_executing->deadline)
            {
                // Deadline miss case
                dead_miss++;
                fprintf(f_writer, "At time %lf: Process %d had missed its deadline at time %d\n", i / 100, prev_executing->p->pid, prev_executing->deadline);
                prev_executing->p->waiting_time += (prev_executing->deadline - prev_executing->arrival_time - prev_executing->cpu_time);
                prev_executing = nullptr;
                i -= 100;
                i += CONTEXT_SWITCH_TIME;
            }
            // Run for time t=i
        }
    }

    fclose(fp);
    fclose(f_writer);

    char *op2_file_name;
    if (is_rms)
        op2_file_name = "RMS-Stats.txt";
    else
        op2_file_name = "EDF-Stats.txt";

    FILE *f_writer2 = fopen(op2_file_name, "w");
    int tot_process = 0;
    for (int i = 0; i < n_proc; i++)
        tot_process += p[i].repeats;
    fprintf(f_writer2, "Total number of processes: %d\n", tot_process);
    fprintf(f_writer2, "Total number of deadline misses: %d\n", dead_miss);
    fprintf(f_writer2, "Total number of successful executions: %d\n", tot_process - dead_miss);
    int total_waiting_time = 0;
    for (int i = 0; i < n_proc; i++)
        total_waiting_time += p[i].waiting_time;
    fprintf(f_writer2, "Waiting time averaged over all process: %lf\n", (double)total_waiting_time / tot_process);
    printf("%lf,%d\n", (double)total_waiting_time / 140, dead_miss);
    fclose(f_writer2);
    return 0;
}
// g++ -w -I include/ *.cpp -o exec && ./exec -rms inp-params.txt && ./exec -edf inp-params.txt