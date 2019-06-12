#include <unistd.h>   /*chamadas ao sistema: defs e decls essenciais*/
#include <fcntl.h>    /*O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "func.h"


//Faz a manutenção de arquivos (inserir artigos, modificar nome e modificar preço)
int main(int argc , char* argv[]){
    
    int i = 1024;
	int l = 0;
   	char str[20];

    while(1){
            char* buf= malloc(sizeof(char[i])) ;
            ssize_t n = readln(0, buf, i);
            if(n <=0){
                break;  
            }

        // tratamento da linha
        char *opcao;
        char *arg1;
        char *arg2;
        trataB(buf,&opcao,&arg1,&arg2);
        
        // fim do tratamento da linha
            
        l++;

        sprintf(str,"%d, ", l);

        if (!strcmp(opcao,"i")){
            insereArtigo(arg1, arg2);

        }
            
        else if(!strcmp(opcao,"n")){
            modificaNome(arg1, arg2);
            
        }
        else if(!strcmp(opcao,"p")){
            modificaPreco(arg1, arg2);
            
        }
        
    }

}      
