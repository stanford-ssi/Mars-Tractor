from board import SCL, SDA
import busio
from adafruit_motor import servo
from adafruit_pca9685 import PCA9685
import time
import socket
import struct

HOST = '10.0.0.22'  # Standard loopback interface address (localhost)
PORT = 65431

i2c = busio.I2C(SCL, SDA)
pca = PCA9685(i2c)
pca.frequency = 50

#8,9,10
servo8 = servo.Servo(pca.channels[8], min_pulse=0, max_pulse=19500)
print("init complete")



with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            speed = (struct.unpack('f', data))[0]
            conn.sendall(b'a')

            if speed>.01:
                print(speed*180)
                pca.channels[10].duty_cycle = 0
                pca.channels[9].duty_cycle = 0xffff
                servo8.angle = speed*180
            elif speed<-.01:
                print(speed*-180)
                pca.channels[9].duty_cycle = 0
                pca.channels[10].duty_cycle = 0xffff
                servo8.angle = speed*-180
            else:
                pca.channels[9].duty_cycle = 0
                pca.channels[10].duty_cycle = 0





