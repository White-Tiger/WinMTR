//*****************************************************************************
// FILE:            WinMTRGlobal.h
//
//
// DESCRIPTION:
//   
//
// NOTES:
//    
//
//*****************************************************************************

#ifndef GLOBAL_H_
#define GLOBAL_H_

#ifndef  _WIN64
#define  _USE_32BIT_TIME_T
#endif

#define VC_EXTRALEAN

#include <afxwin.h>
#include <afxext.h>
#include <afxdisp.h>
#include <afxdtctl.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
  #include <afxcmn.h>
#endif 
#include <afxsock.h>

#include <process.h>
#include <stdio.h>
#include <io.h> 
#include <time.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <math.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/stat.h>

#include "resource.h"

#define WINMTR_VERSION	"0.9"
#define WINMTR_LICENSE	"GPL - GNU Public License"
#define WINMTR_COPYRIGHT "WinMTR 0.9 (c) 2010-2011 Appnor MSP - Fully Managed Hosting & Cloud Provider www.appnor.com"
#define WINMTR_HOMEPAGE	"http://WinMTR.sourceforge.net"

#define DEFAULT_PING_SIZE	64
#define DEFAULT_INTERVAL	1.0
#define DEFAULT_MAX_LRU		128
#define DEFAULT_DNS			TRUE

#define SAVED_PINGS 100
#define MaxHost 256
//#define MaxSequence 65536
#define MaxSequence 32767
//#define MaxSequence 5

#define MAXPACKET 4096
#define MINPACKET 64

#define MaxTransit 4

 
#define ICMP_ECHO		8
#define ICMP_ECHOREPLY		0

#define ICMP_TSTAMP		13
#define ICMP_TSTAMPREPLY	14

#define ICMP_TIME_EXCEEDED	11

#define ICMP_HOST_UNREACHABLE 3

#define MAX_UNKNOWN_HOSTS 10

#define IP_HEADER_LENGTH   20


#define MTR_NR_COLS 9

const char MTR_COLS[ MTR_NR_COLS ][10] = {
		"Hostname",
		"Nr",
		"Loss %",
		"Sent",
		"Recv",
		"Best",
		"Avrg",
		"Worst",
		"Last"
};

const int MTR_COL_LENGTH[ MTR_NR_COLS ] = {
		190, 30, 50, 40, 40, 50, 50, 50, 50
};

int gettimeofday(struct timeval* tv, struct timezone *tz);

#endif // ifndef GLOBAL_H_
