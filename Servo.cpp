#include "Servo.h"
#include <time.h>


ServoClass::ServoClass(EZB_Conn* ezb){
	m_ezb = ezb;

	time_t now = time(NULL);
	for(int i = 0; i < NA; i++){
		m_servos[i].curr_pos = 0;
		m_servos[i].curr_speed = 0;
		m_servos[i].last_move_time = now;
		m_servos[i].isreleased = true;
	}

}

double ServoClass::GetNumberOfSecondsSinceLastMove(ServoPortEnum servoPort){
	time_t now = time(NULL);
	double num_seconds = now - m_servos[servoPort].last_move_time;

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

	char command[2];

	if(speed > -1){
		SetServoSpeed(servoPort, speed);
	}

	command[0] = servoPort + EZB_Conn::SetServoPosition;
	command[1] = position;

	m_ezb->Send(command, 2);

	m_servos[servoPort].curr_pos = position;
	if(position == SERVO_OFF)
		m_servos[servoPort].isreleased = true;
	else
		m_servos[servoPort].isreleased = false;
	m_servos[servoPort].last_move_time = time(NULL);
}

void ServoClass::SetServoSpeed(ServoPortEnum ServoClassPort, int speed){
	if(speed > SERVO_SPEED_SLOWEST)
		speed = SERVO_SPEED_SLOWEST;
	else if(speed < SERVO_SPEED_FASTEST)
		speed = SERVO_SPEED_FASTEST;

	char command[2];
	command[0] = ServoClassPort + EZB_Conn::SetServoSpeed;
	command[1] = speed;

	m_ezb->Send(command, 2);

	m_servos[ServoClassPort].curr_speed = speed;
}

void ServoClass::ReleaseServo(ServoPortEnum servoPort){
	if(!m_servos[servoPort].isreleased)
		SetServoPosition(servoPort, 0);

}
void ServoClass::ReleaseAllServos(){
	char command[1];
	command[0] = 1;
	m_ezb->Send(command, 1);
}
