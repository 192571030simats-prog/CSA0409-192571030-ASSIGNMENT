#include <stdio.h>
typedef struct { unsigned base, limit; } Segment;
int main(void) {
    Segment s[]={{1000,500},{4000,1200},{8000,300}};
    unsigned seg[]={0,1,2,1,0,2,1,0}, off[]={0,100,299,1200,499,300,700,250};
    for(int i=0;i<8;i++){
        if(seg[i]>=3 || off[i]>=s[seg[i]].limit)
            printf("(%u,%u) -> segmentation fault (limit violation)\n",seg[i],off[i]);
        else printf("(%u,%u) -> physical %u\n",seg[i],off[i],s[seg[i]].base+off[i]);
    }
    return 0;
}
