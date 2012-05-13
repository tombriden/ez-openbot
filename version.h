/*
 * version.h
 *
 *  Created on: May 12, 2012
 *      Author: Tom Briden
 */

#ifndef VERSION_H_
#define VERSION_H_

#define STR_EZSDK VERSION_NUM "0.0.0.4\0"
#define EZSDK_VERSION_NUM 0,0,0,4


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
