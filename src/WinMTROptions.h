//*****************************************************************************
// FILE:            WinMTROptions.h
//
//
// DESCRIPTION:
//   
//
// NOTES:
//    
//
//*****************************************************************************

#ifndef WINMTROPTIONS_H_
#define WINMTROPTIONS_H_



//*****************************************************************************
// CLASS:  WinMTROptions
//
//
//*****************************************************************************

class WinMTROptions : public CDialog
{
public:
	WinMTROptions(double interval,int pingsize,int maxLRU,BOOL useDNS,CWnd* pParent=NULL) :
		interval(interval),pingsize(pingsize),maxLRU(maxLRU),useDNS(useDNS),CDialog(WinMTROptions::IDD, pParent){};

	double GetInterval()			{ return interval; };
	int GetPingSize()				{ return pingsize; };
	int GetMaxLRU()					{ return maxLRU; };
	BOOL GetUseDNS()				{ return useDNS; };

	enum { IDD = IDD_DIALOG_OPTIONS };
	CEdit	m_editSize;
	CEdit	m_editInterval;
	CEdit	m_editMaxLRU;
	CButton	m_checkDNS;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnLicense();

	DECLARE_MESSAGE_MAP()
	
private:
	double	interval;
	int		pingsize;
	int		maxLRU;
	BOOL	useDNS;
};

#endif // ifndef WINMTROPTIONS_H_
