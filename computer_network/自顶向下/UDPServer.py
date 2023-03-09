from socket import *
serverPort = 12000
serverSocket = socket(AF_INET,SOCK_DGRAM)

#显示地为服务器套接字分配一个端口号,
serverSocket.bind(('',serverPort))
print('The server is ready to receive')
while True:
    message,clientAddress = serverSocket.recvfrom(2048)
    modifiedMessage = message.decode().upper()
    serverSocket.sendto(modifiedMessage.encode(),clientAddress)
    exit(1)