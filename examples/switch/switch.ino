// Toggle led (Arduino 1.0.5 is suggested)
#include <YeelinkHTTPArduino.h>

// Change this for your API key (from your account dashboard)
String APIKey = "YOUR_API_KEY_HERE";

// Change these for your device and sensor
String device_id = "1234";
String sensor_id = "5678";
Sensor sensor(APIKey, device_id, sensor_id);

long lastRequestTime = 0;
const int INTERVAL = 2000; // update interval, in miliseconds
const int led = 13;

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

