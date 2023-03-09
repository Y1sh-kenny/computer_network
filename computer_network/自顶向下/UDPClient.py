#包含所需网络编程的模块
from socket import *
serverName = '127.0.0.1'
serverPort = 12000

#创建客户套接字
# 第一个参数指示了地址簇,AF_INET指示了底层网络使用ipv4
# 第二个参数指示了套接字是SOCK_DGRAM类型,这意味着他是一个UDP套接字

clientSocket = socket(AF_INET,SOCK_DGRAM)
message = input('Input lowercase sentence:')

#sendto() 我们首先将报文由字符串类型转变为字节类型,因为我们要向套接字传递字节
# 第二个参数附上地址
clientSocket.sendto(message.encode(),(serverName,serverPort))

#等待来自服务器的数据
modifiedMessage,serverAddress = clientSocket.recvfrom(2048)
print(modifiedMessage.decode())
clientSocket.close()