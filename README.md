
# 🚗 Smart Parking Sensor

## 📝 Project Overview
This is an advanced parking assistance system designed as a mechatronic project. It combines high-accuracy ultrasonic distance sensing with a smooth graphical interface.

The system features an **Exponential Moving Average (EMA)** filter to eliminate sensor noise and a **Fast Response** algorithm for immediate emergency detection.

## 💻 Tech Stack
<p align="left">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/Autodesk%20EAGLE-0696D7?style=for-the-badge&logo=autodesk&logoColor=white" />
  <img src="https://img.shields.io/badge/ESP32-E67E22?style=for-the-badge&logo=espressif&logoColor=white" />
</p>

---

## 🛠️ Components Used
- **Microcontroller:** ESP32 (DEVKITV1).
- **Distance Sensor:** HC-SR04 Ultrasonic module.
- **Display:** SSD1306 128x64 OLED (I2C) for real-time bar animation.
- **Indicators:**
  - 🟢 **Green LED:** Safe distance (>30cm).
  - 🟡 **Yellow LED:** Caution (20-30cm).
  - 🔴 **Red LED:** Danger (<20cm).
- **Audio:** Active Buzzer (**F/CM12P**) with dynamic frequency.
- **Control:** Hardware **Mute Button** for sound toggling.

---

## 📐 Hardware Design
The PCB was designed in **Autodesk EAGLE** with a focus on durability and clean layout:
- **Board Dimensions:** 180 x 70 mm.
- **Mounting:** 4x 3.2mm symmetric holes for M3 screws.
- **Layout:** Optimized 2.54mm grid for prototyping consistency.

### 🔌 Pinout Table
| Component | Pin | Note |
| :--- | :--- | :--- |
| **HC-SR04 Trig** | GPIO 5 | Output Trigger |
| **HC-SR04 Echo** | GPIO 18 | Input Echo |
| **OLED SDA** | GPIO 21 | I2C Data |
| **OLED SCL** | GPIO 22 | I2C Clock |
| **Buzzer (+)** | GPIO 27 | PWM Tone Control |
| **Mute Button** | GPIO 4 | Internal Pull-up |
| **LEDs (G, Y, R)**| 13, 12, 14 | Digital Indicators |

---

## 🚀 Software Logic
The firmware includes:
1. **Signal Smoothing:** Prevents the progress bar from flickering using software-based EMA.
2. **Fast Response:** Instantly updates if the distance changes by >15cm to handle rapid movements.
3. **Dynamic Beeping:** The closer the object, the higher the tone and shorter the delay.

---

## 📂 Repository Structure
- `/Firmware` - Arduino source code (.ino).
- `/Hardware` - EAGLE schematic (.sch) and board (.brd) files.
- `/Exports` - Visualizations, PDF schematics, and PCB renders.


