#include "Servo.h"
#include "EZB.h"
#include <time.h>


ServoClass::ServoClass(EZB* ezb){
	m_ezb = ezb;

	struct timespec now;
	clock_gettime(1, &now);
	for(int i = 0; i < NA; i++){
		m_servos[i].curr_pos = 0;
		m_servos[i].curr_speed = 0;
		m_servos[i].last_move_time = now;
		m_servos[i].isreleased = true;
	}

}

double ServoClass::GetNumberOfSecondsSinceLastMove(ServoPortEnum servoPort){
	struct timespec now;
	clock_gettime(1, &now);


	double num_seconds = now.tv_sec - m_servos[servoPort].last_move_time.tv_sec;
	return num_seconds;
}

int ServoClass::GetServoPosition(ServoPortEnum servoPort){
	return m_servos[servoPort].curr_pos;
}

int ServoClass::GetServoSpeed(ServoPortEnum servoPort){
	return m_servos[servoPort].curr_speed;
}

bool ServoClass::IsServoReleased(ServoPortEnum servoPort){
	return m_servos[servoPort].isreleased;
}


void ServoClass::SetServoPosition(ServoPortEnum servoPort, int position, int speed){

	if(position > SERVO_MAX)
		position = SERVO_MAX;
	else if(position < SERVO_MIN)
		position = SERVO_MIN;

	unsigned char args[1];

	if(speed > -1){
		SetServoSpeed(servoPort, speed);
	}

	args[0] = position;

	m_servos[servoPort].curr_pos = position;
	m_servos[servoPort].isreleased = false;
	clock_gettime(1, &m_servos[servoPort].last_move_time);

	if(servoPort != NA)
		m_ezb->SendCommand(servoPort + EZB::SetServoPosition, args, 1);
}

void ServoClass::SetServoPositionScalar(ServoPortEnum servoPort, int servoMin, int servoMax, int clientWidthMin, int clientWidthMax, int clientPosition, bool invert){
	SetServoPositionScalar(servoPort, servoMin, servoMax, (float)clientWidthMin, (float)clientWidthMax, (float)clientPosition, invert);
}
void ServoClass::SetServoPositionScalar(ServoPortEnum servoPort, int servoMin, int servoMax, float clientWidthMin, float clientWidthMax, float clientPosition, bool invert)
{
	if (clientWidthMin < 0.0f){
		clientWidthMax += abs(clientWidthMin);
		clientPosition += abs(clientWidthMin);
		clientWidthMin = 0.0f;
	}

	float num = ((float)(servoMax - servoMin)) / (clientWidthMax - clientWidthMin);
	int position = (int) (num * clientPosition);
	if (invert)
		position = servoMax - position;
	else
		position += servoMin;

	if (position > servoMax)
		position = servoMax;

	if (position < servoMin)
		position = servoMin;

	SetServoPosition(servoPort, position);
}

void ServoClass::SetServoSpeed(ServoPortEnum servoPort, int speed){
	if(speed > SERVO_SPEED_SLOWEST)
		speed = SERVO_SPEED_SLOWEST;
	else if(speed < SERVO_SPEED_FASTEST)
		speed = SERVO_SPEED_FASTEST;

	unsigned char args[1];
	args[0] = speed;
	m_servos[servoPort].curr_speed = speed;

	if(servoPort != NA)
		m_ezb->SendCommand(servoPort + EZB::SetServoSpeed, args, 1);
}

void ServoClass::ReleaseServo(ServoPortEnum servoPort){
	if(!m_servos[servoPort].isreleased){
		unsigned char args[1];
		args[0] = SERVO_OFF;

		if(servoPort != NA)
			m_ezb->SendCommand(servoPort + EZB::SetServoPosition, args, 1);

		m_servos[servoPort].isreleased = true;
		clock_gettime(1, &m_servos[servoPort].last_move_time);
	}

}
void ServoClass::ReleaseAllServos(){
	m_ezb->SendCommand(EZB::ReleaseAllServos);
	for(int i = 0; i < NA; i++){
		m_servos[i].isreleased = true;
		clock_gettime(1, &m_servos[i].last_move_time);
	}
}
