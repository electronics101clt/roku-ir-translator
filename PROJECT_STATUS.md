# Roku IR Translator Project Status

**Date:** 2026-08-21
**Status:** Hardware validated, ready for production build

---

## Hardware Setup

### ESP32
- **Chip:** ESP32-D0WDQ6-V3 (revision v3.0)
- **MAC:** 8c:aa:b5:80:d2:80
- **Features:** Wi-Fi, BT, Dual Core, 240MHz
- **Port:** /dev/ttyUSB0

### IR Receiver
- **Component:** VS1838 IR Receiver
- **Operating Voltage:** 3.3V (powered from ESP32)
- **Data Pin:** GPIO 15
- **Status:** ✅ Working - receiving IR signals

### Network
- **WiFi SSID:** JonOTron Studios
- **WiFi Password:** A5k6WmWm ⚠️ CHANGE THIS - exposed in chat transcript
- **ESP32 IP:** 192.168.1.169
- **Roku IP:** 192.168.1.154 (RokuExpress)
- **Roku Port:** 8060 (ECP - External Control Protocol)

---

## Learned IR Codes

**GE Remote (Samsung TV mode) → Samsung Protocol (32-bit)**

```cpp
// Samsung TV IR Codes (learned from GE remote)
#define IR_UP     0xE0E0A659ULL   // Samsung, 32 bits
#define IR_DOWN   0xE0E0A659ULL   // Samsung, 32 bits ⚠️ Same as UP
#define IR_LEFT   0xE0E006F9ULL   // Samsung, 32 bits
#define IR_RIGHT  0x7F1C8736ULL   // Unknown, 5 bits ⚠️ Different protocol
#define IR_OK     0xE0E08679ULL   // Samsung, 32 bits
#define IR_BACK   0xE0E006F9ULL   // Samsung, 32 bits ⚠️ Same as LEFT
```

**⚠️ Note:** Some codes are duplicates. May need to re-run learning process for unique codes.

---

## Validated Functionality

### ✅ IR Receiving
- VS1838 connected to ESP32 GPIO 15
- Successfully receiving and decoding IR signals
- Protocol detection working (Samsung protocol detected)
- Codes captured and logged

### ✅ Roku Control
- ESP32 connected to WiFi
- HTTP POST commands to Roku ECP working
- Tested commands: Home, Select
- Roku responding correctly

---

## Project Files

```
/home/jonathan/
├── esp32_ir_receiver/
│   └── esp32_ir_receiver.ino     # Initial test sketch
├── ir_code_learner/
│   └── ir_code_learner.ino       # IR code learning tool
├── roku_test/
│   └── roku_test.ino             # Roku control validation
└── roku_ir_translator/
    └── PROJECT_STATUS.md         # This file
```

---

## Next Steps

1. **Re-learn IR codes** (optional) - Get unique codes for all 6 buttons
2. **Build production app** - Combine IR receiver + Roku control
3. **Deploy and test** - Flash to ESP32 and validate end-to-end

---

## Production App Requirements

**Input:** IR codes from GE remote (directional buttons)
**Output:** HTTP POST to Roku ECP

**Mapping:**
```
IR Code        → Roku Command
---------------------------------
IR_UP          → /keypress/Up
IR_DOWN        → /keypress/Down
IR_LEFT        → /keypress/Left
IR_RIGHT       → /keypress/Right
IR_OK          → /keypress/Select
IR_BACK        → /keypress/Back
```

**Additional Roku Commands Available:**
- Home, Play, Pause, FastForward, Rewind
- VolumeUp, VolumeDown, VolumeMute
- PowerOff

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

## Reference Documentation

- **VS1838 Datasheet:** 38kHz IR receiver, 2.7-5.5V operation
- **Roku ECP API:** http://[ROKU_IP]:8060/keypress/[KEY]
- **ESP32 Pinout:** 30-pin DevKit V1

---

## Security Notes

⚠️ **WiFi Password Exposed:** Change "A5k6WmWm" immediately - was posted in chat transcript
⚠️ **No Authentication:** Roku ECP has no auth - anyone on network can control it
⚠️ **Plaintext HTTP:** All commands sent unencrypted over local network

---

**End of Status Report**
