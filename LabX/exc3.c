#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("I am the child process\n");
        pause();
    } 
    else {
        printf("I am the parent process\n");
        sleep(1);
        kill(pid, SIGKILL);
    }
    
    return 0;
}