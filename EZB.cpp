#include "EZB.h"

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
	m_firmware = 0;
	strcpy(m_firmware_str, "");
}

EZB::~EZB(){
	m_exit = true;
	pthread_join(m_keepalive_thread, NULL);
	Disconnect();
	free(m_mac_address);
	m_mac_address = NULL;
}

void EZB::Disconnect(){

	if(m_socket){
		close(m_socket);
		m_socket = 0;
	}

}
void EZB::Connect(char* mac_address){
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
		//throw std::runtime_error(error);
		printf(error);
		return;
	}

	CreateObjects();
	m_connected = true;

	Send(m_keepalive, 1);
	pthread_create(&m_keepalive_thread, NULL, KeepAliveStub, (void*)this);


}

void EZB::CreateObjects(){
	Servo = new ServoClass(this);
	Digital = new DigitalClass(this);
	ADC = new ADCClass(this);
	Configuration = new ConfigurationClass(this);

}

bool EZB::IsConnected(){
	return m_connected;
}

char* EZB::GetFirmwareVersion(){

	if(m_firmware == 0)
		GetFirmwareVersionRaw();

	sprintf(m_firmware_str, "EZ-B Firmware V%.1f", m_firmware);
	return m_firmware_str;
}

double EZB::GetFirmwareVersionRaw(){
	if(m_firmware == 0){
		unsigned char command[1];
		command[0] = EZB::Ping;
		unsigned char* retval = Send(command, 1, 1);
		m_firmware = (double)((double)retval[0] / 10);
	}
	return m_firmware;
}

void EZB::SetVerboseLogging(bool verbose){
	m_verbose = verbose;
}

unsigned char* EZB::Send(unsigned char* command_in, int len, int expected_ret_bytes){

	if(m_verbose){
		printf("Sending: ");
		for(int i = 0; i < len; i++)
			printf("%d ", command_in[i]);
		printf("\n");
	}

	write(m_socket, (void*)command_in, len);
	unsigned char* retval = NULL;

	if(expected_ret_bytes){
		if(m_verbose)
			printf("Expecting bytes: %d\n", expected_ret_bytes);

		retval = new unsigned char[expected_ret_bytes];
		read(m_socket, retval, expected_ret_bytes);

		if(m_verbose){
			printf("Received: ");
			for(int i = 0; i < expected_ret_bytes; i++)
				printf("%d ", retval[i]);
			printf("\n");
		}
	}

	return retval;
}

void EZB::KeepAlive(){

	Send(m_keepalive, 1);

	while(!m_exit){
		sleep(KEEP_ALIVE_INTERVAL / 2);
		unsigned char* retval = Send(m_keepalive, 1, 1);
		if(retval){
			m_firmware = (double)(retval[0] / 10);
			delete [] retval;
		}
		sleep(KEEP_ALIVE_INTERVAL / 2);
	}
}

void* KeepAliveStub(void* lParam){
	((EZB*)lParam)->KeepAlive();
	return NULL;
}

