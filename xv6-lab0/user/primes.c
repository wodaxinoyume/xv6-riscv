//神奇的bug，竟然会因为给char分配多了内存而报错？？？
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int *pi);

int main(int argc,char* argv[])
{
    int p[2];
    pipe(p);

    for(int i=2;i<36;i++){
        write(p[1],(char *)&i,sizeof(int));
    }
    close(p[1]);

    if(fork()==0){
        prime(p);
    }
    close(p[0]);
    wait(0);
    exit(0);
}

void prime(int *pi)
{
    char pnum[4];
    int q[2];

    if(read(pi[0],pnum,sizeof(int))>0){
        int num=*(int *)pnum;
        printf("prime %d\n",num);
        
        pipe(q);

        char buf[4];
        while(read(pi[0],buf,sizeof(int))!=0){
            if(*((int *)buf)%num!=0){
                write(q[1],buf,sizeof(int));
            }
        }
        close(q[1]);

        if(fork()==0){
            prime(q);
        }
        close(q[0]);
        wait(0);
    }
    close(pi[0]);
    exit(0);
}