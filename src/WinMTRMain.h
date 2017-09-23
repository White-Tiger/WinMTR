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
	void	ParseCommandLineParams(LPTSTR cmd, WinMTRDialog* wmtrdlg);
	int		GetParamValue(LPTSTR cmd, TCHAR* param, TCHAR sparam, TCHAR* value);
	int		GetHostNameParamValue(LPTSTR cmd, 
#ifdef _UNICODE
		std::wstring&
#else
		std::string&
#endif
		value);
	
};

#endif // ifndef WINMTRMAIN_H_

