#include "Digital.h"
#include "EZB.h"

DigitalClass::DigitalClass(EZB* ezb){
	m_ezb = ezb;
	MinPoolTimeMS = 100;
}

bool DigitalClass::GetDigitalPort(DigitalPortEnum digitalPort){

	struct timespec now;
	clock_gettime(1, &now);

	unsigned long nowms = (now.tv_sec * 1000) + (now.tv_nsec / 1000000);

	if(MinPoolTimeMS > 0 && m_last_request[digitalPort] + MinPoolTimeMS < nowms){
		unsigned char* retval = m_ezb->SendCommand(digitalPort + EZB::GetDigitalPort, 1);
		if(retval[0])
			m_last_value[digitalPort] = true;
		else
			m_last_value[digitalPort] = false;

		delete [] retval;

		clock_gettime(1, &now);
		m_last_request[digitalPort] = (now.tv_sec * 1000) + (now.tv_nsec / 1000000);
	}
	return m_last_value[digitalPort];
}

int DigitalClass::GetDigitalPortAsInt(DigitalPortEnum digitalPort){
	if( GetDigitalPort(digitalPort))
		return 1;
	else
		return 0;
}

bool DigitalClass::GetLastDigitalPortSet(DigitalPortEnum digitalPort){
	return true;
}

void DigitalClass::SetDigitalPort(DigitalPortEnum digitalPort, bool status){
	if(status)
		m_ezb->SendCommand(digitalPort + EZB::SetDigitalPortOn);
	else
		m_ezb->SendCommand(digitalPort + EZB::SetDigitalPortOff);

	m_last_value[digitalPort] = status;
}
