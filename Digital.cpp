#include "Digital.h"

Digital::Digital(EZB_Conn* ezb){
	m_ezb = ezb;
	MinPoolTimeMS = 100;
}

bool Digital::GetDigitalPort(DigitalPortEnum digitalPort){
	char command[1];
	command[0] = digitalPort + EZB_Conn::GetDigitalPort;
	char* retval = m_ezb->Send(command, 1, 1);
	bool ret;
	if(retval[0])
		ret = true;
	else
		ret = false;

	delete [] retval;

	return ret;
}

int Digital::GetDigitalPortAsInt(DigitalPortEnum digitalPort){
	return 1;
}

bool Digital::GetLastDigitalPortSet(DigitalPortEnum digitalPort){
	return true;
}

void Digital::SetDigitalPort(DigitalPortEnum digitalPort, bool status){
	char command[1];
	if(status)
		command[0] = digitalPort + EZB_Conn::SetDigitalPortOn;
	else
		command[0] = digitalPort + EZB_Conn::SetDigitalPortOff;

	m_ezb->Send(command, 1);
}
