#include <stdio.h>
#include <unistd.h>

int main(){
    printf("The real user ID of the calling process is %d\n", (int) getuid());
    printf("The real group ID of the calling process is %d\n", (int) getgid());
    return 0;
}