#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <conio.h>
int main() {
clrscr();
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
        printf("Child Process: PID = %d\n", getpid());
        exit(0);  // Child exits immediately
    } else {
        // This block is executed by the parent process
        printf("Parent Process: PID = %d\n", getpid());
        printf("Created Child Process: PID = %d\n", child_pid);
        
        // Sleep for 10 seconds to allow the child to become a zombie
        printf("Parent sleeping for 10 seconds...\n");
        sleep(10);

        // Now we can clean up the child process (reap it)
        int status;
        waitpid(child_pid, &status, 0);
        printf("Child Process reaped, exited with status %d.\n", WEXITSTATUS(status));
    }
    getch();	
    return 0;
}
