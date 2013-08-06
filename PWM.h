#ifndef _PWM_H
#define _PWM_H

#include "Digital.h"

class EZB;

class PWMClass{
private:
	EZB* m_ezb;
	int m_pwmPositions[34];
	bool m_pwmReleased[34];
public:
	static const char PWM_MAX = 100;
	static const char PWM_MIN = 0;

	PWMClass(EZB* ezb);

	int GetPWM(DigitalClass::DigitalPortEnum pwmPort);
	bool IsPWMStopped(DigitalClass::DigitalPortEnum pwmPort);
	void SetPWM(DigitalClass::DigitalPortEnum pwmPort, int position);
	void StopPWM(DigitalClass::DigitalPortEnum pwmPort);

};

#endif
