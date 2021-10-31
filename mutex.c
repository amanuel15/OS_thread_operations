#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define NUM_THREADS 20

int common_variable = 0;

void *threadIncrement(void *arg){

    int x = common_variable ;
    printf("threadIncrement; current value %d\n",common_variable);
    x++;
    common_variable = x;

    pthread_exit(NULL);
}

void *threadDicrement(void *arg){

    int y = common_variable;
    printf("threadDicrement; current value %d\n",common_variable);
    y--;
    common_variable = y;

    pthread_exit(NULL);
}

int main(){

    pthread_t threads [NUM_THREADS];
    int rc, t;

    for(t=0; t < NUM_THREADS; t++){
        printf ("Creating thread %d\n", t);

        if(t%2==0){
            rc=pthread_create(&threads[t], NULL, threadDicrement, NULL );
        }
        else{
            rc=pthread_create(&threads[t], NULL, threadIncrement, NULL );
        }
    }

    for(t=0; t < NUM_THREADS; t++){
        pthread_join(threads[t], NULL);
    }

    printf("Main Thread; Final value %d\n",common_variable);

    pthread_exit(NULL);
}