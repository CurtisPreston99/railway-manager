import sqlite3
from driver.serial_interface import SerialInterface
import threading
import uuid
import PySimpleGUI as sg
from entities.motor_status import MotorStatus

class MotorDriver:
    def statusUpdate(self, status):
        self.status = MotorStatus().fromDict(status)
        print(self.id, status)

    def __init__(self, port):
        self.id = uuid.uuid4()
        self.status = MotorStatus()
        self.port = port
        self.Serial = SerialInterface(
            port, statusCallback=lambda x: self.statusUpdate(x))
        self.Serial.open_serial_port()
        serial_thread = threading.Thread(target=self.Serial.read_serial)
        # Allow the thread to be terminated when the main program exits
        serial_thread.daemon = True
        serial_thread.start()

    def exit(self):
        self.Serial.close_serial_port()

    def updateStatus(self, status:MotorStatus):
        self.Serial.send_data(status.toDict())

    def getStatus(self):
        return self.status

    def getUi(self):
        return [[sg.Text('motor controler')],
                [sg.Text('motor 1'), 
                 sg.Slider(orientation='h', range=[0, 100], k=str(self.id)+':m1_spd'), 
                 sg.Radio('fwd', "motor_1_dir", default=True, k=str(self.id)+':m1_fwd'), 
                 sg.Radio('rev', "motor_1_dir", default=True, k=str(self.id)+':m1_rev')],
                [sg.Text('motor 2'),
                 sg.Slider(orientation='h', range=[0, 100], k=str(self.id)+':m2_spd'), 
                 sg.Radio('fwd', "motor_2_dir", default=True, k=str(self.id)+':m2_fwd'), 
                 sg.Radio('rev', "motor_2_dir", default=True, k=str(self.id)+':m2_rev')],
                [sg.Text('motor 3'), 
                 sg.Slider(orientation='h', range=[0, 100], k=str(self.id)+':m3_spd'), 
                 sg.Radio('fwd', "motor_3_dir", default=True, k=str(self.id)+':m3_fwd'), 
                 sg.Radio('rev', "motor_3_dir", default=True, k=str(self.id)+':m3_rev')],
                [sg.Text('motor 4'), 
                 sg.Slider(orientation='h', range=[0, 100], k=str(self.id)+':m4_spd'), 
                 sg.Radio('fwd', "motor_4_dir", default=True, k=str(self.id)+':m4_fwd'), 
                 sg.Radio('rev', "motor_4_dir", default=True, k=str(self.id)+':m4_rev')],
                ]
    
    def updateFromUi(self,update):
        newStatus = MotorStatus()
        
        newStatus.motor1.spd = update[str(self.id)+':m1_spd']
        newStatus.motor1.forward = update[str(self.id)+':m1_fwd']

        newStatus.motor2.spd = update[str(self.id)+':m2_spd']
        newStatus.motor2.forward = update[str(self.id)+':m2_fwd']

        newStatus.motor3.spd = update[str(self.id)+':m3_spd']
        newStatus.motor3.forward = update[str(self.id)+':m3_fwd']

        newStatus.motor4.spd = update[str(self.id)+':m4_spd']
        newStatus.motor4.forward = update[str(self.id)+':m4_fwd']
        self.updateStatus(newStatus)
