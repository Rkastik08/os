#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <conio.h>
int main() {
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // This block is executed by the child process
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        sleep(10);  // Child sleeps for a while
        printf("Child Process: PID = %d, Parent PID = %d (after sleep)\n", getpid(), getppid());
    } else {
        // This block is executed by the parent process
        printf("Parent Process: PID = %d, created Child PID = %d\n", getpid(), child_pid);
        exit(0);  // Parent exits immediately
    }
    getch(); 	
    return 0;
}
