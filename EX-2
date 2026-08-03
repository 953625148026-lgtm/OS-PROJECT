#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main()
{
    pid_t pid;
    int status;
 
    printf("Parent process: PID = %d\n", getpid());
 
    pid = fork();
 
    if (pid < 0) {
        /* fork failed */
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        /* Child process */
        printf("Child process: PID = %d, Parent PID = %d\n",
               getpid(), getppid());
        printf("Child is about to execute 'ls -l' using execlp()\n");
 
        execlp("ls", "ls", "-l", NULL);
 
        /* execlp only returns if it fails */
        perror("execlp failed");
        exit(1);
    }
    else {
        /* Parent process */
        printf("Parent waiting for child (PID = %d) to finish...\n", pid);
        wait(&status);
 
        if (WIFEXITED(status))
            printf("Child terminated normally with exit code %d\n",
                   WEXITSTATUS(status));
        else
            printf("Child terminated abnormally\n");
 
        printf("Parent process finished execution.\n");
    }
 
    return 0;
}
