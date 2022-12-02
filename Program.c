#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h> 
#define SHARED 1
sem_t workerDone, calculating; // Semaphores
int data; // Buffer
int total, worker1sum, worker2sum;


void* WorkerThreadOne(void* threadid) {
    sem_wait(&calculating);
    FILE* inFile = fopen("data1.dat", "r");
    int total = 0;
    for(int k = 0; k < 500; k++){
        int lineNum = 0;
        fscanf(inFile, "%d\n", &lineNum);
        total += lineNum;
    }
    worker1sum = total;
    sem_post(&calculating);
    sem_post(&workerDone);
    pthread_exit(NULL);
}

void* WorkerThreadTwo(void* threadid){
    sem_wait(&calculating);
    FILE* inFile = fopen("data1.dat", "r");
    int total = 0;
    fseek(inFile, (5 * 500), SEEK_SET);
    for(int k = 500; k < 1001; k++){
        int lineNum = 0;
        fscanf(inFile, "%d\n", &lineNum);
        total += lineNum;
    }
    worker2sum = total;
    sem_post(&calculating);
    sem_post(&workerDone);
    pthread_exit(NULL);
}

void* ServerThread(){
    printf("server started\n");
    // Simulate starting threads
    printf("Server sends a start signal to the worker thread 1\n");
    printf("Server sends a start signal to the worker thread 2\n");

    //Get sum of threads
    sem_wait(&workerDone);
    printf("Server receives a completion signal from Worker thread 1\n Worker thread 1 result: %d\n", worker1sum);
    sem_wait(&workerDone);
    printf("Server receives a completion signal from Worker thread 2\n Worker thread 2 result: %d\n", worker2sum);

    printf("Datafile total: %d\n", (worker1sum + worker2sum));
    
    printf("server done\n");
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    // Create semeaphores
    sem_init(&calculating, SHARED, 1);
    sem_init(&workerDone, SHARED, 0); 

    pthread_t pid, cid1, cid2;  
    // Create threads
    pthread_create(&pid, NULL, ServerThread, NULL);
    pthread_create(&cid1, NULL, WorkerThreadOne, NULL);
    pthread_create(&cid2, NULL, WorkerThreadTwo, NULL);

    // Get thread results
    pthread_join(cid1, NULL);
    pthread_join(cid2, NULL);
    pthread_join(pid, NULL);
}