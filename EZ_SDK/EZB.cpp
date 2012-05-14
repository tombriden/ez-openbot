#include "EZB.h"
#include "version.h"

EZB::EZB(){

	Servo = NULL;
	Digital = NULL;
	ADC = NULL;
	Configuration = NULL;

	m_mac_address = NULL;
	m_connected = false;
	m_socket = 0;
	m_keepalive[0] = EZB::Ping;
	m_verbose = true;
	m_firmware = -1;
	strcpy(m_firmware_str, "");
	m_lastcommand_time = time(NULL);
	m_exit = false;
}

EZB::~EZB(){
	m_exit = true;
	if(m_keepalive_thread){
		pthread_join(m_keepalive_thread, NULL);
		m_keepalive_thread = 0;
	}
	Disconnect();
	if(m_mac_address){
		free(m_mac_address);
		m_mac_address = NULL;
	}
}

void EZB::Disconnect(){

	if(m_socket){
		close(m_socket);
		m_socket = 0;
	}

}
void EZB::Connect(char* mac_address){

	if(m_connected)
		throw std::runtime_error("Already connected");


	if(mac_address){
		m_mac_address = (char*)malloc(sizeof(char) * (strlen(mac_address)+1));
		strcpy(m_mac_address, mac_address);
	}else{

	}

	// allocate a socket
	m_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	// set the connection parameters (who to connect to)
	m_addr.rc_family = AF_BLUETOOTH;
	m_addr.rc_channel = (uint8_t) 1;
	str2ba( m_mac_address, &m_addr.rc_bdaddr );

	// connect to server
	int status = connect(m_socket, (struct sockaddr *)&m_addr, sizeof(m_addr));

	if(status < 0){
		char error[512];
		sprintf(error, "%s", strerror(errno));
		throw std::runtime_error(error);
	}

	CreateObjects();

	pthread_mutex_init(&m_send_mutex, NULL);
	m_connected = true;

	SendCommand(EZB::Ping);
	usleep(1000000);



	if(!KeepAlive())
		throw std::runtime_error("Controller not responding");


	pthread_create(&m_keepalive_thread, NULL, ConnectionCheckStub, (void*)this);


}

void EZB::CreateObjects(){
	ADC = new ADCClass(this);
	Configuration = new ConfigurationClass(this);
	Digital = new DigitalClass(this);
	HCSR04 = new HC_SR04Class(this);
	I2C = new I2CClass(this);
	Movement = new MovementClass(this);
	PWM = new PWMClass(this);
	Servo = new ServoClass(this);
	SureDualAxisCompass = new SureDualAxisCompassClass(this);
	Tone = new ToneClass(this);
	Uart = new UartClass(this);

}

bool EZB::IsConnected(){
	return m_connected;
}

char* EZB::GetFirmwareVersion(){

	if(m_firmware == 0)
		sprintf(m_firmware_str, "Unknown Firmware");
	else
		sprintf(m_firmware_str, "EZ-B Firmware V%.1f", m_firmware);

	return m_firmware_str;
}

double EZB::GetFirmwareVersionRaw(){
	return m_firmware;
}

void EZB::SetVerboseLogging(bool verbose){
	m_verbose = verbose;
}

void EZB::SendCommand(unsigned char command){
	SendCommand(command, NULL, 0, 0);
}

void EZB::SendCommand(unsigned char command, unsigned char* args, int num_args){
	SendCommand(command, args, num_args, 0);
}

unsigned char* EZB::SendCommand(unsigned char command, int expected_ret_bytes){
	return SendCommand(command, NULL, 0, expected_ret_bytes);
}

unsigned char* EZB::SendCommand(unsigned char command, unsigned char* args, int num_args, int expected_ret_bytes){

	pthread_mutex_lock(&m_send_mutex);
	unsigned char* bytestosend = (unsigned char*)malloc(sizeof(unsigned char) * (1 + num_args));

	bytestosend[0] = command;
	for(int i = 0; i < num_args; i++)
		bytestosend[i+1] = args[0];

	if(m_verbose){
		printf("Sending: ");
		for(int i = 0; i <= num_args; i++)
			printf("%d ", bytestosend[i]);
		printf("\n");
	}

	if(command == EZB::Unknown)
		throw std::runtime_error("Unknown command");
	else if(!m_connected)
		throw std::runtime_error("Not connected");


	write(m_socket, (void*)bytestosend, num_args+1);
	struct timespec now;
	clock_gettime(1, &now);
	m_lastcommand_time = (now.tv_sec * 1000) + (now.tv_nsec / 1000000);

	free(bytestosend);

	unsigned char* retval = NULL;

	if(expected_ret_bytes){
		if(m_verbose)
			printf("Expecting bytes: %d\n", expected_ret_bytes);

		retval = new unsigned char[expected_ret_bytes];
		memset(retval, 0, expected_ret_bytes);
		read(m_socket, retval, expected_ret_bytes);

		if(m_verbose){
			printf("Received: ");
			for(int i = 0; i < expected_ret_bytes; i++)
				printf("%d ", retval[i]);
			printf("\n");
		}
	}
	pthread_mutex_unlock(&m_send_mutex);

	return retval;
}

void EZB::SetLEDStatus(bool status){
	unsigned char arg[1];
	if(status)
		arg[0] = 1;
	else
		arg[0] = 0;
	SendCommand(EZB::StatusLED, arg, 1);
}

bool EZB::KeepAlive(){

	unsigned char* retval = SendCommand(EZB::Ping, 1);
	if(retval[0] <= 15){
		m_firmware = retval[0];
	}else{
		m_firmware = (double)((double)retval[0] / 10);

	}
	delete [] retval;

	return m_firmware != 0;
}


void EZB::ConnectionCheck(){

	while(!m_exit){
		if(m_lastcommand_time + (KEEP_ALIVE_INTERVAL/1000) <= time(NULL) && !KeepAlive()){
			m_connected = false;
			break;
		}
		usleep(KEEP_ALIVE_INTERVAL * 1000);
	}
}

char* EZB::VersionNumber(){
	return STR_EZSDK_VERSION_NUM;
}

void* ConnectionCheckStub(void* lParam){
	((EZB*)lParam)->ConnectionCheck();
	return NULL;
}
