#ifndef YEELINK_HTTP_ARDUINO_H
#define YEELINK_HTTP_ARDUINO_H

#include <Arduino.h>
#include "FSON.h"

class Sensor {

  public:
    Sensor(String APIKey, String deviceID, String sensorID);
    void request();
    bool available();
    String get();
    String get(String);
    void update(String value);
    
  protected:
    String _APIKey, _deviceID, _sensorID;
    FSON _FSON;                  // FSON utilities
    
};

#endif