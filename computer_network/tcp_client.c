//相对于hello_client.c更改read函数的调用方式
//目的是为了验证TCP的以下特性
//"传输的数据不存在数据边界"

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);

    exit(1);
}

//延迟调用
void delay_call(int time)
{   if(time <= 0){
    error_handling("delay_time should > 0");
}
    for(int i = 0;i<=time;++i)
    {   
        if(i % 100 == 0)
            printf("Wait time %d \n",i);
    }
}

int main(int argc,char* argv[])
{
    //套接字
    int sock;
    //服务器地址
    struct sockaddr_in serv_addr;
    //缓冲区
    char message[30];

    //相对于hello_client新添加的
    int str_len = 0;
    int idx = 0,read_len = 0;



    if(argc != 3)
    {
        printf("Error! Usage: %s <IP> <port>",argv[0]);
        exit(1);
    }
    //创建一个socket
    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)
        error_handling("socket() error.");
    //服务器地址
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    //尝试建立tcp连接
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
        error_handling("connect() error.");

    //相对于hello_client更改的地方
    delay_call(100);

    read_len = read(sock,message,sizeof(message)-1);
    str_len =1;
    //打印结果...
    //这里当我们采用了多段发送数据的时候,我们注意到我们只能接受到前面几段函数而不能接收到后面极端函数
    
    printf("Message from server: %s\n",message);
    
    //查询read()被调用的次数.
    printf("Function read call count: %d \n",str_len);

    //关闭套接字
    close(sock);
    return 0;

}