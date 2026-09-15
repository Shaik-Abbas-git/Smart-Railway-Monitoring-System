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

---

## 📌 Project Overview

The **Smart Railway Monitoring System** is an embedded system developed using the **LPC2148 ARM7TDMI-S microcontroller** to provide real-time railway information and train status monitoring.

The system uses an **RTC (Real-Time Clock)** to maintain the current date and time and compares it with the scheduled train timings. When a train is approaching within the configured time window, the system displays the train information on a **16×2 LCD** and provides **LED and buzzer alerts**.

The system also includes an **Admin Mode**, which allows authorized users to modify RTC settings and train information through a **4×4 keypad**. Input validation and platform collision checking are performed before updated train information is saved.

---

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

---

## 🧩 System Block Diagram

<img width="1536" height="570" alt="block-diagram" src="https://github.com/user-attachments/assets/595c8760-07f5-4e9e-8255-91f0b3ef4260" />

---

## 🧠 Project Mind Map

<img width="1536" height="469" alt="project-mind-map" src="https://github.com/user-attachments/assets/1e70916b-1d79-490f-bf47-58884fae25ee" />

---

## ⚙️ System Working

The system operates in two main modes: **Normal Mode** and **Admin Mode**.

### 🟢 Normal Mode

- Initializes the required peripherals.
- Reads the current date and time from the RTC.
- Compares the current time with the updated train schedules.
- Detects trains approaching within **5 minutes**.
- Displays the approaching train information on the LCD.
- Provides LED and buzzer indications.
- Handles multiple active trains sequentially.
- Displays train summaries when no train is approaching.

### 🔐 Admin Mode

- Activated using the Admin push button through **EINT0**.
- The interrupt service routine sets the Admin Mode flag.
- User enters the PIN for authentication.
- Admin can select RTC or train-data modification.
- Modified values are validated before saving.
- Platform timing conflicts are checked.
- Valid changes are saved and updated train timings are recalculated.

---

## 🔐 Admin Mode & Validation

The Admin Mode provides controlled access to modify railway and RTC information.

### Admin Operations

- 🔑 PIN-based authentication
- 🕒 RTC date and time modification
- 🚆 Train selection and data modification
- ⏱️ Delay modification
- 🛤️ Platform modification
- 🕐 Arrival and departure time modification

### Validation & Safety

Before updating the train database, the system validates:

- Platform number range
- Delay value
- Arrival and departure time format
- Platform availability during the selected time
- Timing conflicts with other trains

Only valid data is saved, after which the **updated arrival and departure times are automatically recalculated**.

---

## 🔧 Hardware Requirements

| Component | Purpose |
|---|---|
| **LPC2148** | Main ARM7 microcontroller |
| **16×2 LCD** | Displays train and menu information |
| **4×4 Keypad** | User input and Admin Mode operations |
| **RTC** | Maintains real-time date and time |
| **LEDs** | Train status indication |
| **Buzzer** | Audio alert |
| **Push Button** | External interrupt for Admin Mode |
| **+3.3V Supply** | Provides power to the system |

---

## 💻 Software & Tools

| Tool / Technology | Purpose |
|---|---|
| **Embedded C** | Application programming |
| **Keil µVision** | Development and compilation |
| **Proteus** | Circuit simulation |
| **LPC2148** | Target microcontroller |
| **ARM7TDMI-S** | Processor architecture |

---

## ✨ Key Features

- 🕒 **Real-Time Monitoring** — Uses RTC for current date and time.
- 🚆 **Train Database** — Maintains information for multiple trains.
- ⏱️ **Approaching Train Detection** — Detects trains approaching within 5 minutes.
- 📺 **LCD Information Display** — Displays train details, timing and platform information.
- 🔄 **Scrolling Display** — Scrolls long train names on the LCD.
- 🚦 **LED Indication** — Provides visual train-status indication.
- 🔊 **Buzzer Alert** — Provides audio indication for approaching trains.
- 🔐 **PIN Authentication** — Protects Admin Mode.
- ⚡ **External Interrupt** — Uses EINT0 to enter Admin Mode.
- 🛤️ **Platform Collision Detection** — Checks for overlapping platform schedules.
- ✅ **Input Validation** — Validates entered train and RTC data.
- 🔁 **Automatic Timing Update** — Recalculates updated train timings after delays.

