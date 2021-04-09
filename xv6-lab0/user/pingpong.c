#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    int p[2];
    char buf[512];

    pipe(p);

    if(fork()==0){
       if(read(p[0],buf,512)>0){
           printf("%d%s",getpid(),": received ping\n");
           write(p[1],"pong",512);
           exit(0);
        }
        exit(1);
    }

    write(p[1],"ping",512);
    wait(0);
    if(read(p[0],buf,512)>0){
        printf("%d%s",getpid(),": received pong\n");
        exit(0);
    }
    exit(1);
}