
#include <stdio.h>
#include <string.h>
int main() {
    char f[20][30],s[30];
    int n=0,c,i;
    do {
        printf("1.Create 2.Search 3.Display 4.Exit\n");
        scanf("%d",&c);
        if(c==1) {
            scanf("%29s",s);
            for(i=0;i<n && strcmp(f[i],s);i++);
            if(i<n) printf("Already exists\n");
            else if(n<20) strcpy(f[n++],s);
            else printf("Directory full\n");
        } else if(c==2) {
            scanf("%29s",s);
            for(i=0;i<n && strcmp(f[i],s);i++);
            printf(i<n?"Found\n":"Not found\n");
        } else if(c==3)
            for(i=0;i<n;i++) printf("%s\n",f[i]);
    } while(c!=4);
    return 0;
}
