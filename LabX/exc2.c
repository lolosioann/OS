#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int fd[2];
    char msg[] = "Hello, World!\n";
    char buf[100];

    if (pipe(fd) < 0) {
        perror("Pipe failed\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("I am the child process\n");
        close(fd[1]);
        read(fd[0], buf, sizeof(buf));
        printf("Received message: %s", buf);
        close(fd[0]);
    } 
    else {
        printf("I am the parent process\n");
        close(fd[0]);
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }
    
    return 0;
}