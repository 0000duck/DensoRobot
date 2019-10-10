
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


#include <afxsock.h>            // MFC �׽�����չ



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

#define WM_Voice (WM_USER + 3)  //���������������ؽ��

#define WM_BaseRbtSend (WM_USER + 4)  //������������Ϣ����
#define WM_MoveRbtSend (WM_USER + 5)  //�˶���������Ϣ����
#define WM_VisionSend (WM_USER + 6)  //�Ӿ�������Ϣ����
#include "JIMIDlg.h"

//����ת��
char * CstringToChar(CString str);//cstring ת����char *
string toString(CString cs);
CString toCString(string str);
void CStringSplit(CString &strSource, CString *strDes, CString strSplitChar);//split������Ӧ��

#define Sigle_MOLDE 0
#define X_Y_MOLDE 1

#define Approch_P 1 //�ӽ��õ������˶�
#define Approch_L 2 //�ӽ��õ�ֱ���˶�
#define Depart_P 3  //Զ�뵱ǰ��λ
#define Move_P 4    //PTP�岹�ƶ����õ㣬���
#define Move_L 5    //ֱ�߲岹�ƶ����õ㣬��ȫ

#define Axis_1_X 1 
#define Axis_2_Y  2 
#define Axis_3_Z  3  
#define Axis_4_RX  4    
#define Axis_5_RY  5    
#define Axis_6_RZ  6    

#define RbtReady 0 //������׼��
#define RbtMarkGet 1 //ȡ��λ�ö�λ
#define RbtMarkPut 2 //����λ�ö�λ
#define RbtGet 3  //ȡ��
#define RbtPut 4    //����

extern CJIMIDlg* pGlobal;//������Ի����һ��ȫ��ָ��
