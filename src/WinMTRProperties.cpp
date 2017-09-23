//*****************************************************************************
// FILE:            WinMTRProperties.cpp
//
//
//*****************************************************************************

#include "WinMTRGlobal.h"
#include "WinMTRProperties.h"

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
BEGIN_MESSAGE_MAP(WinMTRProperties, CDialog)
END_MESSAGE_MAP()


//*****************************************************************************
// WinMTRProperties::WinMTRProperties
//
// 
//*****************************************************************************
WinMTRProperties::WinMTRProperties(CWnd* pParent) : CDialog(WinMTRProperties::IDD, pParent)
{
}


//*****************************************************************************
// WinMTRroperties::DoDataExchange
//
// 
//*****************************************************************************
void WinMTRProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PHOST, m_editHost);
	DDX_Control(pDX, IDC_EDIT_PIP, m_editIP);
	DDX_Control(pDX, IDC_EDIT_PCOMMENT, m_editComment);

	DDX_Control(pDX, IDC_EDIT_PLOSS, m_editLoss);
	DDX_Control(pDX, IDC_EDIT_PSENT, m_editSent);
	DDX_Control(pDX, IDC_EDIT_PRECV, m_editRecv);

	DDX_Control(pDX, IDC_EDIT_PLAST, m_editLast);
	DDX_Control(pDX, IDC_EDIT_PBEST, m_editBest);
	DDX_Control(pDX, IDC_EDIT_PWORST, m_editWorst);
	DDX_Control(pDX, IDC_EDIT_PAVRG, m_editAvrg);
}


//*****************************************************************************
// WinMTRProperties::OnInitDialog
//
// 
//*****************************************************************************
BOOL WinMTRProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	TCHAR buf[255];
	
	m_editIP.SetWindowText(ip);
	m_editHost.SetWindowText(host);
	m_editComment.SetWindowText(comment);

	_stprintf(buf, _T("%d"), pck_loss);
	m_editLoss.SetWindowText(buf);
	_stprintf(buf, _T("%d"), pck_sent);
	m_editSent.SetWindowText(buf);
	_stprintf(buf, _T("%d"), pck_recv);
	m_editRecv.SetWindowText(buf);

	_stprintf(buf, _T("%.1f"), ping_last);
	m_editLast.SetWindowText(buf);
	_stprintf(buf, _T("%.1f"), ping_best);
	m_editBest.SetWindowText(buf);
	_stprintf(buf, _T("%.1f"), ping_worst);
	m_editWorst.SetWindowText(buf);
	_stprintf(buf, _T("%.1f"), ping_avrg);
	m_editAvrg.SetWindowText(buf);

	return FALSE;
}

