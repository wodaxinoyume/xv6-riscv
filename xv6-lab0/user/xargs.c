#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[]){
    for(int i =0;i<argc;i++){
        argv[i]=argv[i+1];
    }

    int fd=dup(0);

    char c;
    char buf[8];
    while(read(fd,&c,1)){
        int i=0;
        while(c!='\n'){
            buf[i]=c;
            read(fd,&c,1);
            i++;
        }
        argv[argc-1]=buf;
        if(fork()==0){
            exec(argv[0],argv);
        }
        memset(buf,0,sizeof(buf));
        wait(0);
    }

    wait(0);
    exit(0);
}