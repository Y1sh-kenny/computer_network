#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{   
    char message[20] = "hello";
    int f1 = open("test.txt",O_CREAT|O_RDWR|O_TRUNC);
    write(f1,message,sizeof(message));

    char buf[20];
    int str_len = read(f1,buf,2);

    printf("str_len :%d\n",str_len);
    return 0;
}