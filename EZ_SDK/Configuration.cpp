#include "Configuration.h"
#include "EZB.h"

ConfigurationClass::ConfigurationClass(EZB* ezb){
	m_ezb = ezb;
}

void ConfigurationClass::BluetoothName_Set(unsigned char* value){
	SetConfiguration(ConfigurationClass::BluetoothName, 9, value);
}

unsigned char* ConfigurationClass::BluetoothName_Get(){
	return GetConfiguration(ConfigurationClass::BluetoothName, 9);
}

unsigned char ConfigurationClass::GetConfiguration(ConfigurationEnum memoryPosition){

	unsigned char args[2];
	args[0] = memoryPosition;
	args[1] = 1;

	unsigned char* retval = m_ezb->SendCommand(EZB::ReadConfiguration, args, 2, 1);
	unsigned char val = retval[0];
	delete [] retval;

	return val;

}

unsigned char* ConfigurationClass::GetConfiguration(StringConfigurationEnum memoryPosition, unsigned char length){

	unsigned char args[2];
	args[0] = memoryPosition;
	args[1] = length;

	unsigned char* retval = m_ezb->SendCommand(EZB::ReadConfiguration, args, 2, length);
	return retval;

}

void ConfigurationClass::SetConfiguration(ConfigurationEnum memoryPosition, unsigned char value){

	unsigned char args[3];
	args[0] = memoryPosition;
	args[1] = 1;
	args[2] = value;

	m_ezb->SendCommand(EZB::WriteConfiguration, args, 3);

}

void ConfigurationClass::SetConfiguration(StringConfigurationEnum memoryPosition, unsigned char maxLength, unsigned char* value){

	unsigned char args[maxLength + 1];
	args[0] = memoryPosition;
	memset(&args[1], 20, maxLength);
	memcpy(&args[1], value, maxLength);

	m_ezb->SendCommand(EZB::WriteConfiguration, args, maxLength+1);
}
