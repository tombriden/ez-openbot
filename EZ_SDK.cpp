#include "EZ_SDK.h"

EZ_SDK::EZ_SDK(){

	m_ezb = new EZB_Conn();
	Servo = new ServoClass(m_ezb);
}

EZ_SDK::~EZ_SDK(){
	delete Servo;
	delete m_ezb;
}

void EZ_SDK::Connect(char* mac){
	m_ezb->Connect(mac);
}
