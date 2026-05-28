# wireless-robotic-arm-control
A wireless robotic arm control system using hand gesture tracking with MPU6050 and Bluetooth communication between two Arduino Nano boards.

---

## Overview

This project implements a real-time robotic arm control system using:
- Hand motion tracking via MPU6050 IMU
- Wireless communication using HC-05 Bluetooth modules
- Dual Arduino Nano architecture (Master/Slave)
- Cubic interpolation for smoother robotic arm trajectories
The system supports both:
- Manual Mode
- Autonomous Playback Mode

---


## System Architecture

| MASTER Controller | SLAVE Robotic Arm |
|:-----------------:|:-----------------:|
| <img width="420" src="https://github.com/user-attachments/assets/104bb7b1-b20e-4b90-972a-daf423b8c788" /> | <img width="420" src="https://github.com/user-attachments/assets/5d986ad6-aaaa-49bd-86c0-656f87fd17e5" /> |

---

## Features

- Real-time hand gesture tracking
- Wireless robotic arm control
- Dual operating modes
- Cubic interpolation trajectory smoothing
- Custom-designed PCB
- Modular master/slave architecture

---

## Hardware Components

- Arduino Nano ×2
- MPU6050 IMU Sensor
- HC-05 Bluetooth Module
- Servo Motors
- Custom PCB

---

## Working Principle

1. MPU6050 captures hand orientation and motion data
2. Master Arduino processes IMU data
3. Motion commands are transmitted wirelessly via HC-05
4. Slave Arduino controls robotic arm servos
5. Cubic interpolation smooths motion trajectories

---

## Design Arm Model

https://github.com/user-attachments/assets/fad48d52-3230-4014-bfa5-0044221ab020

---

## Operating Modes

### Autonomous Mode

The robotic arm can replay predefined movement sequences automatically.

https://github.com/user-attachments/assets/399675f3-544c-414e-842a-c3e3f3e36a60

---

### Manual Mode

Real-time robotic arm control using hand gestures.

https://github.com/user-attachments/assets/842e84bb-c8b7-4dce-be1b-8d80d3b32746

---


## Future Improvements

- Kalman Filter for sensor fusion
- Inverse Kinematics
- ROS Integration
- ESP32 upgrade
- Machine learning gesture recognition

---


Project is for educational and research use only, non-commercial.
