#include "I2C.h"
#include "EZB.h"

I2CClass::I2CClass(EZB* ezb){
	m_ezb = ezb;
}

bool I2CClass::Poll(){
	unsigned char* retval = m_ezb->SendCommand(EZB::I2CPoll, 1);
	bool status = false;
	if(retval[0] == 1)
		status = true;
	delete [] retval;

	return status;
}

unsigned char I2CClass::Read(bool ack){
	unsigned char* retval = Read(ack, 1);
	unsigned char val = retval[0];

	delete [] retval;
	return val;
}

unsigned char* I2CClass::Read(bool ack, unsigned char expected_ret_bytes){

	unsigned char args[2];

	if(ack)
		args[0] = 1;
	else
		args[1] = 0;
	args[1] = expected_ret_bytes;

	return m_ezb->SendCommand(EZB::I2CRead, args, 2, expected_ret_bytes);
}

unsigned char I2CClass::Read(unsigned char device_addr, unsigned char registered_addr){

	unsigned char args[2];
	args[0] = device_addr << 1;
	args[1] = registered_addr;
	Start();
	Write(args, 2);
	Restart();
	Write((device_addr << 1) + 1);
	unsigned char val = Read(false);
	Stop();
	return val;
}

unsigned char* I2CClass::ReadAutoAck(unsigned char expected_ret_bytes){

	if(!m_ezb->IsConnected())
		return NULL;

	unsigned char args[1];
	args[0] = expected_ret_bytes;
	return m_ezb->SendCommand(EZB::I2CReadAutoAck, args, 1, expected_ret_bytes);
}

void I2CClass::Restart(){
	m_ezb->SendCommand(EZB::I2CRestart);
}

void I2CClass::Start(){
	m_ezb->SendCommand(EZB::I2CStart);
}

void I2CClass::Stop(){
	m_ezb->SendCommand(EZB::I2CStop);
}

void I2CClass::Write(unsigned char* bytes, int len){
	if (m_ezb->IsConnected())	{
		if (len > 255){
			throw std::runtime_error("Can not send more than 255 bytes over I2C");
		}
		m_ezb->SendCommand(EZB::I2CWrite, bytes, len);
	}
}
void I2CClass::Write(unsigned char byte){
	unsigned char value[1];
	value[0] = byte;
	Write(value, 1);
}
void I2CClass::Write(unsigned char device_addr, unsigned char* data, int len){
	if (len > 255){
		throw std::runtime_error("Can not send more than 255 bytes over I2C");
	}
	unsigned char* towrite = new unsigned char[len+1];
	towrite[0] = device_addr << 1;
	memcpy(&towrite[1], data, len);
	Start();
	Write(towrite, len+1);
	delete [] towrite;
	Stop();
}

void I2CClass::WriteBinary(unsigned char b7, unsigned char b6, unsigned char b5, unsigned char b4, unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0){
	unsigned char b = (unsigned char) (((((((b0 + (b1 * 2)) + (b2 * 4)) + (b3 * 8)) + (b4 * 0x10)) + (b5 * 0x20)) + (b6 * 0x40)) + (b7 * 0x80));
	Write(b);
}
