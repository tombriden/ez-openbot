/*
 * version.h
 *
 *  Created on: May 12, 2012
 *      Author: Tom Briden
 */

#ifndef VERSION_H_
#define VERSION_H_

#define STR_EZSDK_VERSION_NUM "0.0.0.10\0"
#define EZSDK_VERSION_NUM 0,0,0,10


/// Tom		14/05/2012	0.0.0.10
/// + windows_ports: Required code for windows dll to build
/// + Resource file for windows dll versioning
/// * various fixes for warnings given by visual studio compiler
///
/// Tom		13/05/2012	0.0.0.9
/// * EZB: Added a mutex lock around the internal of SendCommand
/// * ADC: Fixed storing last_values in char not unsigned char
///
/// Tom		13/05/2012	0.0.0.8
/// + BlinkM: Based on official c# code
/// + BV4113: Based on official c# code
/// + BV4615: Based on official c# code
/// + MP3Trigger: Based on official c# code
///
/// Tom		13/05/2012	0.0.0.7
/// * EZB: Store last command time in milliseconds
/// * EZB: Made KeepAlive and CreateObjects private
///
/// Tom		13/05/2012	0.0.0.6
/// * Servo/Digital/ADC: Fixed checking if minpooltime has passed and now store last request time in ms
/// * Digital: Fixed SetDigitalPort
/// * EZB: Only free mac_address if its not null
/// + EZB: Added function to get vn num
///
/// Tom		13/05/2012	0.0.0.5
/// + CompassDirection: Based on official c# code
/// + I2C: Based on official c# code
/// + Movement: Based on official c# code
/// + PWM: Based on official c# code
/// + SureDualAxisCompass: Based on official c# code
/// + Tone: Based on official c# code
/// + Uart: Based on official c# code
///
/// Tom		13/05/2012	0.0.0.4
/// * Rewrote parts to be closer to decompiled  official dll source, eg using the min pool times, the keep alive method, etc
/// * Finished Configuration and HC_SR04 classes
///
/// Tom		12/05/2012	0.0.0.3
/// + ADC: Class to get voltage from ports, all features from official Windows sdk ported
/// + Configuration: Class to set/get config options, although only seems to be blutooth name and a test value?
/// - EZB_SDK: No point in this as was just a parent for all other classes. Moved objects into EZB_Conn instead
/// * EZB: Renamed from EZB_Conn and is now the main class
/// + EZB: Added GetFirmwareVersion and GetFirmwareVersionRaw functions
/// * HC_SR04: Added class code as much as i can without connecting the sensor
///
/// Tom		12/05/2012	0.0.0.2
/// * EZB_Conn: Fixed getting return value
/// * Digital: Finished class and got it working properly
///
/// Tom		12/05/2012	0.0.0.1
/// First build:
/// + EZ_SDK: Main class, this is the object referencing projects will access, it holds the objects for controlling servos, ports, etc
/// + EZB_Conn: Handles the connection to the ezb, sending it commands and has a keep alive thread
/// + Servo: Controls servos, all features from official Windows sdk ported
/// + Digital: Controls digital ports, all features from official Windows sdk ported



#endif /* VERSION_H_ */
