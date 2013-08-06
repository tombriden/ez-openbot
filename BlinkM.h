#ifndef _BLINK_M_H
#define _BLINK_M_H

class EZB;

class BlinkMColor{
public:
  unsigned char red;
  unsigned char green;
  unsigned char blue;

  BlinkMColor(unsigned char red, unsigned char green, unsigned char blue);
};

class BlinkMClass{
private:
  EZB* m_ezb;
public:
  void ChangeToColor(unsigned char address, unsigned char red, unsigned char green, unsigned char blue);
  void FadeToColor(unsigned char address, unsigned char red, unsigned char green, unsigned char blue);
  BlinkMColor GetCurrentColor(unsigned char address);
  void StopScript(unsigned char address);

};


#endif
