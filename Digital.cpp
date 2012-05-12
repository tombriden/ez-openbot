#include "Digital.h"

DigitalClass::DigitalClass(EZB_Conn* ezb){
	m_ezb = ezb;
	MinPoolTimeMS = 100;
}

bool DigitalClass::GetDigitalPort(DigitalPortEnum digitalPort){
	unsigned char command[1];
	command[0] = digitalPort + EZB_Conn::GetDigitalPort;
	unsigned char* retval = m_ezb->Send(command, 1, 1);
	bool ret;
	if(retval[0])
		ret = true;
	else
		ret = false;

	delete [] retval;

	return ret;
}

int DigitalClass::GetDigitalPortAsInt(DigitalPortEnum digitalPort){
	bool status = GetDigitalPort(digitalPort);
	if(status)
		return 1;
	else
		return 0;
}

bool DigitalClass::GetLastDigitalPortSet(DigitalPortEnum digitalPort){
	return true;
}

void DigitalClass::SetDigitalPort(DigitalPortEnum digitalPort, bool status){
	unsigned char command[1];
	if(status)
		command[0] = digitalPort + EZB_Conn::SetDigitalPortOn;
	else
		command[0] = digitalPort + EZB_Conn::SetDigitalPortOff;

	m_ezb->Send(command, 1);
}
