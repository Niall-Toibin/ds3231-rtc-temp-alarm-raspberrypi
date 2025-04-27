# DS3231 Real-Time Clock with Temperature Monitoring & Alarm Interrupt on Raspberry Pi

## Overview

This project demonstrates how to interface a **DS3231 Real-Time Clock (RTC)** module with a **Raspberry Pi 4** using the I²C protocol. It includes full support for:

- Accurate time and date reading/writing
- Built-in temperature sensor access
- Square-wave output configuration
- Alarm-driven event handling via GPIO interrupt
- LED signaling on alarm triggers
- Clean GPIO handling using **libgpiod**

All functionality is implemented in **C++**.

---

## Features

- 🗕️ **Time & Date Handling** – Read and set RTC time/date via I²C  
- 🌡️ **Temperature Monitoring** – Read built-in temperature sensor  
- ⏰ **Alarm Interrupt** – Configure Alarm 1 and trigger events via falling edge on SQW/INT pin  
- 💡 **LED Indicator** – Visual feedback for alarm using GPIO output  
- 💨 **Square-Wave Control** – Program square-wave output at various frequencies  
- 🧠 **Clean Architecture** – Modular C++ classes with reusable I²C and GPIO layers

---

## 1. Hardware & Wiring

| Pi GPIO Pin         | Function               | Connected To           |
|---------------------|------------------------|------------------------|
| Pin 1 (3.3 V)        | Power                  | RTC VCC                |
| Pin 6 (GND)          | Ground                 | RTC GND, LED GND       |
| Pin 3 (GPIO 2, SDA)  | I²C data               | RTC SDA                |
| Pin 5 (GPIO 3, SCL)  | I²C clock              | RTC SCL                |
| Pin 27 (GPIO 27)     | Alarm input (falling)  | RTC SQW/INT            |
| Pin 11 (GPIO 17)     | LED output             | LED via 330 Ω resistor |

> 📷 A wiring diagram is available in the `docs/` directory for visual reference.

---

## 2. Repository Structure

```bash
rtc-project/
├── en-src/
│   ├── application.cpp       # Main demo logic
│   ├── DS3231.cpp/.h         # RTC driver class
│   ├── I2CDevice.cpp/.h      # Generic I²C wrapper
│   └── gpio.cpp              # GPIO control using libgpiod
├── docs/                     # Wiring & timing diagrams
└── README.md                 # This file
```

---

## 3. Build & Run

### Requirements

```bash
sudo apt update
sudo apt install g++ libgpiod-dev i2c-tools
```

- Enable I²C and GPIO in `raspi-config` under **Interfacing Options**

### Build the Project

```bash
git clone https://github.com/Niall-Toibin/ds3231-rtc-temp-alarm-pi.git rtc-project
cd rtc-project/en-src
g++ application.cpp DS3231.cpp I2CDevice.cpp gpio.cpp -o rtc_demo -lgpiod
```

### Run It

```bash
sudo ./rtc_demo
```

Sample output:
```
Time - 19:30:32
Date - 8/3/25
Temperature: 19.5°C
Time set to 14.47.20. Date set to 8/3/25.
Set alarm 1 for 14.47.30 on date 8/3/25.
Interrupt Enabled (alarm 1)
LED on
LED off
```

---

## 4. Future Improvements

- Integrate CLI for dynamic setting  
- Expand front-end with a GUI 
- Wrap in a **systemd service** for persistent RTC sync on boot  
- Introduce optional logging to file/CSV  

---

## 5. License
Niall Tóibín 2025 (https://github.com/Niall-Toibin)

---

## Final Notes

This project demonstrates low-level hardware control and interrupt-driven logic using modern C++ and Linux user-space GPIO libraries. It’s a compact example of embedded systems programming on Raspberry Pi, bridging hardware and software with clean architecture and clear extensibility.

