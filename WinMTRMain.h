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

#ifndef WINMTRMAIN_H_
#define WINMTRMAIN_H_

#include "WinMTRDialog.h"
#include <string>


//*****************************************************************************
// CLASS:  WinMTRMain
//
//
//*****************************************************************************

class WinMTRMain : public CWinApp
{
public:
	WinMTRMain();

	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

private:
	void	ParseCommandLineParams(LPTSTR cmd, WinMTRDialog *wmtrdlg);
	int		GetParamValue(LPTSTR cmd, char * param, char sparam, char *value);
	int		GetHostNameParamValue(LPTSTR cmd, std::string& value);

};

#endif // ifndef WINMTRMAIN_H_

