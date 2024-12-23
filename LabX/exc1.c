#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	pid_t pid[3];

	//create new processes
	for (int i = 0; i < 3; i++) {
		pid[i] = fork();
		if (pid[i] < 0) {
			perror("Fork failed\n");
			exit(EXIT_FAILURE);
		}
		else if (pid[i] == 0) {
			exit(0);
		}
		else if (pid[i] > 0) {
			printf("pid%d: %d\n", i + 1, pid[i]);
			wait(NULL);
		}
	}
}
