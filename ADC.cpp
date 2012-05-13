#include "ADC.h"
#include "EZB.h"

ADCClass::ADCClass(EZB* ezb){
	m_ezb = ezb;
	MinPoolTimeMS=100;
}

int ADCClass::GetADCValue(ADCPortEnum sendSensor){

	struct timespec now;
	clock_gettime(1, &now);
	if(!(MinPoolTimeMS > 0 && m_last_request[sendSensor].tv_nsec + (MinPoolTimeMS * 1000000) > now.tv_nsec)){
		unsigned char* retval = m_ezb->SendCommand(EZB::GetADCValue + sendSensor, 1);

		m_last_value[sendSensor] = retval[0];
		delete [] retval;

		clock_gettime(1, &m_last_request[sendSensor]);
	}
	return m_last_value[sendSensor];

}

float ADCClass::GetADCVoltage(ADCPortEnum sendSensor){
	return GetADCVoltageFromValue(GetADCValue(sendSensor));

}

float ADCClass::GetADCVoltageFromValue(int adcValue){

	return (float)((float)adcValue * 0.01960784f);
}
