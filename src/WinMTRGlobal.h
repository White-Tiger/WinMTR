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
#include <Iphlpapi.h>//IP_OPTION_INFORMATION32
#include <ws2tcpip.h>//sockaddr_in6

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

#define WINMTR_VERSION	"1.0"
#define WINMTR_LICENSE	"GPLv2 - GNU General Public License, version 2"
#define WINMTR_HOMEPAGE	"https://github.com/White-Tiger/WinMTR"

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
    249, 30, 50, 40, 40, 50, 50, 50, 50
};

int gettimeofday(struct timeval* tv, struct timezone* tz);

#define WIN_MTR_NO_GUI


#ifdef WIN_MTR_NO_GUI
#pragma comment( linker, "/SUBSYSTEM:CONSOLE" )
#else
#pragma comment( linker, "/SUBSYSTEM:WINDOWS" )
#endif
#define PRESS_ENTER_KEY {\
    keybd_event(VK_RETURN, 0x9C, 0, 0); \
    keybd_event(VK_RETURN, 0x9C, KEYEVENTF_KEYUP, 0);\
}
#define HELP_TEXT "\
\nWinMTR (Redux) v1.00 is offered under GPLv2 www.appnor.com\n\n\
Usage: WinMTR [options] target_host_name\n\
Options:\n \
\t--interval,   -i VALUE. Set ping interval.\n\
\t--size,       -s VALUE. Set ping size.\n\
\t--maxLRU,     -m VALUE. Set max hosts in LRU list.\n\
\t--numeric,    -n Do not resolve names.\n\
\t--duration,   -d VALUE  Sets the duration for tracing (in seconds).\n\
\t--report,     -r Prints the report on standard output.\n\
\t--help,       -h Print this help.\n"


#endif // ifndef GLOBAL_H_
