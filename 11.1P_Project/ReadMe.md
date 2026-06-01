# Smart Blind Assistance System

## Project Overview

This project was developed as part of the Embedded Systems Development unit.

The aim of the project is to create a Smart Blind Assistance System that helps visually impaired users detect obstacles and identify low-light environments. The system combines an Arduino Nano 33 IoT and a Raspberry Pi 3B+ to provide real-time sensing, user feedback, monitoring, and fault detection.

The Arduino Nano 33 IoT is responsible for reading sensor data and controlling outputs, while the Raspberry Pi acts as a supervisory controller that monitors the system, logs events, and detects faults.

---

## Hardware Components

The following hardware components were used:

- Arduino Nano 33 IoT
- Raspberry Pi 3B+
- HC-SR04 Ultrasonic Sensor
- BH1750 Light Sensor
- Active Buzzer
- LED
- 1kΩ and 2kΩ Resistors (Voltage Divider)
- Breadboard and Jumper Wires
- USB Cable

---

## System Features

The system includes the following features:

- Obstacle detection using an ultrasonic sensor
- Ambient light monitoring using a BH1750 sensor
- Audio feedback through a buzzer
- Visual feedback through an LED
- Real-time serial communication between Arduino and Raspberry Pi
- Event logging
- Communication watchdog monitoring
- Sensor fault detection

---

## How the System Works

The HC-SR04 ultrasonic sensor continuously measures the distance between the user and nearby obstacles.

Depending on the measured distance, the Arduino generates different warning levels:

- Safe State (greater than 50 cm)
- Warning State (15–30 cm)
- Critical State (less than 15 cm)

The BH1750 sensor measures ambient light intensity.

When the light level falls below the configured threshold, the LED turns on to indicate a dark environment.

Sensor readings are sent from the Arduino Nano 33 IoT to the Raspberry Pi through USB serial communication.

The Raspberry Pi receives the data, monitors system status, detects faults, and stores readings in a log file.

---

## Hardware Connections

### HC-SR04 Ultrasonic Sensor

| Sensor Pin | Arduino Pin |
|------------|------------|
| VCC | 5V |
| GND | GND |
| TRIG | D2 |
| ECHO | D3 (through voltage divider) |

### BH1750 Light Sensor

| Sensor Pin | Arduino Pin |
|------------|------------|
| VCC | 3.3V |
| GND | GND |
| SDA | SDA |
| SCL | SCL |

### LED

| LED Pin | Arduino Pin |
|----------|------------|
| Positive | D6 (through resistor) |
| Negative | GND |

### Active Buzzer

| Buzzer Pin | Arduino Pin |
|------------|------------|
| Positive | D9 |
| Negative | GND |

---

## Software Structure

### Arduino Nano 33 IoT

The Arduino is responsible for:

- Reading ultrasonic sensor data
- Reading light sensor data
- Controlling the buzzer
- Controlling the LED
- Sending sensor information to the Raspberry Pi

Source file:

```text
Arduino/smart_blind_assistance.ino
```

### Raspberry Pi

The Raspberry Pi is responsible for:

- Receiving serial data
- Monitoring system status
- Detecting communication faults
- Detecting sensor faults
- Logging events

Source file:

```text
RaspberryPi/supervisor.py
```

---

## Running the Project

### Arduino Setup

1. Open Arduino IDE.
2. Install the BH1750 library.
3. Upload the Arduino code to the Nano 33 IoT.
4. Open Serial Monitor to verify sensor readings.

### Raspberry Pi Setup

Install the required package:

```bash
sudo apt install python3-serial
```

Run the supervisory controller:

```bash
python3 supervisor.py
```

---

## Fault Tolerance

One of the main objectives of this project was implementing fault tolerance.

The Raspberry Pi provides:

### Communication Watchdog

The Raspberry Pi continuously expects data from the Arduino.

If communication stops for more than a few seconds, a communication fault is detected.

Example:

```text
FAULT: COMMUNICATION LOST
```

### Sensor Fault Detection

If the ultrasonic sensor fails to return a valid measurement, the Arduino sends a fault value.

Example:

```text
Distance=999
```

The Raspberry Pi recognises this value and enters a sensor fault state.

### Event Logging

All received sensor readings are stored in a log file for future analysis and debugging.

---

## Future Improvements

If this project were developed further, the following features could be added:

- Voice guidance for users
- GPS navigation support
- Vibration feedback
- Mobile application integration
- Cloud connectivity
- Computer vision object detection
- Battery-powered portable design

---

## Author

Atharva Patel

Embedded Systems Development Project

Deakin University
