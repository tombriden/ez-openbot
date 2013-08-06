#include "BV4113.h"
#include "EZB.h"

BV4113Class::BV4113Class(EZB* ezb){
	m_ezb = ezb;
	m_speed = MovementClass::MAX_SPEED;
}

void BV4113Class::Forward(){
	unsigned char dir[1];
	dir[0] = MovementClass::Forward;
	m_ezb->SendCommand(EZB::BV4113_Cmd, dir, 1);
}

void BV4113Class::Left(){
	unsigned char dir[1];
	dir[0] = MovementClass::Left;
	m_ezb->SendCommand(EZB::BV4113_Cmd, dir, 1);
}

void BV4113Class::Reverse(){
	unsigned char dir[1];
	dir[0] = MovementClass::Reverse;
	m_ezb->SendCommand(EZB::BV4113_Cmd, dir, 1);
}

void BV4113Class::Right(){
	unsigned char dir[1];
	dir[0] = MovementClass::Right;
	m_ezb->SendCommand(EZB::BV4113_Cmd, dir, 1);
}

void BV4113Class::Stop(){
	unsigned char dir[1];
	dir[0] = MovementClass::Stop;
	m_ezb->SendCommand(EZB::BV4113_Cmd, dir, 1);
}
