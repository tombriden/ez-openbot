#include "SureDualAxisCompass.h"
#include "EZB.h"

SureDualAxisCompassClass::SureDualAxisCompassClass(EZB* ezb){
  m_ezb = ezb;
  ReadAddress = 0x61;
  WriteAddress = 0x60;
}

CompassDirection SureDualAxisCompassClass::GetCompassDirection(){

  m_ezb->I2C->Start();
  unsigned char byteArray[2];
  byteArray[0] = WriteAddress;
  byteArray[2] = 1;
  m_ezb->I2C->Write(byteArray, 2);
  m_ezb->I2C->Stop();
  m_ezb->I2C->Start();
  m_ezb->I2C->Write(ReadAddress);

  unsigned char* buffer = m_ezb->I2C->ReadAutoAck(5);
  m_ezb->I2C->Stop();

  short x = ((buffer[2] << 8) | buffer[1]);
  short y = ((buffer[4] << 8) | buffer[3]);

  CompassDirection dir(x, y);

  delete [] buffer;

  return dir;
}
