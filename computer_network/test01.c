#include<sys/socket.h>
//生成套接字
int socket(int domain,int type ,int protocol);
//给套接字分配IP地址和端口号  成功时返回0,失败时返回-1;
int bind(int sockfd,struct sockaddr *myaddr,socklen_t addrlen);
//将套接字转换成可接收连接的状态
int listen(int sockfd,int backlog);
//若接收到请求数据传输的连接,调用函数受理   成功时返回文件描述符,失败时返回-1
int accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);

