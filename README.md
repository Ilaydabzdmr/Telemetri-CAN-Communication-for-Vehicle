<div align="center">

# 📡 Telemetri CAN Communication for Vehicle
### Wireless Real-Time Vehicle Data Transmission System
### MCP2515 CAN Bus + LoRa E32 | Teknofest 2024 — TeamEfe

[![Platform](https://img.shields.io/badge/Platform-Arduino-teal?style=flat-square&logo=arduino)](https://github.com/Ilaydabzdmr/Telemetri-CAN-Communication-for-Vehicle)
[![Hardware](https://img.shields.io/badge/Hardware-MCP2515%20%2B%20LoRa%20E32-informational?style=flat-square)](https://github.com/Ilaydabzdmr/Telemetri-CAN-Communication-for-Vehicle)
[![Protocol](https://img.shields.io/badge/Protocol-CAN%20Bus%20%2F%20LoRa%20RF-9cf?style=flat-square)](https://github.com/Ilaydabzdmr/Telemetri-CAN-Communication-for-Vehicle)
[![Competition](https://img.shields.io/badge/Teknofest-International%20Efficiency%20Challenge%202024-red?style=flat-square)](https://www.teknofest.org)
[![Team](https://img.shields.io/badge/Team-TeamEfe-orange?style=flat-square)](https://github.com/Ilaydabzdmr/Telemetri-CAN-Communication-for-Vehicle)

</div>

---

## 📡 About The Project

This repository contains the **Arduino firmware** developed for the wireless telemetry system of an electric race vehicle competing in the **International Efficiency Challenge at Teknofest 2024**.

The system reads live vehicle data from the **CAN Bus network** via the **MCP2515 module**, then transmits it wirelessly to the pit area using **LoRa E32 RF modules**. The received data is visualized on the PC using [TelemetriApp](https://github.com/Ilaydabzdmr/TelemetriApp).

> *Designed to deliver reliable real-time data under race conditions.*

---

## 🔁 System Architecture

```
[ Electric Race Vehicle ]
        │
        ▼
[ MCP2515 — CAN Bus Reader ]
   Reads: Speed / Voltage / Temperature / Energy
        │
        ▼
[ Arduino + telmetricanbus.ino ]
   Parses CAN frames → Packs into struct
        │
        ▼
[ LoRa E32 — Transmitter (433 MHz) ]
   Wireless RF Transmission
        │
        ▼ (over the air)
        │
[ LoRa E32 — Receiver at Pit Area ]
        │
        ▼
[ PC Serial Port ]
        │
        ▼
[ TelemetriApp — Windows Forms UI ]
   Real-time visualization + CSV logging
```

---

## 📁 Repository Structure

```
Telemetri-CAN-Communication-for-Vehicle/
├── 01_CAN_Read/
│   └── Canbus_read.ino        # Reads potentiometer, sends via CAN Bus
├── 02_CAN_Write/
│   └── Canbus_write.ino       # Receives CAN frames, prints to Serial
├── 03_Telemetri_CAN_LoRa/
│   └── telmetricanbus.ino     # Main firmware: CAN → LoRa E32 transmission
├── 04_Test/
│   └── Testcodetelemetri.ino  # Test firmware with random data via LoRa
├── 05_Transmitter-LoRa/
│   └── verici.ino             # Standalone LoRa E32 transmitter test
└── README.md
```

---

## ⚙️ Firmware Overview

### 01 — CAN Read (`Canbus_read.ino`)
Reads analog input from a potentiometer and transmits the value over the CAN Bus using the MCP2515 module. Used for initial CAN Bus communication testing.

| Parameter | Value |
|---|---|
| CAN ID | `0x036` |
| Bitrate | `500 Kbps` |
| Clock | `8 MHz` |
| Data | `1 byte (potentiometer mapped 0–255)` |

---

### 02 — CAN Write (`Canbus_write.ino`)
Listens on the CAN Bus for messages with ID `0x036` and prints the received data bytes to the Serial Monitor.

| Parameter | Value |
|---|---|
| CAN ID Filter | `0x036` |
| Bitrate | `500 Kbps` |
| Clock | `8 MHz` |
| Output | `Serial (9600 baud)` |

---

### 03 — Telemetri CAN + LoRa (`telmetricanbus.ino`) ⭐ Main Firmware
The core firmware. Reads vehicle telemetry data from the CAN Bus and transmits it wirelessly via LoRa E32.

| Parameter | Value |
|---|---|
| CAN ID | `0x036` |
| Bitrate | `500 Kbps` |
| Clock | `8 MHz` |
| CS Pin | `10` |
| LoRa Address | `620` |
| LoRa Channel | `23` |
| SoftwareSerial | `RX=3, TX=2` |

**Signal Struct — CAN Data Mapping:**
```cpp
typedef struct {
  byte deger1;  // Hiz          → Speed           — canMsg.data[0]
  byte deger2;  // Sicaklik     → Temperature (1) — canMsg.data[1]
  byte deger3;  // Sicaklik2    → Temperature (2) — canMsg.data[2]
  byte deger4;  // Voltaj       → Voltage     (1) — canMsg.data[3]
  byte deger5;  // Voltaj2      → Voltage     (2) — canMsg.data[4]
  byte deger6;  // KalanEnerji  → Remaining Energy (1) — canMsg.data[5]
  byte deger7;  // KalanEnerji2 → Remaining Energy (2) — canMsg.data[6]
} Signal;
```

---

### 04 — Test (`Testcodetelemetri.ino`)
Simulates vehicle data with random values and transmits via LoRa E32. Used for testing the receiver and TelemetriApp without a real vehicle.

| Parameter | Value |
|---|---|
| LoRa Address | `620` |
| LoRa Channel | `23` |
| SoftwareSerial | `RX=3, TX=2` |

---

### 05 — Transmitter LoRa (`verici.ino`)
Standalone LoRa E32 transmitter test. Sends 4 random values wirelessly to verify RF communication independently from CAN Bus.

| Parameter | Value |
|---|---|
| LoRa Address | `620` |
| LoRa Channel | `23` |
| SoftwareSerial | `RX=3, TX=2` |
| Data Fields | `4 bytes (random values)` |

---

## 🔧 Hardware & Wiring

### Required Components

| Component | Purpose |
|---|---|
| Arduino Uno / Nano | Main microcontroller |
| MCP2515 CAN Bus Module | CAN Bus communication |
| LoRa E32 433T20d | Wireless RF transmission |

### LoRa E32 Pin Connection

```
Arduino Uno    →    LoRa E32 433T20d
    2          →       pin 3  (TX)
    3          →       pin 4  (RX)
   3.3V        →       VCC
   GND         →       GND
```

> SoftwareSerial(3, 2) → RX = pin 3, TX = pin 2

### MCP2515 Pin Connection

```
Arduino Uno    →    MCP2515
    10         →      CS
    11         →      MOSI
    12         →      MISO
    13         →      SCK
   GND         →      GND
   5V          →      VCC
```

---

## 📦 Required Libraries

Install via Arduino IDE → Library Manager:

| Library | Install Name |
|---|---|
| MCP2515 | `MCP2515 by autowp` |
| LoRa E32 | `LoRa_E32 by Renzo Mischianti` |
| SoftwareSerial | Built-in |
| SPI | Built-in |
| Wire | Built-in |

---

## 🔗 Related Repository

> 💻 **[TelemetriApp](https://github.com/Ilaydabzdmr/TelemetriApp)** — Windows Forms application that receives and visualizes the data transmitted by this firmware.

---

## 🏁 Competition

| | |
|---|---|
| **Event** | International Efficiency Challenge |
| **Organization** | Teknofest 2024 |
| **Team** | TeamEfe |
| **Vehicle** | Electric Race Car |
| **Category** | Efficiency & Telemetry |

---

## 📬 Contact

<div align="center">

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Ilayda%20Bozdemir-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/ilayda-b-a68708296/)
[![GitHub](https://img.shields.io/badge/GitHub-Ilaydabzdmr-black?style=for-the-badge&logo=github)](https://github.com/Ilaydabzdmr)

</div>

---

<div align="center">

*Developed with ❤️ for TeamEfe — Teknofest 2024*

</div>
