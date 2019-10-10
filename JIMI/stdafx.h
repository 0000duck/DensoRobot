
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#include <afxsock.h>            // MFC 套接字扩展



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#define WM_RunLog (WM_USER + 1)

#define WM_ReadWeighPortRet (WM_USER + 2)//

#define WM_Voice (WM_USER + 3)  //用于语音播报称重结果

#define WM_BaseRbtSend (WM_USER + 4)  //基础机器人消息播放
#define WM_MoveRbtSend (WM_USER + 5)  //运动机器人消息播放
#define WM_VisionSend (WM_USER + 6)  //视觉基础消息播放
#include "JIMIDlg.h"

//类型转换
char * CstringToChar(CString str);//cstring 转换成char *
string toString(CString cs);
CString toCString(string str);
void CStringSplit(CString &strSource, CString *strDes, CString strSplitChar);//split函数的应用

#define Sigle_MOLDE 0
#define X_Y_MOLDE 1

#define Approch_P 1 //接近该点曲线运动
#define Approch_L 2 //接近该点直线运动
#define Depart_P 3  //远离当前点位
#define Move_P 4    //PTP插补移动到该点，最快
#define Move_L 5    //直线插补移动到该点，安全

#define Axis_1_X 1 
#define Axis_2_Y  2 
#define Axis_3_Z  3  
#define Axis_4_RX  4    
#define Axis_5_RY  5    
#define Axis_6_RZ  6    

#define RbtReady 0 //机器人准备
#define RbtMarkGet 1 //取料位置定位
#define RbtMarkPut 2 //放料位置定位
#define RbtGet 3  //取料
#define RbtPut 4    //放料

extern CJIMIDlg* pGlobal;//针对主对话框的一个全局指针
