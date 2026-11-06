#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
static double elapsed(struct timespec a,struct timespec b){return (b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9;}
static void *worker(void *p){(void)p;return NULL;}
int main(void){const int N=1000;struct timespec a,b;int n=0;
clock_gettime(CLOCK_MONOTONIC,&a);
for(int i=0;i<N;i++){pid_t p=fork();if(p<0)break;if(p==0)_exit(0);if(waitpid(p,NULL,0)<0)break;n++;}
clock_gettime(CLOCK_MONOTONIC,&b);printf("Processes: %d; seconds: %.6f\\n",n,elapsed(a,b));
n=0;clock_gettime(CLOCK_MONOTONIC,&a);
for(int i=0;i<N;i++){pthread_t t;if(pthread_create(&t,NULL,worker,NULL)!=0)break;pthread_join(t,NULL);n++;}
clock_gettime(CLOCK_MONOTONIC,&b);printf("Threads: %d; seconds: %.6f\\n",n,elapsed(a,b));return 0;}
