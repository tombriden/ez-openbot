#ifndef _BV4113_H
#define _BV4113_H

#include "Movement.h"

class EZB;
class BV4113Class{
private:
  EZB* m_ezb;
  unsigned char m_speed;
public:
  BV4113Class(EZB* ezb);
  void Forward();
  void Left();
  void Reverse();
  void Right();
  void Stop();
};



#endif
