//*****************************************************************************
// FILE:            WinMTROptions.cpp
//
//
//*****************************************************************************

#include "WinMTRGlobal.h"
#include "WinMTROptions.h"
#include "WinMTRLicense.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//*****************************************************************************
// BEGIN_MESSAGE_MAP
//
// 
//*****************************************************************************
BEGIN_MESSAGE_MAP(WinMTROptions, CDialog)
	ON_BN_CLICKED(ID_LICENSE, OnLicense)
END_MESSAGE_MAP()


//*****************************************************************************
// WinMTROptions::DoDataExchange
//
// 
//*****************************************************************************
void WinMTROptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_editSize);
	DDX_Control(pDX, IDC_EDIT_INTERVAL, m_editInterval);
	DDX_Control(pDX, IDC_EDIT_MAX_LRU, m_editMaxLRU);
	DDX_Control(pDX, IDC_CHECK_DNS, m_checkDNS);
}


//*****************************************************************************
// WinMTROptions::OnInitDialog
//
// 
//*****************************************************************************
BOOL WinMTROptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TCHAR strtmp[20];
	
	_stprintf(strtmp, _T("%.1f"), interval);
	m_editInterval.SetWindowText(strtmp);
	
	_stprintf(strtmp, _T("%d"), pingsize);
	m_editSize.SetWindowText(strtmp);
	
	_stprintf(strtmp, _T("%d"), maxLRU);
	m_editMaxLRU.SetWindowText(strtmp);

	m_checkDNS.SetCheck(useDNS);
	
	m_editInterval.SetFocus();
	return FALSE;
}


//*****************************************************************************
// WinMTROptions::OnOK
//
// 
//*****************************************************************************
void WinMTROptions::OnOK() 
{
	TCHAR tmpstr[20];
	
	useDNS = m_checkDNS.GetCheck();

	m_editInterval.GetWindowText(tmpstr, 20);
	interval = _ttof(tmpstr);

	m_editSize.GetWindowText(tmpstr, 20);
	pingsize = _ttoi(tmpstr);
	
	m_editMaxLRU.GetWindowText(tmpstr, 20);
	maxLRU = _ttoi(tmpstr);

	CDialog::OnOK();
}

//*****************************************************************************
// WinMTROptions::OnLicense
//
// 
//*****************************************************************************
void WinMTROptions::OnLicense() 
{
	WinMTRLicense mtrlicense;
	mtrlicense.DoModal();
}
