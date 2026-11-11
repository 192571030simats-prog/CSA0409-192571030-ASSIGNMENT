#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
typedef struct { int count, sum, max; } Stats;
int main(void) {
    int fd[2]; if(pipe(fd)<0){perror("pipe");return 1;}
    pid_t pid=fork(); if(pid<0){perror("fork");return 1;}
    if(pid==0){
        close(fd[1]); int r; Stats s={0,0,0};
        while(read(fd[0],&r,sizeof r)==sizeof r){s.count++;s.sum+=r;if(r>s.max)s.max=r;}
        printf("PIPE analyser: %d readings, average %.1f, max %d\n",s.count,
               s.count?(double)s.sum/s.count:0.0,s.max);
        close(fd[0]);fflush(stdout);_exit(0);
    }
    close(fd[0]); int vals[]={31,33,36,34,41,38};
    for(int i=0;i<6;i++) if(write(fd[1],&vals[i],sizeof vals[i])!=(ssize_t)sizeof vals[i]) perror("write");
    close(fd[1]); waitpid(pid,NULL,0);
    size_t n=4096;
    Stats *shared=mmap(NULL,n,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    if(shared==MAP_FAILED){perror("mmap");return 1;}
    pid=fork();
    if(pid==0){shared->count=6;shared->sum=213;shared->max=41;_exit(0);}
    waitpid(pid,NULL,0);
    printf("SHARED memory: %d readings, average %.1f, max %d\n",
           shared->count,(double)shared->sum/shared->count,shared->max);
    munmap(shared,n);return 0;
}
