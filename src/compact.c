#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "struct.h"


ssize_t readln(int fd, char *buf, size_t nbyte){
    char* b = buf;
    ssize_t i = 0;
    while(i<nbyte){
        int n = read(fd, &b[i], 1);
        // if(n<=0) return i;
        if(n<=0){
            break;
        }
        if(b[i]=='\n') return i+1;
        i++;

    }
    return i;
}


int main(){
    
    FILE *art;
    art = fopen("./fich_ma/artigos","r");
    fseek(art, 0, SEEK_END);
    int n_artigos = ftell(art) /sizeof(artigo);
    int str = open("./fich_ma/strings",O_RDONLY, 0666);
    int n_str = 0;
    while(1){
        char buf[1000];
        int n=readln(str, buf, sizeof(buf));
        if (n<=0){
            break;
        } 
        n_str++;
    }
    fclose(art);
    
    int fd = open("./fich_ma/ola", O_CREAT|O_TRUNC| O_WRONLY|O_APPEND, 0666);
    int p = (n_artigos * 100) / n_str;
    if (p <= 80){
        printf("Será feita a compactação do ficheiro strings\n");
        artigo art;
        int fd1 = open("./fich_ma/artigos", O_RDWR, 0666);
        int i = 0;
        while(i < n_artigos){
            int a = pread(fd1 ,&art, sizeof(artigo),lseek(fd1,i*sizeof(artigo),SEEK_SET));
            if (a <=0){
                break;
            }
            int pos = art.nome;
            //printf("%d\n",pos);
            int j = 0;
            char buf[1000];
            int n = 0;
            int fd2 = open("./fich_ma/strings", O_RDONLY, 0666);
            while(j<pos){
                char buf[1000];
                n=readln(fd2, buf, sizeof(buf));
                if (n<=0) break; 
                j++;

            }
            close(fd2);
            char* op= malloc(sizeof(char[n])) ;
            memcpy(op, buf, n);
           
            //printf("%s", op );
            write(fd ,op,strlen(op));
            art.nome = i+1;
            pwrite(fd1 ,&art, sizeof(artigo),lseek(fd1,i*sizeof(artigo),SEEK_SET));
            i++;
        }
        close(fd);
        close(fd1);
        execlp("mv","mv","./fich_ma/ola","./fich_ma/strings",(char *)0);

    }
    else printf("Não é necessária a compactação do ficheiro strings\n");

    return(0);  

}
