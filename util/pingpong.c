#include "kernel/types.h"
#include "user/user.h"
#include "stddef.h"
int main(int argc, char *argv[])
{
    if(argc>1)
    {
       fprintf(2,"The number of arguments is wrong!\n");
       exit(1);
    }
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    char buf[8];
    if (fork() == 0) 	
 {
        read(p1[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        write(p2[1], "pong", strlen("pong"));
    }
    else {
        write(p1[1], "ping", strlen("ping"));	
        wait(NULL);
        read(p2[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
    }
    exit(0);
}
