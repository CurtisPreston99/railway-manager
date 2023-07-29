import serial
import time
import json
import threading

class SerialInterfacer:
    
    def __init__(self, port, baud_rate=9600, timeout=1):
        self.debugLogs = False
        self.port = port
        self.baud_rate = baud_rate
        self.timeout = timeout
        self.ser = None

    def open_serial_port(self):
        try:
            self.ser = serial.Serial(self.port, self.baud_rate, timeout=self.timeout)
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
            if(self.debugLogs):
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

if __name__ == "__main__":
    serial_port = "COM4"

    # Replace the following line with the data you want to send
    data_to_send = {
        "motor_1": {"spd":100,"forward":True},
        "motor_2":{"spd":100,"forward":False},
    }

    
    '{"motor_1":{"spd":100,"forward":true},"motor_2":{"spd":50,"forward":false}}'
    # Create an instance of the SerialCommunicator class
    communicator = SerialInterfacer(serial_port)

    try:
        # Open the serial port
        communicator.open_serial_port()

        # Send and receive data

        serial_thread = threading.Thread(target=communicator.read_serial)
        serial_thread.daemon = True  # Allow the thread to be terminated when the main program exits
        serial_thread.start()

        while True:
            # For example, you can run some other tasks in the main thread
            print("Running other tasks...")
            # Add your other functions or tasks here

            # Sleep for a short time to allow the other functions to run
            # Adjust this sleep time based on your specific use case
            communicator.send_data(data_to_send)
            time.sleep(3)

    finally:
        # Close the serial port when done
        communicator.close_serial_port()
