#include "HC_SR04.h"
#include "EZB.h"

HC_SR04::HC_SR04(EZB* ezb){
	m_ezb = ezb;

}

int HC_SR04::GetValue(DigitalClass::DigitalPortEnum triggerPort, DigitalClass::DigitalPortEnum echoPort){

	unsigned char command[2];
	command[0] = EZB::HC_SR04;
	command[1] = 2;

	unsigned char* retval = m_ezb->Send(command, 2, 1);

	m_last_request[triggerPort] = time(NULL);
	m_last_value[triggerPort] = retval[0];

	delete [] retval;

	return m_last_value[triggerPort];
}
