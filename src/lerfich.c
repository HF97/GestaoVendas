#include <unistd.h>   /*chamadas ao sistema: defs e decls essenciais*/
#include <fcntl.h>    /*O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "struct.h"
#include "rdln.h"


int main(){
    char buf[50];
    int n = read(0,buf, sizeof(buf));
    char* op= malloc(sizeof(char[n])) ;
    memcpy(op, buf, n-1);
    

    if (n>0){
        if (!strcmp(op,"vendas")){
            FILE *arq;
            arq=fopen("./fich_sv/vendas","r");
            venda d;
            int len=0;
            while(fread(&d,1,sizeof(venda),arq)!=0){
                
                printf("%d %d %0.2f\n",d.codigo,d.quantidade,d.total);
                len += sizeof(d);
                fseek(arq, len, SEEK_SET);
            }
            fclose(arq);

        }
        else if (!strcmp(op,"strings")){
            int arq=open("./fich_ma/strings", O_RDONLY,0666);
            while(1){
                char buf[1000];
                int n=readln(arq, buf, sizeof(buf));
                if (n<=0){
                    break;
                }
                char* tmp= malloc(sizeof(char[n])) ;
                memcpy(tmp, buf, n);
                char* arg1 = tmp;
                printf("%s",arg1);
            }
            close(arq);

        }
        else if (!strcmp(op,"stocks")){
            FILE *arq;
            arq=fopen("./fich_sv/stocks","r");
            stock d;
            int len=0;
            int i = 0;
            while(fread(&d,1,sizeof(stock),arq)!=0){
                i++;
                printf("%d %d\n",i,d.stock);
                len += sizeof(d);
                fseek(arq, len, SEEK_SET);
            }
            fclose(arq);

        }
        else if (!strcmp(op,"artigos")){
            FILE *arq;
            arq=fopen("./fich_ma/artigos","r");
            artigo d;
            int len=0;
            while(fread(&d,1,sizeof(artigo),arq)!=0){
                
                printf("%d %d %0.2f\n",d.codigo,d.nome,d.preco);
                len += sizeof(d);
                fseek(arq, len, SEEK_SET);
            }
            fclose(arq);
        }
        else if (!strcmp(op,"tmp")){
            FILE *arq;
            arq=fopen("./fich_ma/tmp","r");
            precoM d;
            int len=0;
            while(fread(&d,1,sizeof(precoM),arq)!=0){
                printf("%d %0.2f \n",d.cod, d.preco);
                len += sizeof(d);
                fseek(arq, len, SEEK_SET);
            }
            fclose(arq);
        }

    }
    return 0;
}