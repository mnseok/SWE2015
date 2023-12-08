#include <stdio.h>
#include <stdlib.h>
#include "customer_heap.c"
#include "counter_queue.c"
#include "time.h"

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    CustomerPriorityQueue *customerQueue = initCustomerPriorityQueue(n);
    CounterPriorityQueue *counterQueue = initCounterPriorityQueue(k);

    clock_t s_time = clock();    
    int id, t;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &id, &t);
        Counter c = counter_dequeue(counterQueue);
        c.time += t;
        customer_enqueue(customerQueue, id, c.time, c.id);
        counter_enqueue(counterQueue, c.time, c.id);
    }

    for (int i = 1; i < n+1; i++) {
        customer_dequeue(customerQueue);
    }
    
    clock_t e_time = clock();
    printf("%f\n", (double)(e_time - s_time) / CLOCKS_PER_SEC);
    return 0;
}