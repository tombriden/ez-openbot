#ifndef _ServoClass_H
#define _ServoClass_H

#include "ezb_conn.h"

class ServoClass{

public:
	enum ServoPortEnum{
		D0 = 0,
		D1 = 1,
		D2 = 2,
		D3 = 3,
		D4 = 4,
		D5 = 5,
		D6 = 6,
		D7 = 7,
		D8 = 8,
		D9 = 9,
		D10 = 10,
		D11 = 11,
		D12 = 12,
		D13 = 13,
		D14 = 14,
		D15 = 15,
		D16 = 16,
		D17 = 17,
		D18 = 18,
		D19 = 19,
		NA = 20,
	};

	typedef struct{
		long last_move_time;
		char curr_pos;
		char curr_speed;
		bool isreleased;
	}servo_info;

	static const char SERVO_CENTER = 70;
	static const char SERVO_MAX = 140;
	static const char SERVO_MIN = 1;
	static const char SERVO_OFF = 0;
	static const char SERVO_SPEED_FASTEST = 0;
	static const char SERVO_SPEED_SLOWEST = 10;

	ServoClass(EZB_Conn* ezb);
	double GetNumberOfSecondsSinceLastMove(ServoPortEnum servoPort);
	int GetServoPosition(ServoPortEnum servoPort);
	int GetServoSpeed(ServoPortEnum servoPort);
	bool IsServoReleased(ServoPortEnum servoPort);
	void SetServoPosition(ServoPortEnum servoPort, int position, int speed=-1);
	void SetServoSpeed(ServoPortEnum servoPort, int speed);
	void ReleaseServo(ServoPortEnum servoPort);
	void ReleaseAllServos();

private:
	EZB_Conn* m_ezb;
	servo_info m_servos[NA];
};
/*
namespace EZ_B
{
    public class ServoClass
    {
        protected internal ServoClass(EZB ezb);

        public double GetNumberOfSecondsSinceLastMove(ServoClass.ServoClassPortEnum ServoClassPort);
        //
        // Summary:
        //     Get the position of a ServoClass
        public int GetServoClassPosition(ServoClass.ServoClassPortEnum ServoClassPort);
        //
        // Summary:
        //     Return the current speed of a ServoClass
        public int GetServoClassSpeed(ServoClass.ServoClassPortEnum ServoClassPort);
        //
        // Summary:
        //     Return true if the specified ServoClass port is in a released state
        public bool IsServoClassReleased(ServoClass.ServoClassPortEnum ServoClassPort);
        //
        // Summary:
        //     When ServoClasss have been used, they will hold their position until the EZ-B
        //     power is cycled or until they are told to release.  This will send a command
        //     to the EZ-B to release all ServoClasss
        public void ReleaseAllServoClasss();
        //
        // Summary:
        //     Release ServoClass. Release a ServoClass from holding its position.  If modified, stops
        //     the ServoClass.
        public void ReleaseServoClass(ServoClass.ServoClassPortEnum ServoClassPort);
        //
        // Summary:
        //     Set the position of a ServoClass Uses the last speed specified
        public void SetServoClassPosition(ServoClass.ServoClassPortEnum ServoClassPort, int position);
        //
        // Summary:
        //     Set the speed and position of a ServoClass
        public void SetServoClassPosition(ServoClass.ServoClassPortEnum ServoClassPort, int position, int speed);
        public void SetServoClassPositionScalar(ServoClass.ServoClassPortEnum ServoClassPort, int ServoClassMin, int ServoClassMax, float clientWidthMin, float clientWidthMax, float clientPosition, bool invert);
        public void SetServoClassPositionScalar(ServoClass.ServoClassPortEnum ServoClassPort, int ServoClassMin, int ServoClassMax, int clientWidthMin, int clientWidthMax, int clientPosition, bool invert);
        //
        // Summary:
        //     Set the speed of a ServoClass
        public void SetServoClassSpeed(ServoClass.ServoClassPortEnum ServoClassPort, int speed);

        // Summary:
        //     List of ServoClass Ports
        [Flags]
        public enum ServoClassPortEnum
        {
            D0 = 0,
            D1 = 1,
            D2 = 2,
            D3 = 3,
            D4 = 4,
            D5 = 5,
            D6 = 6,
            D7 = 7,
            D8 = 8,
            D9 = 9,
            D10 = 10,
            D11 = 11,
            D12 = 12,
            D13 = 13,
            D14 = 14,
            D15 = 15,
            D16 = 16,
            D17 = 17,
            D18 = 18,
            D19 = 19,
            NA = 20,
        }
    }
}*/
#endif
