import sys
import os
import socket

TARGETIP  =  "127.0.0.1"
TARGETPO  =  54000

class SILLCONNECTION:

    ss = None
    
    def __init__(self, _ip, _port):
        self.ipaddress  = _ip
        self.port       = _port

    def engage(self):
        while True:
                

def main():
    sillyclient = SILLCONNECTION()
    sillyclient.engage()

if __name__ == "__main__":
    main()