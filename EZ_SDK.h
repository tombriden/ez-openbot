#ifndef _EZ_SDK_H
#define _EZ_SDK_H

#include "Servo.h"
#include "Digital.h"

class EZ_SDK{
private:
	EZB_Conn* m_ezb;
public:
	ServoClass* Servo;
	DigitalClass* Digital;

	EZ_SDK();
	~EZ_SDK();
	void Connect(char* mac);
};



#endif
