//*****************************************************************************
// FILE:            WinMTRGlobal.cpp
//
//
//*****************************************************************************

#include "WinMTRGlobal.h"

//*****************************************************************************
// gettimeofday
//
// win32 port of unix gettimeofday
//*****************************************************************************
int gettimeofday(struct timeval* tv, struct timezone *tz)
{
   if(!tv)
      return -1;
   struct _timeb timebuffer;
   
   _ftime(&timebuffer);

   tv->tv_sec = timebuffer.time;
   tv->tv_usec = timebuffer.millitm * 1000 + 500;
   return 0;
}

