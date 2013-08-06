#ifndef _MP3_TRIGGER_H
#define _MP3_TRIGGER_H

#include "Digital.h"
#include "Uart.h"

class EZB;

class MP3Trigger{
private:
  EZB* m_ezb;
  UartClass::BAUD_RATE_ENUM BaudRate;
  DigitalClass::DigitalPortEnum CommunicationPort;
public:
  MP3Trigger(EZB* ezb);
  void Forward();
  void PlayTrack(unsigned char trackNumber);
  void Reverse();
  void SetVolume(unsigned char volume);
  void StartStop();
};

#endif
