
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint() {

    printf("Recebi um Ctrl + C\n");
}

int main() {

    struct sigaction sa_sigint;
    sa_sigint.sa_handler = &sigint;

    sigaction(SIGINT, &sa_sigint, NULL);
    while (1);
    return 0;
}