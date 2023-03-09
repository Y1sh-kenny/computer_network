import io
import socket
import sys

class WSGIServer(object):
    address_family = socket.AF_INET
    socket_type = socket.SOCK_STREAM
    request_queue_size = 1

    def __init__(self,server_address):
        #Create a listening socket
        self.listen_socket = listen_socket = socket.socket(self.address_family,self.socket_type)
        #Allow to use the same address
        listen_socket.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
        #Bind
        listen_socket.bind(server_address)
        #Activate
        listen_socket.listen(self.request_queue_size)
        #Get server host name and port
        host,port = self.listen_socket.getsockname()[:2]
        self.server_name = socket.getfqdn(host)
        self.server_port = port
        # Return headers set by Web framework/Web app application
        self.headers_set = []
    
    def set_app(self,application):
        self.application = application
    
    def serve_forever(self):
        listen_socket = self.listen_socket
        while True:
            #New client conncetion
            self.client_connection,client_address = listen_socket.accept()
            #Handle one request and close the client connection.Then
            #loop over to wait for another client conncetion
            self.handle_one_request()
    
    def handle_one_request(self):
        request_data = self.client_connection.recv(1024)
        self.request_data = request_data = request_data.decode('utf-8')
        # Print formatted request data a la 'curl -v'
        print(''.join(
            f'<{line}\n' for line in request_data.splitlines()
        ))

        self.parse_request(request_data)

        #Construct enviroment dictionary using request data
        env = self.get_environ()

        #It's time to call our application callable and get back a result thawt will become http response body
        result = self.application(env,self.start_response)

        #Construct a response and send it back to the client
        self.finish_response(result)

    def parse_request(self,text):
        request_line = text.splitlines()[0]
        request_line = request_line.rstrip('\r\n')
        #Break down the request_line into components
        (self.request_method,#Get
         self.path, #/hello
         self.request_version#HTTP/1.1)
        )=request_line.split()
    
    def get_environ(self):
        env = {}
        #The following code snippet does not folow PEP8 conventions
        #but it's formatted the wawy it is for demonstration purpose to emphasize the required variables and their value
        # 
        # Ruquired WSGI variables
        env['wsgi.version']      = (1, 0)
        env['wsgi.url_scheme']   = 'http'
        env['wsgi.input']        = io.StringIO(self.request_data)
        env['wsgi.errors']       = sys.stderr
        env['wsgi.multithread']  = False
        env['wsgi.multiprocess'] = False
        env['wsgi.run_once']     = False
        # Required CGI variables
        env['REQUEST_METHOD']    = self.request_method    # GET
        env['PATH_INFO']         = self.path              # /hello
        env['SERVER_NAME']       = self.server_name       # localhost
        env['SERVER_PORT']       = str(self.server_port)  # 8888

        return env
    
    def start_response(self,status,response_headers,exc_info=None):
        #暂时有点一头雾水,等以后学了一些基础再回来学习... -- 2023/3/5 15:37 by Y1sh
    
