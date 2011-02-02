// WinMTRHelp.cpp : implementation file
//

#include "WinMTRGlobal.h"
#include "WinMTRHelp.h"
#include "afxdialogex.h"


// WinMTRHelp dialog

IMPLEMENT_DYNAMIC(WinMTRHelp, CDialog)

WinMTRHelp::WinMTRHelp(CWnd* pParent /*=NULL*/)
	: CDialog(WinMTRHelp::IDD, pParent)
{

}

WinMTRHelp::~WinMTRHelp()
{
}

void WinMTRHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WinMTRHelp, CDialog)
	ON_BN_CLICKED(IDOK, &WinMTRHelp::OnBnClickedOk)
END_MESSAGE_MAP()


// WinMTRHelp message handlers


void WinMTRHelp::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
