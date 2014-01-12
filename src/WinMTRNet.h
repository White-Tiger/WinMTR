//*****************************************************************************
// FILE:            WinMTRNet.h
//
//
// DESCRIPTION:
//   
//
// NOTES:
//    
//
//*****************************************************************************

#ifndef WINMTRNET_H_
#define WINMTRNET_H_


class WinMTRDialog;

typedef IP_OPTION_INFORMATION IPINFO, *PIPINFO, FAR *LPIPINFO;
#ifdef _WIN64
typedef ICMP_ECHO_REPLY32 ICMPECHO, *PICMPECHO, FAR *LPICMPECHO;
#else
typedef ICMP_ECHO_REPLY ICMPECHO, *PICMPECHO, FAR *LPICMPECHO;
#endif // _WIN64

#define ECHO_REPLY_TIMEOUT 5000

struct s_nethost {
  union{
    sockaddr_in addr;
    sockaddr_in6 addr6;
  };
  int xmit;			// number of PING packets sent
  int returned;		// number of ICMP echo replies received
  unsigned long total;	// total time
  int last;				// last time
  int best;				// best time
  int worst;			// worst time
  char name[255];
};

//*****************************************************************************
// CLASS:  WinMTRNet
//
//
//*****************************************************************************

class WinMTRNet {
	typedef FARPROC PIO_APC_ROUTINE;//not the best way to do it, but works ;) (we do not use it anyway)
	//IPv4
	typedef HANDLE (WINAPI *LPFNICMPCREATEFILE)(VOID);
	typedef BOOL  (WINAPI *LPFNICMPCLOSEHANDLE)(HANDLE);
	typedef DWORD (WINAPI *LPFNICMPSENDECHO2)(HANDLE IcmpHandle,HANDLE Event,PIO_APC_ROUTINE ApcRoutine,PVOID ApcContext,in_addr DestinationAddress,LPVOID RequestData,WORD RequestSize,PIP_OPTION_INFORMATION RequestOptions,LPVOID ReplyBuffer,DWORD ReplySize,DWORD Timeout);
	//IPv6
	typedef HANDLE (WINAPI *LPFNICMP6CREATEFILE)(VOID);
	typedef BOOL  (WINAPI *LPFNICMP6CLOSEHANDLE)(HANDLE);
	typedef DWORD (WINAPI *LPFNICMP6SENDECHO2)(HANDLE IcmpHandle,HANDLE Event,PIO_APC_ROUTINE ApcRoutine,PVOID ApcContext,sockaddr_in6* SourceAddress,sockaddr_in6* DestinationAddress,LPVOID RequestData,WORD RequestSize,PIP_OPTION_INFORMATION RequestOptions,LPVOID ReplyBuffer,DWORD ReplySize,DWORD Timeout);

public:

	WinMTRNet(WinMTRDialog *wp);
	~WinMTRNet();
	void	DoTrace(sockaddr* sockaddr);
	void	ResetHops();
	void	StopTrace();

	sockaddr* GetAddr(int at);
	int		GetName(int at, char *n);
	int		GetBest(int at);
	int		GetWorst(int at);
	int		GetAvg(int at);
	int		GetPercent(int at);
	int		GetLast(int at);
	int		GetReturned(int at);
	int		GetXmit(int at);
	int		GetMax();

	void	SetAddr(int at, u_long addr);
	void	SetAddr6(int at, IPV6_ADDRESS_EX addrex);
	void	SetName(int at, char *n);
	void	SetErrorName(int at,DWORD errnum);
	void	UpdateRTT(int at, int rtt);
	void	AddReturned(int at);
	void	AddXmit(int at);

	WinMTRDialog		*wmtrdlg;
	union{
		in_addr last_remote_addr;
		in6_addr last_remote_addr6;
	};
	bool				hasIPv6;
	bool				tracing;
	bool				initialized;
	HANDLE				hICMP;
	HANDLE				hICMP6;
	//IPv4
	LPFNICMPCREATEFILE lpfnIcmpCreateFile;
	LPFNICMPCLOSEHANDLE lpfnIcmpCloseHandle;
	LPFNICMPSENDECHO2 lpfnIcmpSendEcho2;
	//IPv6
	LPFNICMP6CREATEFILE lpfnIcmp6CreateFile;
	LPFNICMP6SENDECHO2 lpfnIcmp6SendEcho2;
private:
	HINSTANCE			hICMP_DLL;

    struct s_nethost	host[MaxHost];
	HANDLE				ghMutex; 
};

#endif	// ifndef WINMTRNET_H_
