#include "MP3Trigger.h"
#include "EZB.h"

MP3Trigger::MP3Trigger(EZB* ezb){
  m_ezb = ezb;
  BaudRate = UartClass::Baud_38400;
}
void MP3Trigger::Forward(){
  unsigned char byte[1];
  byte[0] = 70;
  m_ezb->Uart->SendSerial(CommunicationPort, BaudRate, byte, 1);
}

void MP3Trigger::PlayTrack(unsigned char trackNumber){
  unsigned char bytes[2];
  bytes[0] = 112;
  bytes[1] = trackNumber;
  m_ezb->Uart->SendSerial(CommunicationPort, BaudRate, bytes, 2);
}

void MP3Trigger::Reverse(){
  unsigned char byte[1];
  byte[0] = 82;
  m_ezb->Uart->SendSerial(CommunicationPort, BaudRate, byte, 1);
}

void MP3Trigger::SetVolume(unsigned char volume){
  unsigned char bytes[2];
  bytes[0] = 118;
  bytes[1] = volume;
  m_ezb->Uart->SendSerial(CommunicationPort, BaudRate, bytes, 2);
}

void MP3Trigger::StartStop(){
  unsigned char byte[1];
  byte[0] = 79;
  m_ezb->Uart->SendSerial(CommunicationPort, BaudRate, byte, 1);
}
