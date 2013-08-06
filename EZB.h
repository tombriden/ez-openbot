#ifndef _EZ_CONN_H
#define _EZ_CONN_H

#include <stdlib.h>
#include <stdio.h>

#include <stdexcept>
#include <errno.h>
#ifdef _WINDOWS
#include "windows_ports.h"
#else
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <sys/socket.h>
#include <pthread.h>

#endif
#include "ADC.h"
#include "Configuration.h"
#include "Digital.h"
#include "HC_SR04.h"
#include "I2C.h"
#include "Movement.h"
#include "PWM.h"
#include "Servo.h"
#include "SureDualAxisCompass.h"
#include "Tone.h"
#include "Uart.h"

#define KEEP_ALIVE_INTERVAL 2000

class EZB{

private:

	long m_socket;
	bool m_exit;
	bool m_connected;
	bool m_verbose;

	double m_firmware;
	char m_firmware_str[20];

	char* m_mac_address;
	

	unsigned char m_keepalive[1];

#ifdef _WINDOWS
	_SOCKADDR_BTH m_addr;
	CRITICAL_SECTION m_send_mutex;
	HANDLE m_keepalive_thread;
#else
	struct sockaddr_rc m_addr;
	pthread_t m_keepalive_thread;
	pthread_mutex_t m_send_mutex;
#endif

	long m_lastcommand_time;

	void CreateObjects();
	bool KeepAlive();

public:

	enum CommandEnum{
		Unknown = 0,
		ReleaseAllServos = 1,
		SetSerialMacro = 2,
		SetI2CMacro = 3,
		WriteConfiguration = 4,
		ReadConfiguration = 5,
		StatusLED = 6,
		I2CStart = 7,
		I2CRestart = 8,
		I2CStop = 9,
		I2CWrite = 10,
		I2CRead = 11,
		I2CReadAutoAck = 12,
		I2CPoll = 13,
		BootLoader = 14,
		SetPWMSpeed = 15,
		BV4113_Cmd = 35,
		SetServoSpeed = 40,
		Ping = 85,
		SetDigitalPortOn = 100,
		SetDigitalPortOff = 120,
		GetDigitalPort = 140,
		SetServoPosition = 160,
		GetADCValue = 180,
		SendSerial = 190,
		HC_SR04 = 210,
		PlayNote = 230,
	};

	ADCClass* ADC;
	ConfigurationClass* Configuration;
	DigitalClass* Digital;
	HC_SR04Class* HCSR04;
	I2CClass* I2C;
	MovementClass* Movement;
	PWMClass* PWM;
	ServoClass* Servo;
	SureDualAxisCompassClass* SureDualAxisCompass;
	ToneClass* Tone;
	UartClass* Uart;

	EZB();
	~EZB();
	void Connect(char* mac_address);
	void Disconnect();
	bool IsConnected();
	void SetVerboseLogging(bool verbose);
	time_t LastCommandTime();
	void SendCommand(unsigned char command);
	void SendCommand(unsigned char command, unsigned char* args, int num_args);
	unsigned char* SendCommand(unsigned char command, unsigned char* args, int num_args, int expected_ret_bytes);
	unsigned char* SendCommand(unsigned char command, int expected_ret_bytes);
	void SetLEDStatus(bool status);
	char* GetFirmwareVersion();
	double GetFirmwareVersionRaw();
	void ConnectionCheck();
	static char* VersionNumber();
};

void* ConnectionCheckStub(void* lParam);

#ifdef _WINDOWS
int str2ba(const char* straddr, BTH_ADDR* btaddr);
#endif


#endif
