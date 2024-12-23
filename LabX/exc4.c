#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FILENAME "process_ids.txt"

void write_pid_to_file(int fd, const char *process_type, pid_t pid) {
    // Lock the file
    if (flock(fd, LOCK_EX) == -1) {
        perror("Failed to lock file");
        exit(EXIT_FAILURE);
    }

    // Write process information
    dprintf(fd, "%s PID: %d\n", process_type, pid);

    // Unlock the file
    if (flock(fd, LOCK_UN) == -1) {
        perror("Failed to unlock file");
        exit(EXIT_FAILURE);
    }
}

int main() {
    pid_t pid;
    int fd;

    // Open the file
    fd = open(FILENAME, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        // Child process
        write_pid_to_file(fd, "Child", getpid());
        printf("Child wrote its PID to the file.\n");
        close(fd);
        exit(EXIT_SUCCESS);
    } 
    else {
        // Parent process
        // Wait for the child to finish
        wait(NULL);

        write_pid_to_file(fd, "Parent", getpid());
        printf("Parent wrote its PID to the file.\n");
        close(fd);
    }

    return 0;
}
