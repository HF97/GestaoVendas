#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include "struct.h"


//Executa 4 clientes ao mesmo tempo com propósito de teste
int main(){
    pid_t p;
    int i;
    for(i=0; i<4; i++){
        p=fork();
        char str[14];
        str[0]='.';
        str[1]='/';
        str[2]='t';
        str[3]='e';
        str[4]='s';
        str[5]='t';
        str[6]='e';
        str[7]='s';
        str[8]='/';
        str[9]='f';
        str[10]='i';
        str[11]='c';
        str[12]='h';
        str[13]= i+'0';
        if(!p){
            int fd = open(str,O_RDONLY,0666);
            dup2(fd,0);
            close(fd);
            execlp("./cv","./cv",0,NULL);
            _exit(0);
        } 
        else wait(NULL);
    }
    _exit(1);
}