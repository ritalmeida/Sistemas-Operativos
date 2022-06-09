// usage ./signal-threads main 1 3 -> main,1 and 3 threads blocking SIGALARM

//  The program will create 8 threads and set an alarm. You can control which threads block SIGALRM and which thread makes the call to alarm(2). Specifying a thread number (or "main" for the main thread) will cause that thread to block SIGALRM. Specifying "a[1-8]" will cause the specified thread to call alarm. By default, the main thread calls alarm. You can use this program to see which thread is delivered SIGALRM. Because Linux 2.4.x platforms use threads based on clone(2), results will differ from the other platforms. Linux 2.6.x platforms will behave more like the others (FreeBSD, Mac OS X, and Solaris).


#include<stdio.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define NTHR 4

sigset_t mask;
pthread_t tid[NTHR];
int block[NTHR];
int alarmthread;

void delay(int nsec){
    struct timespec ts;

    ts.tv_sec = nsec;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);
}

void handler(int signo){
    int i;
    pthread_t id;

    id = pthread_self();
    for (i = 0; i < NTHR; i++)
        if (tid[i] == id)
            break;
    if (i >= NTHR)
        printf("main thread: caught signal %d\n", signo);
    else
        printf("thread %d: caught signal %d\n", i+1, signo);
}

void * thr_fn(void *arg){
    long id;

    id = (long)arg;
    printf("thread %ld started...\n", id);
    
    // blocking the signal on the thread=id
    
    if (block[id-1] != 0) {
        printf("thread %ld blocking SIGALRM...\n", id);
        if (pthread_sigmask(SIG_BLOCK, &mask, NULL))
            printf("thread %ld: can't block SIGALRM", id);
    }
    
    //setting the alarm on the thread=id
    
    if (alarmthread == id) {
        printf("thread %ld: setting alarm...\n", id);
        alarm(5);
    }
    pause();
    printf("thread %ld: exiting\n", id);
    exit(id);
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    long i;
    int err, id;
    int doblock = 0;
    
    // setup a signal mask to catch SIGALRM
    
    setbuf(stdout, NULL);
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    
    // choosing the threads based on the command line arguments
    
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "main") == 0) {
            doblock = 1;
        } else if (argv[i][0] == 'a') {
            alarmthread = atoi(&argv[i][1]);
            if (alarmthread > NTHR || alarmthread < 1)
                printf("thread ID must be between 1 and %d\n", NTHR);
        } else {
            id = atoi(argv[i]);
            if (id > NTHR || id < 1)
                printf("thread ID must be between 1 and %d\n", NTHR);
            block[id-1] = 1;
        }
    }
    
    // Installing the handler in the process
    
    if (sigaction(SIGALRM, &act, NULL) < 0)
        printf("can't install signal handler");
    
    // Creating the threads
    
    for (i = 0; i < NTHR; i++) {
        err = pthread_create(&tid[i], NULL, thr_fn, (void *)(i+1));
        if (err != 0)
            printf("can't create thread");
    }
    
    // blocking the signal on the main thread
    
    if (doblock != 0) {
        printf("main thread blocking SIGALRM...\n");
        if (pthread_sigmask(SIG_BLOCK, &mask, NULL))
            printf("main thread: can't block SIGALRM");
    }
    
    //setting the alarm on the main thread
    
    if (alarmthread == 0) {
        printf("main thread: setting alarm...\n");
        alarm(5);
    }
    
    delay(10);
    printf("main thread: return from delay\n");
    exit(0);
}

