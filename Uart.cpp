#include "Uart.h"
#include "EZB.h"

UartClass::UartClass(EZB* ezb){
  m_ezb = ezb;
}

void UartClass::SendSerial(DigitalClass::DigitalPortEnum digitalPort, BAUD_RATE_ENUM baudRate, unsigned char* data, int len){
  if (m_ezb->IsConnected()){
    if (len > 250){
      throw new std::runtime_error("Data payload cannot exceed 250 bytes");
    }

    unsigned char* args = new unsigned char[1+len];
    args[0] = baudRate;
    memcpy(&args[1], data, len);
    m_ezb->SendCommand(EZB::SendSerial + digitalPort, args, len+1);
    delete [] args;
  }
}
