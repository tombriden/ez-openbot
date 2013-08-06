#include "Movement.h"
#include "EZB.h"

MovementClass::MovementClass(EZB* ezb){
  m_ezb = ezb;

  DroneForwardReverseRate = 0.2f;
  DroneRollLeftRightRate = 0.2f;
  DroneUpDownRate = 0.2f;
  DroneYawLeftRightRate = 0.2f;
  LeftWheelTriggerA = DigitalClass::D14;
  LeftWheelTriggerB = DigitalClass::D13;
  ModifiedServoLeftForwardValue = ServoClass::SERVO_MIN;
  ModifiedServoLeftReverseValue = ServoClass::SERVO_MAX;
  ModifiedServoLeftStopValue = ((ServoClass::SERVO_MAX - ServoClass::SERVO_MIN) / 2);
  ModifiedServoRightForwardValue = ServoClass::SERVO_MAX;
  ModifiedServoRightReverseValue = ServoClass::SERVO_MIN;
  ModifiedServoRightStopValue = ((ServoClass::SERVO_MAX - ServoClass::SERVO_MIN) / 2);
  RightWheelTriggerA = DigitalClass::D12;
  RightWheelTriggerB = DigitalClass::D11;
  ServoWheelLeftModifiedPort = ServoClass::D14;
  ServoWheelRightModifiedPort = ServoClass::D13;
}

void MovementClass::GoDown(){

  if (m_currentDirection != Down){
    if (MovementType == ARDrone){
      //mm_ezb->ARDroneControl.SetProgressiveInputValues(0.0f, 0.0f, -1*DroneUpDownRate, 0.0f);
    }
    m_currentDirection = Down;
    if (OnMovement != NULL)
      OnMovement(m_currentDirection);
  }
}

void MovementClass::GoForward(unsigned char speed){

  if (m_currentDirection != Forward){
    if (speed > MAX_SPEED){
      speed = MAX_SPEED;
    }
    if (MovementType == ModifiedServo){
      m_ezb->Servo->SetServoPosition(ServoWheelRightModifiedPort, ModifiedServoRightForwardValue);
      m_ezb->Servo->SetServoPosition(ServoWheelLeftModifiedPort, ModifiedServoLeftForwardValue);
    }
    else if (MovementType == HBridge)
    {
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerA, true);
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerB, false);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerA, true);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerB, false);
    }
    else if (MovementType == Roomba){
      //m_ezb->Roomba->Forward(speed);
    }
    else if (MovementType == BV4113){
      //m_ezb->BV4113->Forward();
    }
    else if (MovementType == ARDrone){
      //m_ezb->ARDroneControl.SetProgressiveInputValues(0f, -DroneForwardReverseRate, 0f, 0f);
    }
    else if (MovementType == BrookstoneRover){
      //m_ezb->BrookstoneRover.RightForward(speed);
      //m_ezb->BrookstoneRover.LeftForward(speed);
    }
    else if (MovementType == Roboy){
      //m_ezb->Roboy.WalkForward();
    }
    m_currentDirection = Forward;
    if (OnMovement != NULL){
      OnMovement(m_currentDirection);
    }
  }
}

void MovementClass::GoLeft(unsigned char speed){
  if (m_currentDirection != Left)
  {
    if (MovementType == ModifiedServo){
      m_ezb->Servo->SetServoPosition(ServoWheelRightModifiedPort, ModifiedServoRightForwardValue);
      m_ezb->Servo->SetServoPosition(ServoWheelLeftModifiedPort, ModifiedServoLeftReverseValue);
    }
    else if (MovementType == HBridge){
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerA, false);
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerB, true);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerA, true);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerB, false);
    }
    else if (MovementType == Roomba){
      //m_ezb->Roomba.Left(speed);
    }
    else if (MovementType == BV4113){
      //m_ezb->BV4113.Left();
    }
    else if (MovementType == ARDrone){
      //m_ezb->ARDroneControl.SetProgressiveInputValues(0f, 0f, 0f, -DroneYawLeftRightRate);
    }
    else if (MovementType == BrookstoneRover){
      //m_ezb->BrookstoneRover.RightForward(speed);
      //m_ezb->BrookstoneRover.LeftReverse(speed);
    }
    m_currentDirection = Left;
    if (OnMovement != NULL)
    {
      OnMovement(m_currentDirection);
    }
  }
}

