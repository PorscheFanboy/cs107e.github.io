#!/usr/bin/env python
from __future__ import print_function
import sys
import getopt
import serial
import os
from xmodem import XMODEM

def usage():
    print( "usage: rpi-install.py [-p] [port] file" )
    print( " -p   ..... print output from the Pi" )
    print( " port ..... serial port (optional)" )
    print( " file ..... binary file to upload" )

def exists(path):
    try:
        os.stat(path)
    except OSError:
        return False
    return True

try:
    opts, args = getopt.getopt(sys.argv[1:], "p")
except getopt.GetoptError:
    usage()
    sys.exit(1)

if len(args) < 1:
    usage()
    sys.exit(1)


printflag = False
for opt, arg in opts:
    if opt == '-p':
        printflag = True

if len(args) == 2:
    portname = args[0]
    filename = args[1]
else:
    # common serial ports
    portname = None
    if portname is None:
        name = "/dev/tty.SLAB_USBtoUART"
        if exists(name): 
            portname = name
    if portname is None:
        name = "/dev/ttyUSB0"
        if exists(name):
            portname = name
    if portname is None:
        name = "/dev/ttyUSB1"
        if exists(name):
            portname = name

    filename = args[0]


port = serial.Serial(port=portname, baudrate=115200)
if not port:
    print(portname, 'not found')
    sys.exit(1)

if not os.path.isfile(filename):
    print(filename, 'not found')
    sys.exit(1)

stream = open(filename, 'rb')

# problem was the timeout=0
#   needed to wait for NAK
def getc(size, timeout=1):
    return port.read(size)

def putc(data, timeout=1):
    port.write(data)

xmodem = XMODEM(getc, putc)

status = xmodem.send(stream)
print('sent', status)
stream.close()

if printflag:
    try:
        while True:
            c = getc(1)
            if c is None:
                break
            print(c,end='')
    except:
        pass

sys.exit(int(not status))

