// Toggle led (Arduino 1.0.5 is suggested)
#include <YeelinkHTTPArduino.h>

// Change this for your API key (from your account dashboard)
String APIKey = "5d8dde4619afe1ad1643e4656800602f";

// Change these for your device and sensor
String device_id = "4464";
String sensor_id = "6481";
Sensor sensor(APIKey, device_id, sensor_id);

long lastRequestTime = 0;
const int INTERVAL = 2000; // update interval, in miliseconds
const int led = 9;

void setup() {
  Serial.begin(57600);
  pinMode(led, OUTPUT);
}

void loop() {   
  if ((millis() - lastRequestTime) > INTERVAL) {
    sensor.request();
    lastRequestTime = millis();    
  }
    
  if (sensor.available()) {
     String state = sensor.get();
     if (state == "1") {
       digitalWrite(led, HIGH);
     } else {
       digitalWrite(led, LOW);
     }  
  }
}

