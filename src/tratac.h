#ifndef _TRATAC_H
#define _TRATAC_H

#include <stddef.h>

//
int trataCliente(char *buf, char **arg1, char **arg2){

    int conta = 1;
    char* str1= malloc(sizeof(buf)) ;
    str1 = buf;
    int j =0;
    while(memcmp(str1,"\n",sizeof(char))){ 
        if (!memcmp(str1," ",sizeof(char))){
            conta = 2;
            break;
        }
        str1++;
        j++;
    }  
    char* op= malloc(sizeof(char[j])) ;
    memcpy(op, buf, j);
    *arg1 = op;
    if (conta == 1) return conta;
    str1++;
    char* str2= malloc(sizeof(str1)) ;
    str2 = str1;
    j=0;
    while(memcmp(str1,"\n",sizeof(char))){ 
        str1++;
        j++;
    }
    char* a2= malloc(sizeof(char[j])) ;
    memcpy(a2, str2, j);
    *arg2 = a2;
    return 2;
}

#endif /* _TRATAC_H */