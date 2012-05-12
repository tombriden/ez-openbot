#include "ADC.h"
#include "EZB.h"

ADCClass::ADCClass(EZB* ezb){
	m_ezb = ezb;
	MinPoolTimeMS=100;
}

int ADCClass::GetADCValue(ADCPortEnum sendSensor){

	unsigned char command[1];
	command[0] = EZB::GetADCValue + sendSensor;

	unsigned char* retval = m_ezb->Send(command, 1, 1);

	unsigned char adc_value;
	adc_value = retval[0];
	delete [] retval;

	return adc_value;

}

float ADCClass::GetADCVoltage(ADCPortEnum sendSensor){
	return GetADCVoltageFromValue(GetADCValue(sendSensor));

}

float ADCClass::GetADCVoltageFromValue(int adcValue){

	return (float)((float)adcValue / 255) * 5;
}
