#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define BUF_SIZE 1024
#define OPSZ 4

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
int calculate(int opnum,int opnd[],char operator);
int main(int argc, char const *argv[])
{
    //创建套接字
    int clnt_sock,serv_sock;
    struct sockaddr_in serv_addr;

    if(argc != 2){
        printf("Usage: %s <port>",argv[0]);
    }

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1)
        error_handling("socket() error");
    //创建地址
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    //绑定服务器套接字到端口
    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
        error_handling("bind() error.");
    //将服务器套接字设置为监听套接字
    if(listen(serv_sock,5) == -1)
        error_handling("listen() error.");
    
    //设置保存客户端地址的变量
    struct sockaddr_in clnt_addr;
    int clnt_addr_sz = sizeof(clnt_addr);
    
    if(clnt_sock == -1)
        error_handling("accept() error.");

    //我们要读入的的是一个
    //1.操作数个数 1字节
    //2.操作数 = 操作数个数 * 操作数大小(OPSZ)
    //3.操作符号 1字节
    for(int i = 0;i<5;i++)
    {
        int opnd_cnt = 0;
        clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_sz);
        if(clnt_sock == -1)
            error_handling("accept() error.");
        //读入操作数个数
        read(clnt_sock,&opnd_cnt,1);

        int recv_len = 0;
        int recv_cnt = 0;
        char op_info[BUF_SIZE];//...好像把变量都放在程序开头还真是好习惯,看程序舒服多了....

        printf("Debug: opnd_cnt = %d",opnd_cnt);
        while((opnd_cnt*OPSZ+1) > recv_len)
        {
            recv_cnt = read(clnt_sock,&op_info[recv_len],BUF_SIZE-1);
            recv_len += recv_cnt;
        }
        int result = calculate(opnd_cnt,(int*)op_info,op_info[recv_len-1]);

        write(clnt_sock,&result,OPSZ);
        
        close(clnt_sock);
        
    }
    close(serv_sock);

    return 0;
}

int calculate(int opnd_cnt,int opnds[],char operator)
{
    int result =opnds[0],i;
    switch (operator)
    {
    case '+':
        for(i = 1;i<opnd_cnt;i++) result += opnds[i];
        break;
    case '-':
        for(i = 1;i<opnd_cnt;i++) result -= opnds[i];
        break;
    case '*':
        for(i = 1;i<opnd_cnt;i++) result *= opnds[i];
        break;
    return result;
    
    }
}
