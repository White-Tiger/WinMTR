//*****************************************************************************
// FILE:            WinMTRMain.h
//
//
// DESCRIPTION:
//
//
// NOTES:
//
//
//*****************************************************************************
//#pragma comment(linker, "/SUBSYSTEM:Console");

#ifndef WINMTRMAIN_H_
#define WINMTRMAIN_H_

#include "WinMTRDialog.h"
#include <string>

class outbuf : public std::streambuf {
public:
    outbuf() {
        setp(0, 0);
    }

    virtual int_type overflow(int_type c = traits_type::eof()) {
        return fputc(c, stdout) == EOF ? traits_type::eof() : c;
    }
};
class errbuf : public std::streambuf {
public:
    errbuf() {
        setp(0, 0);
    }

    virtual int_type overflow(int_type c = traits_type::eof()) {
        return fputc(c, stdout) == EOF ? traits_type::eof() : c;
    }
};
//*****************************************************************************
// CLASS:  WinMTRMain
//
//
//*****************************************************************************

class WinMTRMain : public CWinApp
{
public:
    WinMTRMain();
    ~WinMTRMain();

    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
private:
    void	ParseCommandLineParams(LPTSTR cmd, WinMTRDialog* wmtrdlg);
    int		GetParamValue(LPTSTR cmd, char* param, char sparam, char* value);
    int		GetHostNameParamValue(LPTSTR cmd, std::string& value);

};

#endif // ifndef WINMTRMAIN_H_

