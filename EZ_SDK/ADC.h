#ifndef _ADC_H
#define _ADC_H

#include <time.h>
#include <unistd.h>

class EZB;
class ADCClass{
private:
	EZB* m_ezb;
	long m_last_request[8];
	unsigned char m_last_value[8];
public:
	enum ADCPortEnum{
		ADC0 = 0,
		ADC1 = 1,
		ADC2 = 2,
		ADC3 = 3,
		ADC4 = 4,
		ADC5 = 5,
		ADC6 = 6,
		ADC7 = 7,
	};

	int MinPoolTimeMS;

	ADCClass(EZB* ezb);
	// Summary:
	//     Get an integer from 0-255 representing the relative voltage of a specified
	//     ADC port (Between 0 and 5 volts)
	int GetADCValue(ADCPortEnum sendSensor);
	//
	// Summary:
	//     Get the voltage from 0-5v of a specified ADC port
	float GetADCVoltage(ADCPortEnum sendSensor);
	//
	// Summary:
	//     Returns the voltage relative to the inputted value. If you want to display
	//     the Value and Voltage, you can pass the value to this function rather then
	//     executing a new command. This saves bandwidth over the line.
	float GetADCVoltageFromValue(int adcValue);
};

#endif
