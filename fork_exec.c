#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
    pid_t pid;
    pid=fork();
    if(pid<0){
        perror("Fork failed");
        exit(1);
    }
    else if(pid==0){
        printf("Child process(PID: %d) executing myadder\n",getpid());
        char *args[]={"./myadder","10","20",NULL};
        execvp(args[0],args);
        perror("execvp failed");
        exit(1);
    }else{
        printf("Parent process(PID : %d) created child process(PID : %d)/n",getpid(),pid);
        wait(NULL);
        printf("Child completed execution./n");
    }
    return 0;

}