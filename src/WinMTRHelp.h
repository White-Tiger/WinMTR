#pragma once

// WinMTRHelp dialog

class WinMTRHelp : public CDialog
{
	DECLARE_DYNAMIC(WinMTRHelp)

public:
	WinMTRHelp(CWnd* pParent = NULL);   // standard constructor
	virtual ~WinMTRHelp();

// Dialog Data
	enum { IDD = IDD_DIALOG_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
