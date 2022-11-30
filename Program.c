#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS	5

void* PrintHello(void* threadid)
{
    int m = *((int*)threadid);
    printf("\n%d: Hello World!\n", m);
    pthread_exit(NULL);
}

void* CalculateFirstHalf(void* threadid) {

}

int main(int argc, char* argv[])
{
    pthread_t threads[3];





    pthread_t threads[NUM_THREADS];
    int rc, t, i;
    int data[NUM_THREADS];
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %d\n", t);
        data[t] = t;
        rc = pthread_create(&threads[t], NULL, PrintHello, (void*)&data[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
    pthread_exit(NULL);
}