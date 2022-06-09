#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>


void* char_print() {

    printf("Hello World!\n");
    printf("PID - %d\n",getpid());
    printf("TID - %d\n",pthread_self());


    pthread_exit(NULL);
}

int main () {

    pthread_t thread1_id;
    pthread_t thread2_id;
    char * return_thread;

    //primeiro thread
    pthread_create (&thread1_id, NULL, &char_print, NULL);

    //segundo thread
    pthread_create (&thread2_id, NULL, &char_print, NULL);

    /* Make sure the first thread has finished.  */
    pthread_join (thread1_id, (void *)&return_thread);

    /* Make sure the second thread has finished.  */
    pthread_join (thread2_id, (void *)&return_thread);

    /* Now we can safely return.  */
    return 0;
}