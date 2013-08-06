#ifndef _MOVEMENT_H
#define _MOVEMENT_H

#include "Digital.h"
#include "Servo.h"

class MovementClass{
public:
  enum MovementDirectionEnum
  {
    Stop,
    Forward,
    Reverse,
    Left,
    Right,
    Up,
    Down,
    RollRight,
    RollLeft
  };

  enum MovementTypeEnum
  {
    Unknown,
    HBridge,
    ModifiedServo,
    Roomba,
    BV4113,
    ARDrone,
    BrookstoneRover,
    Roboy
  };

  typedef void (*OnMovementHandler)(MovementDirectionEnum);

  float DroneForwardReverseRate;
  float DroneRollLeftRightRate;
  float DroneUpDownRate;
  float DroneYawLeftRightRate;
  DigitalClass::DigitalPortEnum LeftWheelTriggerA;
  DigitalClass::DigitalPortEnum LeftWheelTriggerB;
  static const unsigned char MAX_SPEED = 0xff;
  static const unsigned char MIN_SPEED = 0;
  int ModifiedServoLeftForwardValue;
  int ModifiedServoLeftReverseValue;
  int ModifiedServoLeftStopValue;
  int ModifiedServoRightForwardValue;
  int ModifiedServoRightReverseValue;
  int ModifiedServoRightStopValue;
  bool ModifiedServoUseStopValue;
  MovementTypeEnum MovementType;
  DigitalClass::DigitalPortEnum RightWheelTriggerA;
  DigitalClass::DigitalPortEnum RightWheelTriggerB;
  ServoClass::ServoPortEnum ServoWheelLeftModifiedPort;
  ServoClass::ServoPortEnum ServoWheelRightModifiedPort;

  OnMovementHandler OnMovement;

  MovementClass(EZB* ezb);
  void GoDown();
  void GoForward(unsigned char speed = MAX_SPEED);
  void GoLeft(unsigned char speed = MAX_SPEED);
  void GoReverse(unsigned char speed = MAX_SPEED);
  void GoRight(unsigned char speed = MAX_SPEED);
  void GoRollLeft();
  void GoRollRight();
  void GoStop();
  void GoUp();

  MovementDirectionEnum GetCurrentDirection();

private:
  MovementDirectionEnum m_currentDirection;
  EZB* m_ezb;
};

#endif
