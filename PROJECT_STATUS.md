# Roku IR Translator Project Status

**Date:** 2026-08-21
**Status:** ✅ Complete - Production build deployed

---

## Hardware Setup

### ESP32
- **Chip:** ESP32-D0WDQ6-V3 (revision v3.0)
- **Features:** Wi-Fi, BT, Dual Core, 240MHz
- **Port:** /dev/ttyUSB0

### IR Receiver
- **Component:** VS1838 IR Receiver
- **Operating Voltage:** 3.3V (powered from ESP32)
- **Data Pin:** GPIO 15
- **Status:** ✅ Working - receiving IR signals

---

## Learned IR Codes

**GE Remote (Samsung TV mode) → Samsung Protocol (32-bit)**

These codes are compatible with Samsung TV remotes (e.g., AA59-00741A, BN59-01199F series).

```cpp
#define IR_UP     0xE0E006F9ULL   // Samsung, 32 bits
#define IR_DOWN   0xE0E08679ULL   // Samsung, 32 bits
#define IR_LEFT   0xE0E0A659ULL   // Samsung, 32 bits
#define IR_RIGHT  0xE0E046B9ULL   // Samsung, 32 bits
#define IR_OK     0xE0E016E9ULL   // Samsung, 32 bits
#define IR_BACK   0xE0E0B44BULL   // Samsung, 32 bits
#define IR_HOME   0xE0E07887ULL   // Samsung, 32 bits
#define IR_STAR   0xE0E0E41BULL   // Samsung, 32 bits
```

---

## Validated Functionality

### ✅ IR Receiving
- VS1838 connected to ESP32 GPIO 15
- Successfully receiving and decoding IR signals
- Samsung protocol detected and decoded

### ✅ Roku Control
- ESP32 connected to WiFi
- HTTP POST commands to Roku ECP working
- All mapped buttons functioning correctly

---

## Wiring Diagram

```
VS1838 IR Receiver    →    ESP32 (30-pin)
------------------------------------------
Pin 3 (VCC)           →    3V3
Pin 2 (GND)           →    GND
Pin 1 (OUT/DATA)      →    D15 (GPIO 15)
```

**Power:** USB to ESP32 (5V in, 3.3V regulated on board)

---

## Command Mapping

```
IR Button  → Roku Command
-------------------------
UP         → Up
DOWN       → Down
LEFT       → Left
RIGHT      → Right
OK         → Select
BACK       → Back
HOME       → Home
STAR (*)   → Info
```

---

## Reference

- **IR Protocol:** Samsung 32-bit (NEC-like timing)
- **Compatible Remotes:** Samsung AA59-series, GE Universal (Samsung TV mode)
- **Roku ECP API:** http://[ROKU_IP]:8060/keypress/[KEY]

---

**End of Status Report**
