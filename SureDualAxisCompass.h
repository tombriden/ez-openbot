#ifndef _SUREDUALAXISCOMPASS_H
#define _SUREDUALAXISCOMPASS_H

#include "CompassDirection.h"

class EZB;
class SureDualAxisCompassClass{
private:
	EZB* m_ezb;
public:
	SureDualAxisCompassClass(EZB* ezb);
	unsigned char ReadAddress;
	unsigned char WriteAddress;

	CompassDirection GetCompassDirection();
};

#endif
