#ifndef _RDLN_H
#define _RDLN_H

#include <stddef.h>

//lê uma linha
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


#endif /* _RDLN_H */