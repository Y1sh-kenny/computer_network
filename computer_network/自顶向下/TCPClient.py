from socket import *
serverName = '127.0.0.1'
serverPort = 12000
clientSocket = socket(AF_INET,SOCK_STREAM)
#这行代码执行后,进行三次握手,建立TCP连接
clientSocket.connect((serverName,serverPort))

sentence = input('Input lowercase sentence: ')
clientSocket.send(sentence.encode())
modifiedSentence = clientSocket.recv(1024)
print('From Server: ',modifiedSentence.decode())
clientSocket.close()