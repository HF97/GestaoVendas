#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>
#include "rdln.h"

char my_fifo_name [128];
char buf1 [512], buf2 [1024];

int main (){
   
   mkfifo("fifo_server",0666);
   mkfifo("fifo_client",0666);
   int fd, fd_server, bytes_read;
   
   while(1) {
      char buf2 [1024];

      int n = readln(0, buf2, sizeof(buf2));
      if (n<=0) break;
      //printf("%s\n",buf2);


      // send message to server

      if ((fd_server = open ("fifo_server", O_WRONLY)) == -1) {
         perror ("open: server fifo");
         break;
      }

      if (write (fd_server, buf2, n) != n) {
         perror ("write");
         break;
      }
      // read the answer
      if ((fd = open ("fifo_client", O_RDONLY)) == -1)
         perror ("open");

      if ((bytes_read = read (fd, buf2, sizeof (buf2))) > 0) {
         write(1,buf2,bytes_read);
      }
      
   close(fd_server);
   close(fd);
   }
   _exit(1);

  
}