void MovementClass::GoReverse(unsigned char speed){
  if (m_currentDirection != Reverse){
    if (speed > MAX_SPEED)
      speed = MAX_SPEED;

    if (MovementType == ModifiedServo){
      m_ezb->Servo->SetServoPosition(ServoWheelRightModifiedPort, ModifiedServoRightReverseValue);
      m_ezb->Servo->SetServoPosition(ServoWheelLeftModifiedPort, ModifiedServoLeftReverseValue);
    }
    else if (MovementType == HBridge){
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerA, false);
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerB, true);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerA, false);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerB, true);
    }
    else if (MovementType == Roomba){
      //m_ezb->Roomba.Reverse(speed);
    }
    else if (MovementType == BV4113){
      //m_ezb->BV4113.Reverse();
    }
    else if (MovementType == ARDrone){
      //m_ezb->ARDroneControl.SetProgressiveInputValues(0f, DroneForwardReverseRate, 0f, 0f);
    }
    else if (MovementType == BrookstoneRover){
      //m_ezb->BrookstoneRover.RightReverse(speed);
      //m_ezb->BrookstoneRover.LeftReverse(speed);
    }
    m_currentDirection = Reverse;
    if (OnMovement != NULL){
      OnMovement(m_currentDirection);
    }
  }
}

void MovementClass::GoRight(unsigned char speed)
{
  if (m_currentDirection != Right){
    if (MovementType == ModifiedServo){
      m_ezb->Servo->SetServoPosition(ServoWheelRightModifiedPort, ModifiedServoRightReverseValue);
      m_ezb->Servo->SetServoPosition(ServoWheelLeftModifiedPort, ModifiedServoLeftForwardValue);
    }
    else if (MovementType == HBridge){
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerA, true);
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerB, false);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerA, false);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerB, true);
    }
    else if (MovementType == Roomba){
      //m_ezb->Roomba.Right(speed);
    }
    else if (MovementType == BV4113){
      //m_ezb->BV4113.Right();
    }
    else if (MovementType == ARDrone){
      //m_ezb->ARDroneControl.SetProgressiveInputValues(0f, 0f, 0f, DroneYawLeftRightRate);
    }
    else if (MovementType == BrookstoneRover){
      //m_ezb->BrookstoneRover.RightReverse(speed);
      //m_ezb->BrookstoneRover.LeftForward(speed);
    }
    m_currentDirection = Right;
    if (OnMovement != NULL){
      OnMovement(m_currentDirection);
    }
  }
}

void MovementClass::GoRollLeft()
{
  if (m_currentDirection != RollLeft){
    if (MovementType == ARDrone){
      //m_ezb->ARDroneControl.SetProgressiveInputValues(-1*DroneRollLeftRightRate, 0f, 0f, 0f);
    }
    m_currentDirection = RollLeft;
    if (OnMovement != NULL){
      OnMovement(m_currentDirection);
    }
  }
}

void MovementClass::GoRollRight(){
  if (m_currentDirection != RollRight){
    if (MovementType == ARDrone){
      //m_ezb->ARDroneControl.SetProgressiveInputValues(DroneRollLeftRightRate, 0f, 0f, 0f);
    }
    m_currentDirection = RollRight;
    if (OnMovement != NULL){
      OnMovement(m_currentDirection);
    }
  }
}

void MovementClass::GoStop(){
  if (m_currentDirection != Stop){
    if (MovementType == ModifiedServo){
      if (ModifiedServoUseStopValue){
        m_ezb->Servo->SetServoPosition(ServoWheelRightModifiedPort, ModifiedServoRightStopValue);
        m_ezb->Servo->SetServoPosition(ServoWheelLeftModifiedPort, ModifiedServoLeftStopValue);
      }
      else{
        m_ezb->Servo->ReleaseServo(ServoWheelRightModifiedPort);
        m_ezb->Servo->ReleaseServo(ServoWheelLeftModifiedPort);
      }
    }
    else if (MovementType == HBridge){
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerA, false);
      m_ezb->Digital->SetDigitalPort(LeftWheelTriggerB, false);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerA, false);
      m_ezb->Digital->SetDigitalPort(RightWheelTriggerB, false);
    }
    else if (MovementType == Roomba){
      //m_ezb->Roomba.Stop();
    }
    else if (MovementType == BV4113){
      //m_ezb->BV4113.Stop();
    }
    else if (MovementType == ARDrone){
      //m_ezb->ARDroneControl.Hover();
    }
    else if (MovementType == BrookstoneRover){
      //m_ezb->BrookstoneRover.RightStop();
      //m_ezb->BrookstoneRover.LeftStop();
    }
    else if (MovementType == Roboy){
      //m_ezb->Roboy.WalkStop();
    }
    m_currentDirection = Stop;
    if (OnMovement != NULL){
      OnMovement(m_currentDirection);
    }
  }
}

void MovementClass::GoUp(){
  if (m_currentDirection != Up){
    if (MovementType == ARDrone){
      //m_ezb->ARDroneControl.SetProgressiveInputValues(0f, 0f, DroneUpDownRate, 0f);
    }
    m_currentDirection = Up;
    if (OnMovement != NULL){
      OnMovement(m_currentDirection);
    }
  }
}

MovementClass::MovementDirectionEnum MovementClass::GetCurrentDirection(){
  return m_currentDirection;
}

