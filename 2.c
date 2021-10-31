#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 3

int SUM = 0;
int count = 0;
pthread_mutex_t lock;

void *sumThread(void *threadid) {

    pthread_mutex_lock(&lock);
    int x = SUM;


    int *id_ptr = (int *) threadid;

    int result = 0;
    for(int i = count; i <= count + 50; i++){
        result += i;
    }

    printf("\nSum = %d | thread: %d\n", result, *id_ptr);
    SUM += result;
    count += 50;
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}
int main( ) {
    pthread_mutex_init (&lock, NULL);

    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];
    int rc, t;
    for (t = 0; t < NUM_THREADS; t++) {
        taskids[t] = (int *) malloc(sizeof(int));
        *taskids[t] = t;
        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, sumThread, (void *) taskids[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    printf("Final SUM = %d\n", SUM);
    pthread_exit(NULL);
}