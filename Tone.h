#ifndef _TONE_H
#define _TONE_H

#include "Digital.h"

class EZB;
class ToneClass{
private:
  EZB* m_ezb;
public:
  enum NoteEnum{
    C1,
    Db1,
    D1,
    Eb1,
    E1,
    F1,
    Gb1,
    G1,
    Ab1,
    A1,
    Bb1,
    B1,
    C2,
    Db2,
    D2,
    Eb2,
    E2,
    F2,
    Gb2,
    G2,
    Ab2,
    A2,
    Bb2,
    B12,
    NoteCount
  };

  ToneClass(EZB* ezb);
  void PlayTone(DigitalClass::DigitalPortEnum digitalPort, NoteEnum note, unsigned char lengthMs);
  void RandomTone(DigitalClass::DigitalPortEnum digitalPort, unsigned char lengthMs, int numCount);
};

#endif
