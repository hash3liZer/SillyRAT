import sys
import os
import socket
import argparse
import threading

class PULL:

    def print(self, mess):
        print("[@] " + mess)

    def exit(self, mess):
        sys.exit("[~] " + mess)

pull = PULL()

class CLIENT:

    def __init__(self, sock, addr):
        self.sock    = sock
        self.address = addr

    def engage(self):
        return

class INTERFACE:

    SOCKET  = None
    RUNNER  = True

    def __init__(self, prs):
        self.address = prs.address
        self.port    = prs.port

    def bind(self):
        self.SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.SOCKET.bind((self.address, self.port))
            pull.print("Binded Successfully!")
        except E:
            pull.exit("Error While Binding!")

    def accept_threads(self):
        self.SOCKET.listen(10)
        while self.RUNNER:
            conn, addr = self.SOCKET.accept()
            client = CLIENT(conn, addr)
            client.engage()

    def accept(self):
        t = threading.Thread(target=self.accept_threads)
        t.daemon = True
        t.start()

    def launch(self):
        if


    def close(self):
        self.SOCKET.close()

class PARSER:

    def __init__(self, prs):
        self.address = self.v_address(prs.address)
        self.port    = self.v_port(prs.port)

    def v_address(self, str):
        return str

    def v_port(self, port):
        if not port:
            pull.exit("You need to Supply a Valid Port Number")
        
        if port <= 0 or port > 65535:
            pull.exit("Invalid Port Number")

        return port

def main():

    parser = argparse.ArgumentParser()

    parser.add_argument('-a', '--address', dest="address", default="0.0.0.0", type=str, help="Address to Bind to")
    parser.add_argument('-p', '--port'   , dest="port"   , default=0 , type=int, help="Port to Bind to")

    parser = parser.parse_args()

    parser = PARSER(parser)


    iface = INTERFACE(parser)
    iface.bind()
    iface.accept()
    iface.launch()
    iface.close()
    

if __name__ == "__main__":
    main()
