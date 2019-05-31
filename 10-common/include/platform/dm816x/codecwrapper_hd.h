/*****************************************************************************
  ģ����      : Codecwrapper.a
  �ļ���      : codecwrapper_hd.h
  ����ļ�    : codecwrapperdef_hd.h
  �ļ�ʵ�ֹ���: 
  ����        : ������
  �汾        : V4.0  Copyright(C) 2007-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/11/28  4.0         ������      ����
******************************************************************************/
#ifndef _CODECWRAPPER_HD3_H_
#define _CODECWRAPPER_HD3_H_

#include "codecwrapperdef_hd.h"


class CVideoEncoder;
class CAudioEncoder;
class CVideoDecoder;
class CAudioDecoder;

class CKdvVidEnc
{
public:
	CKdvVidEnc();
	~CKdvVidEnc();
public:
	u16    CreateEncoder(TEncoder *pEncoder);                 /*HD1��ʹ��*/
    u16    Create(TVidEncInit* pEnc, void* pReserve = NULL);  /*���������ն���ʹ������ӿ�*/
	u16    CreateHD3(TVidEncHD3RD* pEnc);							/*��������ʹ������ӿ�*/
    u16    GetEncoderStatus(TKdvEncStatus &tKdvEncStatus);/*��ȡ������״̬*/ 		
    u16    GetEncoderStatis(TKdvEncStatis &tKdvEncStatis);/*��ȡ��������ͳ����Ϣ*/
	u16    SetVidDataCallback(FRAMECALLBACK fVidData, void* pContext); /*������Ƶ���ݻص�*/
    u16    GetCodecType(u32& dwType);  /*��������������λ�� VID_CODECTYPE_FPGA VID_CODECTYPE_DSP*/
	//     ׷�ӱ��������Ƚӿڣ�TRUEΪ��������ȣ�FALSEΪ�ر������ȡ�����������ʧ
	u16    SetEncQualityEnhance(BOOL32 bEnhance);
//    u16    StartCap();/*��ʼ�ɼ�ͼ��*/
//    u16    StopCap(); /*ֹͣ�ɼ�ͼ��*/

	u16    SetVidCapPortType(u32 dwType);
	u16    SetVidCapVPID(u32 dwID);  //0:��ͨ��DSPֱ�Ӳɼ��� 1:ͨ��DSP���غ�ɼ�

    u16    SetVideoEncParam(const TVideoEncParam *ptVideoEncParam); /*������Ƶ�������*/
    u16    GetVideoEncParam(TVideoEncParam &tVideoEncParam );       /*�õ���Ƶ�������*/
    u16	   SetVidEncParamCallback(VIDENCCALLBACK fVidEncParamCb, void* pbContext);		/*gaoden:EncParam�������֮�ص�(2009-7-8)*/
    u16    StartEnc();/*��ʼѹ��ͼ��*/
    u16    StopEnc(); /*ֹͣѹ��ͼ��*/
	
	u16    SetVideoEncSlieceLen(u32 nLen);   /*Ĭ��1400��0ʱ��ʾ��Slice���롣������ֱ���1080i������ʱ������8192��*/
    u16    GetVideoSrcInfo(TVidSrcInfo& tInfo); /*��ȡ������Ƶ�ź���ʽ*/
    u16    SetVideoSrcInfo(TVidSrcInfo* ptInfo); /*���ã������ϡ� ǿ�����õ�ǰ�����ź���ʽ������YPbPr,VGA�ӿ�*/

    /*��������   SetVideoEncMBQulity
    ��    �ܣ� ���ú�����ȼ�
    ��    ���� u32 dwQulityMask��������ȼ����룬VIDENC_MBSIZE_ENABLE �� VIDENC_MBSIZE_DISABLE
    �� �� ֵ�� u16  
    ˵    ���� ��������е��ú����б���������Ч*/
    u16    SetVideoEncMBQulity(u32 dwQulityMask); 
    
