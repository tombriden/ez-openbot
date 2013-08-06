#include "BV4615.h"
#include "EZB.h"

BV4615Response::BV4615Response(bool toggle, bool isValid, unsigned char byte1, unsigned char byte2){
  IsValid = isValid;
  Value = byte2;
  Toggle = toggle;
  Byte1 = byte1;
}

BV4615Class::BV4615Class(EZB* ezb){
  m_ezb = ezb;
  ReadAddress = 37;
  WriteAddress = 36;
}

BV4615Response BV4615Class::GetData(){
  m_ezb->I2C->Start();
  m_ezb->I2C->Write(ReadAddress);
  unsigned char* buffer = m_ezb->I2C->ReadAutoAck(2);
  m_ezb->I2C->Stop();

  bool isValid = !((buffer[0] & (((int) 1) << 7))!=0?true:false && (buffer[0] & (((int) 1) << 0))!=0?true:false);

  BV4615Response res(false, isValid, buffer[0], buffer[1]);
  delete [] buffer;
  return res;
}

unsigned char* BV4615Class::GetFirmware(){
  m_ezb->I2C->Start();
  unsigned char byteArray[8] = { 0, 0x27, 0x1b, 0x5b, 0x3f, 0x33, 0x30, 0x62 };
  byteArray[0] = WriteAddress;
  m_ezb->I2C->Write(byteArray, 8);
  m_ezb->I2C->Restart();
  m_ezb->I2C->Write(ReadAddress);
  unsigned char* buffer = m_ezb->I2C->ReadAutoAck(2);
  m_ezb->I2C->Stop();


  return buffer;
}
