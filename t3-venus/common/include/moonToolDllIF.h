// moonToolDllIF.h : main header file for the MOONTOOLDLL DLL
/*---------------------------------------------------------------------
* 文 件	名： moonToolDllIF.h
* 功    能： moonToolDll 的接口文件 
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2014.11.21   1.0          吴蒨蒨        创建
----------------------------------------------------------------------*/

#ifndef MOONTOOLDLLIF_HEAD_H
#define MOONTOOLDLLIF_HEAD_H 


#ifdef  MOONTOOLDLL_EXPORTS
#define MOONTOOLDLL_API extern "C" __declspec(dllexport)
#else 
#define MOONTOOLDLL_API extern "C" __declspec(dllimport)
#endif

namespace MOONTOOL
{
 
	////////////MoonToolDll 所有接口/////////////////////////////
	//
	
	/*---------------------------------------------------------------------
	* 功    能：是否已经初始化moonTool环境
	* 输入参数：
	* 输出参数：
	* 返 回 值：
	* 备    注：  
	* 日期			版本		修改人		修改记录
	* 2014.11.21    1.0         吴蒨蒨        创建
	----------------------------------------------------------------------*/
	MOONTOOLDLL_API BOOL _stdcall IsInitMoonTool();


	/*---------------------------------------------------------------------
	* 功    能：初始化moonTool环境
	* 输入参数：hNotifyWnd  dll外部接受dll消息通知的窗口
	* 输出参数：
	* 返 回 值：
	* 备    注：  
	* 日期			版本		修改人		修改记录
	* 2014.11.21    1.0         吴蒨蒨        创建
	----------------------------------------------------------------------*/
	MOONTOOLDLL_API void _stdcall InitMoonTool( HWND hNotifyWnd );


	/*---------------------------------------------------------------------
	* 功    能：销毁moonTool 
	* 输入参数：
	* 输出参数：
	* 返 回 值：
	* 备    注：  
	* 日期			版本		修改人		修改记录
	* 2014.11.21    1.0         吴蒨蒨        创建
	----------------------------------------------------------------------*/
	MOONTOOLDLL_API void _stdcall DestroyMoonTool();



	/*---------------------------------------------------------------------
	* 功    能：登陆moon90服务器
	* 输入参数：
	* 输出参数：
	* 返 回 值：成功返回NO_ERROR（0），失败返回错误码
	* 备    注：  
	* 日期			版本		修改人		修改记录
	* 2014.11.21    1.0         吴蒨蒨        创建
	----------------------------------------------------------------------*/
	MOONTOOLDLL_API UINT _stdcall ConnectMoon( DWORD dwCnsIP, DWORD dwCnsPort = 60002 );
 
 

	/*---------------------------------------------------------------------
	* 功    能：所有moonTool相关的消息都应通过此接口来处理
	* 输入参数：pMsg消息指针
	* 输出参数：
	* 返 回 值：若MOONTOOL处理该消息，则返回TRUE，未处理返回FALSE
	* 备    注：  
	* 日期			版本		修改人		修改记录
	* 2014.11.21    1.0         吴蒨蒨        创建
	----------------------------------------------------------------------*/
	MOONTOOLDLL_API BOOL _stdcall HandleMoonToolMsg( MSG* pMsg );
 
}

 
#endif 
