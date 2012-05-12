/*
 * version.h
 *
 *  Created on: May 12, 2012
 *      Author: Tom Briden
 */

#ifndef VERSION_H_
#define VERSION_H_

#define STR_EZSDK VERSION_NUM "0.0.0.1\0"
#define EZSDK_VERSION_NUM 0,0,0,1

/// Tom		12/05/2012	0.0.0.1
/// First build:
/// + EZ_SDK: Main class, this is the object referencing projects will access, it holds the objects for controlling servos, ports, etc
/// + EZB_Conn: Handles the connection to the ezb, sending it commands and has a keep alive thread
/// + Servo: Controls servos, all features from official Windows sdk ported
/// + Digital: Controls digital ports, all features from official Windows sdk ported



#endif /* VERSION_H_ */
