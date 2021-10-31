#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
char *message = "This is a message!!!" ;
int main(){
    char buf[1024] ;
    int fd[2];
    pipe(fd); /*create pipe*/
    if (fork() != 0) { /* I am the parent */
        write(fd[1], message, strlen (message) + 1) ;
    }
    else { /*Child code */
        read(fd[0], buf, 1024) ;
        printf("Got this from Parent!!: %s\n", buf) ;
    }
}