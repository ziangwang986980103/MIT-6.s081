#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[2];
int main(int argc, char *argv[])
{
    //child read, parent write
    int p1[2];
    pipe(p1);
    //parent read child write
    int p2[2];
    pipe(p2);
    if(argc > 1){
        fprintf(2, "error: too many parameter\n");
        exit(1);
    }

    int pid = fork();
    if(pid == 0){
        close(p1[1]);
        read(p1[0],buf,sizeof(buf));
        printf("%d: received ping\n", getpid());

        write(p2[1],buf,1);
        close(p2[1]);
        exit(0);
    }
    else{
        write(p1[1],"1",1);
        close(p1[1]);

        close(p2[1]);
        read(p2[0],buf,1);
        printf("%d: received pong\n", getpid());

        exit(0);
    }

}