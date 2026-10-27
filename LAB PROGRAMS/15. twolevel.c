
#include <stdio.h>
#include <string.h>
int main() {
    char u[10][20],f[10][10][20],user[20],file[20];
    int nu=0,n[10]={0},c,i,j,k;
    do {
        printf("1.Add user 2.Create file 3.Display 4.Exit\n");
        scanf("%d",&c);
        if(c==1 && nu<10) {
            scanf("%19s",u[nu++]);
        } else if(c==2) {
            scanf("%19s%19s",user,file);
            for(i=0;i<nu && strcmp(u[i],user);i++);
            if(i==nu) {printf("User not found\n");continue;}
            for(j=0;j<n[i] && strcmp(f[i][j],file);j++);
            if(j<n[i]) printf("File exists\n");
            else if(n[i]<10) strcpy(f[i][n[i]++],file);
            else printf("Directory full\n");
        } else if(c==3) {
            for(i=0;i<nu;i++) {
                printf("%s:",u[i]);
                for(k=0;k<n[i];k++) printf(" %s",f[i][k]);
                printf("\n");
            }
        }
    } while(c!=4);
    return 0;
}
