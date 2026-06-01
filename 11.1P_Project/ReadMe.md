# Smart Blind Assistance System

## Overview

This project is a Smart Blind Assistance System developed using an Arduino Nano 33 IoT and Raspberry Pi 3B+.

The system assists visually impaired users by detecting nearby obstacles and monitoring ambient light conditions.

## Hardware Components

- Arduino Nano 33 IoT
- Raspberry Pi 3B+
- HC-SR04 Ultrasonic Sensor
- BH1750 Light Sensor
- LED
- Active Buzzer
- Voltage Divider (1kΩ and 2kΩ)

## Features

- Obstacle Detection
- Ambient Light Monitoring
- Audio Warning System
- Visual Status Indicator
- Raspberry Pi Supervisory Monitoring
- Communication Watchdog
- Sensor Fault Detection
- Event Logging

## Pin Mapping

| Component | Arduino Pin |
|------------|-------------|
| HC-SR04 TRIG | D2 |
| HC-SR04 ECHO | D3 |
| BH1750 SDA | SDA |
| BH1750 SCL | SCL |
| LED | D6 |
| Buzzer | D9 |

## Running the Project

### Arduino

Upload:

smart_blind_assistance.ino

### Raspberry Pi

Install:

```bash
sudo apt install python3-serial
```

Run:

```bash
python3 supervisor.py
```

## Fault Tolerance

The Raspberry Pi implements:

- Communication watchdog monitoring
- Sensor fault detection
- Event logging

## Author

Atharva Patel