    /*��������   ScaleVideoCap
    ��    �ܣ� ������Ƶ�ɼ�����,����C�ͷ������ӡ�
    ��    ���� u32 dwVidSrcPort :��Ƶ�ɼ����� VIDIO_C0, VIDIO_YPbPr0, VIDIO_YPbPr1
               u8 byType        :�������� VIDCAP_SCALE_BRIGHTNESS ��
               u8 byValue       :������ֵ 0~255; 0x80ΪĬ��ֵ
    �� �� ֵ�� u16  
    ˵    ���� */
    u16    ScaleVideoCap(u32 dwVidSrcPort,u8 byType, u8 byValue); /* ��Ƶ�ɼ����� */

	u16    SetFastUpata(BOOL32 bIsNeedProtect = TRUE);     /*����FastUpdata��MediaCtrl��75֡�ڱ�һ��I֡����*/
	/*���;�̬ͼƬ*/
	u16    SetSendStaticPic(BOOL32  bSendStaticPic);

	u16    StartAddLogoInEncStream(u8 *pbyBmp, u32 dwBmpLen, u32 dwXPos, u32 dwYPos,
		u32 dwWidth, u32 dwHeight, TTranspColor tBackBGDColor);	
       u16 StartAddLogoInEncStream(TFullLogoParam &tLogoParm);
	u16    StopAddLogoInEncStream();

	//ȡ�õ�ǰ����״̬�£����̨��Ĳο���ͼ����
	void   GetBannerImageSrc(u32& dwImagewidth, u32&     dwImageHeight);
	//��ʼ�����������
	u16 StartAddBannerInEncStream(u8 *pbyBmp, u32 dwBmpLen,	const TAddBannerParam& tAddBannerParam);
       u16 StartAddBannerInEncStream(TFullBannerParam &tBannerParam,BOOL32 bSpaceArea=TRUE/*ͼƬǰ���Ƿ���пհ���*/);
    //ֹͣ�����������
	u16 StopAddBannerInEncStream();
	//1080I��ƵԴ��1080P����
	void  Set1080IEnc1080P(BOOL32     bSet,BOOL32 bDeinterlace = FALSE);
    
    //�ɼ�ͼ�����������������һ��ʱ���������ԣ�0���Ӻڱߣ�1���ñߣ�
    u16  SetVidEncResizeMode(s32 nMode);
    u16    SetVidPlayPolicy(u32 dwTimeout = 5, u32 dwPlayType = EN_PLAY_LAST);
protected:
private:
	CVideoEncoder *m_pCodec;
};

class CKdvAudEnc
{
public:
	CKdvAudEnc();
	~CKdvAudEnc();
public:
	u16    CreateEncoder(TEncoder *pEncoder, u32 dwDevVersion=en_H600_Board);

	u16    SetAudDataCallback(FRAMECALLBACK fAudData, void* pContext);/*������Ƶ���ݻص�*/
	/*��ȡ������Ƶ����*/
	u32    GetInputAudioPower();
	
    u16    GetEncoderStatus(TKdvEncStatus &tKdvEncStatus);/*��ȡ������״̬*/ 		
    u16    GetEncoderStatis(TKdvEncStatis &tKdvEncStatis );/*��ȡ��������ͳ����Ϣ*/
    
	
    u16    StartAudioCap();/*��ʼ�����ɼ�*/
    u16    StopAudioCap(); /*ֹͣ�����ɼ�*/

    u16    SetAudioEncParam(u8 byMediaMode, 
                            u8 byMediaType=MEDIA_TYPE_PCMU,
                            u16 wAudioDuration = 30); /*��������ѹ������*/
    u16    GetAudioEncParam(u8 &byAudioEncParam, 
                            u8 *pbyMediaType = NULL,
                            u16 *pwAudioDuration = NULL);/*�õ�����ѹ������*/

	u16    StartAudioEnc();/*��ʼѹ������*/
    u16    StopAudioEnc(); /*ֹͣѹ������*/

