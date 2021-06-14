#!/usr/bin/env python3

import socket
import pygame.joystick
import struct

HOST = '10.0.0.22'  # The server's hostname or IP address
PORT = 65432       # The port used by the server

pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)

print('start')
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    
    while True:
        #print(data)
        pygame.event.get()
        axis0 = joystick.get_axis(0)
        axis1 = joystick.get_axis(1)
        axis2 = joystick.get_axis(2)
        command = struct.pack('fff', axis0, axis1, axis2)
        s.sendall(command)
        
        data = s.recv(1024)
        if not data:
            break
        rssi = struct.unpack('i', data)[0]
        print(rssi)




