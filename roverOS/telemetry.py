import socket
import struct
import rssi

class Telemetry:
   
    speed = 0
       
    def __init__(self, host, port, interface, ssid):
        self.ssids = [ssid]
        self.rssi_scanner = rssi.RSSI_Scan(interface)
        self.get_connection(host,port)

    def get_connection(self, host, port):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as self.s:
            print('waiting')
            self.s.bind((host, port))
            self.s.listen()
            self.conn, addr = self.s.accept()
            print('Connected by', addr)

    def __getTelemetryData(self):
        ap_info = self.rssi_scanner.getAPinfo(networks=self.ssids, sudo=False)
        try:
            signal_quality = (ap_info[0]['quality'])
        except:
            signal_quality = '-1'
        
        signal_quality = int(signal_quality.split('/')[0])
        telemetry_data = struct.pack('i', signal_quality)
        return telemetry_data

    def ping(self):
        data = self.conn.recv(1024)
        if data:#there is data and we are still connected to MC
            self.speed = (struct.unpack('f', data))[0]
            self.conn.sendall(self.__getTelemetryData())
            return True
        else:#there is no data, we lost signal, go into failsafe
            self.speed = 0
            return False
        