    u16    SetAudioMute( BOOL32 bMute );     //�����Ƿ�ྲ������

    u16    SetAudioVolume(u8 byVolume ); /*���òɼ�����*/	
	u16	   SetSingleAudInputVol(u32 dwAudPort, u32 dwVol);//���õ�����Ƶ�ӿ�����,ֻ������һ·

    u16    GetAudioVolume(u8 &byVolume );/*��ȡ�ɼ�����*/
    
    u16    SetAudInPort(u32 dwAudPort, u32 dwAudMasterMic);  /*������Ƶ�ɼ��˿� HDMI or C���������󣬼�������Ƶ�ڣ����ڶ�������ֻ������������AEC�����������ӿڲ���AEC����*/	
	
    u16    StartAec();/*��ʼ��������*/
    u16    StopAec(); /*ֹͣ��������*/
	u16	   AecDebug(u32 dwDebug);/*��Χ4-64*/

	u16	   StartAgcSmp(); /*��ʼsmp����*/
	u16	   StopAgcSmp(); /*ֹͣsmp����*/
	u16	   StartAgcSin(); /*��ʼsin����*/
	u16	   StopAgcSin(); /*ֹͣsin����*/	
protected:
private:
	CAudioEncoder *m_pCodec;
};

class CKdvVidDec
{
public:
	CKdvVidDec();
	~CKdvVidDec();
public:
	u16	   CreateDecoder(TDecoder *pDecoer);   /*HDU, HD1��ʹ��*/
	u16    Create(TVidDecInit* pDec, void* pReserve = NULL); /*���������ն���ʹ������ӿ�*/
	u16    CreateHD3(TVidDecHD3RD* pDec);
	u16    Create();
	u16    StartDec();/*��ʼͼ�����*/
	u16    StopDec(); /*ֹͣͼ�����*/
	u16    GetDecoderStatus(TKdvDecStatus &tKdvDecStatus,u32 dwChnl = 0);/*��ȡ������״̬*/
    u16    GetDecoderStatis(TKdvDecStatis &tKdvDecStatis,u32 dwChnl = 0);/*��ȡ��������ͳ����Ϣ*/	
    u16    GetCodecType(u32& dwType);  /*��������������λ�� VID_CODECTYPE_FPGA VID_CODECTYPE_DSP*/

	u16    SetData(const TFrameHeader& tFrameInfo,u32 dwChnl = 0);        /*������Ƶ��������*/

	/*������Ƶ������������*/
	u16    SetVidDropPolicy(u8 byDropPolicy);

    u16    SetDisplayType(u8 byDisplayType);/*���û�����ʾ����(VIDEO VGA)*/
    
    u16    SetGetVideoScaleCallBack(TDecodeVideoScaleInfo tDecodeVideoScaleInfo);
	u16    SetVideoDecParam(TVideoDecParam *ptVidDecParam);

    /*������Ƶ���л�*/
    u16 SetVidPIPParam(enVideoPIPMode enMode, enVideoPIPIndex enIndex[3]);
    
    /*��������   SetPlayScale
    ��    �ܣ� ���ò����豸����ʾ������
    ��    ���� u16 wWidth  :��ʾ��������0Ϊ�Զ�
               u16 wHeight :��ʾ�߱�����0Ϊ�Զ���
    �� �� ֵ�� u16  
    ˵    ���� ���磺����(0,0)��Ĭ�ϣ�Ϊ���ֲ�����ʽ���������(16,9)��ʾ�����豸��ʾ����Ϊ16:9*/
    u16    SetPlayScale(u16 wWidth, u16 wHeight);
    
    u16    SetVidPlyPortType(u32 dwType);
    u16    SetVideoPlyInfo(u32 dwOutType = VID_OUTTYPE_ORIGIN);//������Ƶ����ź���ʽ��
    u16    SetVideoPlyInfo(TVidSrcInfo* ptInfo);  /*������Ƶ����ź���ʽ��NULL��ʾ�Զ�������*/
    u16    GetVideoSrcInfo(TVidSrcInfo& tInfo);   /*��ȡ�����Ƶ�ź���ʽ*/

