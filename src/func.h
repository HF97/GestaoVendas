#ifndef _MA_H
#define _MA_H

#include <stddef.h>
#include "struct.h"
#include "rdln.h"



//trata o buffer
//coloca em arg1 o primeiro "argumento" do buffer
//coloca em arg2 o segundo "argumento" do buffer
//coloca em arg3 o terceiro "argumento" do buffer
void trataB(char *buf, char **arg1, char **arg2, char **arg3){

    char* str1= malloc(sizeof(buf)) ;
    str1 = buf;
    int j =0;
    while(memcmp(str1," ",sizeof(char))){ 
        str1++;
        j++;
    }  
    char* op= malloc(sizeof(char[j])) ;
    memcpy(op, buf, j);
    *arg1 = op;     
    str1++;
    char* str2= malloc(sizeof(str1)) ;
    str2 = str1;
    j=0;
    while(memcmp(str1," ",sizeof(char))){ 
        str1++;
        j++;
    }
    char* a1= malloc(sizeof(char[j])) ;
    memcpy (a1,str2 , j);
    *arg2 = a1;     
    str1++;
    char* str3= malloc(sizeof(str1)) ;
    str3 = str1;
    j=0;
    while(memcmp(str1,"\n",sizeof(char))){ 
        str1++;
        j++;
    }
    char* a2= malloc(sizeof(char[j])) ;
    memcpy(a2, str3, j);
    *arg3 = a2;
    
  

}

int codigoproduto(){
    artigo d;
    FILE * arq;
    arq = fopen("./fich_ma/artigos","r");

    if (fread(&d,1,sizeof(artigo),arq)==0){
        printf("ficheiro vazio");
        return 0;

    }
    else{
        fseek(arq,-sizeof(artigo), SEEK_END);
    }
    fread(&d,1,sizeof(artigo),arq);
    int x = d.codigo + 1;
    fclose(arq);
    return x;
}

//escreve o nome do artigo no ficheiro "strings" e retorna o nº da linha
int produtos(char *nome){
    int j = 0;
    int fdS = open("./fich_ma/strings", O_CREAT|O_WRONLY|O_APPEND , 0666 );
    write(fdS,strcat(nome, "\n"),strlen(nome)+1);
    close(fdS);
    int fd = open("./fich_ma/strings",  O_RDONLY, 0666 );

    while(1){
        char buf[1000];
        int n=readln(fd, buf, sizeof(buf));
        if (n<=0){
            break;
        } 
        j++;
    }
    close(fd);
    return j;

}



void insereArtigo(char *nome, char *preco){

    int a;
    FILE *arq;
    artigo art;
    int s, c;
    float p;
    arq=fopen("./fich_ma/artigos","r");
    if (arq == NULL){
        c = 1;
    }
    else{
        fseek(arq,-sizeof(artigo), SEEK_END);
        artigo b;
        fread(&b,1,sizeof(artigo),arq);
        c = b.codigo + 1;
    }
   
    a = open("./fich_ma/artigos",O_CREAT|O_RDWR|O_APPEND, 0666);
    s = produtos(nome);
    p = atof(preco);
    art.codigo = c;
    art.nome = s;
    art.preco = p;

    write(a,&art,sizeof(artigo));
    close(a);
    

}


