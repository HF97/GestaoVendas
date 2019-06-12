#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "info.h"
#include "tratac.h"
#include "rdln.h"
#include "struct.h"


//Cria os fifos para a interação com o cliente. Onde é executado o agregador. 
//Altera o stock e regista as vendas.
int main(int argc, const char * argv[]) {
    FILE *art;
    art = fopen("./fich_ma/artigos","r");
    if (art==NULL){
        char *s;
        s = "Não existe artigos!\nVou embora!\n";
        write(1, s, strlen(s));
        return 1;
    }
    system("./compact");
    fseek(art, 0, SEEK_END);
    int n_artigos = ftell(art) /sizeof(artigo);
    float preco[n_artigos];
    for (int n=0; n<n_artigos; n++) preco[n]=0;

    mkfifo("fifo_server",0666);
	mkfifo("fifo_client",0666);
    pid_t cpid;
   
    char buf[255];
    int bytes_read;
    int s;
    char *arg1;
    char *arg2;
    int fd_server = open("fifo_server", O_RDWR);
    int fd_client = open("fifo_client",O_RDWR);
    if (fd_server == -1||fd_client == -1){
        perror ("open");
    }

    int n;
    while(1) {
        if ((cpid = fork()) == 0 ) {
            while(1){
                if((bytes_read=read(fd_server,buf,sizeof(buf))) > 0){
                    s = trataCliente(buf,&arg1,&arg2);
                }
                else break;
                char *send;
                int cod = atoi(arg1);
                if (cod > n_artigos) send = "Não existe artigo!!\n";
                else{
                    if (preco[cod-1]<=0){
                        //printf("%d, %d\n",cod, cod-1);
                        artigo art;
                        int fd2 = open("./fich_ma/artigos", O_RDONLY, 0666);
                        if (fd2 ==-1) send= "Ainda não existe artigos!!!!!\n";
                        else{
                            int n = pread(fd2 ,&art, sizeof(artigo),lseek(fd2,(cod-1)*sizeof(artigo),SEEK_SET));
                            if (n<=0) send = "Não existe artigo!!\n";
                            else preco[cod-1] = art.preco;  
                            close(fd2);
                        }
                    }
                    else{
                        int fd3;
                        precoM novo;
                        if ((fd3 = open("./fich_ma/tmp", O_RDONLY, 0666))>-1){
                            printf("modificação do preço\n");
                            while(1){
                                int n = read(fd3,&novo,sizeof(precoM));
                                if (n==0){
                                    system("rm ./fich_ma/tmp");
                                    break;
                                } 
                                lseek(fd3,sizeof(precoM),SEEK_CUR);
                                
                                preco[(novo.cod)-1]=novo.preco;
                            }
                            close(fd3);
                        
                        }
                    }
                    if (s==1){
                        send= info_1(cod, preco[cod-1]);
                    }
                    else{
                        send = info_2(cod, arg2, preco[cod-1]);
                    }
                    //printf("%0.2f, %d\n", preco[cod-1], cod-1);
                }
                
                if (write (fd_client, send, strlen (send)) != strlen (send))
                    perror ("write");

                
            }
        }
        else {
            char buf2[15];
            n = readln(0, buf2, 15);
            char* op= malloc(sizeof(char[n])) ;
            memcpy(op, buf, n-1);
            if(n<=0||!strcmp(op,"agregador")){
                break;
            }
            else{
                system("./ag");
            }   
        }
        if (n<=0)break;

    }
    
    close(fd_server);
    close(fd_client);
    _exit(1);
} 