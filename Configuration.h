#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

class EZB;


class ConfigurationClass{
private:
	EZB* m_ezb;
public:
	enum ConfigurationEnum{
		Single_Value_Test = 10,
	};

	enum StringConfigurationEnum{
		BluetoothName = 0,
	};

	void BluetoothName_Set(unsigned char* value);
	unsigned char* BluetoothName_Get();

	ConfigurationClass(EZB* ezb);

	unsigned char GetConfiguration(ConfigurationEnum memoryPosition);
	unsigned char* GetConfiguration(StringConfigurationEnum memoryPosition, unsigned char length);
	void SetConfiguration(ConfigurationEnum memoryPosition, unsigned char value);
	void SetConfiguration(StringConfigurationEnum memoryPosition, unsigned char maxLength, unsigned char* value);


};



#endif
