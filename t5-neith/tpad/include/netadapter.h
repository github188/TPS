#ifndef _ADAPTER_INFO_H____
#define _ADAPTER_INFO_H____
#include <windows.h>
#include <tchar.h>
#include <iphlpapi.h>
#include <ipifcons.h>
#include <vector>
#include "SensAPI.h"
#include "ipinfomanager.h"

using namespace std;

class CNetworkAdapter;

#ifndef tstring
	#ifdef _UNICODE
		#define tstring			std::wstring
	#else
		#define tstring			std::string		
	#endif
#endif

// import the internet protocol helper libarary
// #pragma comment( lib, "iphlpapi.lib" )
// #pragma comment(lib, "SensAPI.Lib")
// #pragma comment(lib, "ws2_32.lib")

#define DEFAULT_GATEWAY_ADDR	0

typedef struct tagIPINFO 
{
	tstring sIp;
	tstring sSubnet;
}TIPINFO;

class CIpInfoArray : public vector< TIPINFO > {};
class StringArray : public vector< tstring > {};



#define IsDhcp  0
#define UnDhcp  1

enum EmNetStatus{
    emNetDisconnnect = 0,
        emNetException,
        emNetOK
};



//IP
typedef struct tagIpConfig
{
    BOOL bIpDhcp;             //�Ƿ��Զ���ȡIP��ַ
    u32  dwIP;           //IP
    u32  dwSubMask;         //��������
    u32  dwGateWay;      //����
    
    BOOL bDnsDhcp;           //�Ƿ��Զ���ȡDns������
    u32  dwPriorityCns;   //��ѡdns������
    u32  dwBkupCns;       //����dns������
public:
    tagIpConfig(){ memset( this ,0 ,sizeof( tagIpConfig ) );}

    BOOL operator ==( tagIpConfig& tConfig )
    {   
        if ( this->bIpDhcp == TRUE )
        {
            if ( this->bDnsDhcp == TRUE )
            {
                if ( this->bIpDhcp == tConfig.bIpDhcp && this->bDnsDhcp == tConfig.bDnsDhcp )
                {
                    return TRUE;
                }
                else
                {
                    return FALSE;
                }
            }
            else
            {
                if ( this->bIpDhcp == tConfig.bIpDhcp && this->bDnsDhcp == tConfig.bDnsDhcp && this->dwPriorityCns == tConfig.dwPriorityCns 
                    && this->dwBkupCns == tConfig.dwBkupCns )
                {
                    return TRUE;
                }
                else
                {
                    return FALSE;
                }
            }           
        }
        else
        {
            if ( this->bIpDhcp == tConfig.bIpDhcp && this->dwIP == tConfig.dwIP && this->dwSubMask == tConfig.dwSubMask 
                && this->dwGateWay == tConfig.dwGateWay && this->bDnsDhcp == tConfig.bDnsDhcp && this->dwPriorityCns == tConfig.dwPriorityCns 
                && this->dwBkupCns == tConfig.dwBkupCns )
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }      
    }
}TIpConfig;


//////////////////////////////////////////////////////////////////////////////////////////
//	Desc:
//		Class wrapper for a single network adapter.  A listing of these adapters
//		can be built using the EnumNetworkAdapters(...) function prototyped
//		above.
//////////////////////////////////////////////////////////////////////////////////////////
class CNetworkAdapter 
{
public:
	CNetworkAdapter();
	~CNetworkAdapter();

	//����������ó�ʼ������
	static BOOL InitIPCfgAPI( /* CNetworkAdapter *pNetParam*/  );
    static CNetworkAdapter * GetIpCfg( ){ return m_ptNetParam ; }

    static BOOL InitWifiIPCfgAPI();

    static BOOL GetNetAdapterName(); //��ȡ��ǰ����

	BOOL SetupAdapterInfo( IP_ADAPTER_INFO* pAdaptInfo );

	tstring GetAdapterName() const; //��ȡ����������
	tstring GetAdapterDescription() const;
	
	// dhcp lease access functions
	time_t	GetLeaseObtained() const;
	time_t	GetLeaseExpired() const;
	
	
	SIZE_T	GetNumIpAddrs() const;		         
	SIZE_T	GetNumDnsAddrs() const;
	tstring	GetIpAddr( int nIp = 0 );	        //��ȡ��ǰ��̬ip
	tstring GetSubnetForIpAddr( int nIp = 0 ) const; //��ȡ��ǰ��̬�����ַ
	tstring	GetDnsAddr( int nDns = 0 ) const;		//��ȡ��ǰDNS��ַ
	tstring GetCurrentIpAddress() const;            //��ȡ��ǰIP
	
	// dhcp function
	BOOL	IsDhcpUsed() const;		                //DHCP�Ƿ�����
    BOOL    IsDnsDhcpUsed() const ;
	tstring	GetDchpAddr() const;                    //�õ���ǰDHCP��ַ

	// wins function
	BOOL	IsWinsUsed() const;
	tstring GetPrimaryWinsServer() const;
	tstring GetSecondaryWinsServer() const;

	tstring	GetGatewayAddr( int nGateway = DEFAULT_GATEWAY_ADDR ) const; //��ȡ��ǰ���ص�ַ
	SIZE_T	GetNumGatewayAddrs() const;

