#ifndef _INFO_H
#define _INFO_H

#include <stddef.h>
#include <limits.h>
#include "struct.h"

//Escreve na ultima linha do ficheiro vendas a venda efetuada
void vendas(int qt, int cod, float preco){
    venda venda;
    int fd = open("./fich_sv/vendas", O_CREAT| O_RDWR, 0666);
    venda.codigo = cod;
    venda.quantidade = qt;
    venda.total = preco * qt;
    pwrite(fd ,&venda, sizeof(venda),lseek(fd,0,SEEK_END));
    close(fd);
}

//Escreve em str a mensagem do servidor caso só haja um argumento.
char * info_1 (int cod, float prec){
    char *str;
    str = malloc(sizeof(char[1000]));
    stock stock;
    int fd1 = open("./fich_sv/stocks", O_RDONLY, 0666);
    if (fd1 == -1){
        str = "Ainda não existe stock dos produtos!!!!!\n";
    }
    else{
        int n = pread(fd1 ,&stock, sizeof(stock),lseek(fd1,(cod-1)*sizeof(stock),SEEK_SET));
        close(fd1);
        if (n<=0){
            stock.stock = 0;
            pwrite(fd1 ,&stock, sizeof(stock),lseek(fd1,(cod-1)*sizeof(stock),SEEK_SET));
            close(fd1);
        }
        sprintf(str,"stock: %d preço: %0.2f\n", stock.stock, prec);     
    }
    close(fd1);
    return str;
}

char * info_2 (int cod, char *arg2, float prec ){
    char *str;
    str = malloc(sizeof(char[1000]));
    stock stock;;
    int stk = atoi(arg2);
    int fd1 = open("./fich_sv/stocks", O_CREAT| O_RDWR, 0666);
    if (fd1 == -1){
        str = "Não existe stock ainda!!!!!\n";
    }
    else{
        if (cod >0){ 
            int n = pread(fd1 ,&stock, sizeof(stock),lseek(fd1,(cod-1)*sizeof(stock),SEEK_SET));
            if (n==0) stock.stock=0;
            if (stk >= 0){
                stock.stock += stk;
                pwrite(fd1 ,&stock, sizeof(stock),lseek(fd1,(cod-1)*sizeof(stock),SEEK_SET));
                sprintf(str,"artigo: %d stock: %d \n",cod, stock.stock);
            }
            else{
                int novo = stock.stock+stk;
                if ((novo)>=0){
                    printf("stock suficiente\n");
                    stock.stock += stk;
                    vendas(abs(stk), cod, prec);
                    pwrite(fd1 ,&stock, sizeof(stock),lseek(fd1,(cod-1)*sizeof(stock),SEEK_SET));
                    sprintf(str,"artigo: %d stock: %d \n", cod, stock.stock);
                }
                else{
                    sprintf(str,"O artigo %d não tem stock suficiente\n", cod);
                }
            }
        }
        else str = "Não existe artigo!!!!!\n";
        
    }
    close(fd1);
    return str;
}          

#endif /* _INFO_H */