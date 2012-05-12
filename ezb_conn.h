#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <pthread.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define KEEP_ALIVE 85
#define KEEP_ALIVE_INTERVAL 4

class EZB_Conn{

private:

	long m_socket;
	bool m_exit;
	bool m_connected;

	char* m_mac_address;
	struct sockaddr_rc m_addr;

	char* m_keepalive;

	pthread_t m_keepalive_thread;

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

	EZB_Conn();
	~EZB_Conn();
	void Connect(char* mac_address);
	void Disconnect();
	bool Connected();
	void KeepAlive();
	char* Send(char* command_in, int len, int expected_ret_bytes = 0);
};

void* KeepAliveStub(void* lParam);
