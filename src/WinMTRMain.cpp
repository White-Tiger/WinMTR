//*****************************************************************************
// FILE:            WinMTRMain.cpp
//
//
// HISTORY:
//
//
//    -- versions 0.8
//
// - 01.18.2002 - Store LRU hosts in registry (v0.8)
// - 05.08.2001 - Replace edit box with combo box which hold last entered hostnames.
//				  Fixed a memory leak which caused program to crash after a long
//				  time running. (v0.7)
// - 11.27.2000 - Added resizing support and flat buttons. (v0.6)
// - 11.26.2000 - Added copy data to clipboard and posibility to save data to file as text or HTML.(v0.5)
// - 08.03.2000 - added double-click on hostname for detailed information (v0.4)
// - 08.02.2000 - fix icmp error codes handling. (v0.3)
// - 08.01.2000 - support for full command-line parameter specification (v0.2)
// - 07.30.2000 - support for command-line host specification
//					by Silviu Simen (ssimen@ubisoft.ro) (v0.1b)
// - 07.28.2000 - first release (v0.1)
//*****************************************************************************

#include "WinMTRGlobal.h"
#include "WinMTRMain.h"
#include "WinMTRDialog.h"
#include "WinMTRHelp.h"
#include <algorithm>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

WinMTRMain WinMTR;

//*****************************************************************************
// BEGIN_MESSAGE_MAP
//
//
//*****************************************************************************
BEGIN_MESSAGE_MAP(WinMTRMain, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

//*****************************************************************************
// WinMTRMain::WinMTRMain
//
//
//*****************************************************************************
WinMTRMain::WinMTRMain()
{
}

//*****************************************************************************
// WinMTRMain::InitInstance
//
//
//*****************************************************************************
BOOL WinMTRMain::InitInstance()
{
	INITCOMMONCONTROLSEX icex= {sizeof(INITCOMMONCONTROLSEX),ICC_STANDARD_CLASSES};
	InitCommonControlsEx(&icex);
	if(!AfxSocketInit()) {
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	
	AfxEnableControlContainer();
	
	
	WinMTRDialog mtrDialog;
	m_pMainWnd = &mtrDialog;
	
	if(_tcslen(m_lpCmdLine)) {
		_tcscat(m_lpCmdLine,_T(" "));
		ParseCommandLineParams(m_lpCmdLine, &mtrDialog);
	}
	
	mtrDialog.DoModal();
	
	
	return FALSE;
}


//*****************************************************************************
// WinMTRMain::ParseCommandLineParams
//
//
//*****************************************************************************
void WinMTRMain::ParseCommandLineParams(LPTSTR cmd, WinMTRDialog* wmtrdlg)
{
	TCHAR value[1024];
	_tstring host_name = _T("");
	
	if(GetParamValue(cmd, _T("help"),_T('h'), value)) {
		WinMTRHelp mtrHelp;
		m_pMainWnd = &mtrHelp;
		mtrHelp.DoModal();
		exit(0);
	}
	
	if(GetHostNameParamValue(cmd, host_name)) {
		wmtrdlg->SetHostName(host_name.c_str());
	}
	if(GetParamValue(cmd, _T("interval"),_T('i'), value)) {
		wmtrdlg->SetInterval((float)_ttof(value));
		wmtrdlg->hasIntervalFromCmdLine = true;
	}
	if(GetParamValue(cmd, _T("size"),_T('s'), value)) {
		wmtrdlg->SetPingSize((WORD)_ttoi(value));
		wmtrdlg->hasPingsizeFromCmdLine = true;
	}
	if(GetParamValue(cmd, _T("maxLRU"),_T('m'), value)) {
		wmtrdlg->SetMaxLRU(_ttoi(value));
		wmtrdlg->hasMaxLRUFromCmdLine = true;
	}
	if(GetParamValue(cmd, _T("numeric"),_T('n'), NULL)) {
		wmtrdlg->SetUseDNS(FALSE);
		wmtrdlg->hasUseDNSFromCmdLine = true;
	}
	if(GetParamValue(cmd, _T("ipv6"),_T('6'), NULL)) {
		wmtrdlg->hasUseIPv6FromCmdLine=true;
		wmtrdlg->useIPv6=1;
	}
	if(GetParamValue(cmd, _T("ipv4"),_T('4'), NULL)) {
		wmtrdlg->hasUseIPv6FromCmdLine=true;
		wmtrdlg->useIPv6=0;
	}
}

//*****************************************************************************
// WinMTRMain::GetParamValue
//
//
//*****************************************************************************
int WinMTRMain::GetParamValue(LPTSTR cmd, TCHAR* param, TCHAR sparam, TCHAR* value)
{
	TCHAR* p;
	
	TCHAR p_long[1024];
	TCHAR p_short[1024];
	
	_stprintf(p_long,_T("--%s "), param);
	_stprintf(p_short,_T("-%c "), sparam);
	
	if((p=_tcsstr(cmd, p_long))) ;
	else
		p=_tcsstr(cmd, p_short);
		
	if(p == NULL)
		return 0;
		
	if(!value)
		return 1;
		
	while(*p && *p!=_T(' '))
		p++;
	while(*p==_T(' ')) p++;
	
	int i = 0;
	while(*p && *p!=_T(' '))
		value[i++] = *p++;
	value[i]=_T('\0');
	
	return 1;
}

//*****************************************************************************
// WinMTRMain::GetHostNameParamValue
//
//
//*****************************************************************************
int WinMTRMain::GetHostNameParamValue(LPTSTR cmd, _tstring &host_name)
{
// WinMTR -h -i 1 -n google.com
	size_t size = _tcslen(cmd);
	_tstring name = _T("");
	while(cmd[--size] == _T(' '));
	
	size++;
	while(size-- && cmd[size] != _T(' ') && (cmd[size] != _T('-') || cmd[size - 1] != _T(' '))) {
		name = cmd[size ] + name;
	}
	
	if(size == -1) {
		if(name.length() == 0) {
			return 0;
		} else {
			host_name = name;
			return 1;
		}
	}
	if(cmd[size] == _T('-') && cmd[size - 1] == _T(' ')) {
		// no target specified
		return 0;
	}
	
	_tstring possible_argument = _T("");
	
	while(size-- && cmd[size] != _T(' ')) {
		possible_argument = cmd[size] + possible_argument;
	}
	
	if(possible_argument.length() && (possible_argument[0] != _T('-') || possible_argument == _T("-n") || possible_argument == _T("--numeric") || possible_argument == _T("-6") || possible_argument == _T("--ipv6") || possible_argument == _T("-4") || possible_argument == _T("--ipv4"))) {
		host_name = name;
		return 1;
	}
	
	return 0;
}
