#include "owslib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommandQueue::CCommandQueue()
{
    ClearCommand();
}

CCommandQueue::~CCommandQueue()
{
    ClearCommand();
}

/*=============================================================================
  �� �� ���� GetCommandCount
  ��    �ܣ� ���ػ�����е���Ϣ����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 

  �� �� ֵ�� u32
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2006/08/22    4.0		    ������                  ����
=============================================================================*/
u32 CCommandQueue::GetCommandCount()
{
    return m_vctCommandQueue.size();
}

/*=============================================================================
  �� �� ���� ClearCommand
  ��    �ܣ� ��ջ�����е���Ϣ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 

  �� �� ֵ�� void
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2006/08/22    4.0		    ������                  ����
=============================================================================*/
void CCommandQueue::ClearCommand()
{
    u32 nSize = m_vctCommandQueue.size();
    for(u32 nIndex = 0; nIndex < nSize; nIndex++)
    {
        m_vctCommandQueue.pop();
    }
}

/*=============================================================================
  �� �� ���� PushCommand
  ��    �ܣ� ����һ��������������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� TCOMMAND &tCommand

  �� �� ֵ�� void
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2006/08/22    4.0		    ������                  ����
=============================================================================*/
void CCommandQueue::PushCommand(TCOMMAND &tCommand)
{
    m_vctCommandQueue.push(tCommand);
}

/*=============================================================================
  �� �� ���� PushCommand
  ��    �ܣ� ����һ��������������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� CMessage& cMsg, CMtMsg& cMtMsg, CDispEvent *pDispEvent,
             u16 *pwWaitEvent, s32 nEventNum, u32 dwType, u32 dwTimeOut

  �� �� ֵ�� void
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2006/08/22    4.0		    ������                  ����
=============================================================================*/
void CCommandQueue::PushCommand(CMessage& cMsg, CTpMsg& cMtMsg, CKdvDispEvent *pDispEvent,
                                u16 *pwWaitEvent, s32 nEventNum, u32 dwType, u32 dwTimeOut)
{
    TCOMMAND tCommand;
    tCommand.m_cMsg = cMsg;
    tCommand.m_cMtMsg = cMtMsg;
    tCommand.m_pCDispEvent = pDispEvent;
    tCommand.m_nEventNum = nEventNum;
    tCommand.m_dwType = dwType;
    tCommand.m_dwTimeout = dwTimeOut;

    for(u32 nIndex = 0; nIndex < nEventNum; nIndex++)
    {
        tCommand.m_vctWaitEvent.push_back(*pwWaitEvent);
        pwWaitEvent++;
    }

    PushCommand(tCommand);
}

/*=============================================================================
  �� �� ���� GetNextCommand
  ��    �ܣ� ��ȡ��������е�һ���������������Ϣ�Ӷ�����ɾ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� TCOMMAND &tCommand

  �� �� ֵ�� BOOL32
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2006/08/22    4.0		    ������                  ����
=============================================================================*/
BOOL32 CCommandQueue::GetNextCommand(TCOMMAND& tCommand)
{
    if(!IsEmpty())
    {
        FrontCommand(tCommand);
        PopCommand();
        return TRUE;
    }

    return FALSE;
}

/*=============================================================================
  �� �� ���� PopCommand
  ��    �ܣ� ɾ����������е�һ������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 

  �� �� ֵ�� void
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2006/08/22    4.0		    ������                  ����
=============================================================================*/
void CCommandQueue::PopCommand()
{
    if(m_vctCommandQueue.size() > 0)
    {
        m_vctCommandQueue.pop();
    }
}

/*=============================================================================
  �� �� ���� FrontCommand
  ��    �ܣ� ȡ�û�������еĵ�һ������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� TCOMMAND& tCommand

  �� �� ֵ�� void
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2006/08/22    4.0		    ������                  ����
=============================================================================*/
void CCommandQueue::FrontCommand(TCOMMAND& tCommand)
{
    tCommand = m_vctCommandQueue.front();
}