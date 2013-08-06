#ifdef _WINDOWS

#ifndef _WINDOWS_PORTS_H
#define _WINDOWS_PORTS_H



#include <winsock2.h>


#include <ws2bth.h>
#include <stdint.h>

#define close closesocket
#define AF_BLUETOOTH AF_BTH
#define BTPROTO_RFCOMM BTHPROTO_RFCOMM 
#define usleep Sleep
#define write send

struct timespec{
	time_t   tv_sec;   
	long     tv_nsec;  
};

LARGE_INTEGER getFILETIMEoffset();
int clock_gettime(int X, struct timespec *tv);


#endif
#endif