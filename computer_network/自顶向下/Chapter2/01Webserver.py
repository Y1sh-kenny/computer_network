#import socket module
from socket import *
import sys # In order to terminate the program
serverSocket = socket(AF_INET, SOCK_STREAM)
#Prepare a sever socket
#Fill in start
serverName = "127.0.0.1"
serverPort = 9190
serverSocket.bind((serverName,serverPort))

serverSocket.listen()
#Fill in end
while True:
 #Establish the connection
 print('Ready to serve...')
#Fill in start
 connectionSocket, addr = serverSocket.accept()
#Fill in end 
 try:
 message = connectionSocket.recv(1024)#Fill in start #Fill in end 
 filename = message.split()[1] 
 f = open(filename[1:]) 
 outputdata = #Fill in start #Fill in end 
 #Send one HTTP header line into socket
 #Fill in start
 #Fill in end 
 #Send the content of the requested file to the client
 for i in range(0, len(outputdata)): 
 connectionSocket.send(outputdata[i].encode())
 connectionSocket.send("\r\n".encode())
 
 connectionSocket.close()
 except IOError:
 #Send response message for file not found
 #Fill in start 
 error_response = "file not found."
 connectionSocket.send(error_response.encode())
 #Fill in end
 #Close client socket
 #Fill in start
 connectionSocket.close()
 #Fill in end 
serverSocket.close()
sys.exit()#Terminate the program after sending the corresponding data