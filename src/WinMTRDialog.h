//*****************************************************************************
// FILE:            WinMTRDialog.h
//
//
// DESCRIPTION:
//
//
// NOTES:
//
//
//*****************************************************************************

#ifndef WINMTRDIALOG_H_
#define WINMTRDIALOG_H_

#define WINMTR_DIALOG_TIMER 100

#include "WinMTRStatusBar.h"
#include "WinMTRNet.h"
#include "afxlinkctrl.h"

//*****************************************************************************
// CLASS:  WinMTRDialog
//
//
//*****************************************************************************

class WinMTRDialog : public CDialog
{
public:
	WinMTRDialog(CWnd* pParent = NULL);
	~WinMTRDialog();
	
	enum { IDD = IDD_WINMTR_DIALOG };
	
	afx_msg BOOL InitRegistry();
	
	WinMTRStatusBar	statusBar;
	
	enum STATES {
		IDLE,
		TRACING,
		STOPPING,
		EXIT
	};
	
	enum STATE_TRANSITIONS {
		IDLE_TO_IDLE,
		IDLE_TO_TRACING,
		IDLE_TO_EXIT,
		TRACING_TO_TRACING,
		TRACING_TO_STOPPING,
		TRACING_TO_EXIT,
		STOPPING_TO_IDLE,
		STOPPING_TO_STOPPING,
		STOPPING_TO_EXIT
	};
	
	CButton	m_buttonOptions;
	CButton	m_buttonExit;
	CButton	m_buttonStart;
	CComboBox m_comboHost;
	CButton m_checkIPv6;
	CListCtrl m_listMTR;
	CMFCLinkCtrl m_buttonAppnor;
	
	CStatic	m_staticS;
	CStatic	m_staticJ;
	
	CButton	m_buttonExpT;
	CButton	m_buttonExpH;
	
	int InitMTRNet();
	
	int DisplayRedraw();
	void Transit(STATES new_state);
	
	STATES				state;
	STATE_TRANSITIONS	transition;
	HANDLE				traceThreadMutex;
	double				interval;
	bool				hasIntervalFromCmdLine;
	WORD				pingsize;
	bool				hasPingsizeFromCmdLine;
	int					maxLRU;
	bool				hasMaxLRUFromCmdLine;
	int					nrLRU;
	BOOL				useDNS;
	bool				hasUseDNSFromCmdLine;
	unsigned char		useIPv6;
	bool				hasUseIPv6FromCmdLine;
    long                duration;
    bool                hasDurationFromCmdLine;
    bool                hasReportFromCmdLine;
    bool				hasHostNameFromCmdLine;
    bool                exit_code;
    bool isAllocConsole;


	WinMTRNet*			wmtrnet;
	
	void SetHostName(const char* host);
	void SetInterval(float i);
	void SetPingSize(WORD ps);
	void SetMaxLRU(int mlru);
	void SetUseDNS(BOOL udns);
    void        SetDuration(long d);
    long        GetDuration();
    const char* GetHostName();
    float       GetInterval();

    WinMTRNet* GetWinMTRNetObj();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	
	int m_autostart;
	char msz_defaulthostname[1000];
	
	HICON m_hIcon;
	
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT, int, int);
	afx_msg void OnSizing(UINT, LPRECT);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRestart();
	afx_msg void OnOptions();
	virtual void OnCancel();
	
	afx_msg void OnCTTC();
	afx_msg void OnCHTC();
	afx_msg void OnEXPT();
	afx_msg void OnEXPH();
	
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboHost();
	afx_msg void OnCbnSelendokComboHost();
private:
	void ClearHistory();
public:
	afx_msg void OnCbnCloseupComboHost();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();

    bool ProcessNoGuiTask();
    bool win_mtr_no_gui_flag;
};

#endif // ifndef WINMTRDIALOG_H_
