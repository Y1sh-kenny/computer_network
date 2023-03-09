from socket import *

HOST,PORT = '',8888

listen_socket = socket(AF_INET,SOCK_STREAM)
listen_socket.setsockopt(SOL_SOCKET,SO_REUSEADDR,1)
listen_socket.bind((HOST,PORT))
listen_socket.listen(1)

print(f'Serving HTTP ON port {PORT} ...')
while True:
    client_connection,client_address = listen_socket.accept()
    request_data = client_connection.recv(1024)
    print(request_data.decode('utf-8'))

    http_response = b"""\
HTTP/1.1 200 OK

Hello,and fuck you.
"""
    client_connection.sendall(http_response)
    client_connection.close()