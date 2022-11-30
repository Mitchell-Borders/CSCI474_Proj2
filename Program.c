#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS	3

void* CalculateFirstHalf(void* threadid) {
    FILE* inFile = fopen("data1.dat", "r");
    int total = 0;
    for(int k = 0; k < 500; k++){
        int lineNum = 0;
        fscanf(inFile, "%d\n", &lineNum);
        total += lineNum;
    }
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
    pthread_exit(NULL);
}

void* CalculateDataFile(void* threadid){
    pthread_t workerThreads[2];
    
    pthread_create(&workerThreads[0], NULL, CalculateFirstHalf, NULL);
    pthread_create(&workerThreads[1], NULL, CalculateSecondHalf, NULL);

    pthread_join(workerThreads[0], NULL);
    pthread_join(workerThreads[1], NULL);

    pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
    pthread_t serverThread[1];

    pthread_create(&serverThread[0], NULL, CalculateDataFile, NULL);

    pthread_join(serverThread[0], NULL);
    pthread_exit(NULL);
}