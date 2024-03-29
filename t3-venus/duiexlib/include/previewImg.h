/*---------------------------------------------------------------------
* 文 件	名：previewImg.h
* 功    能：图片预览 
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2013.3.7      1.0         俞锦锦        创建
----------------------------------------------------------------------*/
#pragma once
 
class UILIB_API CPreviewImg: public CControlUI
{
public:
	CPreviewImg();
	CPreviewImg( HWND pParent );
	~CPreviewImg(void);

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

public: 
	/*---------------------------------------------------------------------
	* 功    能：设置预览窗口大小及坐标
	* 输入参数：Rc位置
	* 输出参数：
	* 返 回 值：成功返回S_OK,失败返回错误码
	* 备    注： pRc 是相对于屏幕的坐标
	* 日期			版本		修改人		修改记录
	* 2013.3.4      1.0         俞锦锦        创建
	----------------------------------------------------------------------*/
	void SetPrevRect( RECT &Rc ); 
 
	
	/*---------------------------------------------------------------------
	* 功    能：设置预览窗口及坐标
	* 输入参数：hwndPreview 预览窗口， Rc位置
	* 输出参数：
	* 返 回 值：成功返回S_OK,失败返回错误码
	* 备    注：  pRc 是相对于屏幕的坐标
	* 日期			版本		修改人		修改记录
	* 2013.3.4      1.0         俞锦锦        创建
	----------------------------------------------------------------------*/
	void  SetPrevWindow( HWND hwndPreview, RECT&Rc );

 
	/*-------------------------------------------------------------------
	* 功    能：开始预览 
	* 输入参数：szFile 要预览的文件
	* 输出参数：
	* 返 回 值：成功返回S_OK,失败返回错误码
	* 备    注：设置过预览窗口和位置后再调用该接口 
	* 日期			版本		修改人		修改记录
	* 2013.3.4      1.0         俞锦锦        创建
	-------------------------------------------------------------------*/
	LONG DoPreview(  LPCTSTR  szFile  );

	LONG DoPreview( RECT &rectPreview, LPCTSTR szFile  );
	 
	LONG DoPreview( HWND hWnd, RECT &rectPreview, LPCTSTR szFile ) ;

	void PaintBkImage(HDC hDC);

	void PaintText(HDC hDC);

	virtual void DoEvent(TEventUI& event);

	/*-------------------------------------------------------------------
	* 功    能：停止预览文件
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 
	* 备    注：
	* 日期			版本		修改人		修改记录
	* 2013.3.4      1.0         俞锦锦        创建
	-------------------------------------------------------------------*/
	void Unload();

	/*-------------------------------------------------------------------
	* 功    能：图片绘制
	* 输入参数：  
	* 输出参数：  
	* 返 回 值： 
	* 备    注： 无
	* 日期			版本		修改人		修改记录
	* 2013.6.05      1.0         刘德印        创建
	-------------------------------------------------------------------*/
	void DrawImage(HDC hDC, const RECT& rc);

	void Draw();


	//获取图片缩略图
	LONG GetThumb( LPCTSTR szFile /*= NULL */,OUT HBITMAP &hbt,OUT WTS_ALPHATYPE &alpha  );
	 
	/*-------------------------------------------------------------------
	* 功    能：适配预览图片大小,同时调整图片位置以居中显示
	* 输入参数：  
	* 输出参数：  
	* 返 回 值： 
	* 备    注： 若图片大于显示区域，则等比缩小图片
				 若图片小于显示区域，则按照图片原大小显示
	* 日期			版本		修改人		修改记录
	* 2013.3.18      1.0         俞锦锦        创建
	-------------------------------------------------------------------*/
	void  AdaptImg ( LPCTSTR szFile ); 

	/*-------------------------------------------------------------------
	* 功    能：循环绘制图片
	* 输入参数：  
	* 输出参数：  
	* 返 回 值： 
	* 备    注： 循环绘制Preview图片
	* 日期			版本		修改人		修改记录
	* 2013.6.05      1.0         刘德印        创建
	-------------------------------------------------------------------*/
	void DoPaint(HDC hDC, const RECT& rcPaint);

private:
	ULONG_PTR m_Token;

	CRect     m_rcImg;//图片显示位置
    
	HWND m_hWndThis;
	CRect     m_rcDraw;//图片

	CPaintManagerUI paint_manager_;

};