	static	tstring GetAdapterTypeString( UINT nType );
	UINT	GetAdapterType() const;

	u32	    GetAdapterIndex() const;

	//����3����������������ֱ�ӽ�����IPCtl��GetAddressֵ��Ϊ��������
	BOOL    NetIpConflict( DWORD chIP ); //ip��ͻ���,TRUEΪ��ͻ
	EmNetStatus    NetAlive( DWORD dw );  //��ǰ����������,TRUEΪ����
	EmNetStatus    GetNetWorkState(); //��ȡ����״̬

	BOOL    SetIPToPC( u32 dwIPAddr, u32 dwMaskAddr, u32 dwGateAddr, u32 dwDNSAddr );//��ȷ����TRUE ������
  
    BOOL    SetIPToPC( u32 dwIPAddr, u32 dwMaskAddr, u32 dwGateAddr, BOOL bRefreshIPCfg = TRUE, BOOL bWifi = FALSE );

    BOOL    SetIPToPC( TIpConfig &tEthnet );
	
	BOOL    SetDHCPToPC( BOOL bRefreshIPCfg = TRUE, BOOL bWifi = FALSE ); //��ȷ����TRUE������IPʹ��DHCP
    
    BOOL    SetDnsDhcpToPc(  BOOL bRefreshIPCfg = TRUE, BOOL bWifi = FALSE );   //����DNS������ʹ��DHCP
    
    BOOL    SetDnsAddr( u32 dwDNSAddr , BOOL bRefreshIPCfg = FALSE, BOOL bWifi = FALSE );      //����DNS��ַ
    BOOL    SetBackupDnsAddr( u32 dwDNSAddr , BOOL bRefreshIPCfg = FALSE, BOOL bWifi = FALSE ); //���ñ���DNS��ַ

    BOOL    DeleteDnsAddr( u32 dwDNSAddr, BOOL bWifi = FALSE ); //ɾ��DNS��ַ

	void    StartCheckNet( );//������ʱ����ÿ500������һ�¶�����ip��ͻ

	s32     GetIndex();
	
    static void InitCriticalSection()
    {
        InitializeCriticalSection( &m_s_tCriticalSection );
    }

	static void DelCriticalSection()
    {
        DeleteCriticalSection( &m_s_tCriticalSection );
    }

	static void CreateCurNetCardName( ) ;
	

protected:
	tstring	GetStringFromArray( const StringArray* pPtr, int nIndex ) const;
	
	/////////////////////////////////////////////
	// Function Prototypes
	//��ȡ��ǰ�����������Ϣ
	static DWORD EnumNetworkAdapters( CNetworkAdapter* lpBuffer, ULONG ulSzBuf, LPDWORD lpdwOutSzBuf, BOOL bWifi = FALSE );

	CString GetCurNetCardName(){ return m_cstrCurNetCardName; }

    BOOL  WinExecAndWait(LPCTSTR lpExeName, LPTSTR lpCmdLine);
public:
    static CRITICAL_SECTION    m_s_tCriticalSection;
    static BOOL32  m_bCheckIP;  // �Ƿ�Ҫ���IP��ͻ�Ͷ������

private:		
	tstring			m_sName;		// adapter name with the computer.  For human readable name use m_sDesc.
	tstring			m_sDesc;
	tstring			m_sPriWins;
	tstring			m_sSecWins;
	tstring			m_sDefGateway;
	tstring			m_sDhcpAddr;
	TIPINFO			m_sCurIpAddr;	// ip�б��е�ǰʹ�õ�ip
	DWORD			m_dwIndex;		// ������������
	UINT			m_nAdapterType;	
	BOOL			m_bDhcpUsed;
    BOOL            m_bDnsDhcpUsed;
	BOOL			m_bWinsUsed;		
	StringArray		m_DnsAddresses;
	CIpInfoArray	m_IpAddresses;
	StringArray		m_GatewayList;
	time_t			m_tLeaseObtained;
	time_t			m_tLeaseExpires;
	tstring         m_strMAC;
	u32             m_dwIP;        //��ʼ�������ip

	s32             m_nIndexNet;

	struct UNNAMED 
	{
        BYTE	ucAddress[ MAX_ADAPTER_ADDRESS_LENGTH ];
		UINT	nLen;
	} m_ucAddress;


    static CNetworkAdapter *m_ptNetParam ;

private:

	PMIB_IFROW   m_pIfRow;  
	PMIB_IFTABLE m_pIfTable;
	static s32          m_nNetWorkCnt;       //��������
	static CString      m_strCurNetWorkName; //��ǰʹ�õ���������
	u32          m_dwCurIfRowIndex;   //��ǰʹ�õ�IFROW����
 	static CIPInfoManager* m_pNetWorkAssist;  //���ڻ�ȡ�����ӿ���Ϣ 
	static CString      m_cstrCurNetCardName; //��ǰʹ�õ���������[��������xxx]������netshʹ��
    static CString      m_strWifiNetCardName; //��ǰ������������
public:
	void UpdateUI();
	BOOL GetIfData();

};

#endif //_ADAPTER_INFO_H____