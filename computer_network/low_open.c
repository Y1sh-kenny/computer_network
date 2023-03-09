#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

void error_handling(char * message);

int main(void)
{
    int fd;//文件描述符
    char buf[] = "let's go!\n";

    fd = open("data.txt",O_CREAT|O_WRONLY|O_TRUNC);
    if(fd == -1)
        error_handling("open() error");
    printf("file discriptor : %d \n",fd);
    if(write(fd,buf,sizeof(buf)) ==-1)
    {
        error_handling("write() error.");
    }

    close(fd);
    

    return 0;
}

void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}