	/*��������   OsdShow
    ��    �ܣ� ����̨����ʾ��
    ��    ���� u8 *pbyBmp   :ͼƬ����
               u32 dwBmpLen :ͼƬ�ߴ硣
			   u32 dwXPos   :��ʾλ��X����
			   u32 dwXPos   :��ʾλ��Y����
			   u32 dwChnl   :��ͨ����
    �� �� ֵ�� u16  
    ˵    ���� ͼƬֻ֧��8λ��16λ��24λλͼ��4����ʱ��dwXPos��dwYPos������ڴ�ͨ��ͼ����ʾ��������Ͻǣ��������������4����ĵ����Ͻ�*/
	u16    OsdShow(u8 *pbyBmp, u32 dwBmpLen, u32 dwXPos, u32 dwYPos, u32 dwChnl = 0);

	/*�������� OsdClose
    ��    �ܣ� �ر�̨�ꡣ
    ��    ���� ��
    �� �� ֵ�� u16  
    ˵    ���� �ޣ�*/
	u16    OsdClose(u32 dwChnl = 0);
	
    //u16    SetVidPlyDefault(BOOL32 bNtsc = FALSE); /*�Ƿ�Ĭ�ϲ��� 30/60����*/
    //u16    SetVidPlyVgaDefault(u32 dwFreq = 60); /*VGA����Ƶ��Ĭ��60Hz������75,85��*/
    //u16    SetAutoCheckPlayInfo(BOOL32 bAuto);    /*�Ƿ��Զ���������֡��*/
	//����VGA��1080I��1080P�����Ƶ��(�����μ�codecwrapperdef_hd)
	void   SetVidOutFreq(u8 byVGAFreq, u8 by1080IFreq, u8 by1080PFreq);
    u16    ClearWindow();  /*����*/
    u16    FreezeVideo();  /*��Ƶ����*/
    u16    UnFreezeVideo();/*ȡ����Ƶ����*/	
	void   SetCheckFpga(BOOL32 bIsCheck);	//�����Ƿ���FPGA�쳣
	void   SetFpgaErrReboot(u32 dwErrCount);//����fpga�����Ĵ������
	u16	   SetVidDecResizeMode(s32 nMode);//�������ԣ�0���Ӻڱߣ�1���ñߣ�
	u32    GetRunCaptionTimes();
	u16    SetDspPlayCallBack(CHANGECALLBACK fDspPlay,void *pContext);
	u16	   SetDecTreshold(const u32 dwThresh = 352*288);
	u16	   SetVidOutCallBack(VIDOUTTYPECALLBACK fVidOutType);
	u16	   SetUse720P60(BOOL32 bUse720P60 = FALSE);
	u16    SetStreamPlayTypeCb(VIDDECPLAYTYPECALLBACK fVidDecPlayType);
    u32    GetOutVP(); //�������壬��ʾ���VP�ڣ�����SetVideoOutFromVidDec�ĵ�һ��������
	u16	   TestImage(BOOL32 bSet);//ɫ������
	u16    SnapShot(s8* pFileName);//����
	u16    SnapShotView(s8* pFileName);//�������
	u16    SetVidPlayPolicy(u32 dwTimeout = 5, u32 dwPlayType = EN_PLAY_LAST);
	u16     SetDecRate(u32 dwDecRate = 30);//��������
	u16     SetCutPixel(u32 dwCutPixel);
	u16		OnOutToCPort(BOOL32 bPlayOsd=FALSE);//C�����Ƿ񲥷�OSD
protected:
private:
	CVideoDecoder *m_pCodec;
};

