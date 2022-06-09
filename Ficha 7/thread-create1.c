
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


void* print (void* unused)
{
    int i;
    for(i=0;i<100000;i++) write(1,"#",1);
    return NULL;
}

/* The main program.  */

int main ()
{
    pthread_t thread_id;
    int i;
    
    /* Create a new thread.  The new thread will run the print_# function.  */
    pthread_create (&thread_id, NULL, &print, NULL);

    for(i=0;i<100000;i++) write(1,"_",1);
    
    pthread_join(thread_id,NULL);
    
    return 0;
}
