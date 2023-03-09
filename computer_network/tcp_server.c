
#include<sys/socket.h> // for socket() bind() listen() accept()
#include<arpa/inet.h> // for struct sockaddr_in
#include<stdio.h>   //for stderr
#include<stdlib.h> //for exit(1)
#include<string.h> //for memset()
#include<unistd.h>// for write()-- linux中的文件I/O

void error_handling(char * message);
//延迟调用
void delay_call(int time)
{   if(time <= 0){
    error_handling("delay_time should > 0");
}
    for(int i = 0;i<time;++i)
    {   
        if(i % 1000 == 0)
            printf("Wait time %d \n",i);
    }
}
int main(int argc,char *argv[])
{
    int serv_sock;
    int clnt_scok;
    

    struct sockaddr_in serv_addr;//#include<arpa/inet.h>
    struct sockaddr_in clnt_addr;//#include<arpa/inet.h>
    socklen_t clnt_addr_size;

    char message[] = "hello world.";

    if(argc != 2)
    {
        printf("Usage : %s <port>\n",argv[0]);
    }

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1)
        error_handling("socket() error!");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)& serv_addr,sizeof(serv_addr)) == -1)
        error_handling("bind() error!");
    
    if(listen(serv_sock,5) == -1)
        error_handling("listen() error!");
    
    clnt_addr_size = sizeof(clnt_addr);
    clnt_scok = accept(serv_sock,(struct sockaddr*)& clnt_addr,&clnt_addr_size);
    if(clnt_scok == -1)
        error_handling("accept() error!");
    
    //多次发送数据
    write(clnt_scok,message,4);
    write(clnt_scok,message+4,4);
    write(clnt_scok,message+8,sizeof(message)-8);

    close(clnt_scok);
    close(serv_sock);

    return 0;

}

void error_handling(char * message)
{
    fputs(message,stderr);
    fputc('\n',stderr);

    exit(1);
}