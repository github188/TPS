/****************************************************************************** 
ģ����: FTPC
�ļ���: ftpc_api.h 
����  : 
ftp��ͷ�ļ� �汾�� 
******************************************************************************/

#ifndef _FTPC_API_H
#define _FTPC_API_H 

#include "kdvtype.h"

#ifdef __cplusplus 
extern "C" { 
#endif 

//api����ֵ
#define FTPC_ERR                    -1  //����
#define FTPC_OK                 (s32)0   //����
#define FTPC_PARAMERR           (s32)1   //���ݵĲ�������
#define FTPC_CREATESOCKERR      (s32)2   //����socketʧ��
#define FTPC_GETOPTERR          (s32)3   //��ȡoptionѡ����ʧ��
#define FTPC_SETOPTERR          (s32)4   //����optionѡ��ʧ��
#define FTPC_SELECTERR          (s32)5   //select����ʧ��
#define FTPC_CONNECTIMEOUT      (s32)6   //���ӳ�ʱ
#define FTPC_CONNECTREFUSEDERR  (s32)7   //���ӱ��ܾ�
#define FTPC_CONNECTFAILED      (s32)8   //��ȡserver����״��ʧ��
#define FTPC_PASSERR            (s32)9   //�������
#define FTPC_USERNAMEERR        (s32)10  //�û�������
#define FTPC_PASVMODEERR        (s32)11  //����pasv�������
#define FTPC_SIZEGETERR         (s32)12  //��ȡ�ļ�sizeʧ��
#define FTPC_RETRCOMERR         (s32)13  //������������ʧ��
#define FTPC_THREADERR          (s32)14  //�����߳�ʧ��
#define FTPC_SEMERR             (s32)15  //�ź�������ʧ��
#define FTPC_FILESTATERR        (s32)16  //��ȡ�ļ�����ʧ��
#define FTPC_CWDCOMERR          (s32)17  //����cwd����ʧ��
#define FTPC_STORCOMERR         (s32)18  //����stor����ʧ��
#define FTPC_ALLOCOMERR         (s32)19  //����allo����ʧ��
#define FTPC_MEMMALLOCERR       (s32)20  //malloc memoryʧ��
#define FTPC_OPENFILEERR        (s32)21  //���ļ�����
#define FTPC_FILE_NOT_FINISH    (s32)22  //��һ���ļ�δ�������
#define FTPC_CONNECTERR         (s32)23  //connect���ó���
#define FTPC_RESTCOMERR         (s32)24  //����REST��Ϣʧ��
#define FTPC_DELECOMERR         (s32)25  //ɾ���ļ���Ϣʧ��
#define FTPC_COMMANDRCVERR      (s32)26  //����respond��Ϣʧ��
#define FTPC_SENDCOMMANDERR     (s32)27  //��������ʧ��
#define FTPC_MKDERR             (s32)28  //����Ŀ¼ʧ��
#define FTPC_RMDERR             (s32)29  //ɾ��Ŀ¼ʧ��

//�ص���Ϣ����(��Ӧ�ص��������� s32 dwMsgType)
#define FTPC_TRANSFILEERR       (s32)100 //������������ļ�����
#define FTPC_LOCALFILEERR       (s32)101 //д��������ļ�����
#define FTPC_MEMSPACELACK       (s32)102 //����ĸ��ڴ治��
#define FTPC_TRANSPERCENT       (s32)103 //�ļ��Ѵ���ٷֱ���Ϣ
#define FTPC_FINISHED           (s32)104 //�ļ����������Ϣ
#define FTPC_STOP_SEND_DATA     (s32)105 //����ֹͣ��������


//�ص����������ṹ����
typedef struct 
{
	s32 dwMsgType;		        //��Ϣ����
	union
	{
		u32 dwTransPercent;     //��Ӧ msgType = FTPC_TRANSPERCENT ���ݽṹ	    
		u32 dwMsgDescripton;    //��ȡ���ļ�size
	}UMsgInfo;
	void *pUserData; 
}TFtpcCallback;			

//�ص���������
typedef void (*CBFtpcCallbackFun)(TFtpcCallback *PTParam);


/*=============================================================================
�� �� ����FTPCSetServAddr
��    �ܣ����÷������˵�ip��ַ�Ͷ˿�

ע    �⣺����ĵ�һ�������������ַ�ַ������ǵ�ֶ�������ʽ
�㷨ʵ�֣��������ַ�Ͷ˿����õ�ȫ�ֱ���

ȫ�ֱ�������
����˵����
@param��s8  *pwServIp  -    ������IP�����ַ�ַ���
@param��u16 wServPort  -    �������˿ں�
�� �� ֵ�� s32   FTPC_OK   �ɹ��� FTPC_PARAMERR   ʧ��
=============================================================================*/
s32 FTPCSetServAddr(const s8 *paServIp, const u16 wServPort);

/*=============================================================================
�� �� ����FTPCSetLogId
��    �ܣ����õ�½�û���������

ע    �⣺���������(anonymous),�κ�����Կ�
�㷨ʵ�֣�����½���û�������������ģ���ȫ�ֱ���
ȫ�ֱ�������
��    ����
@param: s8  *paUserName   -     ��½�û���
@param: s8  *pwPassword   -     ��½����
�� �� ֵ�� s32   FTPC_OK   �ɹ��� FTPC_PARAMERR   ʧ��
=============================================================================*/
s32 FTPCSetLogId(const s8 *paUserName, const s8 *paPassword);

/*=============================================================================
�� �� ���� FTPCGetFileinMem
��    �ܣ� 1. �����ļ�������ģʽΪ�ڴ�
           2. ���÷������ļ��ļ�����·��
           3. �����ļ���������ڴ���
ע    �⣺
�㷨ʵ�֣� ͨ��FTP RETRȡ���ļ������ļ�������pwMemBuf�ڴ���
ȫ�ֱ�����
����˵����
@param:   s8  *pwServpath   -   �ļ�·��
@param:   s8  *pwFileName    -  �ļ���
@param:   s8  *pwMemBuf     - ����ļ���ʼ��ַ
@param:   u32 dwMemSize     -��ģ������ڴ��С
�� �� ֵ�� s32   FTPC_OK   �ɹ�;ʧ�ܼ�api����ֵ�ĺ궨��

����˵���� �ļ���������첽ģʽ����������л�ͨ���ص����ļ�����Ľ��ȷ��ظ��ϲ�
=============================================================================*/
s32 FTPCGetFileinMem(const s8 *paServpath, const s8 *paFileName, s8 *pwMemBuf, u32 dwMemSize) ;

/*=============================================================================
�� �� ����  FTPCGetFileinFlash
��    �ܣ�  1. �����ļ�������ģʽΪflash
            2. ���÷������ļ��ļ�����·��
            3. �����ļ��������flash��

ע    �⣺
�㷨ʵ�֣�  ͨ��FTP RETRȡ���ļ������ļ�������paLocalPath FLASH��
ȫ�ֱ�����
����˵����
@param:   s8    *pwServpath   -     �������ļ�·��
@param:   s8    *pwFileName   -     �������ļ���
@param:   s8    *pwLocalPath  -     ���ش��·���������ļ���
�� �� ֵ��s32   FTPC_OK   �ɹ�   ʧ�ܼ�api����ֵ�ĺ궨��
����˵�����ļ���������첽ģʽ����������лὫ����Ľ��ȷ��ظ��ϲ�
=============================================================================*/
s32 FTPCGetFileinFlash(const s8 *paServpath, const s8 *paFileName, const s8 *paLocalPathFile) ;

/*=============================================================================
�� �� ����  FTPCUploadFile
��    �ܣ�  1�������ϴ��ļ���·���ļ���
            2���ϴ��ļ�                        

ע    �⣺
�㷨ʵ�֣�  ͨ��FTP STOR�ϴ��ļ�
ȫ�ֱ�����
����˵����
@param:   s8    *pwServpath   -     �������ļ�·��
@param:   s8    *paServFileName -   ��������ŵ��ļ���
@param:   s8    *pwFileName   -     �����ļ���
@param:   s8    *pwLocalPath  -     ����·��
�� �� ֵ��s32   FTPC_OK   �ɹ�   ʧ�ܼ�api����ֵ�ĺ궨��
����˵�����ļ���������첽ģʽ����������лὫ����Ľ��ȷ��ظ��ϲ�
=============================================================================*/
s32 FTPCPutFile(const s8 *paServpath, const s8 *paServFileName, const s8 *paFileName, const s8 *paLocalPath) ;

/*=============================================================================
�� �� ����  FTPCUploadMemData
��    �ܣ�  1�������ϴ��ڴ����ݵ�ַ
            2���ϴ��ļ�                        

ע    �⣺
�㷨ʵ�֣�  ͨ��FTP STOR�ϴ��ļ�
ȫ�ֱ�����
����˵����
@param:   s8    *pwServpath   -     �������ļ�·��
@param:   s8    *paServFileName -   ��������ŵ��ļ���
@param:   s8    *pwMemAddr   -     �������ݵ�ַ
@param:   u32  *dwMemSize  -     ����·��
�� �� ֵ��s32   FTPC_OK   �ɹ�   ʧ�ܼ�api����ֵ�ĺ궨��
=============================================================================*/
s32 FTPCPutMemData(const s8 *paServpath, const s8 *paServFileName, const s8 *paMemAddr, const s32 dwMemSize) ;
/*=============================================================================
�� �� ����  FTPCPutSerielData
��    �ܣ�  1�������ϴ��ڴ����ݵ�ַ
                        2�����ڶ�ͬһ���ļ�����׷���ϴ�                   

ע    �⣺
�㷨ʵ�֣�  ͨ��FTP STOR�ϴ��ļ�
ȫ�ֱ�����
����˵����
@param:   s8    *pwServpath   -     �������ļ�·��
@param:   s8    *paServFileName -   ��������ŵ��ļ���
@param:   s8    *pwMemAddr   -     �������ݵ�ַ
@param:   u32  *dwMemSize  -       ���ݳ���
@param:   void *pUserData  -        �û�д��ص�����
�� �� ֵ��s32   FTPC_OK   �ɹ�   ʧ�ܼ�api����ֵ�ĺ궨��
=============================================================================*/
s32 FTPCPutSerielData(const s8 *paServpath, const s8 *paServFileName, const s8 *paMemAddr, const u32 dwMemSize, void *pUserData);


/*======================================================
�� �� ����	FTPCDelFile
��    �ܣ�	ftpcģ��ɾ����������ĳ�ļ�
�㷨ʵ�֣�
����˵����	��	 
�� �� ֵ��	FTPC_OK  �ɹ�       FTPC_ERROR  ʧ��	
--------------------------------------------------------
�޸ļ�¼��
	����	�汾	�޸���	�߶���	�޸ļ�¼
========================================================*/
s32 FTPCDelFile(const s8 *paServpath, const s8 *paFileName);

/*======================================================
�� �� �� :	FTPCMkdir
��    �� :	ftpcģ���ڷ������ϴ���Ŀ¼
�㷨ʵ�� :
����˵�� :
@param   :   s8    *paServpath   -     �������ļ�·��
�� �� ֵ :   s32   FTPC_OK   �ɹ�   FTPC_ERROR��FTPC_TIMEOUT��FTPC_LOGERR    ʧ��
--------------------------------------------------------
�޸ļ�¼ :
	����	�汾	�޸���	�߶���	�޸ļ�¼
========================================================*/
s32 FTPCMkdir(const s8 *paServpath);


/*=============================================================================
�� �� ����  FTPCReset
��    �ܣ�  ���ģ�����г�ʼ����

ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����  ��    
��    ����  ��
�� �� ֵ��  s32   FTPC_OK   �ɹ��� FTPC_ERROR   ʧ��
=============================================================================*/
s32 FTPCReset(void);

/*====================================================================
�� �� ����  FTPCRegCallback
��    �ܣ�  ע������ַ�Ļص�����
�㷨ʵ�֣�
ȫ�ֱ�����  ��
����˵����
@param:     CBFtpcCallbackFun fun  -   �ص�����
�� �� ֵ��  s32   FTPC_OK   �ɹ���     FTPC_PARAMERRʧ��
=============================================================================*/
s32 FTPCRegCallback(CBFtpcCallbackFun fun);

/*====================================================================
�� �� ����  FTPCUnRegCallback
��    �ܣ�  ע��������ջص�ַ�Ļص�����
�㷨ʵ�֣�
ȫ�ֱ�����  ��
����˵����  N/A
�� �� ֵ��  s32   FTPC_OK   �ɹ�
=============================================================================*/
s32 FTPCUnRegCallback(void);

/*=============================================================================
�� �� ����FtpcGetVersion
��    �ܣ���ȡftpc�汾��

ע    �⣺dwBufLen �ַ�����Ӧ���ڻ����256
�㷨ʵ�֣�

ȫ�ֱ�������
����˵����
@param��s8 *pchVer: -- �ַ�ָ��
@param��u32 dwBufLen: -- �ַ�����

�� �� ֵ�� s32    FTPC_OK   �ɹ��� FTPC_PARAMERR   ʧ��
=============================================================================*/
s32 FtpcGetVersion(s8 *pchVer, u32 dwBufLen);

/*=============================================================================
�� �� ����  FTPCInit
��    �ܣ�  ��ʼ��FTPCģ��
            
ע    �⣺  
�㷨ʵ�֣�  
ȫ�ֱ�����  ��
��    ����  ��
�� �� ֵ��  u32  FTPC_OK   �ɹ�            FTPC_ERROR   ʧ��
=============================================================================*/
s32 FTPCInit(void);

/*======================================================
�� �� ����	FTPCSetMem
��    �ܣ�	ftpcģ������һ���ڴ�
�㷨ʵ�֣�
����˵����	��	 
�� �� ֵ��	FTPC_OK  �ɹ�       FTPC_MEMMALLOCERR  ʧ��	
--------------------------------------------------------
�޸ļ�¼��
	����	�汾	�޸���	�߶���	�޸ļ�¼
========================================================*/
s32 FTPCSetMem(u32 dwMemLen);

/*======================================================
�� �� ����	FTPCFreeMem
��    �ܣ�	ftpcģ���ͷ��ڴ�
�㷨ʵ�֣�
����˵����	��	 
�� �� ֵ��	FTPC_OK  �ɹ�       FTPC_ERROR  ʧ��	
--------------------------------------------------------
�޸ļ�¼��
	����	�汾	�޸���	�߶���	�޸ļ�¼
========================================================*/
s32 FTPCFreeMem(void);

/*======================================================
�� �� ����	FTPCSetSendDelay
��    �ܣ�	ftpcģ�����÷�����ʱ
�㷨ʵ�֣�
����˵����	dwDelayTime send����ʱʱ��(��λ:΢��)
�� �� ֵ��	FTPC_OK  �ɹ�       FTPC_ERROR  ʧ��	
--------------------------------------------------------
�޸ļ�¼��
	����	�汾	�޸���	�߶���	�޸ļ�¼
========================================================*/
s32 FTPCSetSendDelay(s32 dwDelayTime);

/*======================================================
�� �� �� :	FTPCStopSend
��    �� :	ftpcģ��ֹͣ����
�㷨ʵ�� :
����˵�� :
�� �� ֵ :	FTPC_OK  �ɹ�       FTPC_ERROR  ʧ��	
--------------------------------------------------------
�޸ļ�¼ :
	����	�汾	�޸���	�߶���	�޸ļ�¼
========================================================*/
s32 FTPCStopSend(void);

/*======================================================
�� �� �� :	FTPCCloseAll
��    �� :	ftpcģ��ر���������
�㷨ʵ�� :
����˵�� :	
�� �� ֵ :	FTPC_OK  �ɹ�       FTPC_ERROR  ʧ��	
--------------------------------------------------------
�޸ļ�¼ :
	����	�汾	�޸���	�߶���	�޸ļ�¼
========================================================*/
s32 FTPCCloseAll(void);

/*======================================================
�� �� �� :	FTPCDebug
��    �� :	ftpcģ��򿪵��Կ���
�㷨ʵ�� :
����˵�� :
@param��u8 nOn: -- �Ƿ��
�� �� ֵ :	FTPC_OK  �ɹ�       FTPC_ERROR  ʧ��	
--------------------------------------------------------
�޸ļ�¼ :
	����	�汾	�޸���	�߶���	�޸ļ�¼
========================================================*/
s32 FTPCDebug(u8 nOn);

#ifdef __cplusplus
}
#endif

#endif

