#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define SHMKEY 9999
struct data{
    char s1[50];
    char s2[50];
    char s3[50];
    char result[200];
};
void flipcase(char *str){
    for(int i=0; str[i]!='\0'; i++){
        if(islower(str[i]))
            str[i] = toupper(str[i]);
        else if(isupper(str[i]))
            str[i] = tolower(str[i]);
    }
}
int main(){
    int shmid;
    struct data*d;
    shmid=shmget(SHMKEY,sizeof(struct data),IPC_CREAT|0666);
    d=(struct data*)shmat(shmid,NULL,0);
    printf("Enter first string:\n ");
    scanf("%s",d->s1);
    printf("Enter second string:\n ");
    scanf("%s",d->s2);
    printf("Enter third string:\n ");
    scanf("%s",d->s3);
    printf("\nWaiting for process 2 to concatenate \n");
    sleep(20);
    flipcase(d->result);
    printf("Final Result after case flipping: %s\n",d->result);
    shmdt(d);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}