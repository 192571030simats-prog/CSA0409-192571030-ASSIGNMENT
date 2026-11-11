#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(void) {
    printf("Parent PID: %ld\n", (long)getpid());
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        printf("Child PID: %ld, PPID: %ld\n", (long)getpid(), (long)getppid());
        char path[128], buf[256];
        snprintf(path, sizeof path, "/proc/%ld/status", (long)getpid());
        FILE *f = fopen(path, "r");
        if (f) {
            while (fgets(buf, sizeof buf, f))
                if (!strncmp(buf, "Name:", 5) || !strncmp(buf, "State:", 6) ||
                    !strncmp(buf, "Pid:", 4) || !strncmp(buf, "PPid:", 5))
                    fputs(buf, stdout);
            fclose(f);
        }
        fflush(stdout);
        _exit(0);
    }
    printf("Parent created child PID: %ld\n", (long)pid);
    char cmd[128];
    snprintf(cmd, sizeof cmd, "ps -o pid,ppid,state,comm -p %ld", (long)pid);
    fflush(stdout);
    system(cmd);
    int status;
    waitpid(pid, &status, 0);
    printf("Child exit status: %d\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    return 0;
}