---

## 🧠 Key Implementation Concepts

The project combines several embedded-system concepts to achieve real-time train monitoring and control.

- 🕒 **RTC-Based Time Comparison** — Compares the current RTC time with train schedules.
- 🔢 **Time-to-Minutes Conversion** — Converts hours and minutes into minutes for easier time calculations.
- 🚆 **Multiple Train Handling** — Maintains and processes multiple active trains.
- 📺 **LCD Scrolling** — Displays long train names using a scrolling mechanism.
- ⚡ **External Interrupt Handling** — Uses EINT0 to trigger Admin Mode.
- 🔐 **Finite State Machine** — Controls the different stages of the Admin Menu.
- ✅ **Input Validation** — Checks entered values before accepting changes.
- 🛤️ **Platform Collision Checking** — Detects overlapping train schedules on the same platform.
- 🔁 **Automatic Timing Recalculation** — Updates arrival and departure times according to the configured delay.
- 🧩 **Modular Design** — Separates application logic, hardware drivers and supporting modules.

---

## 📂 Project Structure

```text
Smart-Railway-Monitoring-System/
│
├── Startup.s
├── types.h
│
├── train_main.c
│
├── railway.c
├── railway.h
│
├── train_dprint.c
├── train_dprint.h
│
├── admin.c
├── admin.h
│
├── RTC.c
├── RTC.h
│
├── lcd.c
├── lcd.h
│
├── keypad.c
├── keypad.h
│
├── indicator.c
├── indicator.h
│
├── interrupt.c
├── interrupt.h
│
├── delay.c
├── delay.h
│
├── images/
│   ├── block-diagram.png
│   └── project-mind-map.png
│
└── README.md
```

---

## 🧩 Module Description

| Module | Responsibility |
|---|---|
| `train_main.c` | Main application flow and system control |
| `railway.c` | Train database and train information |
| `train_dprint.c` | Train summaries, approaching-train display and scrolling |
| `admin.c` | Admin menu, data editing, validation and collision checking |
| `RTC.c` | RTC initialization, date/time handling and RTC editing |
| `lcd.c` | 16×2 LCD driver and display operations |
| `keypad.c` | 4×4 keypad scanning and key detection |
| `indicator.c` | LED and buzzer control |
| `interrupt.c` | External interrupt configuration and ISR |
| `delay.c` | Delay generation |
| `Startup.s` | ARM startup and initialization code |
| `*.h` | Function declarations, structures and macros |

---

## 🔄 System Workflow

The overall system continuously monitors train schedules and responds to user or administrator actions.

<img width="1199" height="1312" alt="ChatGPT Image Sep 15, 2026, 07_31_41 PM" src="https://github.com/user-attachments/assets/78034db0-ed84-4ee5-93e3-94d781da9d80" />


---

## 🖥️ Simulation & Output

The system was developed and tested using **Keil µVision** and simulated in **Proteus** to verify the interaction between the microcontroller and connected peripherals.

### 🔬 Simulation Setup

The simulation includes:

- LPC2148-based ARM7 controller
- 16×2 LCD
- 4×4 keypad
- RTC
- Status LEDs
- Buzzer
- Admin push button

> **Note:** The Proteus simulation uses an LPC2138 device model as a simulator substitute for the LPC2148 where the LPC2148 model is unavailable in the Proteus device library.

---

## 🛠️ Development

**Microcontroller:** LPC2148  
**Architecture:** ARM7TDMI-S  
**Programming Language:** Embedded C  
**IDE:** Keil µVision  
**Simulation:** Proteus  

---

## ⭐ Project Highlights

> **Real-Time • Safe • Efficient • Modular**

The project combines real-time scheduling, embedded hardware interfacing, interrupt handling, user interaction and validation into a single railway monitoring system.

---

<p align="center">
  🚆 <b>Smart Railway Monitoring System</b> 🚆
  <br>
  <i>Building Smarter Transit for a Better Tomorrow.</i>
</p>
