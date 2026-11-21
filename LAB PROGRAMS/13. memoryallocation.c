
#include <stdio.h>
void run(int b[],int m,int p[],int n,int mode) {
    int a[10],i,j,k;
    for(i=0;i<m;i++) a[i]=b[i];
    for(i=0;i<n;i++) {
        k=-1;
        for(j=0;j<m;j++)
            if(a[j]>=p[i] && (k==-1 ||
              (mode==1 && a[j]<a[k]) ||
              (mode==2 && a[j]>a[k]))) k=j;
        if(k!=-1){a[k]-=p[i];printf("%d -> Block %d\n",p[i],k+1);}
        else printf("%d -> Not allocated\n",p[i]);
    }
}
int main() {
    int m,n,b[10],p[10],i;
    scanf("%d",&m);
    for(i=0;i<m;i++) scanf("%d",&b[i]);
    scanf("%d",&n);
    for(i=0;i<n;i++) scanf("%d",&p[i]);
    printf("First Fit:\n"); run(b,m,p,n,0);
    printf("Best Fit:\n"); run(b,m,p,n,1);
    printf("Worst Fit:\n"); run(b,m,p,n,2);
    return 0;
}
