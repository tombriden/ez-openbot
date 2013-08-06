#include "PWM.h"
#include "EZB.h"

PWMClass::PWMClass(EZB* ezb){
  m_ezb = ezb;

  for(int i = 0; i < 34; i++){
    m_pwmPositions[i] = 0;
    m_pwmReleased[i] = true;
  }
}

int PWMClass::GetPWM(DigitalClass::DigitalPortEnum pwmPort){
  return m_pwmPositions[pwmPort];
}

bool PWMClass::IsPWMStopped(DigitalClass::DigitalPortEnum pwmPort){
  return m_pwmReleased[pwmPort];
}

void PWMClass::SetPWM(DigitalClass::DigitalPortEnum pwmPort, int position)
{
  if (m_ezb->IsConnected()){
    if (position > PWM_MAX){
      position = PWM_MAX;
    }
    else if (position < PWM_MIN){
      position = PWM_MIN;
    }
    m_pwmPositions[pwmPort] = position;
    m_pwmReleased[pwmPort] = false;

    unsigned char args[1];
    args[0] = position;
    m_ezb->SendCommand(EZB::SetPWMSpeed + pwmPort, args, 1);
  }
}

void PWMClass::StopPWM(DigitalClass::DigitalPortEnum pwmPort)
{
  if (m_ezb->IsConnected()){
    m_pwmPositions[pwmPort] = 0;
    m_pwmReleased[pwmPort] = true;

    unsigned char args[1];
    args[0] = 0;
    m_ezb->SendCommand(EZB::SetPWMSpeed + pwmPort, args, 1);
  }
}
