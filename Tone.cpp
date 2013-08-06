#include "Tone.h"
#include "EZB.h"

ToneClass::ToneClass(EZB* ezb){
	m_ezb = ezb;
}

void ToneClass::PlayTone(DigitalClass::DigitalPortEnum digitalPort, NoteEnum note, unsigned char lengthMs){

	unsigned char args[2];
	args[0] = note;
	args[1] = lengthMs;

	m_ezb->SendCommand(EZB::PlayNote + digitalPort, args, 2, 1);
}

void ToneClass::RandomTone(DigitalClass::DigitalPortEnum digitalPort, unsigned char lengthMs, int numCount){

	srand(time(NULL));
	for (int i = 0; i <= numCount; i++){
		int num3 = rand() % NoteCount;
		PlayTone(digitalPort, (NoteEnum)num3, lengthMs);
	}
}