void modificaNome(char *codigo,  char *nome){
    int erro;
    FILE *arq;
    int a;
    a = open("./fich_ma/artigos",O_RDWR, 0666);
    artigo art;
    int c;
    int s;

    if (a<0){
        erro = open("./fich_ma/Erro_Artigos",O_CREAT|O_WRONLY|O_APPEND,0666);
        char *c = "Erro 1: Ficheiro não existe, insira algum artigo!";
        write(erro, c, strlen(c));
        close(erro);
        printf("ERRO 1\n");

    }
    else{
        arq = fopen("./fich_ma/artigos","r");
        fseek(arq, 0, SEEK_END);
        int n = ftell(arq);
        fclose(arq);
        //printf("%d bytes\n", n);
        if (n==0){
            erro = open("./fich_ma/Erro_Artigos",O_CREAT|O_WRONLY|O_APPEND,0666);
            char *c = "Erro 2: Ficheiro existe, mas está vazio!";
            write(erro, c, strlen(c));
            close(erro);
            printf("ERRO 2\n");
        }
        else{
            c = atoi(codigo);
            if (c >(n/sizeof(artigo))){
                erro = open("./fich_ma/Erro_Artigos",O_CREAT|O_WRONLY|O_APPEND,0666);
                char *c = "Erro 3: Artigo não encontrado!";
                write(erro, c, strlen(c));
                close(erro);
                printf("ERRO 3\n");
            }
            else{
                s = produtos(nome);
                //fseek(a,(c-1)*sizeof(artigo),SEEK_SET);
                int novo;
                novo= open("./fich_ma/artigos",O_CREAT|O_RDWR, 0666);
                pread(novo,&art, sizeof(artigo),lseek(a,(c-1)*sizeof(artigo),SEEK_SET));
                //printf("%d %d %f\n",art.codigo,art.nome,art.preco);
                art.nome = s;
                pwrite(novo,&art, sizeof(artigo),lseek(a,(c-1)*sizeof(artigo),SEEK_SET));
                close(novo);
            }
        }
    }

}

void modificaPreco(char *codigo,  char *preco){
    
    FILE *arq;
    int a, erro;
    a = open("./fich_ma/artigos",O_RDWR, 0666);
    artigo art;
    int c;
    float p;
    if (a<0){
       erro = open("./fich_ma/Erro_Artigos",O_CREAT|O_WRONLY|O_APPEND,0666);
        char *c = "Erro 1: Ficheiro não existe, insira algum artigo!";
        write(erro, c, strlen(c));
        close(erro);
        printf("ERRO 1\n");

    }
    else{
        arq = fopen("./fich_ma/artigos","r");
        fseek(arq, 0, SEEK_END);
        int n = ftell(arq);
        fclose(arq);
        //printf("%d bytes\n", n);
        if (n==0){
            erro = open("./fich_ma/Erro_Artigos",O_CREAT|O_WRONLY|O_APPEND,0666);
            char *c = "Erro 2: Ficheiro existe, mas está vazio!";
            write(erro, c, strlen(c));
            close(erro);
            printf("ERRO 2\n");
        }
        else{
            c = atoi(codigo);
            p = atof(preco);
            if (c >(n/sizeof(artigo))){
                erro = open("./fich_ma/Erro_Artigos",O_CREAT|O_WRONLY|O_APPEND,0666);
                char *c = "Erro 3: Artigo não encontrado!";
                write(erro, c, strlen(c));
                close(erro);
                printf("ERRO 3\n");
            }
            else{
                //fseek(a,(c-1)*sizeof(artigo),SEEK_SET);
                int novo;
                int tmp = open("./fich_ma/tmp", O_CREAT|O_WRONLY|O_APPEND, 0666);
                precoM mod;
                
                novo = open("./fich_ma/artigos",O_CREAT|O_RDWR, 0666);
                pread(novo,&art, sizeof(artigo),lseek(novo,(c-1)*sizeof(artigo),SEEK_SET));
                //printf("%d %d %f\n",art.codigo,art.nome,art.preco);
                art.preco = p;
                mod.preco= p;
                mod.cod = c;
                pwrite(novo,&art, sizeof(artigo),lseek(novo,(c-1)*sizeof(artigo),SEEK_SET));
                //pwrite(tmp,&mod, sizeof(precoM),lseek(tmp,(c-1)*sizeof(precoM),SEEK_SET));
                write(tmp,&mod, sizeof(precoM));
                close(tmp);
                close(novo);


            }
        }
    }
}


#endif /* _MA_H */