import serial
from config import SERIAL_PORT, BAUDRATE

ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)

def send_command(cmd: str):
    ser.write(f"{cmd}\n".encode())

def read_status():
    if ser.in_waiting:
        return ser.readline().decode().strip()
    return None
