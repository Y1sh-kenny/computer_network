//用low_read函数读取low_open中创建的data.txt文件
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#define BUF_SIZE 100
void error_handling(char *message);

int main(void)
{
    int fd;//文件描述符
    char BUF[BUF_SIZE];

    fd = open("test.txt",O_RDONLY);
    if(fd == -1)
    {
        error_handling("open() error.");
    }
    printf("file descirptor: %d \n",fd);

    int str_len = read(fd,BUF,sizeof(BUF));
    if(str_len == -1)
        error_handling("read() error");
    
    printf("file data: %s \n",BUF);
    close(fd);

    return 0 ;
}



void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);

    exit(1);
}
