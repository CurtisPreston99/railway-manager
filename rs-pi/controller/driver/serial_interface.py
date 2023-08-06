import serial
import json


class SerialInterface:

    def __init__(self, port, baud_rate=9600, timeout=1, statusCallback=lambda x: x):
        self.debugLogs = False
        self.port = port
        self.baud_rate = baud_rate
        self.timeout = timeout
        self.ser = None
        self.listening = False
        self.statusCallback = statusCallback

    def open_serial_port(self):
        try:
            self.ser = serial.Serial(
                self.port, self.baud_rate, timeout=self.timeout)
            print(f"Serial port {self.port} opened.")
        except serial.SerialException as e:
            print(f"Error: {e}")

    def close_serial_port(self):
        self.listening = False
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
        self.listening = True
        while self.listening:
            try:
                # Read data from the serial port
                data = self.ser.readline().decode()
                print(f"Received data: {data}")
                if(len(data)>0):
                    jsonData = json.loads(data)
                    self.statusCallback(jsonData)
            except json.JSONDecodeError as e:
                print(f"Error decoding json data: {e}: {data}")

            except UnicodeDecodeError as e:
                print(f"Error decoding data: {e}")
            except KeyboardInterrupt:
                # Stop listening if Ctrl+C is pressed
                break
