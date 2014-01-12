//*****************************************************************************
// FILE:            WinMTRDialog.cpp
//
//
//*****************************************************************************

#include "WinMTRGlobal.h"
#include "WinMTRDialog.h"
#include "WinMTROptions.h"
#include "WinMTRProperties.h"
#include "WinMTRNet.h"
#include <iostream>
#include <sstream>
#include "afxlinkctrl.h"

#define TRACE_MSG(msg)										\
	{														\
	std::ostringstream dbg_msg(std::ostringstream::out);	\
	dbg_msg << msg << std::endl;							\
	OutputDebugString(dbg_msg.str().c_str());				\
	}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static	 char THIS_FILE[] = __FILE__;
#endif

void PingThread(void *p);

//*****************************************************************************
// BEGIN_MESSAGE_MAP
//
// 
//*****************************************************************************
BEGIN_MESSAGE_MAP(WinMTRDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_RESTART, OnRestart)
	ON_BN_CLICKED(ID_OPTIONS, OnOptions)
	ON_BN_CLICKED(ID_CTTC, OnCTTC)
	ON_BN_CLICKED(ID_CHTC, OnCHTC)
	ON_BN_CLICKED(ID_EXPT, OnEXPT)
	ON_BN_CLICKED(ID_EXPH, OnEXPH)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MTR, OnDblclkList)
	ON_CBN_SELCHANGE(IDC_COMBO_HOST, &WinMTRDialog::OnCbnSelchangeComboHost)
	ON_CBN_SELENDOK(IDC_COMBO_HOST, &WinMTRDialog::OnCbnSelendokComboHost)
	ON_CBN_CLOSEUP(IDC_COMBO_HOST, &WinMTRDialog::OnCbnCloseupComboHost)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &WinMTRDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


//*****************************************************************************
// WinMTRDialog::WinMTRDialog
//
// 
//*****************************************************************************
WinMTRDialog::WinMTRDialog(CWnd* pParent) 
			: CDialog(WinMTRDialog::IDD, pParent),
			state(IDLE),
			transition(IDLE_TO_IDLE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_autostart = 0;
	useDNS = DEFAULT_DNS;
	interval = DEFAULT_INTERVAL;
	pingsize = DEFAULT_PING_SIZE;
	maxLRU = DEFAULT_MAX_LRU;
	nrLRU = 0;

	hasIntervalFromCmdLine = false;
	hasPingsizeFromCmdLine = false;
	hasMaxLRUFromCmdLine = false;
	hasUseDNSFromCmdLine = false;

	traceThreadMutex = CreateMutex(NULL, FALSE, NULL);
	wmtrnet = new WinMTRNet(this);
}

WinMTRDialog::~WinMTRDialog()
{
	delete wmtrnet;
	CloseHandle(traceThreadMutex);
}

//*****************************************************************************
// WinMTRDialog::DoDataExchange
//
// 
//*****************************************************************************
void WinMTRDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_OPTIONS, m_buttonOptions);
	DDX_Control(pDX, IDCANCEL, m_buttonExit);
	DDX_Control(pDX, ID_RESTART, m_buttonStart);
	DDX_Control(pDX, IDC_COMBO_HOST, m_comboHost);
	DDX_Control(pDX, IDC_LIST_MTR, m_listMTR);
	DDX_Control(pDX, IDC_STATICS, m_staticS);
	DDX_Control(pDX, IDC_STATICJ, m_staticJ);
	DDX_Control(pDX, ID_EXPH, m_buttonExpH);
	DDX_Control(pDX, ID_EXPT, m_buttonExpT);
}


//*****************************************************************************
// WinMTRDialog::OnInitDialog
//
// 
//*****************************************************************************
BOOL WinMTRDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	#ifndef  _WIN64
	char caption[] = {"WinMTR v0.92 32 bit by Appnor MSP - www.winmtr.net"};
	#else
	char caption[] = {"WinMTR v0.92 64 bit by Appnor MSP - www.winmtr.net"};
	#endif

	SetTimer(1, WINMTR_DIALOG_TIMER, NULL);
	SetWindowText(caption);

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);
	
	if(!statusBar.Create( this ))
		AfxMessageBox("Error creating status bar");
	statusBar.GetStatusBarCtrl().SetMinHeight(23);
		
	UINT sbi[1];
	sbi[0] = IDS_STRING_SB_NAME;	
	statusBar.SetIndicators( sbi,1);
	statusBar.SetPaneInfo(0, statusBar.GetItemID(0),SBPS_STRETCH, NULL );
	{ // Add appnor URL
		CMFCLinkCtrl* m_pWndButton = new CMFCLinkCtrl;
		if (!m_pWndButton->Create(_T("www.appnor.com"), WS_CHILD|WS_VISIBLE|WS_TABSTOP, CRect(0,0,0,0), &statusBar, 1234)) {
			TRACE(_T("Failed to create button control.\n"));
			return FALSE;
		}

		m_pWndButton->SetURL("http://www.appnor.com/?utm_source=winmtr&utm_medium=desktop&utm_campaign=software");
			
		if(!statusBar.AddPane(1234,1)) {
			AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
			return FALSE;
		}
			
		statusBar.SetPaneWidth(statusBar.CommandToIndex(1234), 100);
		statusBar.AddPaneControl(m_pWndButton, 1234, true);
	}

	for(int i = 0; i< MTR_NR_COLS; i++)
		m_listMTR.InsertColumn(i, MTR_COLS[i], LVCFMT_LEFT, MTR_COL_LENGTH[i] , -1);
   
	m_comboHost.SetFocus();

	// We need to resize the dialog to make room for control bars.
	// First, figure out how big the control bars are.
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
				   0, reposQuery, rcClientNow);

	// Now move all the controls so they are in the same relative
	// position within the remaining client area as they would be
	// with no control bars.
	CPoint ptOffset(rcClientNow.left - rcClientStart.left,
					rcClientNow.top - rcClientStart.top);

	CRect  rcChild;
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)
	{
		pwndChild->GetWindowRect(rcChild);
		ScreenToClient(rcChild);
		rcChild.OffsetRect(ptOffset);
		pwndChild->MoveWindow(rcChild, FALSE);
		pwndChild = pwndChild->GetNextWindow();
	}

	// Adjust the dialog window dimensions
	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow(rcWindow, FALSE);

	// And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	InitRegistry();

	if (m_autostart) {
		m_comboHost.SetWindowText(msz_defaulthostname);
		OnRestart();
	}

	return FALSE;
}

