#include <atomic>
#include <pthread.h>
#include <stdio.h>
#include <string>

int k = 4;
int type;
std::atomic<int> var(0);
std::atomic<int> control_var(0);
std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
// control_var is used as control in this experiment. We will increment control_var using
// inbuilt atomic increment function and compare it with increment by compare and swap.

typedef struct params
{
    int id;
} params;

void *testCS(void *parameters)
{
    int t_id = ((params *)parameters)->id;
    for (int i = 0; i < k; i++)
    {
        // Incrementing control_var using inbuilt atomic increment function
        control_var.fetch_add(1);

        if (type == 1)
        {
            // compare and swap: increment var by 1 using compare and swap
            int temp;
            do
            {
                temp = var.load();
            } while (!var.compare_exchange_strong(temp, temp + 1));
        }
        else if (type == 2)
        {
            while (lock_stream.test_and_set())
                ; // spin
            var += 1;
            lock_stream.clear();
        }
        else if (type == 3)
        {
        }
    }
    return nullptr;
}

int main()
{
    int n_threads = 4;
    type = 1;
    pthread_t tids[n_threads];

    for (int i = 0; i < n_threads; i++)
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr); // Load with default attributes
        params *p = new params();
        p->id = i + 1;
        pthread_create(&tids[i], &attr, testCS, (void *)p);
    }

    // waiting for all threads to finish
    for (int i = 0; i < n_threads; i++)
    {
        pthread_join(tids[i], NULL);
    }
    printf("Ans: %d %d\n", control_var.load(), var.load());
    return 0;
}

// g++ -std=c++11 -pthread main.cpp -o main && ./main