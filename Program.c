#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SHARED 1
sem_t empty, full;    /* the global semaphores */
int data;             /* shared buffer         */
int numIters;
int total;

void* CalculateFirstHalf(void* threadid) {
    FILE* inFile = fopen("data1.dat", "r");
    int total = 0;
    for(int k = 0; k < 500; k++){
        int lineNum = 0;
        fscanf(inFile, "%d\n", &lineNum);
        total += lineNum;
    }
    Producer(total);
    Consumer();
    pthread_exit(NULL);
}

void* CalculateSecondHalf(void* threadid){
    FILE* inFile = fopen("data1.dat", "r");
    int total = 0;
    for(int k = 500; k < 1001; k++){
        int lineNum = 0;
        fscanf(inFile, "%d\n", &lineNum);
        total += lineNum;
    }
    Producer(total);
    Consumer();
    pthread_exit(NULL);
}


void Producer(int calculated) {
    sem_wait(&empty);
    data = calculated;
    sem_post(&full);
}

void Consumer() {
    sem_wait(&full);
    total = total+data;
    sem_post(&empty);
}

int main(int argc, char* argv[])
{
    pthread_t pid, cid1, cid2;  
    pthread_create(&pid, NULL, NULL, NULL);
    printf("main started\n");
    sem_init(&empty, SHARED, 1);  /* sem empty = 1 */
    sem_init(&full, SHARED, 0);   /* sem full = 0  */

    printf("Server sends a start signal to the worker thread 1\n");
    pthread_create(&cid1, NULL, CalculateFirstHalf, NULL);
    printf("Server receives a completion signal from Worker thread 1\n Worker thread 1 result: %d\n", data);
    printf("Server sends a start signal to the worker thread 2\n");
    pthread_create(&cid2, NULL, CalculateSecondHalf, NULL);
    printf("Server receives a completion signal from Worker thread 1\n Worker thread 2 result: %d\n", data);
    pthread_join(pid, NULL);
    pthread_join(cid1, NULL);
    pthread_join(cid2, NULL)
    printf("main done\n");
}