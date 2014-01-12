//*****************************************************************************
// FILE:            WinMTRProperties.h
//
//
// DESCRIPTION:
//   
//
// NOTES:
//    
//
//*****************************************************************************

#ifndef WINMTRPROPERTIES_H_
#define WINMTRPROPERTIES_H_



//*****************************************************************************
// CLASS:  WinMTRLicense
//
//
//*****************************************************************************

class WinMTRProperties : public CDialog
{
public:
	WinMTRProperties(CWnd* pParent = NULL);

	
	enum { IDD = IDD_DIALOG_PROPERTIES };

	char	host[255];
	char	ip[16];
	char	comment[255];

	float	ping_last;
	float	ping_best;
	float	ping_avrg;
	float	ping_worst;

	int		pck_sent;
	int		pck_recv;
	int		pck_loss;

	CEdit	m_editHost,
			m_editIP,
			m_editComment,
			m_editSent,
			m_editRecv,
			m_editLoss,
			m_editLast,
			m_editBest,
			m_editWorst,
			m_editAvrg;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()
};

#endif // ifndef WINMTRLICENSE_H_
