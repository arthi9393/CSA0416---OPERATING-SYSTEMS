
#include <stdio.h>
int main() {
    int n,m,i,j,k,alloc[10][10],max[10][10];
    int avail[10],need[10][10],finish[10]={0},safe[10],c=0,ok;
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++)
        for(j=0;j<m;j++) scanf("%d",&alloc[i][j]);
    for(i=0;i<n;i++)
        for(j=0;j<m;j++) scanf("%d",&max[i][j]);
    for(j=0;j<m;j++) scanf("%d",&avail[j]);
    for(i=0;i<n;i++)
        for(j=0;j<m;j++) need[i][j]=max[i][j]-alloc[i][j];
    while(c<n) {
        ok=0;
        for(i=0;i<n;i++) if(!finish[i]) {
            for(j=0;j<m && need[i][j]<=avail[j];j++);
            if(j==m) {
                for(k=0;k<m;k++) avail[k]+=alloc[i][k];
                safe[c++]=i; finish[i]=1; ok=1;
            }
        }
        if(!ok) break;
    }
    if(c==n) {
        printf("Safe sequence: ");
        for(i=0;i<n;i++) printf("P%d ",safe[i]);
    } else printf("Unsafe state");
    printf("\n");
    return 0;
}
