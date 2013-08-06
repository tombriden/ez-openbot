#ifndef _UART_H
#define _UART_H

#include "Digital.h"

class EZB;
class UartClass{
private:
  EZB* m_ezb;
public:
  enum BAUD_RATE_ENUM{
    Baud_9600,
    Baud_19200,
    Baud_38400,
    Baud_57600,
    Baud_115200
  };

  UartClass(EZB* ezb);
  void SendSerial(DigitalClass::DigitalPortEnum digitalPort, BAUD_RATE_ENUM baudRate, unsigned char* data, int len);
};

#endif
