#include <WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// 🔥 OLED
#include <U8g2lib.h>
#include <Wire.h>

// ✅ YOUR WORKING OLED DRIVER
U8G2_SSD1327_MIDAS_128X128_F_SW_I2C u8g2(
  U8G2_R0, 22, 21, U8X8_PIN_NONE
);

// Relay pin
const int relayPin = 26;

#define RELAY_PIN 26

// WiFi credentials
const char* WIFI_SSID = "Redmi Note 7 Pro";
const char* WIFI_PASS = "99999999";

// SinricPro credentials
#define APP_KEY    "eeba8449-c23f-46e2-a2c2-fbea51573e73"
#define APP_SECRET "3e636dfe-c3ae-47e1-b641-c94df5e2e625-7a7169b8-5b4a-4cf0-bd6c-f0688b54f130"
#define DEVICE_ID "69a93a2fdb0f6e0b1596ed77"


// 🔥 OLED FUNCTIONS
void showBoot() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.drawStr(30, 40, "STARTING...");
  u8g2.sendBuffer();
}

void showWiFiConnected() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.drawStr(15, 40, "WiFi CONNECTED");
  u8g2.drawStr(10, 60, WiFi.localIP().toString().c_str());
  u8g2.sendBuffer();
}

void showON() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso24_tf);
  u8g2.drawStr(30, 70, "ON");
  u8g2.drawCircle(100, 30, 10);
  u8g2.sendBuffer();
}

void showOFF() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso24_tf);
  u8g2.drawStr(25, 70, "OFF");
  u8g2.drawLine(90, 20, 110, 40);
  u8g2.drawLine(110, 20, 90, 40);
  u8g2.sendBuffer();
}


// ⚡ SINRIC CALLBACK (ONLY ADDED DISPLAY)
bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Device %s turned %s\r\n", deviceId.c_str(), state ? "ON" : "OFF");
  
  if (state) {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Light turned ON via voice");
    showON();   // ✅ added
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Light turned OFF via voice");
    showOFF();  // ✅ added
  }
  
  return true;
}


void setup() {
  Serial.begin(115200);

  // 🔥 OLED START
  u8g2.begin();
  showBoot();

  // Setup relay
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  
  // Connect WiFi (YOUR ORIGINAL CODE ✅)
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.drawStr(10, 40, "Connecting WiFi...");
  u8g2.sendBuffer();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");

  // 🔥 SHOW ON OLED
  showWiFiConnected();

  // Setup SinricPro device
  SinricProSwitch& mySwitch = SinricPro[DEVICE_ID];
  mySwitch.onPowerState(onPowerState);
  
  // Start SinricPro
  SinricPro.begin(APP_KEY, APP_SECRET);

  Serial.println("SinricPro initialization complete!");
}


void loop() {
  SinricPro.handle();
  delay(10);
}