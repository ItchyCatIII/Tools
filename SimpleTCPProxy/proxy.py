#!/usr/bin/env python
import socket
import sys
import threading

def sender(client, s):
    while True:
        try:
            s.send(client.recv(99999))
        except:
            break
def receiver(client,s):
    while True:
        try:
            client.send(s.recv(99999))
        except:
            break

def tcpHandler(client, RHOST, RPORT):
    s = socket.socket()
    s.connect((RHOST, RPORT))
    send = threading.Thread(target=sender, args=(client, s))
    send.start()
    receive = threading.Thread(target=receiver, args=(client, s))
    receive.start()

LHOST = "0.0.0.0"
LPORT = 1234
RHOST = "localhost"
RPORT = 5901

server = socket.socket()
server.bind((LHOST,LPORT))
server.listen(5)
print "[*] Listening on %s %d" % (LHOST, LPORT)
try:
    while True:
        client, addr = server.accept()
        print "[+]Incomming connection from %s:%d" % (addr[0], addr[1])
        t = threading.Thread(target=tcpHandler, args=(client, RHOST, RPORT))
        t.start()
except (KeyboardInterrupt, SystemExit):
    sys.exit()
