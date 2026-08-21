#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include <WiFi.h>
#include <HTTPClient.h>

// --- WiFi Configuration ---
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// --- Roku Configuration ---
const char* rokuIP = "YOUR_ROKU_IP";  // e.g., "192.168.1.154"

// --- IR Receiver Configuration ---
const int IR_PIN = 15;

IRrecv irrecv(IR_PIN);
decode_results results;

// --- Learned Samsung TV IR Codes ---
#define IR_UP     0xE0E006F9ULL
#define IR_DOWN   0xE0E08679ULL
#define IR_LEFT   0xE0E0A659ULL
#define IR_RIGHT  0xE0E046B9ULL
#define IR_OK     0xE0E016E9ULL
#define IR_BACK   0xE0E0B44BULL
#define IR_HOME   0xE0E07887ULL
#define IR_STAR   0xE0E0E41BULL

unsigned long lastCommandTime = 0;
const unsigned long DEBOUNCE_MS = 300;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n\n========================================");
  Serial.println("  Roku IR Translator - PRODUCTION");
  Serial.println("========================================");
  Serial.println();

  // Initialize IR receiver
  irrecv.enableIRIn();
  Serial.println("IR Receiver ready on GPIO 15");

  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ WiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n✗ WiFi FAILED - restarting...");
    delay(1000);
    ESP.restart();
  }

  Serial.println();
  Serial.println("========================================");
  Serial.println("Ready! Point GE remote at IR receiver.");
  Serial.println("========================================");
  Serial.println();
  Serial.println("Mapped buttons:");
  Serial.println("  UP    -> Roku Up");
  Serial.println("  DOWN  -> Roku Down");
  Serial.println("  LEFT  -> Roku Left");
  Serial.println("  RIGHT -> Roku Right");
  Serial.println("  OK    -> Roku Select");
  Serial.println("  BACK  -> Roku Back");
  Serial.println("  HOME  -> Roku Home");
  Serial.println("  STAR  -> Roku Info");
  Serial.println();
}

void loop() {
  // Check WiFi still connected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost - reconnecting...");
    WiFi.reconnect();
    delay(1000);
    return;
  }

  if (irrecv.decode(&results)) {
    uint64_t code = results.value;

    // Ignore repeat codes and debounce
    if (code != 0xFFFFFFFF && code != 0xFFFFFFFFFFFFFFFF) {
      if (millis() - lastCommandTime > DEBOUNCE_MS) {
        handleIRCode(code);
        lastCommandTime = millis();
      }
    }

    irrecv.resume();
  }
}

void handleIRCode(uint64_t code) {
  String rokuKey = "";
  String buttonName = "";

  switch (code) {
    case IR_UP:
      rokuKey = "Up";
      buttonName = "UP";
      break;
    case IR_DOWN:
      rokuKey = "Down";
      buttonName = "DOWN";
      break;
    case IR_LEFT:
      rokuKey = "Left";
      buttonName = "LEFT";
      break;
    case IR_RIGHT:
      rokuKey = "Right";
      buttonName = "RIGHT";
      break;
    case IR_OK:
      rokuKey = "Select";
      buttonName = "OK";
      break;
    case IR_BACK:
      rokuKey = "Back";
      buttonName = "BACK";
      break;
    case IR_HOME:
      rokuKey = "Home";
      buttonName = "HOME";
      break;
    case IR_STAR:
      rokuKey = "Info";
      buttonName = "STAR";
      break;
    default:
      // Unknown code - ignore
      Serial.printf("Unknown IR: 0x%llX\n", code);
      return;
  }

  Serial.printf("[%s] -> Roku %s ... ", buttonName.c_str(), rokuKey.c_str());

  if (sendRokuCommand(rokuKey)) {
    Serial.println("✓");
  } else {
    Serial.println("✗ FAILED");
  }
}

bool sendRokuCommand(String key) {
  HTTPClient http;

  String url = "http://" + String(rokuIP) + ":8060/keypress/" + key;

  http.begin(url);
  http.setTimeout(2000);

  int httpCode = http.POST("");
  http.end();

  return (httpCode >= 200 && httpCode < 300);
}
