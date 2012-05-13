#include "Digital.h"
#include "EZB.h"

DigitalClass::DigitalClass(EZB* ezb){
	m_ezb = ezb;
	MinPoolTimeMS = 100;
}

bool DigitalClass::GetDigitalPort(DigitalPortEnum digitalPort){

	struct timespec now;
	clock_gettime(1, &now);
	if(!(MinPoolTimeMS > 0 && m_last_request[digitalPort].tv_nsec + (MinPoolTimeMS * 1000000) > now.tv_nsec)){
		unsigned char* retval = m_ezb->SendCommand(digitalPort + EZB::GetDigitalPort, 1);
		if(retval[0])
			m_last_value[digitalPort] = true;
		else
			m_last_value[digitalPort] = false;

		delete [] retval;

		clock_gettime(1, &m_last_request[digitalPort]);
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
		m_ezb->SendCommand(digitalPort + EZB::SetDigitalPortOn, 1);
	else
		m_ezb->SendCommand(digitalPort + EZB::SetDigitalPortOff, 1);

	m_last_value[digitalPort] = status;
}
