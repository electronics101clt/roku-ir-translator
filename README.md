# Roku IR Translator

ESP32-based IR-to-WiFi bridge that translates Samsung TV remote codes to Roku commands.

## Overview

Use a GE Universal Remote (programmed to Samsung TV mode) to control a Roku device over WiFi. The ESP32 receives IR signals via a VS1838 IR receiver and sends HTTP commands to the Roku's External Control Protocol (ECP) API.

## Hardware Requirements

- ESP32 DevKit (30-pin or similar)
- VS1838 IR Receiver
- GE Universal Remote (or any remote sending Samsung TV codes)
- Roku device on the same WiFi network

## Wiring

```
VS1838 IR Receiver    →    ESP32
----------------------------------
Pin 3 (VCC)           →    3.3V
Pin 2 (GND)           →    GND
Pin 1 (OUT/DATA)      →    GPIO 15
```

## Mapped Buttons

| IR Button | Roku Command |
|-----------|--------------|
| UP        | Up           |
| DOWN      | Down         |
| LEFT      | Left         |
| RIGHT     | Right        |
| OK        | Select       |
| BACK      | Back         |
| HOME      | Home         |
| STAR (*)  | Info         |

## Learned IR Codes (Samsung Protocol, 32-bit)

```cpp
#define IR_UP     0xE0E006F9ULL
#define IR_DOWN   0xE0E08679ULL
#define IR_LEFT   0xE0E0A659ULL
#define IR_RIGHT  0xE0E046B9ULL
#define IR_OK     0xE0E016E9ULL
#define IR_BACK   0xE0E0B44BULL
#define IR_HOME   0xE0E07887ULL
#define IR_STAR   0xE0E0E41BULL
```

## Configuration

Edit these values in `roku_ir_translator.ino`:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* rokuIP = "YOUR_ROKU_IP";
```

To find your Roku's IP address:
```bash
nmap -p 8060 --open 192.168.1.0/24
```

## Building & Flashing

### Using Arduino CLI

```bash
# Install ESP32 core (if not already installed)
arduino-cli core install esp32:esp32

# Install IRremoteESP8266 library
arduino-cli lib install IRremoteESP8266

# Compile
arduino-cli compile --fqbn esp32:esp32:esp32 roku_ir_translator.ino

# Upload
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32 roku_ir_translator.ino

# Monitor serial output
arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=115200
```

## How It Works

1. GE Remote sends Samsung TV IR codes
2. VS1838 receives and demodulates the 38kHz IR signal
3. ESP32 decodes the IR protocol using IRremoteESP8266 library
4. ESP32 maps the IR code to a Roku command
5. ESP32 sends HTTP POST to `http://ROKU_IP:8060/keypress/COMMAND`
6. Roku executes the command

## Roku ECP Commands

Additional Roku commands you can add:

- `Play`, `Pause`, `PlayPause`
- `FastForward`, `Rewind`
- `VolumeUp`, `VolumeDown`, `VolumeMute`
- `PowerOff`
- `InstantReplay`
- `Search`

## License

MIT License
