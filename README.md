# 🚆 Smart Railway Monitoring System

<p align="center">
  <img src="https://img.shields.io/badge/LPC2148-ARM7TDMI--S-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Embedded-C-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Keil-µVision-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Proteus-Simulation-red?style=for-the-badge" />
</p>

<p align="center">
  <b>A real-time railway monitoring and information display system developed using the LPC2148 ARM7 microcontroller.</b>
</p>

<p align="center">
  Real-Time Train Information • Smart Alerts • Admin Control
</p>

## 📌 Project Overview

The **Smart Railway Monitoring System** is an embedded system developed using the **LPC2148 ARM7TDMI-S microcontroller** to provide real-time railway information and train status monitoring.

The system uses an **RTC (Real-Time Clock)** to maintain the current date and time and compares it with the scheduled train timings. When a train is approaching within the configured time window, the system displays the train information on a **16×2 LCD** and provides **LED and buzzer alerts**.

The system also includes an **Admin Mode**, which allows authorized users to modify RTC settings and train information through a **4×4 keypad**. Input validation and platform collision checking are performed before updated train information is saved.

## 🎯 Objectives

- 🕒 Maintain and display real-time date and time using an RTC.
- 🚆 Store and manage information for multiple trains.
- 📺 Display train details such as train number, name, destination, timing and platform.
- ⏱️ Automatically detect approaching trains within the defined time window.
- 🚦 Provide visual train-status indication using LEDs.
- 🔊 Provide audio alerts using a buzzer.
- 🔄 Display long train names using LCD scrolling.
- 🔐 Provide secure Admin Mode using PIN authentication.
- ✏️ Allow modification of RTC and train information through a keypad.
- 🛤️ Validate platform assignments and detect platform timing conflicts.
- ✅ Validate user inputs before saving changes.