class CKdvAudDec
{
public:
	CKdvAudDec();
	~CKdvAudDec();
public:
	u16	   CreateDecoder(TDecoder *pDecoer, u32 dwDevVersion=en_H600_Board);
	u16    GetDecoderStatus(TKdvDecStatus &tKdvDecStatus);/*��ȡ������״̬*/
    u16    GetDecoderStatis(TKdvDecStatis &tKdvDecStatis);/*��ȡ��������ͳ����Ϣ*/	

    u16    SetData(const TFrameHeader& tFrameInfo); /*������Ƶ��������*/
    u16    SetAudioDecParam(const TAudioDecParam& tAudParam);/*��Ƶ���������AAC_LC��Ч*/ 
    
    u16    SetAudOutPort(u32 dwAudPort);  /*������Ƶ���Ŷ˿� HDMI or C*/

    u16    StartDec();/*��ʼ��������*/	
    u16    StopDec(); /*ֹͣ��������*/	
    u16    SetAudioVolume(u8 byVolume );  /*���������������*/	
    u16    GetAudioVolume(u8 &pbyVolume );/*�õ������������*/	
    u16    SetAudioMute(BOOL32 bMute);/*���þ���*/
		
	/*��ȡ�����Ƶ����*/
	u32    GetOutputAudioPower();
	
	//�������� ������
	u16   PlayRing(s8* pData = NULL);
protected:
private:
	CAudioDecoder *m_pCodec;
};
// 
// class COsdMap
// {
// public:
// 	COsdMap();
// 	~COsdMap();
// public:
// 	u16   Create(u32 dwDspID);
// 	u16   Destroy();
// 	//�ϴ�ͼƬ
// 	u16   LoadBmp(u32 dwBmpID, u8 *pbyBmp, u32 dwBmpLen, TTranspColor tBackBGDColor);
// 	//����̨���ͼƬ��λ��
// 	u16   SetLogoInfo(u32 dwLogoID, u32 dwBmpID, u32 dwXPos, u32 dwYPos);
// 	//��ʾ̨��
// 	u16   ShowLogo(u32 dwLogoID, BOOL32 bShow = TRUE);
// 	//���̨���ͼƬ��λ����Ϣ��SetLogoInfo�ķ�����
// 	u16   ClearLogoInfo(u32 dwLogoID);
// 	//����ͼƬ��LoadBmp�ķ�����
// 	u16   ClearBmp(u32 dwBmpID);
// 
// 	//�ϴ�����ͼƬ��dwSumOfNumPic��ͼƬ������СͼƬ�ĸ�����ͼƬ������������
// 	u16   LoadNumBmp(u8 *pbyBmp, u32 dwBmpLen, TTranspColor tBackBGDColor, u32 dwSumOfNumPic);
// 	//������ʾͼƬ�����ݣ�λ��
// 	u16   SetNumLogoInfo(u32 dwNumLogoID, u8 *pbyLogoInfo, u32 dwLogoNum, u32 dwXPos, u32 dwYPos);
// 	//��ʾ����ͼƬ
// 	u16   ShowNumLogo(u32 dwNumLogoID, BOOL32 bShow = TRUE);
// protected:
// private:
// 	CLogoAdd  *m_pLogoAdd;
// };

class COsdMap
{
public:
	COsdMap();
	~COsdMap();
public:
	/*����������dwDspID��0��pPlayStd��������Ĳ�����ʽ.
	��Ҫע����ǽ�����һ��Ҫ�ȴ����ã����ܵ��øýӿڣ���Ȼosd��ʧ��
	*/
	u16   Create(u32 dwDspID,TVidSrcInfo *pPlayStd=NULL);
	u16   Destroy();
	u16   OsdShow(u8 *pbyBmp, u32 dwBmpLen, 
		u32 dwXPos, u32 dwYPos,	u32 dwWidth, u32 dwHeight, 
		u32 dwBgdColor, u32 dwClarity, BOOL32 bAutoCenter = TRUE);
	
	/*��������osdʹ�����½ӿڣ��ɽӿڲ���Ч*/
	u16   OsdShow(u8 *pbyBmp, u32 dwBmpLen, 
		u32 dwXPos, u32 dwYPos,	u32 dwWidth, u32 dwHeight);
	
