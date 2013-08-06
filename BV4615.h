#ifndef _BV4165_H
#define _BV4165_H

#include "Movement.h"

class EZB;

class BV4615Response{
public:
	unsigned char Byte1;
	bool IsValid;
	bool Toggle;
	unsigned char Value;

	BV4615Response(bool toggle, bool isValid, unsigned char byte1, unsigned char byte2);
};

class BV4615Class{
private:
	EZB* m_ezb;
	unsigned char m_speed;
public:
	unsigned char ReadAddress;
	unsigned char WriteAddress;


	BV4615Class(EZB* ezb);

	BV4615Response GetData();
	unsigned char* GetFirmware();
};



#endif
