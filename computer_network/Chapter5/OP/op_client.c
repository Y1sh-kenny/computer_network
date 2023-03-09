#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define BUF_SIZE 1024
#define OPSZ 4
#define RLT_SIZE 4

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc, char const *argv[])
{
    int sock;

    //创建套接字
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock == -1)
        error_handling("socket() error.");
    if(argc != 3){
        printf("Usage : %s <IP> <port>.",argv[0]);
    }

    //服务器地址
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    //连接服务器
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
        error_handling("conncet() error.");
    else
        puts("Connected......\n");    
    fputs("Operand count: ",stdout);
    //字符数
    int opnd_cnt;
    scanf("%d",&opnd_cnt);
    
    char opmsg[BUF_SIZE];
    opmsg[0]=(char)opnd_cnt;
    

    for(int i = 0;i<opnd_cnt;i++)
    {
        printf("Operand %d: ",i+1);
        char operator;
        scanf("%d",(int*)&opmsg[i*OPSZ+1]);
    }
    //fgetc()是消除'\n'的...
    fgetc(stdin);

    fputs("Operator: ",stdout);
    scanf("%c",&opmsg[opnd_cnt*OPSZ+1]);
    printf("[Debug]: writing to server...\n");
    write(sock,opmsg,opnd_cnt*OPSZ+2);
    
    //读入结果
    int result;
    printf("[Debug]: Reading from server...\n");
    read(sock,&result,RLT_SIZE);
    
    //打印结果
    printf("Operaton result: %d \n",result);
    close(sock);
    
    return 0;
    
}