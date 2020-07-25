import sys
import os
import socket
import time
import argparse
import threading

__LOGO__ = """
 ____  _ _ _       ____      _  _____ 
/ ___|(_) | |_   _|  _ \\    / \\|_   _|
\\___ \\| | | | | | | |_) |  / _ \\ | |  
 ___) | | | | |_| |  _ <  / ___ \\| |  
|____/|_|_|_|\\__, |_| \\_\\/_/   \\_\\_|  
             |___/                    
                    %s v1.0 @hash3liZer/@TheFlash2k
"""

class PULL:

    WHITE = '\033[1m\033[0m'
    PURPLE = '\033[1m\033[95m'
    CYAN = '\033[1m\033[96m'
    DARKCYAN = '\033[1m\033[36m'
    BLUE = '\033[1m\033[94m'
    GREEN = '\033[1m\033[92m'
    YELLOW = '\033[1m\033[93m'
    RED = '\033[1m\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'
    LINEUP = '\033[F'

    def __init__(self):
        if not self.support_colors:
            self.win_colors()
    
    def support_colors(self):
        plat = sys.platform
        supported_platform = plat != 'Pocket PC' and (plat != 'win32' or \
														'ANSICON' in os.environ)
        is_a_tty = hasattr(sys.stdout, 'isatty') and sys.stdout.isatty()
        if not supported_platform or not is_a_tty:
            return False
        return True

    def win_colors(self):
        self.WHITE = ''
        self.PURPLE = ''
        self.CYAN = ''
        self.DARKCYAN = ''
        self.BLUE = ''
        self.GREEN = ''
        self.YELLOW = ''
        self.RED = ''
        self.BOLD = ''
        self.UNDERLINE = ''
        self.END = ''

    def get_com(self):
        return input(self.DARKCYAN + "$" + self.END + self.RED + " " + self.END)

    def print(self, mess):
        print(self.GREEN + "[" + self.UNDERLINE + "*" + self.END + self.GREEN + "] " + self.END + mess + self.END)

    def exit(self, mess=""):
        sys.exit(self.RED + "[" + self.UNDERLINE + "~" + self.END + self.RED + "] " + self.END + mess + self.END)

    def logo(self):
        print(self.DARKCYAN + __LOGO__ % self.YELLOW + self.END)

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
    CLIENTS = {}

    def __init__(self, prs):
        self.address = prs.address
        self.port    = prs.port

    def bind(self):
        self.SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.SOCKET.bind((self.address, self.port))
            pull.print("Successfuly Bind to %s%s:%i" % (
                pull.RED,
                self.address,
                self.port,
            ))
        except Exception as e:
            pull.exit("Unable to bind to %s%s:%i" % (
                pull.RED,
                self.address,
                self.port,
            ))

    def accept_threads(self):
        self.SOCKET.listen(10)

        while self.RUNNER:
            conn, addr = self.SOCKET.accept()
            
            if addr[0] not in tuple(self.CLIENTS.keys()):
                client = CLIENT(conn, addr)
                client.engage()

                self.CLIENTS[addr[0]] = (
                    addr[0],
                    addr[1],
                    client
                )

            #client = CLIENT(conn, addr)
            #client.engage()

    def accept(self):
        t = threading.Thread(target=self.accept_threads)
        t.daemon = True
        t.start()

    def execute(self, val):
        if val == "exit":
            pull.exit()
        elif val == "sessions":
            print("Sessions")

    def launch(self):
        pull.print("Launching Interface! Enter 'help' to get avaible commands! \n")

        while True:
            val = pull.get_com()

            self.execute(val)

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
    pull.logo()

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
