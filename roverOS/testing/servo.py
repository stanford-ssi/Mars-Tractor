from board import SCL, SDA
import busio
from adafruit_motor import servo
from adafruit_pca9685 import PCA9685
import time

i2c = busio.I2C(SCL, SDA)
devices = i2c.scan()

pca = PCA9685(i2c, address=0x40)
pca.frequency = 150

print("pin setup complete")

servo1a = servo.Servo(pca.channels[3], min_pulse=500, max_pulse=2500)
servo1b = servo.Servo(pca.channels[7], min_pulse=500, max_pulse=2500)
servo2a = servo.Servo(pca.channels[11], min_pulse=500, max_pulse=2500)
servo2b = servo.Servo(pca.channels[15], min_pulse=500, max_pulse=2500)
#servo3a = servo.Servo(pca.channels[19], min_pulse=500, max_pulse=2500)
#servo3b = servo.Servo(pca.channels[23], min_pulse=500, max_pulse=2500)

everyone = [servo1a, servo1b, servo2a, servo2b]

while True:
    servo2a.angle=180
    time.sleep(2)
    servo2a.angle=0
    time.sleep(15)
