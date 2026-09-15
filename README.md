# 🚆 Smart Railway Monitoring System

<p align="center">
  <img src="https://img.shields.io/badge/Controller-LPC2148-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Architecture-ARM7TDMI--S-informational?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Language-Embedded%20C-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/IDE-Keil%20µVision-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Simulation-Proteus-red?style=for-the-badge" />
</p>

<p align="center">
  <b>A real-time embedded railway monitoring and information display system based on LPC2148 ARM7.</b>
</p>

---

## 📌 Project Overview

The **Smart Railway Monitoring System** is an embedded system developed using the **LPC2148 ARM7TDMI-S microcontroller** to simulate a real-time railway station information board.

The system uses an **RTC** to maintain the current date and time and compares it with predefined train schedules. When a train is approaching within the configured time window, its information is displayed on a **16×2 LCD**, along with **LED and buzzer alerts**.

The system also provides an **Admin Mode** through which authorized users can modify RTC settings and train information using a **4×4 keypad**.

---

## 🎯 Objectives

- Display real-time train information.
- Maintain train schedules using RTC.
- Detect approaching trains automatically.
- Provide visual and audio alerts.
- Allow modification of train schedules through Admin Mode.
- Validate train timing and platform information.
- Prevent platform timing conflicts.
- Provide a simple and user-friendly embedded interface.

---

## 🧩 System Block Diagram

<p align="center">
  <img src="images/block-diagram.png" alt="Smart Railway Monitoring System Block Diagram" width="900">
</p>

### System Flow

**Input Devices → LPC2148 Processing → Output Devices**

The LPC2148 acts as the central controller, receiving user input and real-time information, processing train schedules, and controlling the LCD, LEDs, and buzzer.

---

## 🧠 Project Mind Map

<p align="center">
  <img src="images/project-mind-map.png" alt="Smart Railway Monitoring System Mind Map" width="900">
</p>

The mind map summarizes the major areas of the project:

- **Input:** Keypad, Push Button, RTC
- **Processing:** LPC2148, schedule comparison, approaching-train detection
- **Admin Mode:** PIN authentication, data modification and validation
- **Output:** LCD, LEDs and buzzer
- **Core Features:** Real-time monitoring, scrolling display and multiple train handling
- **Technology:** Embedded C, Keil µVision and Proteus

---

# ⚙️ System Working

## 🟢 Normal Mode

After initialization, the system continuously monitors the current RTC time and compares it with the updated train schedules.

```text
System Initialization
        ↓
Read RTC Date & Time
        ↓
Compare Train Schedules
        ↓
Check Approaching Trains
        ↓
Train Within 5 Minutes?
      ↙             ↘
    YES              NO
     ↓                ↓
Display Train      Display Train
Information        Summary / RTC
     ↓
LED + Buzzer Alert
     ↓
Handle Active Trains