	//�ر�Osd, �ɹ�����OSD_OK; ʧ�ܷ���OSD_ERROR.
    u16 OsdClose(u32 dwXPos, u32 dwYPos, u32 dwWidth, u32 dwHeight, BOOL32 bAutoCenter = TRUE);	

    /*�������� OsdDefaultClarity
    ��    �ܣ� ����Ĭ�ϵ�͸���ȣ�δ������Ϊ��͸��
    ��    ���� u8 byClarity��͸����(0-255,255Ϊ��͸��)��
    �� �� ֵ�� u16 
    ˵    ���� */
    u16 OsdDefaultClarity(u8 byClarity);
    /*�������� OsdDefaultBGDColor
    ��    �ܣ� ����Ĭ�ϵ�͸��ɫ��δ����Ϊ��ɫ
    ��    ���� u32 dwRed
               u32 dwGreen
               u32 dwBlue
    �� �� ֵ�� u16 
    ˵    ���� */
	u16 OsdDefaultBGDColor(u32 dwRed, u32 dwGreen, u32 dwBlue);
	
    //Osd��������Ϣ
    //����ֵ:Codec_Error_Param, 	Codec_Success
    u16  StartRunCaption(
		u8 *pbyBmp,        //����ͼƬ����
		u32 dwBmpLen,      //����ͼƬ����
		u32 dwBgXPos,      //���������x
		u32 dwBgYPos,      //���������y
		u32 dwBgWidth,     //���������
		u32 dwBgHeigh,     //������߶�
		u32 dwBgColor,     //���������ɫ,��rgb:0x0RGB
		u32 dwClarity,     // ͸����
		u32 dwTimes = 1,   //ѭ�������Ĵ���(Ĭ��1)
		u32 dwSpeed = RUNSPEED_NORM,   //�����ٶ�(��codecwapperdef_hd�궨�壬Ĭ��RUNSPEED_NORM) 
		u32 dwRunMode = RUNMODE_LEFTRIGHT);  //������ʽ(��codecwapperdef_hd�궨�壬Ĭ��RUNMODE_LEFTRIGHT)
    //ֹͣOsd��������Ϣ
    void  StopRunCaption(); 
    // ���������У���֧�ֶ����������Ϣ�������ڹر�ʱ��Ҫָ����Χ 
    void  StopRunCaption(u32 dwBgXPos,      //���������x
		u32 dwBgYPos,      //���������y
		u32 dwBgWidth,     //���������
		u32 dwBgHeigh     //������߶�
		); 
    // ����osdͼƬ����Ӧ��ʽ��������������720p��1080p����,�����ֱ�Ϊ1280x720,1920x1080
    void  SetOsdStd(u32 dwWidth, u32 dwHeight);
protected:
private:
	u32	m_dwOsdWidth;
	u32	m_dwOsdHeight;
	TTranspColor m_tTranColor;
	//CLogoAdd  *m_pLogoAdd;
};

//�趨��ǰ*.bin,*.out·����Ĭ��/usr/bin
void SetCodecAppDir(s8* szPath);
//ע��OSP����
void RegsterCommands();

//��ʼ��DSPоƬ
u16 HardCodecInitDSP(TDSPInit* pInit);
u16 HardCodecDestroyDSP(u32 dwDSPID);
//��ʼ��FPGA
u16 HardCodecDevInit(u32 nDecDevNum, u32 nEncDevNum);
u16 HardCodecDestroy();
u16 HardEnvInitial(u32 dwHWtype);

s32    ScaleVideoCap(u32 dwVidSrcPort,u8 byType, u8 byValue); /* ��Ƶ�ɼ����� */