//*****************************************************************************
// WinMTRDialog::InitRegistry
//
// 
//*****************************************************************************
BOOL WinMTRDialog::InitRegistry()
{
	HKEY hKey, hKey_v;
	DWORD res, tmp_dword, value_size;
	LONG r;

	r = RegCreateKeyEx(	HKEY_CURRENT_USER, 
					"Software", 
					0, 
					NULL,
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS,
					NULL,
					&hKey,
					&res);
	if( r != ERROR_SUCCESS) 
		return FALSE;

	r = RegCreateKeyEx(	hKey, 
					"WinMTR", 
					0, 
					NULL,
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS,
					NULL,
					&hKey,
					&res);
	if( r != ERROR_SUCCESS) 
		return FALSE;

	RegSetValueEx(hKey,"Version", 0, REG_SZ, (const unsigned char *)WINMTR_VERSION, sizeof(WINMTR_VERSION)+1);
	RegSetValueEx(hKey,"License", 0, REG_SZ, (const unsigned char *)WINMTR_LICENSE, sizeof(WINMTR_LICENSE)+1);
	RegSetValueEx(hKey,"HomePage", 0, REG_SZ, (const unsigned char *)WINMTR_HOMEPAGE, sizeof(WINMTR_HOMEPAGE)+1);

	r = RegCreateKeyEx(	hKey, 
					"Config", 
					0, 
					NULL,
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS,
					NULL,
					&hKey_v,
					&res);
	if( r != ERROR_SUCCESS) 
		return FALSE;

	if(RegQueryValueEx(hKey_v, "PingSize", 0, NULL, (unsigned char *)&tmp_dword, &value_size) != ERROR_SUCCESS) {
		tmp_dword = pingsize;
		RegSetValueEx(hKey_v,"PingSize", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
	} else {
		if(!hasPingsizeFromCmdLine) pingsize = tmp_dword;
	}
	
	if(RegQueryValueEx(hKey_v, "MaxLRU", 0, NULL, (unsigned char *)&tmp_dword, &value_size) != ERROR_SUCCESS) {
		tmp_dword = maxLRU;
		RegSetValueEx(hKey_v,"MaxLRU", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
	} else {
		if(!hasMaxLRUFromCmdLine) maxLRU = tmp_dword;
	}
	
	if(RegQueryValueEx(hKey_v, "UseDNS", 0, NULL, (unsigned char *)&tmp_dword, &value_size) != ERROR_SUCCESS) {
		tmp_dword = useDNS ? 1 : 0;
		RegSetValueEx(hKey_v,"UseDNS", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
	} else {
		if(!hasUseDNSFromCmdLine) useDNS = (BOOL)tmp_dword;
	}

	if(RegQueryValueEx(hKey_v, "Interval", 0, NULL, (unsigned char *)&tmp_dword, &value_size) != ERROR_SUCCESS) {
		tmp_dword = (DWORD)(interval * 1000);
		RegSetValueEx(hKey_v,"Interval", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
	} else {
		if(!hasIntervalFromCmdLine) interval = (float)tmp_dword / 1000.0;
	}

	r = RegCreateKeyEx(	hKey, 
					"LRU", 
					0, 
					NULL,
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS,
					NULL,
					&hKey_v,
					&res);
	if( r != ERROR_SUCCESS) 
		return FALSE;
	if(RegQueryValueEx(hKey_v, "NrLRU", 0, NULL, (unsigned char *)&tmp_dword, &value_size) != ERROR_SUCCESS) {
		tmp_dword = nrLRU;
		RegSetValueEx(hKey_v,"NrLRU", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
	} else {
		char key_name[20];
		unsigned char str_host[255];
		nrLRU = tmp_dword;
		for(int i=0;i<maxLRU;i++) {
			sprintf(key_name,"Host%d", i+1);
			if((r = RegQueryValueEx(hKey_v, key_name, 0, NULL, NULL, &value_size)) == ERROR_SUCCESS) {
				RegQueryValueEx(hKey_v, key_name, 0, NULL, str_host, &value_size);
				str_host[value_size]='\0';
				m_comboHost.AddString((CString)str_host);
			}
		}
	}
	m_comboHost.AddString(CString((LPCSTR)IDS_STRING_CLEAR_HISTORY));
	RegCloseKey(hKey_v);
	RegCloseKey(hKey);
	return TRUE;
}


//*****************************************************************************
// WinMTRDialog::OnSizing
//
// 
//*****************************************************************************
void WinMTRDialog::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);

	int iWidth = (pRect->right)-(pRect->left);
	int iHeight = (pRect->bottom)-(pRect->top);

	if (iWidth < 600)
		pRect->right = pRect->left + 600;
	if (iHeight <250)
		pRect->bottom = pRect->top + 250;
}


//*****************************************************************************
// WinMTRDialog::OnSize
//
// 
//*****************************************************************************
void WinMTRDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CRect r;
	GetClientRect(&r);
	CRect lb;
	
	if (::IsWindow(m_staticS.m_hWnd)) {
		m_staticS.GetWindowRect(&lb);
		ScreenToClient(&lb);
		m_staticS.SetWindowPos(NULL, lb.TopLeft().x, lb.TopLeft().y, r.Width()-lb.TopLeft().x-10, lb.Height() , SWP_NOMOVE | SWP_NOZORDER);
	}

	if (::IsWindow(m_staticJ.m_hWnd)) {
		m_staticJ.GetWindowRect(&lb);
		ScreenToClient(&lb);
		m_staticJ.SetWindowPos(NULL, lb.TopLeft().x, lb.TopLeft().y, r.Width() - 21, lb.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}

	if (::IsWindow(m_buttonExit.m_hWnd)) {
		m_buttonExit.GetWindowRect(&lb);
		ScreenToClient(&lb);
		m_buttonExit.SetWindowPos(NULL, r.Width() - lb.Width()-21, lb.TopLeft().y, lb.Width(), lb.Height() , SWP_NOSIZE | SWP_NOZORDER);
	}
	
	if (::IsWindow(m_buttonExpH.m_hWnd)) {
		m_buttonExpH.GetWindowRect(&lb);
		ScreenToClient(&lb);
		m_buttonExpH.SetWindowPos(NULL, r.Width() - lb.Width()-21, lb.TopLeft().y, lb.Width(), lb.Height() , SWP_NOSIZE | SWP_NOZORDER);
	}
	if (::IsWindow(m_buttonExpT.m_hWnd)) {
		m_buttonExpT.GetWindowRect(&lb);
		ScreenToClient(&lb);
		m_buttonExpT.SetWindowPos(NULL, r.Width() - lb.Width()- 103, lb.TopLeft().y, lb.Width(), lb.Height() , SWP_NOSIZE | SWP_NOZORDER);
	}

	if (::IsWindow(m_listMTR.m_hWnd)) {
		m_listMTR.GetWindowRect(&lb);
		ScreenToClient(&lb);
		m_listMTR.SetWindowPos(NULL, lb.TopLeft().x, lb.TopLeft().y, r.Width() - 21, r.Height() - lb.top - 25, SWP_NOMOVE | SWP_NOZORDER);
	}

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
				   0, reposQuery, r);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

}


//*****************************************************************************
// WinMTRDialog::OnPaint
//
// 
//*****************************************************************************
void WinMTRDialog::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


//*****************************************************************************
// WinMTRDialog::OnQueryDragIcon
//
// 
//*****************************************************************************
HCURSOR WinMTRDialog::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//*****************************************************************************
// WinMTRDialog::OnDblclkList
//
//*****************************************************************************
void WinMTRDialog::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;

	if(state == TRACING) {
		
		POSITION pos = m_listMTR.GetFirstSelectedItemPosition();
		if(pos!=NULL) {
			int nItem = m_listMTR.GetNextSelectedItem(pos);
			WinMTRProperties wmtrprop;

			if(wmtrnet->GetAddr(nItem)==0) {
				strcpy(wmtrprop.host,"");
				strcpy(wmtrprop.ip,"");
				wmtrnet->GetName(nItem, wmtrprop.comment);

				wmtrprop.pck_loss = wmtrprop.pck_sent = wmtrprop.pck_recv = 0;

				wmtrprop.ping_avrg = wmtrprop.ping_last = 0.0;
				wmtrprop.ping_best = wmtrprop.ping_worst = 0.0;
			} else {
				wmtrnet->GetName(nItem, wmtrprop.host);
				int addr = wmtrnet->GetAddr(nItem);
				sprintf (	wmtrprop.ip , "%d.%d.%d.%d", 
							(addr >> 24) & 0xff, 
							(addr >> 16) & 0xff, 
							(addr >> 8) & 0xff, 
							addr & 0xff
				);
				strcpy(wmtrprop.comment , "Host alive.");

				wmtrprop.ping_avrg = (float)wmtrnet->GetAvg(nItem); 
				wmtrprop.ping_last = (float)wmtrnet->GetLast(nItem); 
				wmtrprop.ping_best = (float)wmtrnet->GetBest(nItem);
				wmtrprop.ping_worst = (float)wmtrnet->GetWorst(nItem); 

				wmtrprop.pck_loss = wmtrnet->GetPercent(nItem);
				wmtrprop.pck_recv = wmtrnet->GetReturned(nItem);
				wmtrprop.pck_sent = wmtrnet->GetXmit(nItem);
			}

			wmtrprop.DoModal();
		}
	}
}


//*****************************************************************************
// WinMTRDialog::SetHostName
//
//*****************************************************************************
void WinMTRDialog::SetHostName(const char *host)
{
	m_autostart = 1;
	strncpy(msz_defaulthostname,host,1000);
}


//*****************************************************************************
// WinMTRDialog::SetPingSize
//
//*****************************************************************************
void WinMTRDialog::SetPingSize(int ps)
{
	pingsize = ps;
}

//*****************************************************************************
// WinMTRDialog::SetMaxLRU
//
//*****************************************************************************
void WinMTRDialog::SetMaxLRU(int mlru)
{
	maxLRU = mlru;
}


//*****************************************************************************
// WinMTRDialog::SetInterval
//
//*****************************************************************************
void WinMTRDialog::SetInterval(float i)
{
	interval = i;
}

//*****************************************************************************
// WinMTRDialog::SetUseDNS
//
//*****************************************************************************
void WinMTRDialog::SetUseDNS(BOOL udns)
{
	useDNS = udns;
}




//*****************************************************************************
// WinMTRDialog::OnRestart
//
// 
//*****************************************************************************
void WinMTRDialog::OnRestart() 
{
	// If clear history is selected, just clear the registry and listbox and return
	if(m_comboHost.GetCurSel() == m_comboHost.GetCount() - 1) {
		ClearHistory();
		return;
	}

	CString sHost;

	if(state == IDLE) {
		m_comboHost.GetWindowText(sHost);
		sHost.TrimLeft();
		sHost.TrimLeft();
      
		if(sHost.IsEmpty()) {
			AfxMessageBox("No host specified!");
			m_comboHost.SetFocus();
			return ;
		}
		m_listMTR.DeleteAllItems();
	}

	if(state == IDLE) {

		if(InitMTRNet()) {
			if(m_comboHost.FindString(-1, sHost) == CB_ERR) {
				m_comboHost.InsertString(m_comboHost.GetCount() - 1,sHost);

				HKEY hKey;
				DWORD tmp_dword;
				LONG r;
				char key_name[20];

				r = RegOpenKeyEx(	HKEY_CURRENT_USER, "Software", 0, KEY_ALL_ACCESS,&hKey);
				r = RegOpenKeyEx(	hKey, "WinMTR", 0, KEY_ALL_ACCESS, &hKey);
				r = RegOpenKeyEx(	hKey, "LRU", 0, KEY_ALL_ACCESS, &hKey);

				if(nrLRU >= maxLRU)
					nrLRU = 0;
				
				nrLRU++;
				sprintf(key_name, "Host%d", nrLRU);
				r = RegSetValueEx(hKey,key_name, 0, REG_SZ, (const unsigned char *)(LPCTSTR)sHost, strlen((LPCTSTR)sHost)+1);
				tmp_dword = nrLRU;
				r = RegSetValueEx(hKey,"NrLRU", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
				RegCloseKey(hKey);
			}
			Transit(TRACING);
		}
	} else {
		Transit(STOPPING);
	}
}


//*****************************************************************************
// WinMTRDialog::OnOptions
//
// 
//*****************************************************************************
void WinMTRDialog::OnOptions() 
{
	WinMTROptions optDlg;

	optDlg.SetPingSize(pingsize);
	optDlg.SetInterval(interval);
	optDlg.SetMaxLRU(maxLRU);
	optDlg.SetUseDNS(useDNS);

	if(IDOK == optDlg.DoModal()) {

		pingsize = optDlg.GetPingSize();
		interval = optDlg.GetInterval();
		maxLRU = optDlg.GetMaxLRU();
		useDNS = optDlg.GetUseDNS();

		HKEY hKey;
		DWORD tmp_dword;
		LONG r;
		char key_name[20];

		r = RegOpenKeyEx(	HKEY_CURRENT_USER, "Software", 0, KEY_ALL_ACCESS,&hKey);
		r = RegOpenKeyEx(	hKey, "WinMTR", 0, KEY_ALL_ACCESS, &hKey);
		r = RegOpenKeyEx(	hKey, "Config", 0, KEY_ALL_ACCESS, &hKey);
		tmp_dword = pingsize;
		RegSetValueEx(hKey,"PingSize", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
		tmp_dword = maxLRU;
		RegSetValueEx(hKey,"MaxLRU", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
		tmp_dword = useDNS ? 1 : 0;
		RegSetValueEx(hKey,"UseDNS", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
		tmp_dword = (DWORD)(interval * 1000);
		RegSetValueEx(hKey,"Interval", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
		RegCloseKey(hKey);
		if(maxLRU<nrLRU) {
			r = RegOpenKeyEx(	HKEY_CURRENT_USER, "Software", 0, KEY_ALL_ACCESS,&hKey);
			r = RegOpenKeyEx(	hKey, "WinMTR", 0, KEY_ALL_ACCESS, &hKey);
			r = RegOpenKeyEx(	hKey, "LRU", 0, KEY_ALL_ACCESS, &hKey);

			for(int i = maxLRU; i<=nrLRU; i++) {
					sprintf(key_name, "Host%d", i);
					r = RegDeleteValue(hKey,key_name);
			}
			nrLRU = maxLRU;
			tmp_dword = nrLRU;
			r = RegSetValueEx(hKey,"NrLRU", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
			RegCloseKey(hKey);
		}
	}
}


//*****************************************************************************
// WinMTRDialog::OnCTTC
//
// 
//*****************************************************************************
void WinMTRDialog::OnCTTC() 
{	
	char buf[255], t_buf[1000], f_buf[255*100];
	
	int nh = wmtrnet->GetMax();
	
	strcpy(f_buf,  "|------------------------------------------------------------------------------------------|\r\n");
	sprintf(t_buf, "|                                      WinMTR statistics                                   |\r\n");
	strcat(f_buf, t_buf);
	sprintf(t_buf, "|                       Host              -   %%  | Sent | Recv | Best | Avrg | Wrst | Last |\r\n" ); 
	strcat(f_buf, t_buf);
	sprintf(t_buf, "|------------------------------------------------|------|------|------|------|------|------|\r\n" ); 
	strcat(f_buf, t_buf);

	for(int i=0;i <nh ; i++) {
		wmtrnet->GetName(i, buf);
		if(strcmp(buf,"")==0) strcpy(buf,"No response from host");
		
		sprintf(t_buf, "|%40s - %4d | %4d | %4d | %4d | %4d | %4d | %4d |\r\n" , 
					buf, wmtrnet->GetPercent(i),
					wmtrnet->GetXmit(i), wmtrnet->GetReturned(i), wmtrnet->GetBest(i),
					wmtrnet->GetAvg(i), wmtrnet->GetWorst(i), wmtrnet->GetLast(i));
		strcat(f_buf, t_buf);
	}	
	
	sprintf(t_buf, "|________________________________________________|______|______|______|______|______|______|\r\n" ); 
	strcat(f_buf, t_buf);

	CString cs_tmp((LPCSTR)IDS_STRING_SB_NAME);
	strcat(f_buf, "   ");
	strcat(f_buf, (LPCTSTR)cs_tmp);

	CString source(f_buf);

	HGLOBAL clipbuffer;
	char * buffer;
	
	OpenClipboard();
	EmptyClipboard();
	
	clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);
	buffer = (char*)GlobalLock(clipbuffer);
	strcpy(buffer, LPCSTR(source));
	GlobalUnlock(clipbuffer);
	
	SetClipboardData(CF_TEXT,clipbuffer);
	CloseClipboard();
}


//*****************************************************************************
// WinMTRDialog::OnCHTC
//
// 
//*****************************************************************************
void WinMTRDialog::OnCHTC() 
{
	char buf[255], t_buf[1000], f_buf[255*100];
	
	int nh = wmtrnet->GetMax();
	
	strcpy(f_buf, "<html><head><title>WinMTR Statistics</title></head><body bgcolor=\"white\">\r\n");
	sprintf(t_buf, "<center><h2>WinMTR statistics</h2></center>\r\n");
	strcat(f_buf, t_buf);
	
	sprintf(t_buf, "<p align=\"center\"> <table border=\"1\" align=\"center\">\r\n" ); 
	strcat(f_buf, t_buf);
	
	sprintf(t_buf, "<tr><td>Host</td> <td>%%</td> <td>Sent</td> <td>Recv</td> <td>Best</td> <td>Avrg</td> <td>Wrst</td> <td>Last</td></tr>\r\n" ); 
	strcat(f_buf, t_buf);

	for(int i=0;i <nh ; i++) {
		wmtrnet->GetName(i, buf);
		if( strcmp(buf,"")==0 ) strcpy(buf,"No response from host");
		
		sprintf(t_buf, "<tr><td>%s</td> <td>%4d</td> <td>%4d</td> <td>%4d</td> <td>%4d</td> <td>%4d</td> <td>%4d</td> <td>%4d</td></tr>\r\n" , 
					buf, wmtrnet->GetPercent(i),
					wmtrnet->GetXmit(i), wmtrnet->GetReturned(i), wmtrnet->GetBest(i),
					wmtrnet->GetAvg(i), wmtrnet->GetWorst(i), wmtrnet->GetLast(i));
		strcat(f_buf, t_buf);
	}	
	
	sprintf(t_buf, "</table></body></html>\r\n"); 
	strcat(f_buf, t_buf);

	CString source(f_buf);

	HGLOBAL clipbuffer;
	char * buffer;
	
	OpenClipboard();
	EmptyClipboard();
	
	clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);
	buffer = (char*)GlobalLock(clipbuffer);
	strcpy(buffer, LPCSTR(source));
	GlobalUnlock(clipbuffer);
	
	SetClipboardData(CF_TEXT,clipbuffer);
	CloseClipboard();
}


//*****************************************************************************
// WinMTRDialog::OnEXPT
//
// 
//*****************************************************************************
void WinMTRDialog::OnEXPT() 
{	
	TCHAR BASED_CODE szFilter[] = _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");

	CFileDialog dlg(FALSE,
                   _T("TXT"),
                   NULL,
                   OFN_HIDEREADONLY | OFN_EXPLORER,
                   szFilter,
                   this);
	if(dlg.DoModal() == IDOK) {

		char buf[255], t_buf[1000], f_buf[255*100];
	
		int nh = wmtrnet->GetMax();
	
		strcpy(f_buf,  "|------------------------------------------------------------------------------------------|\r\n");
		sprintf(t_buf, "|                                      WinMTR statistics                                   |\r\n");
		strcat(f_buf, t_buf);
		sprintf(t_buf, "|                       Host              -   %%  | Sent | Recv | Best | Avrg | Wrst | Last |\r\n" ); 
		strcat(f_buf, t_buf);
		sprintf(t_buf, "|------------------------------------------------|------|------|------|------|------|------|\r\n" ); 
		strcat(f_buf, t_buf);

		for(int i=0;i <nh ; i++) {
			wmtrnet->GetName(i, buf);
			if( strcmp(buf,"")==0 ) strcpy(buf,"No response from host");
		
			sprintf(t_buf, "|%40s - %4d | %4d | %4d | %4d | %4d | %4d | %4d |\r\n" , 
					buf, wmtrnet->GetPercent(i),
					wmtrnet->GetXmit(i), wmtrnet->GetReturned(i), wmtrnet->GetBest(i),
					wmtrnet->GetAvg(i), wmtrnet->GetWorst(i), wmtrnet->GetLast(i));
			strcat(f_buf, t_buf);
		}	
	
		sprintf(t_buf, "|________________________________________________|______|______|______|______|______|______|\r\n" ); 
		strcat(f_buf, t_buf);

	
		CString cs_tmp((LPCSTR)IDS_STRING_SB_NAME);
		strcat(f_buf, "   ");
		strcat(f_buf, (LPCTSTR)cs_tmp);

		FILE *fp = fopen(dlg.GetPathName(), "wt");
		if(fp != NULL) {
			fprintf(fp, "%s", f_buf);
			fclose(fp);
		}
	}
}


//*****************************************************************************
// WinMTRDialog::OnEXPH
//
// 
//*****************************************************************************
void WinMTRDialog::OnEXPH() 
{
   TCHAR BASED_CODE szFilter[] = _T("HTML Files (*.htm, *.html)|*.htm;*.html|All Files (*.*)|*.*||");

   CFileDialog dlg(FALSE,
                   _T("HTML"),
                   NULL,
                   OFN_HIDEREADONLY | OFN_EXPLORER,
                   szFilter,
                   this);

	if(dlg.DoModal() == IDOK) {

		char buf[255], t_buf[1000], f_buf[255*100];
	
		int nh = wmtrnet->GetMax();
	
		strcpy(f_buf, "<html><head><title>WinMTR Statistics</title></head><body bgcolor=\"white\">\r\n");
		sprintf(t_buf, "<center><h2>WinMTR statistics</h2></center>\r\n");
		strcat(f_buf, t_buf);
	
		sprintf(t_buf, "<p align=\"center\"> <table border=\"1\" align=\"center\">\r\n" ); 
		strcat(f_buf, t_buf);
	
		sprintf(t_buf, "<tr><td>Host</td> <td>%%</td> <td>Sent</td> <td>Recv</td> <td>Best</td> <td>Avrg</td> <td>Wrst</td> <td>Last</td></tr>\r\n" ); 
		strcat(f_buf, t_buf);

		for(int i=0;i <nh ; i++) {
			wmtrnet->GetName(i, buf);
			if( strcmp(buf,"")==0 ) strcpy(buf,"No response from host");
		
			sprintf(t_buf, "<tr><td>%s</td> <td>%4d</td> <td>%4d</td> <td>%4d</td> <td>%4d</td> <td>%4d</td> <td>%4d</td> <td>%4d</td></tr>\r\n" , 
					buf, wmtrnet->GetPercent(i),
					wmtrnet->GetXmit(i), wmtrnet->GetReturned(i), wmtrnet->GetBest(i),
					wmtrnet->GetAvg(i), wmtrnet->GetWorst(i), wmtrnet->GetLast(i));
			strcat(f_buf, t_buf);
		}	

		sprintf(t_buf, "</table></body></html>\r\n"); 
		strcat(f_buf, t_buf);

		FILE *fp = fopen(dlg.GetPathName(), "wt");
		if(fp != NULL) {
			fprintf(fp, "%s", f_buf);
			fclose(fp);
		}
	}


}


//*****************************************************************************
// WinMTRDialog::WinMTRDialog
//
// 
//*****************************************************************************
void WinMTRDialog::OnCancel() 
{
}


//*****************************************************************************
// WinMTRDialog::DisplayRedraw
//
// 
//*****************************************************************************
int WinMTRDialog::DisplayRedraw()
{
	char buf[255], nr_crt[255];
	int nh = wmtrnet->GetMax();
	while( m_listMTR.GetItemCount() > nh ) m_listMTR.DeleteItem(m_listMTR.GetItemCount() - 1);

	for(int i=0;i <nh ; i++) {

		wmtrnet->GetName(i, buf);
		if( strcmp(buf,"")==0 ) strcpy(buf,"No response from host");
		
		sprintf(nr_crt, "%d", i+1);
		if(m_listMTR.GetItemCount() <= i )
			m_listMTR.InsertItem(i, buf);
		else
			m_listMTR.SetItem(i, 0, LVIF_TEXT, buf, 0, 0, 0, 0); 
		
		m_listMTR.SetItem(i, 1, LVIF_TEXT, nr_crt, 0, 0, 0, 0); 

		sprintf(buf, "%d", wmtrnet->GetPercent(i));
		m_listMTR.SetItem(i, 2, LVIF_TEXT, buf, 0, 0, 0, 0);

		sprintf(buf, "%d", wmtrnet->GetXmit(i));
		m_listMTR.SetItem(i, 3, LVIF_TEXT, buf, 0, 0, 0, 0);

		sprintf(buf, "%d", wmtrnet->GetReturned(i));
		m_listMTR.SetItem(i, 4, LVIF_TEXT, buf, 0, 0, 0, 0);

		sprintf(buf, "%d", wmtrnet->GetBest(i));
		m_listMTR.SetItem(i, 5, LVIF_TEXT, buf, 0, 0, 0, 0);

		sprintf(buf, "%d", wmtrnet->GetAvg(i));
		m_listMTR.SetItem(i, 6, LVIF_TEXT, buf, 0, 0, 0, 0);

		sprintf(buf, "%d", wmtrnet->GetWorst(i));
		m_listMTR.SetItem(i, 7, LVIF_TEXT, buf, 0, 0, 0, 0);

		sprintf(buf, "%d", wmtrnet->GetLast(i));
		m_listMTR.SetItem(i, 8, LVIF_TEXT, buf, 0, 0, 0, 0);

   
	}

	return 0;
}


//*****************************************************************************
// WinMTRDialog::InitMTRNet
//
// 
//*****************************************************************************
int WinMTRDialog::InitMTRNet()
{
	char strtmp[255];
	char *Hostname = strtmp;
	char buf[255];
	struct hostent *host;
	m_comboHost.GetWindowText(strtmp, 255);
   	
	if (Hostname == NULL) Hostname = "localhost";
   
	int isIP=1;
	char *t = Hostname;
	while(*t) {
		if(!isdigit(*t) && *t!='.') {
			isIP=0;
			break;
		}
		t++;
	}

	if(!isIP) {
		sprintf(buf, "Resolving host %s...", strtmp);
		statusBar.SetPaneText(0,buf);
		host = gethostbyname(Hostname);
		if(host == NULL) {
			statusBar.SetPaneText(0, CString((LPCSTR)IDS_STRING_SB_NAME) );
			AfxMessageBox("Unable to resolve hostname.");
			return 0;
		}
	}

	return 1;
}


//*****************************************************************************
// PingThread
//
// 
//*****************************************************************************
void PingThread(void *p)
{
	WinMTRDialog *wmtrdlg = (WinMTRDialog *)p;
	WaitForSingleObject(wmtrdlg->traceThreadMutex, INFINITE);

	struct hostent *host, *lhost;
	char strtmp[255];
	char *Hostname = strtmp;
	int traddr;
	int localaddr;

	wmtrdlg->m_comboHost.GetWindowText(strtmp, 255);
   	
	if (Hostname == NULL) Hostname = "localhost";
   
	int isIP=1;
	char *t = Hostname;
	while(*t) {
		if(!isdigit(*t) && *t!='.') {
			isIP=0;
			break;
		}
		t++;
	}

	if(!isIP) {
      host = gethostbyname(Hostname);
      traddr = *(int *)host->h_addr;
	} else
      traddr = inet_addr(Hostname);

	lhost = gethostbyname("localhost");
	if(lhost == NULL) {
      AfxMessageBox("Unable to get local IP address.");
      ReleaseMutex(wmtrdlg->traceThreadMutex);
      return;
	}
	localaddr = *(int *)lhost->h_addr;
	
	wmtrdlg->wmtrnet->DoTrace(traddr);

	ReleaseMutex(wmtrdlg->traceThreadMutex);
   _endthread();
}



void WinMTRDialog::OnCbnSelchangeComboHost()
{
}

void WinMTRDialog::ClearHistory()
{
	HKEY hKey;
	DWORD tmp_dword;
	LONG r;
	char key_name[20];

	r = RegOpenKeyEx(	HKEY_CURRENT_USER, "Software", 0, KEY_ALL_ACCESS,&hKey);
	r = RegOpenKeyEx(	hKey, "WinMTR", 0, KEY_ALL_ACCESS, &hKey);
	r = RegOpenKeyEx(	hKey, "LRU", 0, KEY_ALL_ACCESS, &hKey);

	for(int i = 0; i<=nrLRU; i++) {
		sprintf(key_name, "Host%d", i);
		r = RegDeleteValue(hKey,key_name);
	}
	nrLRU = 0;
	tmp_dword = nrLRU;
	r = RegSetValueEx(hKey,"NrLRU", 0, REG_DWORD, (const unsigned char *)&tmp_dword, sizeof(DWORD));
	RegCloseKey(hKey);

	m_comboHost.Clear();
	m_comboHost.ResetContent();
	m_comboHost.AddString(CString((LPCSTR)IDS_STRING_CLEAR_HISTORY));
}

void WinMTRDialog::OnCbnSelendokComboHost()
{
}


void WinMTRDialog::OnCbnCloseupComboHost()
{
	if(m_comboHost.GetCurSel() == m_comboHost.GetCount() - 1) {
		ClearHistory();
	}
}

void WinMTRDialog::Transit(STATES new_state)
{
	switch(new_state) {
		case IDLE:
			switch (state) {
				case STOPPING:
					transition = STOPPING_TO_IDLE;
				break;
				case IDLE:
					transition = IDLE_TO_IDLE;
				break;
				default:
					TRACE_MSG("Received state IDLE after " << state);
					return;
			}
			state = IDLE;
		break;
		case TRACING:
			switch (state) {
				case IDLE:
					transition = IDLE_TO_TRACING;
				break;
				case TRACING:
					transition = TRACING_TO_TRACING;
				break;
				default:
					TRACE_MSG("Received state TRACING after " << state);
					return;
			}
			state = TRACING;
		break;
		case STOPPING:
			switch (state) {
				case STOPPING:
					transition = STOPPING_TO_STOPPING;
				break;
				case TRACING:
					transition = TRACING_TO_STOPPING;
				break;
				default:
					TRACE_MSG("Received state STOPPING after " << state);
					return;
			}
			state = STOPPING;
		break;
		case EXIT:
			switch (state) {
				case IDLE:
					transition = IDLE_TO_EXIT;
				break;
				case STOPPING:
					transition = STOPPING_TO_EXIT;
				break;
				case TRACING:
					transition = TRACING_TO_EXIT;
				break;
				case EXIT:
				break;
				default:
					TRACE_MSG("Received state EXIT after " << state);
					return;
			}
			state = EXIT;
		break;
		default:
			TRACE_MSG("Received state " << state);
	}

	// modify controls according to new state
	switch(transition) {
		case IDLE_TO_TRACING:
			m_buttonStart.EnableWindow(FALSE);
			m_buttonStart.SetWindowText("Stop");
			m_comboHost.EnableWindow(FALSE);
			m_buttonOptions.EnableWindow(FALSE);
			statusBar.SetPaneText(0, "Double click on host name for more information.");
			_beginthread(PingThread, 0 , this);
			m_buttonStart.EnableWindow(TRUE);
		break;
		case IDLE_TO_IDLE:
			// nothing to be done
		break;
		case STOPPING_TO_IDLE:
			m_buttonStart.EnableWindow(TRUE);
			statusBar.SetPaneText(0, CString((LPCSTR)IDS_STRING_SB_NAME) );
			m_buttonStart.SetWindowText("Start");
			m_comboHost.EnableWindow(TRUE);
			m_buttonOptions.EnableWindow(TRUE);
			m_comboHost.SetFocus();
		break;
		case STOPPING_TO_STOPPING:
			DisplayRedraw();
		break;
		case TRACING_TO_TRACING:
			DisplayRedraw();
		break;
		case TRACING_TO_STOPPING:
			m_buttonStart.EnableWindow(FALSE);
			m_comboHost.EnableWindow(FALSE);
			m_buttonOptions.EnableWindow(FALSE);
			wmtrnet->StopTrace();
			statusBar.SetPaneText(0, "Waiting for last packets in order to stop trace ...");
			DisplayRedraw();
		break;
		case IDLE_TO_EXIT:
			m_buttonStart.EnableWindow(FALSE);
			m_comboHost.EnableWindow(FALSE);
			m_buttonOptions.EnableWindow(FALSE);
		break;
		case TRACING_TO_EXIT:
			m_buttonStart.EnableWindow(FALSE);
			m_comboHost.EnableWindow(FALSE);
			m_buttonOptions.EnableWindow(FALSE);
			wmtrnet->StopTrace();
			statusBar.SetPaneText(0, "Waiting for last packets in order to stop trace ...");
		break;
		case STOPPING_TO_EXIT:
			m_buttonStart.EnableWindow(FALSE);
			m_comboHost.EnableWindow(FALSE);
			m_buttonOptions.EnableWindow(FALSE);
		break;
		default:
			TRACE_MSG("Unknown transition " << transition);
	}
}


void WinMTRDialog::OnTimer(UINT_PTR nIDEvent)
{
	static unsigned int call_count = 0;
	call_count += 1;

	if(state == EXIT && WaitForSingleObject(traceThreadMutex, 0) == WAIT_OBJECT_0) {
		ReleaseMutex(traceThreadMutex);
		OnOK();
	}


	if( WaitForSingleObject(traceThreadMutex, 0) == WAIT_OBJECT_0 ) {
		ReleaseMutex(traceThreadMutex);
		Transit(IDLE);
	} else if( (call_count % 10 == 0) && (WaitForSingleObject(traceThreadMutex, 0) == WAIT_TIMEOUT) ) {
		ReleaseMutex(traceThreadMutex);
		if( state == TRACING) Transit(TRACING);
		else if( state == STOPPING) Transit(STOPPING);
	}

	CDialog::OnTimer(nIDEvent);
}


void WinMTRDialog::OnClose()
{
	Transit(EXIT);
}


void WinMTRDialog::OnBnClickedCancel()
{
	Transit(EXIT);
}
