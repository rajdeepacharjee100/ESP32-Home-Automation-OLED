ESP32 Voice Controlled Smart Switch IoT Project

Overview
This project is a WiFi based smart switching system built using ESP32. It allows users to control electrical appliances using voice commands through Google Assistant. The system uses the SinricPro IoT cloud platform to enable real time communication between the device and the user.

Features
Voice control using Google Assistant
Remote switching over WiFi
Real time status display on OLED
Relay based AC load control
Low cost and scalable design

Components Used
ESP32 Development Board
Relay Module
OLED Display I2C
DC DC Buck Converter
Breadboard and Jumper Wires
Power Supply

Working Principle
The ESP32 connects to a WiFi network and communicates with the SinricPro cloud platform. When a user gives a voice command through Google Assistant, the command is sent to SinricPro. The cloud then triggers the ESP32 to switch the relay ON or OFF. The OLED display shows the current status of the device.

Code

#include <WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define RELAY_PIN 26

const char* WIFI_SSID = "Your_WiFi_Name";
const char* WIFI_PASS = "Your_WiFi_Password";

#define APP_KEY "YOUR_APP_KEY"
#define APP_SECRET "YOUR_APP_SECRET"
#define DEVICE_ID "YOUR_DEVICE_ID"

bool onPowerState(const String &deviceId, bool &state) {
Serial.printf("Device %s turned %s\n", deviceId.c_str(), state ? "ON" : "OFF");
digitalWrite(RELAY_PIN, state ? LOW : HIGH);
return true;
}

void setup() {
Serial.begin(115200);
pinMode(RELAY_PIN, OUTPUT);
digitalWrite(RELAY_PIN, HIGH);

WiFi.begin(WIFI_SSID, WIFI_PASS);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
}

SinricProSwitch& mySwitch = SinricPro[DEVICE_ID];
mySwitch.onPowerState(onPowerState);

SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
SinricPro.handle();
}

How to Use
Create an account on SinricPro
Add a new switch device
Copy your App Key Secret and Device ID
Update the code with your WiFi credentials and SinricPro details
Upload the code to ESP32
Connect SinricPro with Google Assistant

Voice Commands
Hey Google turn on the device
Hey Google turn off the device

Learning Outcomes
Understanding of IoT cloud platforms
ESP32 WiFi communication
Relay interfacing with real world devices
Voice assistant integration
Practical embedded system development

Future Improvements
Mobile application dashboard
Energy monitoring system
Multiple device control
Secure IoT system design

Author
Rajdeep Acharjee
Diploma in Electronics and Telecommunication Engineering
