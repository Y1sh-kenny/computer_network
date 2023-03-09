#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
//生成套接字
//int socket(int domain,int type ,int protocol);
//给套接字分配IP地址和端口号  成功时返回0,失败时返回-1;
//int bind(int sockfd,struct sockaddr *myaddr,socklen_t addrlen);
//将套接字转换成可接收连接的状态
//int listen(int sockfd,int backlog);
//若接收到请求数据传输的连接,调用函数受理   成功时返回文件描述符,失败时返回-1
//int accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);

void error_handling(char *message);

int main(int argc,char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "hello world!";

    if(argc!=2)
    {
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*) &serv_addr,sizeof(serv_addr))==-1)
        error_handling("bind() error");
    
    if(listen(serv_sock,5) == -1)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock=accept(serv_sock,(struct sockaddr*) &clnt_addr,&clnt_addr_size);
    if(clnt_sock ==-1)
        error_handling("accept() error");
    
    write(clnt_sock,message,sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
