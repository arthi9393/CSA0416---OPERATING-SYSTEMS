
#include <stdio.h>
typedef struct {
    int id;
    char name[30];
    float salary;
} Employee;

int main() {
    FILE *fp;
    Employee e;
    int n,i,pos;
    fp=fopen("employee.dat","wb+");
    if(!fp){perror("File");return 1;}
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        scanf("%d%29s%f",&e.id,e.name,&e.salary);
        fwrite(&e,sizeof(e),1,fp);
    }
    scanf("%d",&pos);
    if(pos<1 || pos>n) printf("Invalid record\n");
    else {
        fseek(fp,(long)(pos-1)*sizeof(e),SEEK_SET);
        if(fread(&e,sizeof(e),1,fp)==1)
            printf("%d %s %.2f\n",e.id,e.name,e.salary);
    }
    fclose(fp);
    return 0;
}
