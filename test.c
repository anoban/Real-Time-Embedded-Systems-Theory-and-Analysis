#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  gcc test.c -Wall -O3 -g0 -lpthread -std=c2x -o test.exe

// seems like gcc version 12.2.0 (Debian 12.2.0-14) doesn't support C23 nullptr, yikes!
// we need gcc 13 for that, screw apt & debian :(

// create the function to be executed as a thread
void* thread(void* ptr) {
    const unsigned long long type    = (unsigned long long) ptr;
    int* const               randoms = malloc(1000 * sizeof(int));
    if (!randoms) return NULL; // C23
    srand(time(NULL));
    // we can of course sum the numbers w/o saving them in the array, but :p
    for (size_t i = 0; i < 1000; ++i) randoms[i] = rand();
    long long sum = 0;
    for (size_t i = 0; i < 1000; ++i) sum += randoms[i];
    fprintf(stdout, "Thread - %2lld, Sum - %10lld\n", type, sum);
    free(randoms);
    return ptr;
}

int main(void) {
    // create the thread objs
    pthread_t          thread1, thread2;
    unsigned long long thr1 = 1, thr2 = 2;
    // start the threads
    pthread_create(&thread1, NULL, *thread, (void*) thr1);
    pthread_create(&thread2, NULL, *thread, (void*) thr2);
    // wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}