//////////////////////////////////////////////////////////////////////////
//�ӿ�FPGA����
    /*�������� SetVideoOutFromVidIn
    ��    �ܣ� �л��������Ƶ��ָ������ӿ������
    ��    ���� u32 dwFromVidIn������ӿ�����VIDIO_HDMI0�ȣ�ֻ��ָ��һ���ӿ�
               u32 dwVidOut   ������ӿ�����VIDIO_HDMI0�ȣ���ָ������ӿ�
                                �磨VIDIO_YPbPr0|VIDIO_HDMI0��
               TVidSrcInfo* ptOutInfo:�����Ƶ��ʽ����ΪNULL
    �� �� ֵ�� u16 :0 �ɹ������� ʧ�ܡ�
    ˵    ���� ��һ�Զ࣬���ܶ�Զ����һ*/
u16 SetVideoOutFromVidIn(u32 dwFromVidIn, u32 dwVidOut, TVidSrcInfo* ptOutInfo = NULL);
//////////////////////////////////////////////////////////////////////////
    /*�������� SetVideoOutFromVidDec
    ��    �ܣ� �л���������������ݵ������ӿڡ�
    ��    ���� u32 dwFromDecVP����Ϊ����Ľ�������VPID (0 , 1, 2)
                             ***HD2��������Ҫ��ϸָ������ͨ��
               u32 dwVidOut   ������ӿ�����VIDIO_HDMI0�ȣ���ָ������ӿ�
               TVidSrcInfo* ptOutInfo�������Ƶ��ʽ������ΪNULL
    �� �� ֵ�� u16 
    ˵    ���� */
u16 SetVideoOutFromVidDec(u32 dwFromDecVP, u32 dwVidOut, TVidSrcInfo* ptOutInfo = NULL);
/*=============================================================================
  �� �� ���� GetVGAPhaseClock
  ��    �ܣ� ��ȡVGAԴ��λʱ�Ӻͷֱ���
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVGAPort
             TVidSrcInfo* ptVGAInfo
             u32& dwPhaseValue
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/6/17     1.0	        ��ѩ��                   ����
=============================================================================*/
u16 GetVGAPhaseClock(u32 dwVGAPort, TVidSrcInfo* ptVGAInfo, u32& dwPhaseValue);
/*=============================================================================
  �� �� ���� SetVGAPhaseClock
  ��    �ܣ� ����VGAԴ��λʱ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVGAPort
             u32 dwPhaseValue
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/6/17     1.0	        ��ѩ��                   ����
=============================================================================*/
u16 SetVGAPhaseClock(u32 dwVGAPort, u32 dwPhaseValue);
/*=============================================================================
  �� �� ���� GetVGAFiltStatus
  ��    �ܣ� ��ȡVGAԴ�˲�״̬
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVGAPort
             TVidSrcInfo* ptVGAInfo
             u32& dwFiltSet
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/6/17     1.0	        ��ѩ��                   ����
=============================================================================*/
u16 GetVGAFiltStatus(u32 dwVGAPort, TVidSrcInfo* ptVGAInfo, u32& dwFiltSet);
/*=============================================================================
  �� �� ���� SetVGAFiltStatus
  ��    �ܣ� ����VGAԴ�˲�
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVGAPort
             u32 dwFiltSet
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/6/17     1.0	        ��ѩ��                   ����
=============================================================================*/
u16 SetVGAFiltStatus(u32 dwVGAPort, u32 dwFiltSet);

/*=============================================================================
  �� �� ���� SetVDecTosMaxBufNum
  ��    �ܣ� ����TOS����������״̬ʱ���ѻ�������֡��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwBufferMax 
             s32 nIndex
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/8/28     1.0	        ��ѩ��                   ����
=============================================================================*/
void SetVDecTosMaxBufNum(u32 dwBufferMax, s32 nIndex);

/*=============================================================================
  �� �� ���� GetVidPortInfo
  ��    �ܣ� ��ȡ��ƵԴ�˿ں���ʽ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVidPortType:��ѯ�ӿڣ���VIDIO_DVI0��
             TVidPortInfo* ptVidPortInfo:����ʵ�ʶ˿ں���ʽ
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2011/4/27     1.0	        ��ѩ��                   ����
=============================================================================*/
void GetVidPortInfo(u32 dwVidPortType, TVidPortInfo* ptVidPortInfo);

