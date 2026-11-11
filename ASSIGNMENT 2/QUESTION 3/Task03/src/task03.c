#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define CAMERAS 64
#define FRAMES 12000
static long results[CAMERAS];
static int next_camera=0;
static pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
static void *worker(void *arg) {
    (void)arg;
    for (;;) {
        pthread_mutex_lock(&lock);
        int c=next_camera++;
        pthread_mutex_unlock(&lock);
        if(c>=CAMERAS) break;
        unsigned long x=(unsigned long)(c+1);
        for(int i=0;i<FRAMES;i++) { x=(x*1103515245u+12345u)&0x7fffffff; }
        results[c]=(long)(x%100000);
    }
    return NULL;
}
int main(void) {
    int pools[]={1,4,8,16};
    for(int k=0;k<4;k++) {
        next_camera=0;
        for(int i=0;i<CAMERAS;i++) results[i]=0;
        pthread_t t[16];
        struct timespec a,b;
        clock_gettime(CLOCK_MONOTONIC,&a);
        for(int i=0;i<pools[k];i++) if(pthread_create(&t[i],NULL,worker,NULL)!=0){perror("pthread_create");return 1;}
        for(int i=0;i<pools[k];i++) pthread_join(t[i],NULL);
        clock_gettime(CLOCK_MONOTONIC,&b);
        double sec=(b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9;
        long checksum=0;for(int i=0;i<CAMERAS;i++) checksum+=results[i];
        printf("Pool %2d threads: %.6f seconds, checksum=%ld\n",pools[k],sec,checksum);
    }
    return 0;
}
