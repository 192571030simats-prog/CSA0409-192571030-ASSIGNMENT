#include <stdio.h>
int main(void){
 double videos=1200.0, gb=1.0, replicas=2.0;
 double raw=videos*gb, usable=raw*replicas;
 double users=200000.0, peak_fraction=0.10, bitrate_mbps=4.0;
 double peak=users*peak_fraction*bitrate_mbps;
 double server_count=20.0, per_server_mbps=5000.0;
 printf("Video catalogue: %.0f videos x %.1f GB = %.1f TB\n",videos,gb,raw);
 printf("With %.0f replicas: %.1f TB raw capacity\n",replicas,usable);
 printf("Peak concurrent viewers: %.0f\n",users*peak_fraction);
 printf("Peak delivery bandwidth: %.1f Gbit/s\n",peak/1000.0);
 printf("20 origin servers at 5 Gbit/s each: %.1f Gbit/s\n",server_count*per_server_mbps/1000.0);
 printf("Recommendation: SSD cache for hot first-week content; HDD/object store for archive; CDN for delivery.\n");
 return 0;
}
