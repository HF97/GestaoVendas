#include <unistd.h>   /*chamadas ao sistema: defs e decls essenciais*/
#include <fcntl.h>    /*O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include "struct.h"

//escreve em ag.txt todas as agregacoes, mas não estao agregadas
int lerfich(char *buf){
    FILE *arq;
    arq=fopen(buf,"r");
    if (arq <=0 ) return 1;
    int fd = open("./fich_ag/ag.txt", O_CREAT| O_WRONLY|O_APPEND, 0666);
    venda d;
    char x[1000];
    int len=0;
    
    while(fread(&d,1,sizeof(venda),arq)!=0){
        //printf("ola\n");
        int n = sprintf(x,"%d %d %f\n",d.codigo,d.quantidade,d.total);
        write(fd,x,n);
        len += sizeof(d);
        fseek(arq, len, SEEK_SET);
    }
    write(fd,"\n",2);
    fclose(arq);
    close(fd);
    return 0;
}

//Cria o nome do ficheiro do resultado da agregação (usando a data e a hora)
void nomefich(char **buffer){
    time_t rawtime;
    struct tm *info;
    char buf[80];
    time( &rawtime );
    info = localtime( &rawtime );
    strftime(buf,90,"./fich_ag/%Y-%m-%dT%H:%M:%S", info);
    char* op= malloc(sizeof(buf)) ;
    memcpy(op,buf, sizeof(buf));
    *buffer = op;     
}

//Le de um ficheiro temporario quantas linhas ja foram linhas do ficheiro vendas 
// agrega tudo ate ao final do ficheiro vendas(momento em que o agregador foi chamado)
int main(){
    FILE *arq1 = fopen("./fich_sv/vendas","r");
    fseek(arq1, 0, SEEK_END);
    int bt = ftell(arq1)/sizeof(venda);
    fclose(arq1);
    // int fd1 = open("./fich_ag/linhas_vendas.txt", O_CREAT|O_WRONLY, 0666);
    // char *linhas;
    // int t = sprintf(linhas,"%d\n",bt);
    // write(fd1, linhas, t);
    // close(fd1); 
    FILE *arq = fopen("./fich_ma/artigos","r");
    fseek(arq, 0, SEEK_END);
    int n = ftell(arq);
    fclose(arq);
    if (n == 0) return 1;
    char *buffer;
    char lidos[100];
    //le o ficheiro lidos.txt para saber de que linha no ficheiro vendas deve comecar
    int n_vendas = open("./fich_ag/lidos.txt", O_CREAT|O_RDONLY,0666);
    int a = read(n_vendas,lidos, sizeof(lidos));
    int i = 0;
    int qtd;
    if (a>0){
        char* op= malloc(sizeof(char[n])) ;
        memcpy(op,lidos, n);
        char *qt = op;
        qtd = atoi(qt);
        i = qtd;
    }
    close(n_vendas);
    //le o ficheiro linhas_vendas.txt para saber em que linha deve parar no ficheiro vendas
    // char n_linhas[100];
    // int fd = open("./fich_ag/linhas_vendas.txt",O_RDONLY,0666);
    // int b = read(fd,n_linhas, sizeof(n_linhas));
    int linha_final= bt;
    nomefich(&buffer);
    // if (b>0){
    //     char* op= malloc(sizeof(char[n])) ;
    //     memcpy(op,lidos, n);
    //     char *qt = op;
    //     linha_final = atoi(qt);
    // }
    // close(fd);
    
    // verifica se ja foram efectuadas vendas
    int vendas = open("./fich_sv/vendas",O_RDONLY,0666);
    if (vendas<0){
        printf("ficheiro vazio");
        return 1;
    }  

    int j = 0;
    
    while(i<=linha_final){
        venda vd;
        venda ag;
        int n = pread(vendas,&vd, sizeof(venda),lseek(vendas,i*sizeof(venda),SEEK_SET));
        if(n<=0){
            printf("não há mais vendas\n");
            break;
        }
        int fd1 = open(buffer,O_CREAT|O_RDWR,0666);
        int t = pread(fd1,&ag, sizeof(venda),lseek(fd1,(vd.codigo -1)*sizeof(venda),SEEK_SET));
        if (t<=0){
            ag.codigo=vd.codigo;
            ag.quantidade = vd.quantidade;
            ag.total = vd.total;
            pwrite(fd1, &ag, sizeof(venda),lseek(fd1,(vd.codigo -1)*sizeof(venda),SEEK_SET));
        }
        else{
            ag.codigo=vd.codigo;
            ag.quantidade += vd.quantidade;
            ag.total += vd.total;
            pwrite(fd1, &ag, sizeof(venda),lseek(fd1,(vd.codigo -1)*sizeof(venda),SEEK_SET));
        }
        j++;
        i++;
        close(fd1);
    }
    close(vendas);

    
    char c[100];
    if (j>0){
        qtd += j;
        sprintf(c,"%d",j);
        n_vendas = open("./fich_ag/lidos.txt", O_CREAT|O_WRONLY,0666);
        write(n_vendas,c, strlen(c));
        close(n_vendas);
    }

    lerfich(buffer);    
}

