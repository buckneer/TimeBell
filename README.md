# Arduino Bell Scheduler

This project uses an Arduino, a DS3231 RTC module, a seven-segment display, push buttons, and a relay to schedule and ring a bell at predefined times. It also allows you to adjust the time using the buttons and toggle between two periods (e.g., winter and summer) stored in EEPROM.

## Table of Contents

- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Wiring Diagram](#wiring-diagram)
- [Software Setup](#software-setup)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [License](#license)

## Features

- **Real-Time Clock:** Uses a DS3231 RTC module for accurate timekeeping.
- **Display:** A seven-segment display (configured as common anode) shows the current time.
- **Button Controls:** Two buttons allow you to:
  - Toggle between different period modes ("zi" for winter and "let" for summer).
  - Enter a SETUP mode to adjust hours and minutes.
- **Bell Trigger:** A relay activates a bell at specific scheduled times.
- **EEPROM Storage:** The period setting is stored in EEPROM so that it is retained between power cycles.

## Hardware Requirements

- Arduino board (Uno, Mega, etc.)
- DS3231 RTC module
- Seven-Segment display (common anode)
- Two push buttons
- Relay module
- Jumper wires and breadboard

## Wiring Diagram

### RTC Module
- **SDA:** Connect to Arduino SDA (A4 on Uno)
- **SCL:** Connect to Arduino SCL (A5 on Uno)
- **VCC:** Connect to 5V
- **GND:** Connect to GND

### Seven-Segment Display
- **Digit Pins:** As defined in the code (e.g., `digitPins[] = {1, 4, 5, 12}`)
  - **Note:** Pin 1 is used for TX on some Arduino boards; change it if needed.
- **Segment Pins:** As defined in the code (e.g., `segmentPins[] = {2, 6, 10, 8, 7, 3, 11, 9}`)
- Follow the [SevSeg library](https://github.com/sparkfun/SevSeg) guidelines for proper wiring.

### Push Buttons
- **Hours Button:** Connect to analog pin A1 (`HOURS_PIN`)
- **Minutes Button:** Connect to analog pin A2 (`MINUTES_PIN`)
- Use appropriate pull-up or pull-down resistors if necessary.

### Relay Module
- **Relay Control:** Connect to digital pin 13 (`relay`)
- **Logic:** This project assumes an active-low relay (ON = LOW, OFF = HIGH). Confirm your relay module’s requirements.

## Software Setup

1. **Install Required Libraries:**  
   In the Arduino IDE, install the following libraries:
   - [Wire](https://www.arduino.cc/en/Reference/Wire)
   - [RTClib](https://github.com/adafruit/RTClib)
   - [SevSeg](https://github.com/sparkfun/SevSeg)
   - [EasyButton](https://github.com/marcoschwartz/EasyButton)

2. **Project Files:**  
   Ensure all project files are in one folder, including:
   - `YourProject.ino` (the main Arduino sketch)
   - `config.h` (custom configuration file)
   - `Period.h` and `Period.cpp` (for period management)

3. **Upload the Code:**  
   - Open the project folder in the Arduino IDE.
   - Verify the sketch.
   - Upload it to your Arduino board.

## Usage

### Normal Operation (ARMED Mode)
- The RTC keeps track of time and the seven-segment display shows the current time.
- The sketch compares the current time against a predefined schedule (see the `compare()` function).
- When a match is found and the bell has not yet rung for that minute, the relay activates and rings the bell.

### Adjusting Time (SETUP Mode)
- **Entering SETUP Mode:**  
  A long press on the hours button (duration defined by `longPressDuration`) will toggle the mode.
- **Time Adjustment:**  
  In SETUP mode:
  - Press the hours button to increment hours.
  - Press the minutes button to increment minutes.
  - The display shows the new time values (using `hoursSet` and `minutesSet`).
- **Saving Changes:**  
  A long press in SETUP mode saves the new time to the RTC using `rtc.adjust()`.

### Toggling Periods
- A short press on the hours button while in ARMED mode toggles between period settings (e.g., "zi" for winter and "let" for summer) and displays the current period.

## Troubleshooting

- **Display Issues:**  
  Verify the wiring of the seven-segment display against the pin definitions in your sketch.

- **Button Behavior:**  
  Ensure that your buttons are correctly wired with the necessary resistors and that they are debounced if needed (handled by the EasyButton library).

- **RTC Issues:**  
  Check the DS3231 module’s wiring (SDA/SCL) and test it using a simple RTC sketch.

- **Relay Operation:**  
  Confirm your relay module’s control logic (active-low vs. active-high) and ensure proper wiring to the Arduino.

## License

This project is provided "as is" without warranty of any kind. Feel free to modify and distribute as needed.

---

Happy tinkering!
