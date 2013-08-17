// Send a random temperature to Yeelink every 5 seconds
// (Arduino 1.0.5 is suggested)
#include <YeelinkHTTPArduino.h>

// Change this for your API key (from your account dashboard)
String APIKey = "YOUR_API_KEY_HERE";

// Change these for your device and sensor
String device_id = "1234";
String sensor_id = "5678";
Sensor sensor(APIKey, device_id, sensor_id);

void setup() {
  Serial.begin(57600);
  
  randomSeed(analogRead(0));
}

void loop() {  
  int temperature = random(20, 40);
  String value = String(temperature);
  sensor.update(value);
  
  delay(10000);      // rate limit: must > 10 seconds    
}


