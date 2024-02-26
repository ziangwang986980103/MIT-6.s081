#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){

    //read in the lines of arguments
    char* lines[MAXARG];
    for(int i = 1; i < argc; ++i){
        lines[i-1] = malloc(strlen(argv[i]) + 1);
        memcpy(lines[i-1],argv[i],strlen(argv[i]));
        lines[i-1][strlen(argv[i])] = 0;
    }
    int i = argc-1;
    char temp[100];
    int index = 0;
    while(read(0,&temp[index],1) != 0){
        if (index >= 1 && (temp[index] == '\n' || temp[index] == ' '))
        {
            lines[i] = malloc(index+1);
            memcpy(lines[i],temp,index);
            lines[i][index] = 0;
            i++;
            index = 0;
        }
        else{
            index++;
        }
    }

    int pid = fork();
    if(pid == 0){
        exec(argv[1],lines);
        exit(1);
    }
    else{
        wait(0);
    }
    for(int j = i-1; j >= 0; --j){
        free(lines[j]);
    }

    exit(0);
}