//*****************************************************************************
// FILE:            WinMTRLicense.h
//
//
// DESCRIPTION:
//   
//
// NOTES:
//    
//
//*****************************************************************************

#ifndef WINMTRLICENSE_H_
#define WINMTRLICENSE_H_



//*****************************************************************************
// CLASS:  WinMTRLicense
//
//
//*****************************************************************************

class WinMTRLicense : public CDialog
{
public:
	WinMTRLicense(CWnd* pParent = NULL);

	
	enum { IDD = IDD_DIALOG_LICENSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()
};

#endif // ifndef WINMTRLICENSE_H_
