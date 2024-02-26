#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// char buf[2];
void primes(int read_fd){
    int first_val;
    if(read(read_fd,&first_val,4) == 0){
        exit(0);
    }
    printf("prime %d\n", first_val);
    int val;
    // more numbers to come, need to fork
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid < 0){
        exit(1);
    }
    else if(pid == 0){
        close(p[1]);
        primes(p[0]);
        close(p[0]);
        exit(0);
    }
    else{
        close(p[0]);
        while (read(read_fd, &val, 4) != 0){
            if (val % first_val != 0)
            {
                write(p[1], &val, 4);
            }
        }
        close(read_fd);
        close(p[1]);
        wait(0);
        exit(0);
    }   
}
int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid < 0){
        exit(1);
    }
    else if(pid == 0){
        close(p[1]);
        primes(p[0]);
        close(p[0]);
        exit(0);
    }
    else{
        close(p[0]);
        for (int i = 2; i <= 35; ++i)
        {
            write(p[1], &i, 4);
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
}