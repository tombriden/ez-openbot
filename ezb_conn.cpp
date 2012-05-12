#include "ezb_conn.h"

EZB_Conn::EZB_Conn(){
	m_mac_address = NULL;
	m_connected = false;
	m_socket = 0;
	m_keepalive = new char[1];
	m_keepalive[0] = KEEP_ALIVE;
}

EZB_Conn::~EZB_Conn(){
	m_exit = true;
	pthread_join(m_keepalive_thread, NULL);
	Disconnect();
	free(m_mac_address);
	m_mac_address = NULL;
}

void EZB_Conn::Disconnect(){

	if(m_socket){
		close(m_socket);
		m_socket = 0;
	}

}
void EZB_Conn::Connect(char* mac_address){
	if(mac_address){
		m_mac_address = (char*)malloc(sizeof(char) * (strlen(mac_address)+1));
		strcpy(m_mac_address, mac_address);
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

	pthread_create(&m_keepalive_thread, NULL, KeepAliveStub, (void*)this);


}

bool EZB_Conn::Connected(){
	return m_connected;
}

char* EZB_Conn::Send(char* command_in, int len, int expected_ret_bytes){

	char buff[255];
	write(m_socket, (void*)command_in, len);
	int ret = 0;
	char* retval = NULL;

	if(expected_ret_bytes){
		ret = read(m_socket, buff, 255);
		if(ret > 0){
			retval = new char[ret];
			memcpy(retval, buff, ret);
		}
	}

	return retval;
}

void EZB_Conn::KeepAlive(){

	while(!m_exit){
		char* retval = Send(m_keepalive, 1);
		if(retval){
			printf("Return %d\n", retval[0]);
			delete [] retval;
		}
		sleep(KEEP_ALIVE_INTERVAL);
	}
}

void* KeepAliveStub(void* lParam){
	((EZB_Conn*)lParam)->KeepAlive();
	return NULL;
}

