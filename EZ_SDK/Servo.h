#ifndef _ServoClass_H
#define _ServoClass_H

#include <time.h>

class EZB;

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
		unsigned long last_move_time;
		char curr_pos;
		char curr_speed;
		bool isreleased;
	}servo_info;

	static const unsigned char SERVO_CENTER = 70;
	static const unsigned char SERVO_MAX = 140;
	static const unsigned char SERVO_MIN = 1;
	static const unsigned char SERVO_OFF = 0;
	static const unsigned char SERVO_SPEED_FASTEST = 0;
	static const unsigned char SERVO_SPEED_SLOWEST = 10;

	ServoClass(EZB* ezb);
	double GetNumberOfSecondsSinceLastMove(ServoPortEnum servoPort);
	int GetServoPosition(ServoPortEnum servoPort);
	int GetServoSpeed(ServoPortEnum servoPort);
	bool IsServoReleased(ServoPortEnum servoPort);
	void SetServoPosition(ServoPortEnum servoPort, int position, int speed=-1);
	void SetServoPositionScalar(ServoPortEnum servoPort, int servoMin, int servoMax, int clientWidthMin, int clientWidthMax, int clientPosition, bool invert);
	void SetServoPositionScalar(ServoPortEnum servoPort, int servoMin, int servoMax, float clientWidthMin, float clientWidthMax, float clientPosition, bool invert);
	void SetServoSpeed(ServoPortEnum servoPort, int speed);
	void ReleaseServo(ServoPortEnum servoPort);
	void ReleaseAllServos();

private:
	EZB* m_ezb;
	servo_info m_servos[NA];
};

#endif
