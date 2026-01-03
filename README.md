# Smart Secure Access Gate

## Overview
Smart Secure Access Gate is an IoT-based access control system that combines real-time embedded control with high-level processing and internet connectivity.  
The system uses **Arduino (C/C++)** for deterministic, real-time motor and safety control, and **Raspberry Pi (Python)** for authentication, monitoring, data logging, and IP camera integration.

This project was developed as a **Capstone Project** for the course  
**Programming for the Internet of Things – University of California, Irvine (UCI)**.

---

## System Architecture
The system follows a **distributed architecture**:

- **Arduino Uno**
  - Real-time motor control
  - Safety monitoring (IR sensors, current sensing, limit switches)
  - Immediate reaction to hazardous conditions
- **Raspberry Pi 4**
  - User authentication (keypad-based user ID)
  - Central decision making
  - IP camera handling
  - Event logging and web-based monitoring

Communication between Arduino and Raspberry Pi is performed via **serial communication (UART)**.

---

## Hardware Components
- Arduino Uno
- Raspberry Pi 4
- DC Gear Motor (PWM controlled)
- Motor Driver (H-Bridge)
- IP Camera (Hikvision or compatible)
- IR Obstacle Sensors
- Current / Pressure Sensing Circuit
- Limit Switches (Fully Open / Fully Closed)
- Emergency Stop Button
- Buzzer / Siren
- Alarm LED
- 12V Power Supply + Buck Converter (12V → 5V)

---

## Software Stack
### Arduino (C/C++)
- Real-time motor control using PWM
- Sensor monitoring loop
- Safety interrupt handling
- Serial command interface

### Raspberry Pi (Python)
- User authentication logic
- IP camera streaming and capture
- Tailgating (multiple-person entry) detection
- Event logging and database storage
- Web-based monitoring interface

Main libraries and tools:
- Python 3
- OpenCV (image/video processing)
- Flask (web dashboard)
- SQLite (local database)

---

## Repository Structure
