import serial
import time
import json
import threading
import keyboard
import PySimpleGUI as sg


class SerialInterfacer:

    def __init__(self, port, baud_rate=9600, timeout=1):
        self.debugLogs = False
        self.port = port
        self.baud_rate = baud_rate
        self.timeout = timeout
        self.ser = None

    def open_serial_port(self):
        try:
            self.ser = serial.Serial(
                self.port, self.baud_rate, timeout=self.timeout)
            print(f"Serial port {self.port} opened.")
        except serial.SerialException as e:
            print(f"Error: {e}")

    def close_serial_port(self):
        if self.ser:
            self.ser.close()
            print(f"Serial port {self.port} closed.")

    def send_data(self, data_to_send):
        try:
            # Clear input buffer
            self.ser.reset_input_buffer()

            # Send data to the serial port
            json_string = json.dumps(data_to_send)
            if (self.debugLogs):
                print(json_string)

            self.ser.write(json_string.encode())
            self.ser.flush()
        except serial.SerialException as e:
            print(f"Error: {e}")
            return None

    def read_serial(self):
        while True:
            try:
                # Read data from the serial port
                data = self.ser.readline()
                print(f"Received data: {data}")

            except UnicodeDecodeError as e:
                print(f"Error decoding data: {e}")
            except KeyboardInterrupt:
                # Stop listening if Ctrl+C is pressed
                break

def makeMotorFromUi(inputs):
    #  {'m1_spd': 45.0, 'm1_fwd': False, 'm1_rev': True, 'm1_spd0': 0.0, 'm2_fwd': False, 'm2_rev': True}
    data = {
        "motor_1": {"spd": inputs["m1_spd"], "forward": inputs["m1_rev"]},
        "motor_2": {"spd": inputs["m2_spd"], "forward": inputs["m2_rev"]},
        "motor_3": {"spd": inputs["m3_spd"], "forward": inputs["m3_rev"]},
        "motor_4": {"spd": inputs["m4_spd"], "forward": inputs["m4_rev"]},
    }
    return data

if __name__ == "__main__":
    serial_port = "COM5"

    # Replace the following line with the data you want to send
    data_to_send = {
        "motor_1": {"spd": 100, "forward": True},
        "motor_2": {"spd": 100, "forward": False},
    }

    '{"motor_1":{"spd":100,"forward":true},"motor_2":{"spd":50,"forward":false}}'
    # Create an instance of the SerialCommunicator class
    communicator = SerialInterfacer(serial_port)

    try:
        # Open the serial port
        communicator.open_serial_port()

        # Send and receive data

        serial_thread = threading.Thread(target=communicator.read_serial)
        # Allow the thread to be terminated when the main program exits
        serial_thread.daemon = True
        serial_thread.start()

        sg.theme('DarkAmber')   # Add a touch of color
        layout = [[sg.Text('motor controler')],
                  [sg.Text('motor 1'), sg.Slider(orientation='h',range=[0,100],k='m1_spd'),sg.Radio('fwd', "motor_1_dir", default=True, k='m1_fwd'), sg.Radio('rev', "motor_1_dir", default=True, k='m1_rev')],
                  [sg.Text('motor 2'), sg.Slider(orientation='h',range=[0,100],k='m2_spd'), sg.Radio('fwd', "motor_2_dir", default=True, k='m2_fwd'), sg.Radio('rev', "motor_2_dir", default=True, k='m2_rev')],
                  [sg.Text('motor 3'), sg.Slider(orientation='h',range=[0,100],k='m3_spd'), sg.Radio('fwd', "motor_3_dir", default=True, k='m3_fwd'), sg.Radio('rev', "motor_3_dir", default=True, k='m3_rev')],
                  [sg.Text('motor 4'), sg.Slider(orientation='h',range=[0,100],k='m4_spd'), sg.Radio('fwd', "motor_4_dir", default=True, k='m4_fwd'), sg.Radio('rev', "motor_4_dir", default=True, k='m4_rev')],
                  [sg.Button('Ok'), sg.Button('Cancel')]]

        window = sg.Window('Window Title', layout)

        while True:

            event, values = window.read()
            if event == sg.WIN_CLOSED or event == 'Cancel':  # if user closes window or clicks cancel
                break
            print('You entered ', values)
            newMotorValues = makeMotorFromUi(values)
            print(newMotorValues)
            communicator.send_data(newMotorValues)


    finally:
        # Close the serial port when done
        communicator.close_serial_port()



