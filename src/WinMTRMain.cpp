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
#ifdef WIN_MTR_NO_GUI
    CString header = "Welcome to the WinMTR - SHELL MODE!\n\n";
    bool is_attach_success = AttachConsole(ATTACH_PARENT_PROCESS);     // Use current console window
    bool is_alloc_console_success = false;
    if(!is_attach_success)
    {
        is_alloc_console_success = AllocConsole();
    }
 //   LPDWORD charsWritten = 0;
 //   WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), header, header.GetLength(), NULL, NULL);
#endif
    AfxEnableControlContainer();


    WinMTRDialog mtrDialog;
    m_pMainWnd = &mtrDialog;

    if(strlen(m_lpCmdLine)) {
        strcat(m_lpCmdLine," ");
        ParseCommandLineParams(m_lpCmdLine, &mtrDialog);
    }
#ifdef WIN_MTR_NO_GUI
    m_pMainWnd = NULL;
    bool exit_code =  EXIT_SUCCESS;
    if  (
        mtrDialog.hasReportFromCmdLine   == true
        &&
        mtrDialog.hasDurationFromCmdLine == false
        )
    {
        if(mtrDialog.hasReportFromCmdLine)
        {
            CString err_msg = "Error: -report requires --duration to be passed!\n";
            WriteConsole(GetStdHandle(STD_ERROR_HANDLE), err_msg, err_msg.GetLength(), NULL, NULL);
        }
        exit_code = EXIT_FAILURE;
    }
    else if(!mtrDialog.hasHostNameFromCmdLine)
    {
        if(mtrDialog.hasReportFromCmdLine)
        {
            CString err_msg = "Error: No hostname specified!\n";
            WriteConsole(GetStdHandle(STD_ERROR_HANDLE), err_msg, err_msg.GetLength(), NULL, NULL);
        }
        exit_code = EXIT_FAILURE;
    }
    else if(!mtrDialog.hasDurationFromCmdLine)
    {
        if(mtrDialog.hasReportFromCmdLine)
        {
            CString err_msg = "Error: No duration specified!\n";
            WriteConsole(GetStdHandle(STD_ERROR_HANDLE), err_msg, err_msg.GetLength(), NULL, NULL);
        }
        exit_code = EXIT_FAILURE;
    }
    else
    {
        exit_code = mtrDialog.ProcessNoGuiTask();
    }
    FreeConsole();
    return exit_code;
#else
    mtrDialog.DoModal();
#endif
    return FALSE;
}


//*****************************************************************************
// WinMTRMain::ParseCommandLineParams
//
//
//*****************************************************************************
void WinMTRMain::ParseCommandLineParams(LPTSTR cmd, WinMTRDialog* wmtrdlg)
{
    char value[1024];
    std::string host_name = "";

    if(GetParamValue(cmd, "help",'h', value)) {
#ifdef WIN_MTR_NO_GUI
        CString help_text("\
WinMTR (Redux) v1.00 is offered under GPLv2 www.appnor.com\n\n\
Usage: WinMTR [options] target_host_name\n \
Options:\n \
\t--interval,   -i VALUE. Set ping interval.\n\
\t--size,       -s VALUE. Set ping size.\n \
\t--maxLRU,     -m VALUE. Set max hosts in LRU list.\n \
\t--numeric,    -n Do not resolve names.\n \
\t--duration,   -d VALUE  Sets the duration for tracing (in seconds).\n \
\t--report,     -r Prints the report on standard output.\n \
\t--help,       -h Print this help.\n");
        WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), help_text, help_text.GetLength(), NULL, NULL);

#else
        WinMTRHelp mtrHelp;
        m_pMainWnd = &mtrHelp;
        mtrHelp.DoModal();
#endif
        exit(0);
    }

    if(GetHostNameParamValue(cmd, host_name)) {
        wmtrdlg->SetHostName(host_name.c_str());
        wmtrdlg->hasHostNameFromCmdLine = true;
    }
    if(GetParamValue(cmd, "interval",'i', value)) {
        wmtrdlg->SetInterval((float)atof(value));
        wmtrdlg->hasIntervalFromCmdLine = true;
    }
    if(GetParamValue(cmd, "size",'s', value)) {
        wmtrdlg->SetPingSize((WORD)atoi(value));
        wmtrdlg->hasPingsizeFromCmdLine = true;
    }
    if(GetParamValue(cmd, "maxLRU",'m', value)) {
        wmtrdlg->SetMaxLRU(atoi(value));
        wmtrdlg->hasMaxLRUFromCmdLine = true;
    }
    if(GetParamValue(cmd, "numeric",'n', NULL)) {
        wmtrdlg->SetUseDNS(FALSE);
        wmtrdlg->hasUseDNSFromCmdLine = true;
    }
    if(GetParamValue(cmd, "ipv6",'6', NULL)) {
        wmtrdlg->hasUseIPv6FromCmdLine=true;
        wmtrdlg->useIPv6=1;
    }    
    if(GetParamValue(cmd, "ipv4",'4', NULL)) {
        wmtrdlg->hasUseIPv6FromCmdLine=true;
        wmtrdlg->useIPv6=0;
    }    
    if(GetParamValue(cmd, "duration",'d', value)) {
        wmtrdlg->SetDuration((long)atol(value));
        wmtrdlg->hasDurationFromCmdLine = true;
    }    
    if(GetParamValue(cmd, "report",'r', value)) {
        wmtrdlg->hasReportFromCmdLine   = true;
    }

}

//*****************************************************************************
// WinMTRMain::GetParamValue
//
//
//*****************************************************************************
int WinMTRMain::GetParamValue(LPTSTR cmd, char* param, char sparam, char* value)
{
    char* p;

    char p_long[1024];
    char p_short[1024];

    sprintf(p_long,"--%s ", param);
    sprintf(p_short,"-%c ", sparam);

    if((p=strstr(cmd, p_long))) ;
    else
        p=strstr(cmd, p_short);

    if(p == NULL)
        return 0;

    if(!value)
        return 1;

    while(*p && *p!=' ')
        p++;
    while(*p==' ') p++;

    int i = 0;
    while(*p && *p!=' ')
        value[i++] = *p++;
    value[i]='\0';

    return 1;
}

//*****************************************************************************
// WinMTRMain::GetHostNameParamValue
//
//
//*****************************************************************************
int WinMTRMain::GetHostNameParamValue(LPTSTR cmd, std::string& host_name)
{
    // WinMTR -h -i 1 -n google.com
    size_t size = strlen(cmd);
    std::string name = "";
    while(cmd[--size] == ' ');

    size++;
    while(size-- && cmd[size] != ' ' && (cmd[size] != '-' || cmd[size - 1] != ' ')) {
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
    if(cmd[size] == '-' && cmd[size - 1] == ' ') {
        // no target specified
        return 0;
    }

    std::string possible_argument = "";

    while(size-- && cmd[size] != ' ') {
        possible_argument = cmd[size] + possible_argument;
    }

    if(possible_argument.length() && (possible_argument[0] != '-' || possible_argument == "-n" || possible_argument == "--numeric" || possible_argument == "-6" || possible_argument == "--ipv6" || possible_argument == "-4" || possible_argument == "--ipv4" || \
        possible_argument == "--report" || possible_argument == "-r" || \
        possible_argument == "--duration" || possible_argument == "-d"
        )) 
    {
        host_name = name;
        return 1;
    }

    return 0;
}
