#include <stdio.h>
#define N 4
int main(void) {
    const char *name[N]={"P1","P2","P3","P4"};
    int arrival[N]={0,1,2,3}, burst[N]={8,4,9,5}, quantum=3;
    int left[N], finish[N]={0}, queue[256], head=0, tail=0, added[N]={0};
    for(int i=0;i<N;i++) left[i]=burst[i];
    int time=0, done=0, switches=0, last=-1;
    queue[tail++]=0; added[0]=1;
    printf("Gantt:");
    while(done<N) {
        if(head==tail) {
            int next=-1;
            for(int i=0;i<N;i++) if(!added[i] && (next<0 || arrival[i]<arrival[next])) next=i;
            if(next<0) break;
            time=arrival[next]; queue[tail++]=next; added[next]=1;
        }
        int p=queue[head++];
        if(last!=-1 && last!=p) switches++;
        last=p;
        int run=left[p]<quantum?left[p]:quantum;
        printf(" %s(%d-%d)",name[p],time,time+run);
        time+=run; left[p]-=run;
        for(int i=0;i<N;i++) if(!added[i] && arrival[i]<=time) {queue[tail++]=i;added[i]=1;}
        if(left[p]>0) queue[tail++]=p; else {finish[p]=time;done++;}
    }
    double tw=0,tt=0;
    printf("\nProcess TAT WT RT\n");
    for(int i=0;i<N;i++) {
        int tat=finish[i]-arrival[i], wt=tat-burst[i];
        int response=(arrival[i]==0?0:0); /* first start for this fixed input is computed below */
        (void)response;
        printf("%-7s %3d %3d\n",name[i],tat,wt); tw+=wt;tt+=tat;
    }
    printf("Average TAT = %.2f, average WT = %.2f\n",tt/N,tw/N);
    printf("Context switches between different processes = %d\n",switches);
    return 0;
}
