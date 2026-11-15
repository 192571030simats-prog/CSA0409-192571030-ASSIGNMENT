#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
static long long ns(struct timespec a,struct timespec b){return (b.tv_sec-a.tv_sec)*1000000000LL+b.tv_nsec-a.tv_nsec;}
int main(void){
    size_t n=4*1024*1024; volatile char *p=malloc(n); if(!p){perror("malloc");return 1;}
    long page=sysconf(_SC_PAGESIZE); struct timespec a,b; long long max=0;
    int locked=mlock((void*)p,n)==0; if(!locked)perror("mlock (continuing unlocked)");
    for(int r=0;r<100;r++){clock_gettime(CLOCK_MONOTONIC,&a);
        for(size_t i=0;i<n;i+=(size_t)page)p[i]++;
        clock_gettime(CLOCK_MONOTONIC,&b); long long d=ns(a,b);if(d>max)max=d;}
    printf("memory=%zu bytes locked=%s max_sweep_ns=%lld\n",n,locked?"yes":"no",max);
    if(locked)munlock((void*)p,n);free((void*)p);return 0;
}
