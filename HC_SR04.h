#ifndef _HC_SR04_H
#define _HC_SR04_H

#include <time.h>
#include "Digital.h"
#include "windows_ports.h"

class EZB;

class HC_SR04Class{
private:
  EZB* m_ezb;
  struct timespec m_last_request[22];
  unsigned char m_last_value[22];
public:
  static const unsigned char MAX_VALUE = 255;

  HC_SR04Class(EZB* ezb);
  //
  // Summary:
  //     To prevent ADC requests from flooding the communication channel, this limit
  //     prevents too many calls. Best to leave it alone.
  int MinPoolTimeMS;

  // Summary:
  //     Get the value received from the HC-SR04 Ping Sensor
  int GetValue(DigitalClass::DigitalPortEnum triggerPort, DigitalClass::DigitalPortEnum echoPort);
};


#endif