void CloseTaos(u32 nDevId);

/*�������� SetMicVol
��    �ܣ� ��ũ��˷����棬��Χ0-50
��    ���� u32 dwAudPort
           s32 nVol
�� �� ֵ�� API void 
˵    ���� */
API void SetMicVol(u32 dwAudPort, s32 nVol);

API s32 GetMicVol();

//����h600����ͷ��ʽ
API void SetVidInPortStd(TVidSrcInfo* ptCamInfo);

//��ȡ���DVI�ӿ���ʵ�ʵ������ӿ�����
void GetVidOutPortType(u32 dwDVIId, u32 &dwRealPortType);
/*�������� SetCanonPowerOn
��    �ܣ� ��ũ��˷�����ӿ�48v���翪�ؽӿ�ʵ��
��    ���� BOOL32 bEnable=TRUE
�� �� ֵ�� 
˵    ���� */
void SetCanonPowerOn(u32 dwAudPort, BOOL32 bEnable=TRUE);

//��ȡ���������״̬
API BOOL32 GetDigitalMicStatus(u32 dwAudPort);

//��ȡ3.5�ڲ���״̬  bIsAudIn = TRUE:�ɼ���  FALSE:���ſ�
API BOOL32 Get35InOrOutStatus(BOOL32 bIsAudIn);

API BOOL32 GetTRS635Status(u32 dwAudPort);

//��ȡHDMI��Ƶ��״̬
API BOOL32 GetAudHdmiStatus(u32 dwAudPort);

/*��ȡSDI�ӿ����� SDITYPE_ININ SDITYPE_INOUT*/
API u32 GetHDMtSDIIntType();

/*���ò��ŷֱ��ʸı���Ϣ֪ͨ*/
API void SetNtscPalChangeCallBack(CHANGECALLBACK pChangeProc);

//����оƬ����֪ͨ�ص�
API void SetCpuResetNotify(CpuResetNotify fNotify);
//����ƵԴ��������ʱ����ʱ����ͼ��:EN_PLAY_LAST/EN_PLAY_BLUE
u16    SetVidPlayPolicy(u32 dwTimeout = 5, u32 dwPlayType = EN_PLAY_LAST);

//�Ƿ�����ȫ��OSD
API void UseFullOSD(BOOL32 bFullOsd = TRUE);
//HDMI�����HDMI��DVI�ź�ѡ��
API void HDMIDVISwitch(BOOL32 bHDMI = TRUE);
//����SD�ź������ʽ
API void SetSDOutType(u32 dwOutType = VID_OUTTYPE_ORIGIN);	   //�����μ�codecwrapperdef_hd
//����������豸
API void RebootCodecDev(u32 dwDevID = CODECDEV_VIDENC);	   //�����μ�codecwrapperdef_hd
//�ж�2��D���֮ǰ�汾
API void SetHardWareVer(BOOL32 bBefore2ndD = FALSE);
s32 HardMPUInit(u32 dwHWType_Mode); //ָ�������������Լ�����ģʽ:codecwrapperdef_hd:enBoardType
s32 HardMPUInitDev(u32 nEncTos, u32 nDecTos, u32 nDspNum);
s32 HardMPUDestroy();
//�����ն˳�ʼ��
s32 HardMTInit(u32 nMode);
s32 HardMTDestroy();
//�ر���ָ���Ƶ��ʾ
void SetVideoShow(BOOL32 bShow);
//���ý���ȼ� �μ� codecwrapperdef_hd.h�� NF_MODE_DISABLE etc�����Ե�һ·��Ч
void SetNfMode(u32 dwMode);
//���ý��뿪�� �Ƽ�ʹ�� TRUE
void SetNfEnable(BOOL32 bOpen);
#endif