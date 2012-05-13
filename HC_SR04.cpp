#include "HC_SR04.h"
#include "EZB.h"

HC_SR04Class::HC_SR04Class(EZB* ezb){
	m_ezb = ezb;
	MinPoolTimeMS = 200;
}

int HC_SR04Class::GetValue(DigitalClass::DigitalPortEnum triggerPort, DigitalClass::DigitalPortEnum echoPort){

	struct timespec now;
	clock_gettime(1, &now);
	if(!(MinPoolTimeMS > 0 && m_last_request[triggerPort].tv_nsec + (MinPoolTimeMS*1000000) > now.tv_nsec)){
		unsigned char args[1];
		args[0] = echoPort;
		unsigned char* retval = m_ezb->SendCommand(EZB::HC_SR04 + triggerPort, args, 1, 1);
		m_last_value[triggerPort] = retval[0];
		delete [] retval;
		clock_gettime(1, &m_last_request[triggerPort]);
	}
	return m_last_value[triggerPort];
}
