#include <stdio.h>
// #include <threads.h>
#include "c11threads.h"
#include <stdatomic.h>

atomic_int acnt;
int cnt;

int f(void *thr_data)
{
    for (int n = 0; n < 1000; ++n)
    {
        ++cnt;
        ++acnt;
        // for this example, relaxed memory order is sufficient, e.g.
        atomic_fetch_add_explicit(&acnt, 1, memory_order_relaxed);
        atomic_fetch_add(&acnt, 1);
    }
    return 0;
}

int main(void)
{
    int n_threads = 3;
    thrd_t thr[n_threads];
    for (int n = 0; n < n_threads; ++n)
        thrd_create(&thr[n], f, NULL);
    for (int n = 0; n < n_threads; ++n)
        thrd_join(thr[n], NULL);

    printf("The atomic counter is %u\n", acnt);
    printf("The non-atomic counter is %u\n", cnt);
}

// Line 272 changed in c11threads.h