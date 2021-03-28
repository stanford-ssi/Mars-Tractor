from board import SCL, SDA
import busio
from adafruit_pca9685 import PCA9685
import RPi.GPIO as GPIO
import threading
import time
from simple_pid import PID

class Encoder:
    position = 0

    def count_tick(self, channel):
        a_new = GPIO.input(self.input_pinA)
        b_new = GPIO.input(self.input_pinB)
        if(not self.a and not self.b and a_new and not b_new) or (self.a and not self.b and a_new and b_new) or (self.a and self.b and not a_new and b_new) or (not self.a and self.b and not a_new and not b_new):
            self.position += 1
        else:
            self.position -= 1
        self.a = a_new
        self.b = b_new
        

    def __init__(self, input_pinA, input_pinB):
        self.position = 0
        self.input_pinA = input_pinA
        self.input_pinB = input_pinB
        GPIO.setup(input_pinA, GPIO.IN)
        GPIO.setup(input_pinB, GPIO.IN)
        GPIO.add_event_detect(input_pinA, GPIO.BOTH, callback=self.count_tick)
        GPIO.add_event_detect(input_pinB, GPIO.BOTH, callback=self.count_tick)
        self.a = GPIO.input(input_pinA)
        self.b = GPIO.input(input_pinB)

    def reset_position(self):
        self.position = 0
    
    def get_position(self):
        return self.position

class Motor:

    VEL_SCALE_FACTOR = 655

    

    position = 0
    
    PID_TIME = .1
    PV=.05
    IV=.7
    DV=.001

    def __init__(self, pin_pwm, pin_a, pin_b, pca_object, encoder_a, encoder_b):
        self.a = pin_a
        self.b = pin_b
        self.pwm = pin_pwm
        self.pca = pca_object
        self.encoder = Encoder(encoder_a, encoder_b)
        self.pidV = PID(self.PV, self.IV, self.DV)
        self.pidV.output_limits=(-100,100)
        self.pid_active = False


    def set_power(self, power):
        power = int(power)
        if power > 0:
            self.pca.channels[self.a].duty_cycle = 0
            self.pca.channels[self.b].duty_cycle = 0xffff
            self.pca.channels[self.pwm].duty_cycle = power*self.VEL_SCALE_FACTOR
        elif power < 0:
            self.pca.channels[self.b].duty_cycle = 0
            self.pca.channels[self.a].duty_cycle = 0xffff
            self.pca.channels[self.pwm].duty_cycle = power*-self.VEL_SCALE_FACTOR
        else:
            self.pca.channels[self.a].duty_cycle = 0
            self.pca.channels[self.b].duty_cycle = 0
    
    def get_position(self):
        return self.encoder.get_position()

    def __velocity_PID(self, velocity):
        self.pidV.setpoint = velocity
        old_position = self.get_position()
        while self.pid_active:
            self.current_velocity = (self.get_position()-old_position)/self.PID_TIME
            old_position = self.get_position()
            command = self.pidV(self.current_velocity)
            self.set_power(command)
            time.sleep(self.PID_TIME)

    def set_velocity(self, velocity):
        self.pid_active=True
        self.pid_thread = threading.Thread(target=self.__velocity_PID, args=(velocity,))
        self.pid_thread.start()

    def get_velocity(self):
        return self.current_velocity

    def cancel_pid(self):
        self.pid_active=False
        

class Chassis:
    """
    Motor naming convention:
    1A-----1B
    |       |
    |       |
    2A-----2B
    |       |
    |       |
    3A-----3B
    """
    i2c = busio.I2C(SCL, SDA)
    pca = PCA9685(i2c, address=0x40)
    pca2 = PCA9685(i2c, address=0x41)
    pca.frequency = 50
    pca2.frequency = 50

    def getPosition(self):
        return self.b1.get_position()

    def setVelocity(self, velocity):
        self.b1.set_velocity(velocity)

    def getVelocity(self):
        return self.b1.get_velocity()
    
    a1 = Motor(15,14,13,pca2, 'DAP1_FS', 'GPIO_PQ4')
    b1 = Motor(12,11,10,pca2, 'GPIO_PQ5', 'CAN_GPIO2')
    a2 = Motor(9,8,7,pca2, 'DAP1_DIN', 'DAP1_DOUT')
    b2 = Motor(6,4,5,pca2, 'UART1_CTS', 'CAN_GPIO1')
    a3 = Motor(1,2,3,pca2, 'CAN_GPIO0', 'GPIO_MDM2')
    b3 = Motor(15,14,13,pca, 'GPIO_CAM5', 'GPIO_CAM4')

    motors = [a1,b1,a2,b2,a3,b3]

    def drive(self, power):
        for motor in self.motors:
            motor.set_power(power)
    
    def stop_all(self):
        self.drive(0)
        for motor in self.motors:
            motor.cancel_pid()

    def getVelocity(self):
        for motor in self.motors:
            print(motor.get_velocity())
        print('--------------')
    
    

chassis = Chassis()
chassis.drive(0)
"""
for _ in range(10):
    chassis.getVelocity()
    time.sleep(1)
chassis.stop_all()
"""
