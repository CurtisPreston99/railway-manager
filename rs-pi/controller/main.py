import time
from driver.serial_interface import SerialInterface
from driver.motor_driver import MotorDriver
import sqlite3
import PySimpleGUI as sg

ui = True

def main():
    con = sqlite3.connect("system.db")
    cur = con.cursor()
    motorDriver = MotorDriver('COM4')

    drivers = [
        motorDriver
    ]
    try:
        layout = [[sg.Text('motor controler')]]
        if(ui):
            for driverIndex in range(len(drivers)):
                driver = drivers[driverIndex]
                layout.append(driver.getUi())
                layout.append([sg.Button('send',key=driverIndex)])

            
            window = sg.Window('Controler', layout)

            while True:
                event, values = window.read()
                if event == sg.WIN_CLOSED: # if user closes window
                    break

                driver = drivers[event]
                driver.updateFromUi(values)

                print(driver.id)
        else:
            while(True):
                time.sleep(1)
    finally:
        motorDriver.exit()


if __name__ == "__main__":
    main()
    