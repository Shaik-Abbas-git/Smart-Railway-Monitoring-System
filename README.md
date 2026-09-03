# Smart Railway Monitoring System

An LPC2148-based Smart Railway Monitoring System that simulates a real-time railway station information board using an RTC, 16x2 LCD, keypad, LEDs, buzzer, and external interrupt.

## Features

- Real-time date and time display using RTC
- Railway train database for multiple trains
- Train number, name, destination, platform and schedule display
- Automatic detection of approaching trains
- Scrolling display of approaching train names
- Arrival, departure and delay information
- LED and buzzer indications for approaching trains
- Admin mode using external interrupt and PIN authentication
- RTC date and time modification
- Train information editing
- Platform collision checking
- Automatic recalculation of arrival and departure times after delay updates

## Hardware Used

- LPC2148 ARM7 microcontroller
- 16x2 LCD
- 4x4 Keypad
- RTC
- LEDs
- Buzzer
- Push Button for external interrupt

## Project Operation

### Normal Mode

1. The system initializes the LCD, RTC, keypad, external interrupt and indicators.
2. The RTC date and time are set or modified through the RTC menu.
3. The system continuously checks the schedules of all trains.
4. Trains approaching within 5 minutes are detected and added to the active train list.
5. The approaching train information is displayed on the LCD with a scrolling train name.
6. LEDs and buzzer indicate an approaching train.
7. Multiple active trains are displayed one after another.
8. When no train is approaching, the system displays train summaries and the current RTC date and time.

### Admin Mode

1. Pressing the push button generates an external interrupt.
2. The interrupt service routine sets the admin mode flag.
3. The admin menu is opened and PIN authentication is performed.
4. The administrator can modify RTC settings or train information.
5. Train information such as delay, platform, arrival time and departure time can be edited.
6. The entered values are validated before saving.
7. Platform timing conflicts with other trains are checked.
8. If the data is valid, the changes are saved and the updated train timings are recalculated.

## Software Modules

- `train_main.c` – Main program and train monitoring logic
- `railway.c` – Train database and railway-related data
- `train_dprint.c` – Train information and approaching train display
- `admin.c` – Admin menu, editing and validation
- `RTC.c` – RTC initialization, display and date/time settings
- `lcd.c` – LCD interfacing
- `keypad.c` – Keypad interfacing
- `interrupt.c` – External interrupt configuration and ISR
- `indicator.c` – LED and buzzer control
- `delay.c` – Delay functions
- `Startup.s` – ARM7 startup and initialization code

## Controller

**Microcontroller:** LPC2148 ARM7TDMI-S

## Development Environment

**IDE:** Keil µVision

## Project Type

Embedded Systems / ARM7 / Real-Time Railway Monitoring
