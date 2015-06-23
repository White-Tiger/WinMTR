
#include "WinMTRGlobal.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>

extern "C"
{
int PASCAL WinMain(HINSTANCE inst,HINSTANCE dumb,LPSTR param,int show);
};


int main(int ac,char *av[])
{
 //   FreeConsole();
    char buf[256];
    int i;
    HINSTANCE inst;

    inst=(HINSTANCE)GetModuleHandle(NULL);

    buf[0]=0;
    for(i=1; i<ac; i++)
    {
        strcat(buf,av[i]);
        strcat(buf," ");
    }

    return WinMain(inst,NULL,buf,SW_SHOWNORMAL);
}