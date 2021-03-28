#from chassis import Chassis
from telemetry import Telemetry
from chassis import Chassis
#192.168.1.107

IP_ADDRESS = '10.0.0.22'
PORT = 65432
SSID = 'utmresak'

telemetry = Telemetry(IP_ADDRESS, PORT, 'wlan0', SSID)
chassis = Chassis()

while True:
    connected = telemetry.ping()
    if not connected:#failsafe condition
        chassis.stop_all()#for extra safety but technically redundant as telemetry.speed is set to 0 failsafe condition
        telemetry.get_connection(IP_ADDRESS, PORT)
    
    chassis.drive(int(telemetry.speed*100))
