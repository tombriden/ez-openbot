#ifndef _I2C_H
#define _I2C_H

class EZB;

class I2CClass{
private:
  EZB* m_ezb;
public:
  I2CClass(EZB* ezb);
  bool Poll();
  unsigned char Read(bool ack);
  unsigned char* Read(bool ack, unsigned char expected_ret_bytes);
  unsigned char Read(unsigned char device_addr, unsigned char registered_addr);
  unsigned char* ReadAutoAck(unsigned char expected_ret_bytes);
  void Restart();
  void Start();
  void Stop();
  void Write(unsigned char* bytes, int len);
  void Write(unsigned char byte);
  void Write(unsigned char device_addr, unsigned char* data, int len);
  void WriteBinary(unsigned char b7, unsigned char b6, unsigned char b5, unsigned char b4, unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);
};

#endif
