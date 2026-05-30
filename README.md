<div align="center">

# 🦾 Wireless Robotic Arm Control

**Real-time robotic arm control via hand gesture tracking — powered by MPU6050 IMU and Bluetooth communication between two Arduino Nano boards.**

![Arduino](https://img.shields.io/badge/Arduino-Nano-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Bluetooth](https://img.shields.io/badge/Bluetooth-HC--05-0082FC?style=for-the-badge&logo=bluetooth&logoColor=white)
![License](https://img.shields.io/badge/License-Non--Commercial-lightgrey?style=for-the-badge)

</div>

---

## 📖 Overview

This project implements a real-time robotic arm control system that translates natural hand movements into precise servo commands — wirelessly.

| Component | Details |
|---|---|
| **Motion Sensing** | MPU6050 IMU — captures hand orientation and acceleration |
| **Communication** | HC-05 Bluetooth modules — low-latency wireless link |
| **Architecture** | Dual Arduino Nano (Master / Slave) |
| **Trajectory** | Cubic spline interpolation for smooth, fluid motion |

The system supports two operating modes: **Manual** (real-time gesture control) and **Autonomous** (predefined sequence playback).

---

## 🏗️ System Architecture

<div align="center">

| 🎮 MASTER — Gesture Controller | 🤖 SLAVE — Robotic Arm |
|:---:|:---:|
| <img width="420" src="https://github.com/user-attachments/assets/104bb7b1-b20e-4b90-972a-daf423b8c788" /> | <img width="420" src="https://github.com/user-attachments/assets/5d986ad6-aaaa-49bd-86c0-656f87fd17e5" /> |
| Reads MPU6050 → transmits commands | Receives commands → drives servos |

</div>

---

## ✨ Features

- 🖐️ **Real-time hand gesture tracking** via IMU sensor
- 📡 **Wireless control** over Bluetooth — no cables required
- 🔄 **Dual operating modes** — Manual and Autonomous
- 📈 **Cubic interpolation** for smooth, human-like motion trajectories
- 🔌 **Custom-designed PCB** for clean hardware integration
- 🧩 **Modular master/slave architecture** — easily extensible

---

## 🛒 Hardware Components

| Component | Quantity | Role |
|---|:---:|---|
| Arduino Nano | ×2 | Master controller & Slave controller |
| MPU6050 IMU | ×1 | Hand motion sensing (accel + gyro) |
| HC-05 Bluetooth | ×2 | Wireless communication |
| Servo Motors | ×4 | Joint actuation on robotic arm |
| Custom PCB | ×1 | Integrated circuit board |

---

## ⚙️ Working Principle

```
[Hand Movement]
      │
      ▼
[MPU6050] ──→ [Master Arduino] ──→ [HC-05 TX]
                                         │
                                    (Bluetooth)
                                         │
                                    [HC-05 RX]
                                         │
                                         ▼
                               [Slave Arduino] ──→ [Servo Motors]
                                         │
                                         ▼
                               [Cubic Interpolation]
                               (smooth trajectories)
```

1. **Sense** — MPU6050 captures hand orientation in 3D space
2. **Process** — Master Arduino filters and encodes motion data
3. **Transmit** — Commands are sent wirelessly via HC-05 Bluetooth
4. **Execute** — Slave Arduino drives servo joints accordingly
5. **Smooth** — Cubic interpolation removes jerky motion artifacts

---

## 🎨 3D Arm Design

https://github.com/user-attachments/assets/fad48d52-3230-4014-bfa5-0044221ab020

---

## 🕹️ Operating Modes

### 🤖 Autonomous Mode

The arm replays a predefined sequence of movements automatically — useful for demonstrations or repetitive tasks.
 
https://github.com/user-attachments/assets/399675f3-544c-414e-842a-c3e3f3e36a60
 
#### 📊 Trajectory Smoothing — Before vs. After Cubic Interpolation
 
Cubic spline interpolation eliminates abrupt, step-like joint movements by fitting smooth curves through each waypoint. The comparison below demonstrates the difference in motion quality:
 
| ❌ Without Cubic Interpolation | ✅ With Cubic Interpolation |
|:---:|:---:|
|  <img width="282" height="500" alt="beforecubic-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/785cf269-4b4f-4ef0-94cc-a19c2a094d17" /> | <img width="226" height="500" alt="aftercubic-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/2cd1a08a-b468-4581-aa47-7cb4ec10ffd8" /> |
| Jerky, discontinuous motion | Smooth, fluid trajectories |
 
> 💡 **How it works:** Instead of jumping directly between setpoints, the controller fits a cubic polynomial through consecutive waypoints — ensuring continuity in both position and velocity at every joint.
 
---


### 🖐️ Manual Mode

The operator controls the arm in real time using hand gestures — intuitive and responsive.

https://github.com/user-attachments/assets/842e84bb-c8b7-4dce-be1b-8d80d3b32746

---

## 🚀 Future Improvements

| Improvement | Description |
|---|---|
| **Inverse Kinematics** | Coordinate-based end-effector control |
| **ROS Integration** | Full robot operating system compatibility |
| **ESP32 Upgrade** | Wi-Fi + faster processing to replace HC-05/Arduino Nano |
| **ML Gesture Recognition** | Classify complex gestures beyond raw orientation data |

---

## 📄 License

This project is developed for **educational and research purposes only**, not for **commercial**

---

<div align="center">

*Built with curiosity and a love for robotics* 🤖

</div>
