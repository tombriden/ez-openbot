#include "Configuration.h"
#include "EZB.h"

ConfigurationClass::ConfigurationClass(EZB* ezb){
	m_ezb = ezb;
	m_bluetoothname_maxlen = 9;
}

unsigned char ConfigurationClass::GetConfiguration(ConfigurationEnum memoryPosition){

	unsigned char command[3];
	command[0] = EZB::ReadConfiguration;
	command[1] = memoryPosition;
	command[2] = 1;

	unsigned char* retval = m_ezb->Send(command, 3, 1);
	unsigned char val = retval[0];
	delete [] retval;

	return val;

}

unsigned char* ConfigurationClass::GetConfiguration(StringConfigurationEnum memoryPosition, unsigned char length){
	unsigned char command[3];
	command[0] = EZB::ReadConfiguration;
	command[1] = memoryPosition;
	command[2] = BluetoothName;

	unsigned char* retval = m_ezb->Send(command, 3, length);
	return retval;

}

void ConfigurationClass::SetConfiguration(ConfigurationEnum memoryPosition, unsigned char value){

	/*unsigned char command[12];
	memset(command, 20, 12);
	command[0] = EZB::WriteConfiguration;
	command[1] = memoryPosition;
	command[2] = value;*/

}

void ConfigurationClass::SetConfiguration(StringConfigurationEnum memoryPosition, unsigned char maxLength, unsigned char* value){
	/*unsigned char command[3];
	command[0] = EZB::WriteConfiguration;
	command[1] = memoryPosition;
	command[2] = value;*/
}
