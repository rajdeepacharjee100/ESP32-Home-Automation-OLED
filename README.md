ESP32 Voice Controlled Smart Switch (IoT Project)
Overview

This project is a WiFi-based smart switching system built using ESP32 that allows users to control electrical appliances using voice commands via Google Assistant.

The system uses the SinricPro cloud platform to connect the ESP32 with voice assistants, enabling real-time remote control from anywhere.

Features
   Voice control using Google Assistant
   Remote switching over WiFi
   OLED display for ON/OFF status
   Relay-based AC load control
   Low-cost and scalable design
Components Used
    ESP32 Development Board
    2-Channel Relay Module
    OLED Display (I2C)
    DC-DC Buck Converter
    Breadboard & Jumper Wires
    Power Supply
    
Working Principle
    ESP32 connects to WiFi network
    It communicates with SinricPro cloud
    Google Assistant sends voice command
    SinricPro triggers ESP32
    ESP32 controls relay (ON/OFF)
    OLED displays current status
    
Code
    #include <WiFi.h>
    #include <SinricPro.h>
    #include <SinricProSwitch.h>
    
    // Relay pin
    const int relayPin = 26;
    
    // WiFi credentials
    const char* WIFI_SSID = "Redmi Note 7 Pro";
    const char* WIFI_PASS = "99999999";
    
    // SinricPro credentials (get from website)
    #define APP_KEY    "eeba8449-c23f-46e2-a2c2-fbea51573e73"     // From SinricPro dashboard
    #define APP_SECRET "3e636dfe-c3ae-47e1-b641-c94df5e2e625-7a7169b8-5b4a-4cf0-bd6c-f0688b54f130"  // From SinricPro dashboard
    #define DEVICE_ID "69a93a2fdb0f6e0b1596ed77"     // From SinricPro dashboard
    
    
    #define RELAY_PIN 26  // GPIO 26 connected to relay
    
    
    bool onPowerState(const String &deviceId, bool &state) {
      Serial.printf("Device %s turned %s\r\n", deviceId.c_str(), state ? "ON" : "OFF");
      
      // Control the relay
      if (state) {
        digitalWrite(RELAY_PIN, LOW);  // Turn relay ON
        Serial.println("Light turned ON via voice");
      } else {
        digitalWrite(RELAY_PIN, HIGH); // Turn relay OFF
        Serial.println("Light turned OFF via voice");
      }
      
      return true;
    }
    
    void setup() {
      Serial.begin(115200);
      
      // Setup relay
      pinMode(RELAY_PIN, OUTPUT);
      digitalWrite(RELAY_PIN, HIGH); // Start OFF
      
      // Connect WiFi
      WiFi.begin(WIFI_SSID, WIFI_PASS);
      Serial.print("Connecting to WiFi");
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("\nConnected to WiFi!");
      
      // Setup SinricPro device
      SinricProSwitch& mySwitch = SinricPro[DEVICE_ID];
      mySwitch.onPowerState(onPowerState);
      
      // Start SinricPro
      SinricPro.begin(APP_KEY, APP_SECRET);
      Serial.println("SinricPro initialization complete!");
      Serial.println("You can now use voice commands:");
      Serial.println("- 'Hey google, turn on living room's Lab led'");
      Serial.println("- 'Hey google, turn off living room's Lab led'");
    }
    
    void loop() {
      SinricPro.handle(); // Handle SinricPro commands
      delay(10);
    }
    
How to Use
    Create account on SinricPro
    Add a new switch device
    Copy APP KEY, SECRET & DEVICE ID
    Update code with your WiFi + credentials
    Upload code to ESP32
    Connect with Google Assistant
    
Voice Commands
    "Hey Google, turn ON the device"
    "Hey Google, turn OFF the device"
    
Learning Outcomes
    IoT cloud integration
    ESP32 WiFi communication
    Relay interfacing with AC load
    Voice assistant integration
    Real-time embedded system design
    
Future Improvements
    Mobile app dashboard
    Energy monitoring system
    Multiple device control
    Secure payment integration (for EV charging use-case)
    
Author

Rajdeep Acharjee
Diploma in Electronics & Telecommunication Engineering
