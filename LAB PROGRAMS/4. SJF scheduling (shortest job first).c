
#include <stdio.h>
int main() {
    int n,i,j,b[10],p[10],w[10],t[10],x;
    float aw=0,at=0;
    scanf("%d",&n);
    for(i=0;i<n;i++){scanf("%d",&b[i]);p[i]=i+1;}
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(b[i]>b[j]){
                x=b[i];b[i]=b[j];b[j]=x;
                x=p[i];p[i]=p[j];p[j]=x;
            }
    w[0]=0;
    for(i=1;i<n;i++) w[i]=w[i-1]+b[i-1];
    for(i=0;i<n;i++){
        t[i]=w[i]+b[i]; aw+=w[i]; at+=t[i];
        printf("P%d WT=%d TAT=%d\n",p[i],w[i],t[i]);
    }
    printf("Avg WT=%.2f\nAvg TAT=%.2f\n",aw/n,at/n);
    return 0;
}
