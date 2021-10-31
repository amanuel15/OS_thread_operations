#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
/* This is the initial thread routine */
void* compute_thread (void*);
/* This is the lock for thread synchronization */
pthread_mutex_t my_sync;
/* This is the condition variable */
pthread_cond_t rx;
#define TRUE 1
#define FALSE 0
/* this is the Boolean predicate */
int thread_done = FALSE;
void main(){
    pthread_t tid;
    pthread_attr_t attr;
    char hello[ ] = {"Hello, "};
    char thread[ ] = {"thread"};
/* Initialize the thread attributes */
    pthread_attr_init (&attr);
/* Initialize the mutex (default attributes) */
    pthread_mutex_init (&my_sync, NULL);
/* Initialize the condition variable (default attr) */
    pthread_cond_init (&rx, NULL);
/* Create another thread. ID is returned in &tid */
/* The last parameter is passed to the thread function
*/
    pthread_create(&tid, &attr, compute_thread, hello);
/* wait until the thread does its work */
    pthread_mutex_lock(&my_sync);
    while (!thread_done)
        pthread_cond_wait(&rx, &my_sync);
/* When we get here, the thread has been executed */
    printf(thread);
    printf("\n");
    pthread_mutex_unlock(&my_sync);
    exit(0);

}
void* compute_thread(void* msg){
/* Lock the mutex - the cond_wait has unlocked it */
    pthread_mutex_lock (&my_sync);
    printf(msg);
/* set the predicate and signal the other thread */
    thread_done = TRUE;
    pthread_cond_signal (&rx);
    pthread_mutex_unlock (&my_sync);
}