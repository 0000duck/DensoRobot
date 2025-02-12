﻿// JIMIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "JIMIDlg.h"
#include "afxdialogex.h"
#include<FSTREAM>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <mmsystem.h>
#include "afxdialogex.h"
#include "math.h"
#include "RobotControldlg.h"
#include "VisionTestdlg.h"
#include <afxsock.h>


#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

map<int, CString>CJIMIDlg::SyllableMap;
map<int, CString>CJIMIDlg::BindMap;
BOOL Imei3Flag;
CRITICAL_SECTION Sec_BaseRbtSocket;
CRITICAL_SECTION Sec_MoveRbtSocket;
CRITICAL_SECTION Sec_VisionSocket;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJIMIDlg 对话框



CJIMIDlg::CJIMIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_JIMI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_JIMI);
}

CJIMIDlg::~CJIMIDlg(void)
{
	KillTimer(1);
}
void CJIMIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Run, m_LIST_Run);
	DDX_Control(pDX, IDC_LIST_Warning, m_LIST_Warning);
	DDX_Control(pDX, IDC_COMBO_COM, c_PortCom);
	DDX_Control(pDX, IDC_BTN_StateView, m_StateView);
	DDX_Control(pDX, IDC_BTN_UWView, m_UWView);
	DDX_Control(pDX, IDC_BTN_VisonView, m_VisionView);
	DDX_Control(pDX, IDC_BTN_NULL_View, m_NullView);
	DDX_Control(pDX, IDC_BTN_Down_View, m_DownView);
	DDX_Control(pDX, IDC_TAB_Mian, m_Maintab);
}

BEGIN_MESSAGE_MAP(CJIMIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_RunLog, &CJIMIDlg::OnRunlog)
	ON_MESSAGE(WM_Voice, &CJIMIDlg::OnVoice)
	ON_MESSAGE(WM_BaseRbtSend, &CJIMIDlg::OnBaseRbtSend)
	ON_MESSAGE(WM_MoveRbtSend, &CJIMIDlg::OnMoveRbtSend)
	ON_MESSAGE(WM_VisionSend, &CJIMIDlg::OnVisionSend)
	ON_MESSAGE(WM_VisUpdataBTN, &CJIMIDlg::OnVisUpdataStatue)
	ON_MESSAGE(WM_VisNumLog, &CJIMIDlg::OnVisLogStatue)

	ON_BN_CLICKED(IDC_BTN_ClearError, &CJIMIDlg::OnBnClickedBtnClearerror)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Mian, &CJIMIDlg::OnSelchangeTabMian)
	ON_WM_NCLBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON_COMOK2, &CJIMIDlg::OnBnClickedButtonComok2)
	ON_BN_CLICKED(IDC_BTM_RunMain, &CJIMIDlg::OnBnClickedBtmRunmain)
	ON_BN_CLICKED(IDC_BTM_CycleStop, &CJIMIDlg::OnBnClickedBtmCyclestop)
	ON_BN_CLICKED(IDC_BTM_Stop, &CJIMIDlg::OnBnClickedBtmStop)
	ON_BN_CLICKED(IDC_BTM_InitialALL, &CJIMIDlg::OnBnClickedBtmInitialall)
	ON_STN_CLICKED(IDC_STATIC_logo, &CJIMIDlg::OnStnClickedStaticlogo)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CJIMIDlg 消息处理程序


BOOL CJIMIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	pGlobal = (CJIMIDlg*)((CJIMIApp*)AfxGetApp())->GetMainWnd();
	//UserLogin userDlg;
	//userDlg.DoModal();
	//if (userDlg.sUSER == _T(""))
	//{
	//	CDialog::OnCancel();
	//	return FALSE;
	//}
	bJimiAPPStart = true;
	bInitialALL = false;
	bRunAutoThread = false;
	bCycleStop = false;
	bRunStop = false;
	bVisionCon = false;
	iRbtStatue = RbtReady;
	iProcessTimes = 1;
	InitializeCriticalSection(&Sec_BaseRbtSocket);
	InitializeCriticalSection(&Sec_MoveRbtSocket);
	InitializeCriticalSection(&Sec_VisionSocket);
	bmark = true;
	for (int i = 0; i < 10; i++)
	{
		pJimiThread[i] = NULL;
	}

//	ShowWindow(SW_MAXIMIZE);//对话框默认最大化弹出
	//初始化串口列表
	GetLocalHostIPName(m_PCName,m_PCIP);
	SetDlgItemText(IDC_PCIP_EDIT, m_PCIP);

	FindCommPort((CComboBox*)GetDlgItem(IDC_COMBO_COM), sComPort, 1);
	FontInit();
//	AddToRunList(_T("登录人员：")+ userDlg.sUSER);
	IniSystemini();
	initMainTab();
	EventInitial();//初始化事件 
	IniVoice();
	GetDlgItem(IDC_BTM_InitialALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_RunMain)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_CycleStop)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTM_Stop)->EnableWindow(FALSE);
	
	pJimiThread[0] = AfxBeginThread(AutoRunThread, this);
	pJimiThread[1] = AfxBeginThread(InitialALLThread, this);
	SetTimer(1, 500, NULL);
	//AddToRunList(_T("初始化完成！！"));
	pGlobal->UWdlg.bNeedReady = 1;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJIMIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_MOVE || nID == 0xF012)//禁止拖动
	{
		return;
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CJIMIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJIMIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//初始化串口
HANDLE CJIMIDlg::InitCom(CString comName)
{
	HANDLE hCom;
	hCom = CreateFile(L"\\\\.\\" + comName,//COM口
		GENERIC_READ | GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,
		OPEN_EXISTING, //打开而不是创建
		0, //同步方式
		NULL);
	if (hCom == INVALID_HANDLE_VALUE)
	{
		//SetRicheditText(comName+L"串口初始化失败！", 1);
		MessageBox(L"串口初始化失败！", L"提示信息", NULL);
		return NULL;
	}
	SetupComm(hCom, 100, 100); //输入缓冲区和输出缓冲区的大小都是100
	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	//在读一次输入缓冲区的内容后读操作就立即返回，
	//而不管是否读入了要求的字符。
	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier = 1500;
	TimeOuts.WriteTotalTimeoutConstant = 1500;
	SetCommTimeouts(hCom, &TimeOuts); //设置超时

	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 9600; //波特率为9600
	dcb.ByteSize = 8; //每个字节有8位
	dcb.Parity = NOPARITY; //无奇偶校验位
	dcb.StopBits = ONESTOPBIT; //1个停止位
	SetCommState(hCom, &dcb);
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	//SetRicheditText(L"串口初始化成功！", 0);
	return hCom;
}

//关闭串口
int CJIMIDlg::CloseCom(HANDLE handler)
{
	return CloseHandle(handler);
}

//获取当前串口号
void CJIMIDlg::GetCommPort(CComboBox *pComboBox, CString &ComNo)
{
	int nSel;
	nSel = pComboBox->GetCurSel();
	pComboBox->GetLBText(nSel, ComNo);

	if (ComNo == "")
	{
		MessageBox(L"请先选择串口号！", L"提示信息", NULL);
	}
}

/*串口通用操作*/
//从注册表中寻找已经注册串口号然后展示出来
void CJIMIDlg::FindCommPort(CComboBox *pComboBox, CString &ComNo, int PortNO)
{
	//先获取当前串口号
	int cur = 0;
	int nSel;
	BOOL curflag = TRUE;
	nSel = pComboBox->GetCurSel();
	if (nSel >= 0)
	{
		pComboBox->GetLBText(nSel, ComNo);
	}

	//先清空一下列表
	pComboBox->ResetContent();

	HKEY hKey;
#ifdef _DEBUG
	ASSERT(pComboBox != NULL);
	pComboBox->AssertValid();
#endif
	if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey) == ERROR_SUCCESS) // 打开串口注册表
	{
		int i = 0;
		char portName[256], commName[256];
		DWORD dwLong, dwSize;
		while (1)
		{
			dwLong = dwSize = sizeof(portName);
			if (::RegEnumValue(hKey, i, LPWSTR(portName), &dwLong, NULL, NULL, (PUCHAR)commName, &dwSize) == ERROR_NO_MORE_ITEMS) // 枚举串口
			{
				break;
			}
			cur = i;
			pComboBox->AddString(LPWSTR(commName));
			i++;
		}
		pComboBox->SetCurSel(cur);
		RegCloseKey(hKey);
	}
}

//获取本机IP和地址
int CJIMIDlg::GetLocalHostIPName(CString &sLocalName, CString &sIpAddress)
{
	char szLocalName[256];//定义
	WSADATA wsaData;//定义套接字存储变量
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)//<span class="con">windows初始化socket网络库，申请2，0的版本，windows socket编程必<img class="selectsearch-hide" id="selectsearch-icon" alt="搜索" src="http://img.baidu.com/img/iknow/qb/select-search.png" />须先初始化。如果出错,则返回0</span>
	{
		if (gethostname(szLocalName, sizeof(szLocalName)) != 0)//产生错误
		{
			sLocalName = _T("没有取得");
			WSACleanup();
			return GetLastError();
		}
		else
		{
			sLocalName = szLocalName;//用sLocalName变量存储获得的计算机名称
			struct hostent FAR * lpHostEnt = gethostbyname(CStringA(sLocalName));
			if (lpHostEnt == NULL)//错误
			{
				sIpAddress = _T("");
				WSACleanup();
				return GetLastError();
			}
			LPSTR lpAddr = lpHostEnt->h_addr_list[0];//获取IP地址
			if (lpAddr)
			{
				struct in_addr inAddr;
				memmove(&inAddr, lpAddr, 4);
				sIpAddress = inet_ntoa(inAddr);//转换为标准格式
				if (sIpAddress.IsEmpty())
				{
					sIpAddress = _T("没有取得");
					WSACleanup();
					return 1;
				}
			}
		}
	}
	WSACleanup();//清空套接字初始化变量
	return 0;
}

UINT CJIMIDlg::ComRxThread(LPVOID pParam)
{
	CJIMIDlg *pThisThreadDlg = (CJIMIDlg *)pParam;
	int res;
	DWORD dwError = 0;
	DWORD dwEvtMask = 0;
	DWORD dwReadSize = 0;
	char *RxBuffer, buf[1024];;
	BOOL bRet;
	CString str, temp;
	str = _T("");
	temp = _T("");
	////设置接收时间掩码
	//if (SetCommMask(pThisThreadDlg->port1handler, EV_RXCHAR) == 0) {
	//	pThisThreadDlg->SetDlgItemText(IDC_WeightView, _T("电子秤未连接"));
	//	AfxMessageBox(_T("设置接收时间掩码出错"));
	//	return 1;
	//}
	while (TRUE)
	{
		memset(buf,0, sizeof(buf));
		RxBuffer = buf;
		bRet = ReadFile(pThisThreadDlg->port1handler, RxBuffer, 512, &dwReadSize, NULL);
		if (bRet)
		{
			if (dwReadSize != 0)
			{
				str = RxBuffer;
				str.Trim();//清除空格等
				str.Replace(_T("\r"), _T(""));//清除换行符号等
				str.Replace(_T("\n"), _T(""));//清除换行符号等
				temp.Format(_T("收到串口消息:  %s"), str);
			//	pThisThreadDlg->DealtSerialData(str);

				str = _T("");
			}
			else
			{
			//	pThisThreadDlg->m_newWeightValue = _T("");
				pThisThreadDlg->SetDlgItemText(IDC_WeightView, _T("电子秤未连接"));
			}
		}
		else
		{
		//	pThisThreadDlg->m_newWeightValue = _T("");
			pThisThreadDlg->SetDlgItemText(IDC_WeightView, _T("电子秤未连接"));
			OutputDebugString(_T("ReadFile 读文件出错/r/n"));
		}
		PurgeComm(pThisThreadDlg->port1handler, PURGE_RXABORT | PURGE_RXCLEAR);
		Sleep(140);
		str = _T("");
	}
	return 0;
}


bool CJIMIDlg::IniVoice()
{
	pVoice = NULL; //初始化COM 

	if (FAILED(CoInitialize(NULL)))
	{
		AfxMessageBox(_T("Error to intiliaze COM"));
		return false;
	}
	//初始化SAPI HRESULT
	hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	ISpObjectToken * pSpObjectToken = NULL;
	if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, L"language=804", NULL, &pSpObjectToken)))//804代表中文 
	{
		pVoice->SetVoice(pSpObjectToken);//声音大小
		pVoice->SetRate(1);//语速
		pSpObjectToken->Release();
	}
	else {
		AfxMessageBox(_T("没有安装微软语音库!"));
		return false;
	}
	//朗读编辑框中的文字 
	//if (SUCCEEDED(hr))
	//{
	//	CString strText = _T("语音测试");//引号是朗读的话 可以是中文  
	//	PlayVoice(strText);
	//  hr = pVoice->Speak(strText.AllocSysString(), 0, NULL);
	//	pVoice->Release();
	//	pVoice = NULL;
	//}
	return true;
}


void CJIMIDlg::AddToRunList(CString str)
{
	//添加运行日志
	/**/
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString strTime;
	strTime.Format(_T("%02d:%02d:%02d  %s"), time.wHour, time.wMinute, time.wSecond, str);

	if (m_LIST_Run.GetCount() > 100)
	{
		for (int i = m_LIST_Run.GetCount(); i >= 50; i--)
		{
			m_LIST_Run.DeleteString(i - 1);
		}
	}
	m_LIST_Run.InsertString(0, strTime);

	char * buffer = new char[1024];
	memset(buffer, 0, 1024);
    
	/////////对数据长度做判断，假设数据长度过长，则打印的日志取前面的数据/////
	if (str.GetLength() > 512)
	{
		str = str.Left(512);
	}
	/////////对数据长度做判断，假设数据长度过长，则打印的日志取前面的数据/////
	va_list list;
	va_start(list, str);
	
	const char* cstr;
	char temp[1024];
	::wsprintfA(temp, "%ls", (LPCTSTR)str);
	cstr = temp;
	vsprintf_s(buffer, 1024, cstr, list);
	va_end(list);

	::PostMessage(this->m_hWnd, WM_RunLog, (WPARAM)buffer, 0);

}
void CJIMIDlg::AddToErrorList(CString str)
{
	//添加运行日志
	/**/
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString strTime;
	strTime.Format(_T("%02d:%02d:%02d  %s"), time.wHour, time.wMinute, time.wSecond, str);

	m_LIST_Warning.InsertString(0, strTime);
	if (m_LIST_Warning.GetCount())
	{
		GetDlgItem(IDC_BTN_ClearError)->EnableWindow(TRUE); 
	}
		
	char * buffer = new char[1024];
	memset(buffer, 0, 1024);

	va_list list;
	va_start(list, str);

	const char* cstr;
	char temp[100];
	::wsprintfA(temp, "%ls", (LPCTSTR)str);
	cstr = temp;
	vsprintf_s(buffer, 1024, cstr, list);
	va_end(list);

	::PostMessage(this->m_hWnd, WM_RunLog, (WPARAM)buffer, 1);
}
void CJIMIDlg::PlayVoice(CString str)
{
	char * buffer = new char[1024];
	memset(buffer, 0, 1024);
	va_list list;
	va_start(list, str);

	const char* cstr;
	char temp[100];
	::wsprintfA(temp, "%ls", (LPCTSTR)str);
	cstr = temp;
	vsprintf_s(buffer, 1024, cstr, list);
	va_end(list);

	::PostMessage(this->m_hWnd, WM_Voice, (WPARAM)buffer, NULL);
}
void CJIMIDlg::BaseRbtSend(CString str)
{
	char * buffer = new char[1024];
	memset(buffer, 0, 1024);
	va_list list;
	va_start(list, str);

	const char* cstr;
	char temp[100];
	::wsprintfA(temp, "%ls", (LPCTSTR)str);
	cstr = temp;
	vsprintf_s(buffer, 1024, cstr, list);
	va_end(list);

	::PostMessage(this->m_hWnd, WM_BaseRbtSend, (WPARAM)buffer, NULL);
}

void CJIMIDlg::MoveRbtSend(CString str)
{
	char * buffer = new char[1024];
	memset(buffer, 0, 1024);
	va_list list;
	va_start(list, str);

	const char* cstr;
	char temp[100];
	::wsprintfA(temp, "%ls", (LPCTSTR)str);
	cstr = temp;
	vsprintf_s(buffer, 1024, cstr, list);
	va_end(list);

	::PostMessage(this->m_hWnd, WM_MoveRbtSend, (WPARAM)buffer, NULL);
}
void CJIMIDlg::VisionSend(CString str)
{
	char * buffer = new char[1024];
	memset(buffer, 0, 1024);
	va_list list;
	va_start(list, str);

	const char* cstr;
	char temp[100];
	::wsprintfA(temp, "%ls", (LPCTSTR)str);
	cstr = temp;
	vsprintf_s(buffer, 1024, cstr, list);
	va_end(list);

	::PostMessage(this->m_hWnd, WM_VisionSend, (WPARAM)buffer, NULL);
}

void CJIMIDlg::VisBtnUpdata()
{
	::PostMessage(this->m_hWnd, WM_VisUpdataBTN, NULL, NULL);
}
afx_msg LRESULT CJIMIDlg::OnVoice(WPARAM wParam, LPARAM lParam)
{
	char * pBuf = (char *)wParam;
	CString sVoice = CString(pBuf);
	hr = pVoice->Speak(sVoice.AllocSysString(), 0, NULL);
	return 0;
}
afx_msg LRESULT CJIMIDlg::OnBaseRbtSend(WPARAM wParam, LPARAM lParam)
{
	char * pBuf = (char *)wParam;
	CString sMsg = CString(pBuf);
	pGlobal->BaseRbtSocket.SendMSG(sMsg);
	return 0;
}

afx_msg LRESULT CJIMIDlg::OnMoveRbtSend(WPARAM wParam, LPARAM lParam)
{
	char * pBuf = (char *)wParam;
	CString sMsg = CString(pBuf);
	pGlobal->RbtSocket.SendMSG(sMsg);
	return 0;
}

afx_msg LRESULT CJIMIDlg::OnVisionSend(WPARAM wParam, LPARAM lParam)
{
	char * pBuf = (char *)wParam;
	CString sMsg = CString(pBuf);
	pGlobal->VisMarkSocekt.SendMSG(sMsg);
	return 0;
}

afx_msg LRESULT CJIMIDlg::OnRunlog(WPARAM wParam, LPARAM lParam)
{
	//写日志
	char * pBuf = (char *)wParam;
	SYSTEMTIME time;
	GetLocalTime(&time);	
	try
	{
		CFile file;
		FILE* m_pStream = NULL;
		//CLineRead file;
		CStdioFile m_SFile;
		CFileFind m_FileFind;
		CString strLogMessage = CString(pBuf);
		CString m_sFileName;
		if (lParam == 0)
		{
			m_sFileName.Format(_T("%04d-%02d-%02d  Run.log"), time.wYear, time.wMonth, time.wDay);
		}
		else if (lParam == 1)
		{
			m_sFileName.Format(_T("%04d-%02d-%02d  Error.log"), time.wYear, time.wMonth, time.wDay );
		}

		CString m_sFilePath = _T(".\\LOG");
		//SYSTEMTIME time;
		//GetLocalTime(&time);
		CString strCurrentTime;
		strCurrentTime.Format(_T("%04d-%02d-%02d  %02d:%02d:%02d:%03d  "), time.wYear, time.wMonth, time.wDay,
			time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		strLogMessage = strCurrentTime + strLogMessage + _T("\r");// + "\r\n";

		if (!m_FileFind.FindFile(m_sFilePath))
		{
			CreateDirectory(m_sFilePath, NULL);
		}

		if (!m_SFile.Open(m_sFilePath + _T("\\") + m_sFileName, CFile::modeReadWrite | CFile::modeNoTruncate))
		{
			if (!m_SFile.Open(m_sFilePath + _T("\\") + m_sFileName,CFile::modeCreate | CFile::modeReadWrite | CFile::typeText | CFile::modeNoTruncate))
			{
				//AfxMessageBox("打开日志文件 %s 失败", m_sFilePath + "\\" + m_sFileName);
				return FALSE;
			}
		}
		m_SFile.SeekToEnd();

#ifdef UNICODE 
		CString strTmp = strLogMessage;
		int len = 0;
		char *buf = NULL;
		len = WideCharToMultiByte(CP_ACP, 0, strTmp, strTmp.GetLength(), NULL, 0, NULL, NULL) + 1;
		buf = new char[len];
		memset(buf, 0, len);
		WideCharToMultiByte(CP_ACP, 0, strTmp, strTmp.GetLength(), buf, len - 1, NULL, NULL);
#else
		CString strTmp = strLog;
		char *buf = NULL;
		int len = 0;
		len = strTmp.GetLength() + 1;//多分配一个存放结束符号
		buf = new char[len];
		memset(buf, 0, len);
		buf = strTmp.GetBuffer();
#endif

		m_SFile.Write(buf, strlen(buf));
		m_SFile.Close();
	}
	catch (CFileException *fileException)
	{
		if (pBuf) {
			delete[] pBuf;
		}
		return false;
	}
	if (pBuf) {
		delete[] pBuf;
	}
	return 0;
}

afx_msg LRESULT CJIMIDlg::OnVisUpdataStatue(WPARAM wParam, LPARAM lParam)
{
	char * pBuf = (char *)wParam;
	CString sMsg = CString(pBuf);
	pGlobal->Autouidlg.UpdataVisBTNstatue();
	return 0;
}
afx_msg LRESULT CJIMIDlg::OnVisLogStatue(WPARAM wParam, LPARAM lParam)
{
	CString str;
	int itotlenum,itruenum,ifalsenum,inullnum;
	int num;
	GetPrivateProfileString(_T("VisNumLog"), _T("totlenum"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	itotlenum = _ttoi(str);
	GetPrivateProfileString(_T("VisNumLog"), _T("truenum"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	itruenum = _ttoi(str);
	GetPrivateProfileString(_T("VisNumLog"), _T("falsenum"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ifalsenum = _ttoi(str);
	GetPrivateProfileString(_T("VisNumLog"), _T("nullnum"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	inullnum = _ttoi(str);

	itotlenum = itotlenum + 40;
	for (int i = 0; i < 40; i++)
	{
		switch (pGlobal->Visiondlg.iVisGetResult[i])
		{
		case 1:       itruenum = itruenum + 1;             break;
		case 2:       ifalsenum = ifalsenum + 1;           break;
		case 3:       inullnum = inullnum + 1;             break;

		default:
			break;
		}
	}
	str.Format(_T("%d"), itotlenum);
	WritePrivateProfileString(_T("VisNumLog"), _T("totlenum"), str, _T(".\\SystemInfo.ini"));
	str.Format(_T("%d"), itruenum);
	WritePrivateProfileString(_T("VisNumLog"), _T("truenum"), str, _T(".\\SystemInfo.ini"));
	str.Format(_T("%d"), ifalsenum);
	WritePrivateProfileString(_T("VisNumLog"), _T("falsenum"), str, _T(".\\SystemInfo.ini"));
	str.Format(_T("%d"), inullnum);
	WritePrivateProfileString(_T("VisNumLog"), _T("nullnum"), str, _T(".\\SystemInfo.ini"));
	return 0;
}

afx_msg LRESULT CJIMIDlg::OnUWLogStatue(WPARAM wParam, LPARAM lParam)
{
	CString str;
	int itotlenum, itruenum, ifalsenum, ierrornum,inullnum;
	int num;
	GetPrivateProfileString(_T("UWNumLog"), _T("totlenum"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	itotlenum = _ttoi(str);
	GetPrivateProfileString(_T("UWNumLog"), _T("truenum"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	itruenum = _ttoi(str);
	GetPrivateProfileString(_T("UWNumLog"), _T("falsenum"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ifalsenum = _ttoi(str);
	GetPrivateProfileString(_T("UWNumLog"), _T("erroenum"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ierrornum = _ttoi(str);
	GetPrivateProfileString(_T("UWNumLog"), _T("nullnum"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	inullnum = _ttoi(str);

	itotlenum = itotlenum + 40;
	for (int i = 0; i < 40; i++)
	{
		switch (pGlobal->Visiondlg.iVisGetResult[i])//
		{
		case 1:       itruenum = itruenum + 1;             break;
		case 2:       ifalsenum = ifalsenum + 1;           break;
		case 3:       ierrornum = ierrornum + 1;             break;
		case 4:       inullnum = inullnum + 1;             break;

		default:
			break;
		}
	}
	str.Format(_T("%d"), itotlenum);
	WritePrivateProfileString(_T("UWNumLog"), _T("totlenum"), str, _T(".\\SystemInfo.ini"));
	str.Format(_T("%d"), itruenum);
	WritePrivateProfileString(_T("UWNumLog"), _T("truenum"), str, _T(".\\SystemInfo.ini"));
	str.Format(_T("%d"), ifalsenum);
	WritePrivateProfileString(_T("UWNumLog"), _T("falsenum"), str, _T(".\\SystemInfo.ini"));
	str.Format(_T("%d"), ierrornum);
	WritePrivateProfileString(_T("UWNumLog"), _T("erroenum"), str, _T(".\\SystemInfo.ini"));
	str.Format(_T("%d"), inullnum);
	WritePrivateProfileString(_T("UWNumLog"), _T("nullnum"), str, _T(".\\SystemInfo.ini"));
	return 0;
}

void CJIMIDlg::OnBnClickedBtnClearerror()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LIST_Warning.ResetContent();
}

BOOL CJIMIDlg::IsDoubleNumber(const CString& strTest)
{
	CString str = strTest;

	// 根据需要，决定是否要去掉字串两端空格、TAB或换行符
	str.TrimLeft();
	str.TrimRight();

	if (str.IsEmpty())
		return FALSE;

	str.TrimLeft(L"0123456789.-");
	str.TrimRight(L"0123456789.-");
	// 如果去掉数字，字串为空，说明字串中全部是数字
	// 如果不允许第一个字符为0，前面再加一个判断if(str.GetAt(0) != '0') return FALSE;
	//if ((str.GetAt(0) < '0'||str.GetAt(0)>'9')&& str!="") 
	//return FALSE;
	if (str.IsEmpty())
		return TRUE;

	return FALSE;
}

//判断扫入的数据是否为数字或者字母
BOOL CJIMIDlg::IsNumber(const CString& strTest)
{
	CString str = strTest;

	// 根据需要，决定是否要去掉字串两端空格、TAB或换行符
	str.TrimLeft();
	str.TrimRight();

	if (str.IsEmpty())
		return FALSE;

	str.TrimLeft(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	str.TrimRight(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	// 如果去掉数字和字母后，字串为空，说明字串中全部是字母或数字，否则就是非法字符
	// 如果不允许第一个字符为0，前面再加一个判断if(str.GetAt(0) != '0') return FALSE;
	//if ((str.GetAt(0) < '0'||str.GetAt(0)>'9')&& str!="") 
	//return FALSE;
	if (str.IsEmpty())
		return TRUE;

	return FALSE;
}




void CJIMIDlg::FontInit()
{
	Font1.CreatePointFont(400, L"宋体");
	Font2.CreatePointFont(300, L"隶书");
	Font3.CreatePointFont(200, L"隶书");
	Font4.CreatePointFont(200, L"宋体");

//	GetDlgItem(IDC_WeightView)->SetFont(&Font1);	
}

void CJIMIDlg::initMainTab()
{
	m_Maintab.InsertItem(0, _T("机器人"));         // 插入第一个标签
	m_Maintab.InsertItem(1, _T("VISION"));
	m_Maintab.InsertItem(2, _T("UW"));
	m_Maintab.InsertItem(3, _T("扫码测试"));
	m_Maintab.InsertItem(4, _T("运行界面"));
	
	//m_Maintab.InsertItem(2, _T("其它"));
	CRect tabRect;   // 标签控件客户区的位置和大小

	RBTCTdlg.Create(IDD_DLG_RobotControl, &m_Maintab);    // 创建第一个标签页   
	Visiondlg.Create(IDD_DLG_VisionTest, &m_Maintab); // 创建第二个标签页  
	Autouidlg.Create(IDD_DLG_AutoUI, &m_Maintab); // 创建第三个标签页  
	UWdlg.Create(IDD_DLG_UW_Test, &m_Maintab); // 创建第四个标签页  
	CSdlg.Create(IDD_DLG_CodeScan, &m_Maintab); // 创建第五个标签页  
	m_Maintab.GetWindowRect(&tabRect);

	tabRect.left += 1;
	tabRect.right -= 3;
	tabRect.top += 28;
	tabRect.bottom -= 3;
	// 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为显示   
	RBTCTdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	// 根据调整好的tabRect放置m_androidDlg子对话框，并设置为隐藏   
	Visiondlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	Autouidlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	UWdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	CSdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	return;
}

void CJIMIDlg::ShowAutouidlg()
{
	CRect tabRect;    // 标签控件客户区的Rect   
	m_Maintab.GetWindowRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 3;
	tabRect.top += 28;
	tabRect.bottom -= 3;
	m_Maintab.SetCurSel(3);
	Autouidlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	RBTCTdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	Visiondlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	UWdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	CSdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
}

void CJIMIDlg::OnSelchangeTabMian(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CRect tabRect;    // 标签控件客户区的Rect   
	m_Maintab.GetWindowRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 3;
	tabRect.top += 28;
	tabRect.bottom -= 3;

	switch (m_Maintab.GetCurSel())
	{
	case 0://机器人
		RBTCTdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		Visiondlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		Autouidlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		UWdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		CSdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;  
	case 1://VISION
		RBTCTdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		Visiondlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		Autouidlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		UWdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		CSdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 2://UW
		Autouidlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		RBTCTdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		Visiondlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		UWdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);		
		CSdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 3://扫码测试
		Autouidlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		RBTCTdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		Visiondlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		UWdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		CSdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 4://运行界面
		Autouidlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		RBTCTdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		Visiondlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		UWdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		CSdlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	default:
		break;
	}
}


void CJIMIDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// 防止双击标题栏对话框变小的问题
	return;
	CDialogEx::OnNcLButtonDblClk(nHitTest, point);
}

void CJIMIDlg::EventInitial()
{
	Handle_GetPOS = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_GetPOS);

	Handle_FinishPOS[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_FinishPOS[0]);
	Handle_FinishPOS[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_FinishPOS[1]);

	Handle_RBTReadIO[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_RBTReadIO[0]);
	Handle_RBTReadIO[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_RBTReadIO[1]);
	Handle_RBTReadIO[2] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_RBTReadIO[2]);

	Handle_VisionRetPOS = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_VisionRetPOS);

	Handle_UWRetData = CreateEvent(NULL, FALSE, FALSE, NULL);
	Handle_UWRetData_reach_out = CreateEvent(NULL, FALSE, FALSE, NULL);
	Handle_UWRetData_out = CreateEvent(NULL, FALSE, FALSE, NULL);
	Handle_UWRetData_ack = CreateEvent(NULL, FALSE, FALSE, NULL);
	Handle_UWRetData_reach_in = CreateEvent(NULL, FALSE, FALSE, NULL);
	Handle_UWRetData_forklift_reach = CreateEvent(NULL, FALSE, FALSE, NULL);
	Handle_UWRetData_material_position_info = CreateEvent(NULL, FALSE, FALSE, NULL);

	ResetEvent(Handle_UWRetData);
	ResetEvent(Handle_UWRetData_reach_out);
	ResetEvent(Handle_UWRetData_out);
	ResetEvent(Handle_UWRetData_ack);
	ResetEvent(Handle_UWRetData_reach_in);
	ResetEvent(Handle_UWRetData_forklift_reach);
	ResetEvent(Handle_UWRetData_forklift_reach);

	Handle_CSRetData[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_CSRetData[0]);
	Handle_CSRetData[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_CSRetData[1]);
	Handle_CSRetData[2] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(Handle_CSRetData[2]);
}

void CJIMIDlg::OnBnClickedButtonComok2()
{
	// TODO: 在此添加控件通知处理程序代码
}

UINT CJIMIDlg::InitialALLThread(LPVOID pParam)
{
	CJIMIDlg *pThisThreadDlg = (CJIMIDlg *)pParam;
	while (pThisThreadDlg->bJimiAPPStart)
	{
		if (pThisThreadDlg->bInitialALL)
		{
			if (!pThisThreadDlg->InitialALL()) // 全部硬件初始化函数
			{
				
				pThisThreadDlg->AddToErrorList(_T("硬件初始化失败"));
				pThisThreadDlg->GetDlgItem(IDC_BTM_InitialALL)->EnableWindow(TRUE);
				pThisThreadDlg->GetDlgItem(IDC_BTM_RunMain)->EnableWindow(FALSE);
				pThisThreadDlg->GetDlgItem(IDC_BTM_CycleStop)->EnableWindow(FALSE);
				pThisThreadDlg->GetDlgItem(IDC_BTM_Stop)->EnableWindow(FALSE);
			}
			else
			{
				pThisThreadDlg->GetDlgItem(IDC_BTM_InitialALL)->EnableWindow(TRUE);
				pThisThreadDlg->GetDlgItem(IDC_BTM_RunMain)->EnableWindow(TRUE);
				pThisThreadDlg->GetDlgItem(IDC_BTM_CycleStop)->EnableWindow(FALSE);
				pThisThreadDlg->GetDlgItem(IDC_BTM_Stop)->EnableWindow(FALSE);
				pThisThreadDlg->AddToRunList(_T("初始化完成"));
			}

			pThisThreadDlg->bInitialALL = false;
		}
		Sleep(20);
	}
	return 1;
}

UINT CJIMIDlg::AutoRunThread(LPVOID pParam)
{
	CJIMIDlg *pThisThreadDlg = (CJIMIDlg *)pParam;
	pThisThreadDlg->iProcessTimes = 1;
	CString str;
	while (pThisThreadDlg->bJimiAPPStart)
	{
		if (pThisThreadDlg->bRunAutoThread )
		{
			
			if (true == pGlobal->bUWCon)//
			{
				if (pThisThreadDlg->UW_ON_MainRunProgram()) //主线程加工函数,带UW运行，此函数可按照任意顺序执行UW命令				
				{
					pThisThreadDlg->bRunAutoThread = false;
					pThisThreadDlg->GetDlgItem(IDC_TAB_Mian)->EnableWindow(TRUE);
					pThisThreadDlg->GetDlgItem(IDC_BTM_InitialALL)->EnableWindow(TRUE);
					pThisThreadDlg->GetDlgItem(IDC_BTM_RunMain)->EnableWindow(TRUE);
					pThisThreadDlg->GetDlgItem(IDC_BTM_CycleStop)->EnableWindow(TRUE);
					pThisThreadDlg->GetDlgItem(IDC_BTM_Stop)->EnableWindow(FALSE);
					
				//	pGlobal->UWSocekt.CloseSocket();
					Sleep(10);
					pThisThreadDlg->iProcessTimes = 1;
				}
				else
				{
				//	pThisThreadDlg->iProcessTimes++;
				}
			}
			else
			{
				Sleep(20);
				str.Format(_T("%d"), pThisThreadDlg->iProcessTimes);
				pThisThreadDlg->AddToRunList(_T("*******************第 ") + str + _T(" 次加工流程开始***********"));
				if (pThisThreadDlg->UW_OFF_MainRunProgram()) //主线程加工函数，不带UW运行
				{
					pThisThreadDlg->bRunAutoThread = false;
					pThisThreadDlg->GetDlgItem(IDC_TAB_Mian)->EnableWindow(TRUE);
					pThisThreadDlg->GetDlgItem(IDC_BTM_InitialALL)->EnableWindow(TRUE);
					pThisThreadDlg->GetDlgItem(IDC_BTM_RunMain)->EnableWindow(TRUE);
					pThisThreadDlg->GetDlgItem(IDC_BTM_CycleStop)->EnableWindow(FALSE);
					pThisThreadDlg->GetDlgItem(IDC_BTM_Stop)->EnableWindow(FALSE);
					Sleep(10);
					pThisThreadDlg->iProcessTimes = 1;
				}
				else
				{
					pThisThreadDlg->iProcessTimes++;
				}
			}			
		}
		Sleep(20);
	}
	return 1;
}

UINT CJIMIDlg::CheckRbtMoveSocketAliveThread(LPVOID pParam)
{
	CJIMIDlg *pThisThreadDlg = (CJIMIDlg *)pParam;
	while (pThisThreadDlg->bJimiAPPStart)
	{
		if (pThisThreadDlg->RbtSocket.m_bConnected)
		{
			Sleep(5000);
		}
		else
		{
			Sleep(5000);
		}
		
	}
	return 1;
}
BOOL CJIMIDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	pGlobal->BaseRbtSocket.SendMSG(_T("#,B,5,0,@"));//运动服务器停止
	bJimiAPPStart = false;
	return CDialogEx::DestroyWindow();
}

void CJIMIDlg::IniSystemini()
{
	CString sText;
	GetPrivateProfileString(_T("VisionSocekt"), _T("bConnect"), _T("0"), sText.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	//pGlobal->VisMarkSocekt.iPort = _ttoi(sText);
	return;
}
bool CJIMIDlg::InitialResetevent()
{
	ResetEvent(Handle_GetPOS);
	ResetEvent(Handle_FinishPOS[0]);
	ResetEvent(Handle_FinishPOS[1]);
	ResetEvent(Handle_VisionRetPOS);
	ResetEvent(Handle_RBTReadIO[0]);
	ResetEvent(Handle_RBTReadIO[1]);
	ResetEvent(Handle_RBTReadIO[2]);

	//ResetEvent(Handle_UWRetData);
	//ResetEvent(Handle_UWRetData_reach_out);
	//ResetEvent(Handle_UWRetData_out);
	//ResetEvent(Handle_UWRetData_ack);
	//ResetEvent(Handle_UWRetData_reach_in);

	ResetEvent(Handle_CSRetData[0]);
	ResetEvent(Handle_CSRetData[1]);
	ResetEvent(Handle_CSRetData[2]);
	return true;
}
bool CJIMIDlg::InitialALL()
{
	//自动前初始化全部硬件
	bool bret;
	InitialResetevent();
	//初始化位置
	WritePrivateProfileString(_T("ProcessDATA"), _T("UWStartPos"), _T("0"), _T(".\\SystemInfo.ini"));
	/////////初始化电爪///////////
	//if (!pGlobal->RBTCTdlg.IniIOClamp())
	//{
	//	pGlobal->AddToErrorList(_T("夹爪初始化失败"));
	//	return false;
	//}

	return true;
}

int CJIMIDlg::UW_ON_MainRunProgramAsFolow()
{
	int bret;
	//////////////////////////////////Step1///////////////////////////////////////////
	pGlobal->AddToRunList(_T("----- Step1.0:等待UW_reach_out出库的命令 -----"));
	DWORD dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_reach_out, INFINITE);
	if (bCycleStop)
	{
		return 1;
	}
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_UWRetData_reach_out);
		pGlobal->AddToRunList(_T("-----Step1.1:UW的出库到账信号:reach_out-----"));
		//pGlobal->UWdlg.UW_Ack_Send();
		pGlobal->AddToRunList(_T("-----Step1.2:ROBOT回复UW ack命令-----"));
	}
	//////////////////////////////////Step2///////////////////////////////////////////
	pGlobal->AddToRunList(_T("----- Step2.0:等待UW_out出库的命令 -----"));
	dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_out, 300000);	
	if (bCycleStop)
	{
		return 1;
	}
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_UWRetData_out);
		pGlobal->AddToRunList(_T("-----Step2.1:UW的出库到账信号:out-----"));
		//pGlobal->UWdlg.UW_Ack_Send();
		pGlobal->AddToRunList(_T("-----Step2.2:ROBOT回复UW ack命令-----"));
		pGlobal->AddToRunList(_T("-----Step2.3:ROBOT开始进行出库取放料-----"));
		////////机械臂开始取放料//////////
		bret = UW_OUT_IN_ROBOT_Process();
		if (bret != 0)
		{
			pGlobal->AddToRunList(_T("-----Step2.4:ROBOT出库取放料动作机器人动作失败-----"));
			pGlobal->UWdlg.UW_OutFinish_Send(_T("success"));
			pGlobal->AddToErrorList(_T("-----Step2.5:ROBOT发送出库结果：失败-----"));
			return bret;
		}
		else
		{
			pGlobal->AddToRunList(_T("-----Step2.4:ROBOT出库取放料动作完成-----"));
			pGlobal->UWdlg.UW_OutFinish_Send(_T("success"));
			pGlobal->AddToRunList(_T("-----Step2.5:ROBOT发送出库结果：成功-----"));
		}
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_UWRetData_out);
		pGlobal->AddToErrorList(_T("-----Step2.1.:等到UW_OUT信号300s超时"));
		return 1;
	}
	//////////////////////////////////Step3///////////////////////////////////////////
	pGlobal->AddToRunList(_T("----- Step3.0:等待UW_ack出库的命令 -----"));
	dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_ack, 50000);
	if (bCycleStop)
	{		
		return 1;
	}
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_UWRetData_ack);
		pGlobal->AddToRunList(_T("-----Step3.1.:收到UW的ack出库信号-----"));
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_UWRetData_ack);
		pGlobal->AddToErrorList(_T("-----Step3.1.:等到UW_ack出库信号50s超时"));
		return 1;
	}
	/////////////开始入库//////////////////////////
	//////////////////////////////////Step4///////////////////////////////////////////
	pGlobal->AddToRunList(_T("----- Step4.0:等待UW_reach_in入库的命令 -----"));
	dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_reach_in, INFINITE);
	if (bCycleStop)
	{
		return 1;
	}
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_UWRetData_reach_in);
		pGlobal->AddToRunList(_T("-----Step4.1:UW的入库到账信号:reach_in-----"));
	//	pGlobal->UWdlg.UW_Ack_Send();
		pGlobal->AddToRunList(_T("-----Step4.2:ROBOT回复UW ack命令-----"));
		pGlobal->AddToRunList(_T("-----Step4.3:ROBOT开始进行入库取放料-----"));
		////////机械臂开始取放料//////////
		bret = UW_OUT_IN_ROBOT_Process();
		if (bret != 0)
		{
			pGlobal->AddToRunList(_T("-----Step4.4:ROBOT入库取放料动作机器人动作失败-----"));
			pGlobal->UWdlg.UW_InFinish_Send();
			pGlobal->AddToRunList(_T("-----Step4.5:ROBOT发送入库结果：失败-----"));
			return bret;
		}
		else
		{
			pGlobal->AddToRunList(_T("-----Step3.4:ROBOT入库取放料动作完成-----"));
			pGlobal->UWdlg.UW_InFinish_Send();
			pGlobal->AddToRunList(_T("-----Step3.5:ROBOT发送入库结果：成功-----"));
		}
	}
	//////////////////////////////////Step5///////////////////////////////////////////
	pGlobal->AddToRunList(_T("----- Step5.0:等待UW_ack入库的命令 -----"));
	dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_ack, 50000);
	if (bCycleStop)
	{
		return 1;
	}
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_UWRetData_ack);
		pGlobal->AddToRunList(_T("-----Step5.1.:收到UW的ack入库信号-----"));
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_UWRetData_ack);
		pGlobal->AddToErrorList(_T("-----Step5.1.:等到UW_ack入库信号50s超时"));
		return 1;
	}

	return 0;
}
int CJIMIDlg::UW_ON_MainRunProgram()
{
	DWORD dwState;
	int iret;
	CString str;
	pGlobal->UWdlg.iErrorCode = 0;
	if (false == pGlobal->UWSocekt.m_bConnected)
	{
		pGlobal->AddToErrorList(_T("UW_Socket连接失败!!退出循环"));
		return 1;
	}
	int bret;
	///------step 1、机器人ready-----可以进行
	//-------此处要加是否需要-ready，如果是异常处理则不需要再次发ready---
	GetPrivateProfileString(_T("ProcessDATA"), _T("NeedReady"), _T("1"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	pGlobal->UWdlg.bNeedReady = _ttoi(str);//从历史记录的数据开始计数
	if (1 == pGlobal->UWdlg.bNeedReady)
	{
		ResetEvent(pGlobal->Handle_UWRetData_ack);
		ResetEvent(pGlobal->Handle_UWRetData_forklift_reach);
		pGlobal->UWdlg.UW_Ready_Send();
		////等待UW回复ACK信号----
		pGlobal->AddToRunList(_T("-----step1.1、机器人ready，等待UW ACK信号..... -----"));
		dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_ack, 3000);
		if (bCycleStop)
		{
			return 1;
		}
		if (dwState - WAIT_OBJECT_0 == 0)
		{
			ResetEvent(pGlobal->Handle_UWRetData_ack);
			pGlobal->AddToRunList(_T("-----Step1.2.:收到UW的ack信号-----"));
		}
		else if (WAIT_TIMEOUT == dwState)
		{
			ResetEvent(pGlobal->Handle_UWRetData_ack);
			pGlobal->AddToErrorList(_T("-----Step1.2.:等到UW_ack出库信号3s超时"));
			return 1;
		}
		pGlobal->AddToRunList(_T("-----step1.3、机器人收到ready_ACK，等待UW叉车到站信号..... -----"));
	    dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_forklift_reach,INFINITE );
		if (dwState - WAIT_OBJECT_0 == 0)
		{
			ResetEvent(pGlobal->Handle_UWRetData_forklift_reach);
			pGlobal->AddToRunList(_T("-----Step1.4.:收到UW的已经到站的信号!向UW发送到帐ACK-----"));
			//pGlobal->UWdlg.UW_Ack_Send();

			pGlobal->UWdlg.bNeedReady = 0;
			WritePrivateProfileString(_T("ProcessDATA"), _T("NeedReady"), _T("0"), _T(".\\SystemInfo.ini"));
		}
		if (bCycleStop)
		{
			return 1;
		}
		///------step 2.0、视觉开始全盘定位		
		pGlobal->AddToRunList(_T("-----step2.0、视觉开始全盘定位 -----"));
		//iPos  第几个取料位置，总共40个,0开始计数，ipos为1，4，7，10，13，16，19，21，24，27，30，33，36，39，3个一组一拍三，
		for (int i = 0; i < 6; i++)
		{
			bret = pGlobal->Visiondlg.GoGetPosAndMark(1 + i * 3);
			if (bret != 0)
			{
				pGlobal->AddToErrorList(_T("-----step2.0、视觉1-19定位异常 -----"));
				return 1;
			}
		}
		bret = pGlobal->Visiondlg.GoGetPosAndMark(18);//一拍三的单独处理
		for (int i = 0; i < 6; i++)
		{
			bret = pGlobal->Visiondlg.GoGetPosAndMark(21 + i * 3);
			if (bret != 0)
			{
				pGlobal->AddToErrorList(_T("-----step2.0、视觉21-39定位异常 -----"));
				return 1;
			}
		}
		bret = pGlobal->Visiondlg.GoGetPosAndMark(38);//一拍三的单独处理
		bmark = false;

	}	
	//得到数据，然后处理json数据，然后再开启以下的步骤。//先出库再入库
	if (bmark == true)
	{	
		/////------step 2.0、视觉开始全盘定位
		pGlobal->AddToRunList(_T("-----step2.0、视觉开始全盘定位 -----"));
		//iPos  第几个取料位置，总共40个,0开始计数，ipos为1，4，7，10，13，16，19，21，24，27，30，33，36，39，3个一组一拍三，
		for (int i = 0; i < 6; i++)
		{
			bret = pGlobal->Visiondlg.GoGetPosAndMark(1 + i * 3);
			if (bret != 0)
			{
				pGlobal->AddToErrorList(_T("-----step2.0、视觉1-19定位异常 -----"));
				return 1;
			}
		}
		bret = pGlobal->Visiondlg.GoGetPosAndMark(18);//一拍三的单独处理
		for (int i = 0; i < 6; i++)
		{
			bret = pGlobal->Visiondlg.GoGetPosAndMark(21 + i * 3);
			if (bret != 0)
			{
				pGlobal->AddToErrorList(_T("-----step2.0、视觉21-39定位异常 -----"));
				return 1;
			}
		}
		bret = pGlobal->Visiondlg.GoGetPosAndMark(38);//一拍三的单独处理
		bmark = false;
	}
	ResetEvent(pGlobal->Handle_UWRetData_ack);
	ResetEvent(pGlobal->Handle_UWRetData_material_position_info);
	pGlobal->UWdlg.UW_AskPostion_Send();
	pGlobal->AddToRunList(_T("-----step2.1、机器人向UW请求取放位置与料盘编码,等待位置ACK..... -----"));
	dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_ack, 3000);
	if (bCycleStop)
	{
		return 1;
	}
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_UWRetData_ack);
		pGlobal->AddToRunList(_T("-----Step2.2.:收到UW的位置ack信号-----"));
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_UWRetData_ack);
		pGlobal->AddToErrorList(_T("-----Step2.2.:等到UW_ack信号3s超时"));
		return 1;
	}

	pGlobal->AddToRunList(_T("-----step2.3、机器人收倒UW 位置ACK，继续等待位置信息..... -----"));
    dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_material_position_info, INFINITE);
	if (bCycleStop)
	{
		return 1;
	}
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_UWRetData_material_position_info);
		pGlobal->AddToRunList(_T("-----Step2.4.:收到UW的位置与料盘编码信息!!!!，回复UW ack命令-----"));
		//pGlobal->UWdlg.UW_Ack_Send();
		if (_T("null")!=UWdlg.sMaterialId)
		{
			iret = UW_Num_Code_Check_Process();
			if (0 == iret)
			{	
				if (0 == pGlobal->UWdlg.iErrorCode)
				{
					//扫码成功，把码上传
				   pGlobal->UWdlg.UW_ScanMaterilaInfo_Send(pGlobal->UWdlg.sMaterialId, pGlobal->UWdlg.iQuantity);
				  // pGlobal->UWdlg.bNeedReady = 0;		
				  // WritePrivateProfileString(_T("ProcessDATA"), _T("NeedReady"), _T("0"), _T(".\\SystemInfo.ini"));
				}
				else
				{
					pGlobal->AddToErrorList(_T("-----Step3.1.:收机器人扫码结果异常，异常码为5"));
					pGlobal->UWdlg.UW_ScanMaterilaInfo_Error_Send(pGlobal->UWdlg.sMaterialId, pGlobal->UWdlg.iErrorCode);//ierrorCode视情况而定
					return 1;//异常码得停下来 由人工处理后继续
				}
			}
			else
			{
				if (pGlobal->UWdlg.iErrorCode  == 0)
				{
					pGlobal->UWdlg.iErrorCode = 5;
				}
				str.Format(_T("%d"), pGlobal->UWdlg.iErrorCode);
				if (pGlobal->UWdlg.iErrorCode == 5)
				{
					pGlobal->AddToRunList(_T("-----Step3.1.:收机器人或者视觉动作异常，异常码为:") + str);
					pGlobal->AddToErrorList(_T("-----Step3.1.:收机器人或者视觉动作异常，异常码为:") + str);

				}
				else
				{
					pGlobal->AddToRunList(_T("-----Step3.1.:收扫码结果或者UW数据异常，异常码为:")+ str);
				    pGlobal->AddToErrorList(_T("-----Step3.1.:收扫码结果或者UW数据异常，异常码为:") + str);
				}
				
				pGlobal->UWdlg.UW_ScanMaterilaInfo_Error_Send(pGlobal->UWdlg.sMaterialId, pGlobal->UWdlg.iErrorCode);//ierrorCode视情况而定
				return 1;//异常码得停下来 由人工处理后继续
			}
			////等待UW回复ACK信号----
			dwState = WaitForSingleObject(pGlobal->Handle_UWRetData_ack, 3000);
			if (bCycleStop)
			{
				return 1;
			}
			if (dwState - WAIT_OBJECT_0 == 0)
			{
				ResetEvent(pGlobal->Handle_UWRetData_ack);
				pGlobal->AddToRunList(_T("-----Step3.1.:收到UW的ack信号-----"));
			}
			else if (WAIT_TIMEOUT == dwState)
			{
				ResetEvent(pGlobal->Handle_UWRetData_ack);
				pGlobal->AddToErrorList(_T("-----Step3.1.:等到UW_ack出库信号3s超时"));
				return 1;
			}
		}
		else
		{
			BackToStartPos();
			pGlobal->UWdlg.bNeedReady = 1;	
			WritePrivateProfileString(_T("ProcessDATA"), _T("NeedReady"), _T("1"), _T(".\\SystemInfo.ini"));
		}
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_UWRetData_material_position_info);
		pGlobal->AddToErrorList(_T("-----Step2.2.:等到UW的位置与料盘编码信息超时"));
		return 1;
	}
////////////////////////////////////////////////	
////////////////////////////////////////////////
	::PostMessage(this->m_hWnd, WM_VisNumLog, NULL, NULL);
	return 0;
}
int CJIMIDlg::UW_OFF_MainRunProgram()
{
	CString sMsg, str;
	CString sRunGetPos[7];
	CString sRunPutPos[7];
	CString sMidTransPos[7];
	CString sGetAngle = _T("0");
	CString sPutAngle = _T("0");
	CString slen;
	int ret;//位置返回值
	bool bret;
	int i;//for循环用

	////////////////IO夹松开紧开始//////////////////////////
	Sleep(100);//此处可以添加夹料IO处理
	ret = pGlobal->RBTCTdlg.OpenClamp();
	if (!ret)
	{
		ret = pGlobal->RBTCTdlg.OpenClamp();
	}
	if (!ret || bCycleStop)
	{
		return 1;
	}
	////////////////IO夹爪松开结束//////////////////////////

/////////////////////////////功能位置开始循环取放料处理//////////////////////
/////////////////////////////功能位置开始循环取放料处理//////////////////////
	for (int itimes = 0; itimes < pGlobal->RBTCTdlg.iProcessNum; itimes++)
	{
		for (i = 0; i < 7; i++)
		{
			sRunGetPos[i] = pGlobal->RBTCTdlg.sFunctionPos[itimes*2+1][i];
		}
		for (i = 0; i < 7; i++)
		{
			sRunPutPos[i] = pGlobal->RBTCTdlg.sFunctionPos[itimes*2 + 2][i];
		}
		for (i = 0; i < 7; i++)
		{
			sMidTransPos[i] = pGlobal->RBTCTdlg.sFunctionPos[0][i];//中转点位用固定点位
		}
		if (true == bVisionCon)
		{
			str.Format(_T("%d"), itimes+1);
			/////*****************2、放料定位*************////////////////
			if (1!= pGlobal->RBTCTdlg.iWorkType)//如果不是盘点
			{
				pGlobal->AddToRunList(_T("--------1、前往第") + str + _T("个放料料位置视觉定位"));
				pGlobal->iRbtStatue = RbtMarkPut;
				ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunPutPos, 100);
				if (!ret || bCycleStop)
				{
					return 1;
				}
				Sleep(1500);
				pGlobal->AddToRunList(_T("将位置发送给相机"));
				ret = pGlobal->Visiondlg.SendAndGetVisRetPos(sRunPutPos);
				if (ret == 0 || ret == 2 || ret == 3 || bCycleStop)
				{
					return 1;
				}
				for (i = 0; i < 7; i++)
				{
					sRunPutPos[i] = pGlobal->Visiondlg.sRecvPos[i];//定好视觉更新后的取料位置
				}
				sPutAngle = pGlobal->Visiondlg.sRomateAngle;
				Sleep(100);
			}
		
			/////*****************1、取料定位************* 先定放料位的位置，节省行程////////////////
			pGlobal->AddToRunList(_T("--------2、前往第") + str + _T("个取料位置视觉定位"));
			pGlobal->iRbtStatue = RbtMarkGet;
			ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunGetPos, 100);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			Sleep(1500);
			pGlobal->AddToRunList(_T("将位置发送给相机"));
			ret = pGlobal->Visiondlg.SendAndGetVisRetPos(sRunGetPos);
			if (ret == 0 || ret == 2 || bCycleStop)
			{
				return 1;
			}
			for (i = 0; i < 7; i++)
			{
				sRunGetPos[i] = pGlobal->Visiondlg.sRecvPos[i];//定好视觉更新后的取料位置
			}
			sGetAngle = pGlobal->Visiondlg.sRomateAngle;
			Sleep(100);

			if (1== pGlobal->RBTCTdlg.iWorkType)
			{
				for (i = 0; i < 7; i++)
				{
					sRunPutPos[i] = sRunGetPos[i];//定好视觉更新后的取料位置
				}
				sPutAngle = sGetAngle;//取放料同一个位置
			}
		}
		/////*****************3、取料位取料*************////////////////
		pGlobal->AddToRunList(_T("--------3、前往定位后第") + str + _T("个取料位置取料"));
		pGlobal->iRbtStatue = RbtGet;
		ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunGetPos, 100);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		Sleep(100);
		if (true == bVisionCon)//旋转视觉返回的旋转角度
		{ 
			ret = pGlobal->RBTCTdlg.SingleAxisMove(Axis_6_RZ, sGetAngle);
			if (!ret || bCycleStop)
			{
				return 1;
			}
		}
		slen .Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis);
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		//ret = pGlobal->RBTCTdlg.MoveToPostion(Approch_L, sRunGetPos, 0 - pGlobal->RBTCTdlg.dbGetProDis);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		////////////////IO夹爪夹紧开始//////////////////////////
		Sleep(200);//此处可以添加夹料IO处理
		ret = pGlobal->RBTCTdlg.CloseClamp();
		if (!ret)
		{
			ret = pGlobal->RBTCTdlg.CloseClamp();
		}
		if (!ret || bCycleStop)
		{
			return 1;
		}
		Sleep(200);
		////////////////IO夹爪夹紧结束//////////////////////////
		slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbPutProDis);//这个地方不需要完全起来
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		//ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunGetPos, 100);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		/////////////////////判断夹爪是否取料////////////////
		if (true == bVisionCon )//旋转视觉返回的旋转角度
		{
			if (0 == pGlobal->Visiondlg.bSuccessGet())
			{
				//如果没有取料成功，那就再夹一次；
				ret = pGlobal->RBTCTdlg.OpenClamp();
				if (!ret)
				{
					ret = pGlobal->RBTCTdlg.OpenClamp();
				}
				slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis);
				ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
				
				if (!ret || bCycleStop)
				{
					return 1;
				}
				////////////////IO夹爪夹紧开始//////////////////////////
				Sleep(200);//此处可以添加夹料IO处理
				ret = pGlobal->RBTCTdlg.CloseClamp();
				if (!ret)
				{
					ret = pGlobal->RBTCTdlg.CloseClamp();
				}
				if (!ret || bCycleStop)
				{
					return 1;
				}
				Sleep(200);
				////////////////IO夹爪夹紧结束//////////////////////////
				slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbGetProDis);
				ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);

				//pGlobal->AddToErrorList(_T("夹爪未成功取料"));
				//return 1;
			}
		}
		/////////////////////判断夹爪是否取料////////////////
		pGlobal->AddToRunList(_T("取料成功"));
		Sleep(100);
		/////*****************3、中转位置*************////////////////
		if (true == pGlobal->RBTCTdlg.bNeedTransPos)//是否启用中转位置
		{
			/////*****************3.1、中转放料*************////////////////
			pGlobal->AddToRunList(_T("--------3.1、前往中转位置放料"));

			ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sMidTransPos, 100);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			Sleep(100);

			ret = pGlobal->RBTCTdlg.MoveToPostion(Approch_L, sMidTransPos, 0 - pGlobal->RBTCTdlg.dbGetProDis - 10);//要比取料高度高个10，防止撞到料盒
			//slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis - 10);
			//ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			////////////////IO夹松开紧开始//////////////////////////
			Sleep(100);//此处可以添加夹料IO处理
			ret = pGlobal->RBTCTdlg.OpenClamp();
			if (!ret)
			{
				ret = pGlobal->RBTCTdlg.OpenClamp();
			}
			if (!ret || bCycleStop)
			{
				return 1;
			}
			////////////////IO夹爪松开结束//////////////////////////

			pGlobal->AddToRunList(_T("中转位置放料成功"));
			Sleep(100);
			/////*****************3.2、中转取料*************////////////////
			pGlobal->AddToRunList(_T("--------3.2、前往中转位置取料"));

			ret = pGlobal->RBTCTdlg.MoveToPostion(Approch_L, sMidTransPos, 0 - pGlobal->RBTCTdlg.dbGetProDis - 83);
			//slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis - 83);
			//ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			////////////////IO夹爪夹紧开始//////////////////////////
			Sleep(200);//此处可以添加夹料IO处理
			ret = pGlobal->RBTCTdlg.CloseClamp();
			if (!ret)
			{
				ret = pGlobal->RBTCTdlg.CloseClamp();
			}
			if (!ret || bCycleStop)
			{
				return 1;
			}
			Sleep(200);
			////////////////IO夹爪夹紧结束//////////////////////////
			ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sMidTransPos, 100);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			if (true == bVisionCon)//旋转视觉返回的旋转角度
			{
				if (0 == pGlobal->Visiondlg.bSuccessGet())
				{
					//如果没有取料成功，那就再夹一次；
					ret = pGlobal->RBTCTdlg.OpenClamp();
					if (!ret)
					{
						ret = pGlobal->RBTCTdlg.OpenClamp();
					}
					slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis);
					ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
					if (!ret || bCycleStop)
					{
						return 1;
					}
					////////////////IO夹爪夹紧开始//////////////////////////
					Sleep(200);//此处可以添加夹料IO处理
					ret = pGlobal->RBTCTdlg.CloseClamp();
					if (!ret)
					{
						ret = pGlobal->RBTCTdlg.CloseClamp();
					}
					if (!ret || bCycleStop)
					{
						return 1;
					}
					Sleep(200);
					////////////////IO夹爪夹紧结束//////////////////////////
					slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbGetProDis);
					ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);

					//pGlobal->AddToErrorList(_T("夹爪未成功取料"));
					//return 1;
				}
			}
			/////////////////////判断夹爪是否取料////////////////
			pGlobal->AddToRunList(_T("中转位置取料成功"));
			Sleep(100);

		}
		
		/////*****************4、放料位放料*************////////////////
		if (1 != pGlobal->RBTCTdlg.iWorkType)//如果不是盘点，就不用
		{
			pGlobal->AddToRunList(_T("--------4、前往定位后第") + str + _T("个放料位置放料"));
			pGlobal->iRbtStatue = RbtPut;
			ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunPutPos, 100);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			Sleep(100);
			if (true == bVisionCon )//旋转视觉返回的旋转角度,
			{
				ret = pGlobal->RBTCTdlg.SingleAxisMove(Axis_6_RZ, sPutAngle);
				if (!ret || bCycleStop)
				{
					return 1;
				}
			}
		}		
		slen.Format(_T("%f"), 10 - pGlobal->RBTCTdlg.dbPutProDis);
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		//ret = pGlobal->RBTCTdlg.MoveToPostion(Approch_L, sRunPutPos, 10 - pGlobal->RBTCTdlg.dbGetProDis);//要比取料高度高个10，防止撞到料盒
		if (!ret || bCycleStop)
		{
			return 1;
		}
		////////////////IO夹松开紧开始//////////////////////////
		Sleep(100);//此处可以添加夹料IO处理
		ret = pGlobal->RBTCTdlg.OpenClamp();
		if (!ret)
		{
			ret = pGlobal->RBTCTdlg.OpenClamp();
		}
		if (!ret || bCycleStop)
		{
			return 1;
		}
		////////////////IO夹爪松开结束//////////////////////////
		slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbGetProDis-10);
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		//ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunPutPos, 100);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		pGlobal->AddToRunList(_T("下料位置放料成功"));
		Sleep(100);
	}	
	return 0;
}

void CJIMIDlg::OnBnClickedBtmRunmain()
{
//开启自动则
	if (true == bUWCon)
	{
		if (true == pGlobal->UWSocekt.m_bConnected)
		{
		}
		else
		{
			pGlobal->UWSocekt.Config();
			pGlobal->UWdlg.GetDlgItem(IDC_BTN_Connect)->SetWindowText(_T("断开"));
			pGlobal->UWdlg.WidgetStatue(TRUE);
			Sleep(10);			
		}
		if (true == pGlobal->CSSocekt.m_bConnected)
		{			
		}
		else
		{
			pGlobal->CSSocekt.Config();
			pGlobal->CSdlg.SetDlgItemText(IDC_BTN_ConScanSocket, _T("断开"));
			pGlobal->CSdlg.WidgetStatue(TRUE);
		}
	}
	//ShowAutouidlg();
	//GetDlgItem(IDC_TAB_Mian)->EnableWindow(FALSE);
	//ResetEvent(Handle_UWRetData);
	CString strMSG = _T("#,V,2,") + pGlobal->RBTCTdlg.CurSpeed + _T(",@");
	pGlobal->MoveRbtSend(strMSG);//速度恢复
	bRunAutoThread = true;
	bCycleStop = false;
	bRunStop = false;
	RBTCTdlg.bIOUpdata = false;
	GetDlgItem(IDC_BTM_InitialALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTM_RunMain)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTM_CycleStop)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_Stop)->EnableWindow(TRUE);
}


void CJIMIDlg::OnBnClickedBtmCyclestop()
{
	bRunAutoThread = false;
	bCycleStop = true;
	bRunStop = false;
	if (true == bUWCon)
	{
		if (true == pGlobal->UWSocekt.m_bConnected)
		{
			pGlobal->UWSocekt.CloseSocket();
		}
	}
	
	SetEvent(Handle_FinishPOS[1]);//机器人手动停止
	SetEvent(Handle_UWRetData);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_reach_out);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_out);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_ack);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_reach_in);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_forklift_reach);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_material_position_info);//停止UW的持续等待动作

	ResetEvent(Handle_FinishPOS[1]);//机器人手动停止
	ResetEvent(Handle_UWRetData);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_reach_out);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_out);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_ack);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_reach_in);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_forklift_reach);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_material_position_info);//停止UW的持续等待动作


	GetDlgItem(IDC_TAB_Mian)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_InitialALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_RunMain)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_CycleStop)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTM_Stop)->EnableWindow(FALSE);
}


void CJIMIDlg::OnBnClickedBtmStop()
{
	//pGlobal->BaseRbtSocket.SendMSG(_T("#,B,2,0,@"));
	pGlobal->BaseRbtSocket.SendMSG(_T("#,B,5,0,@"));//运动服务器停止
	bRunAutoThread = false;
	bCycleStop = true;
	bRunStop = true;
	if (true == bUWCon)
	{
		if (true == pGlobal->UWSocekt.m_bConnected)
		{
			pGlobal->UWSocekt.CloseSocket();
		}
	}
	SetEvent(Handle_FinishPOS[1]);//机器人手动停止
	//SetEvent(Handle_CSRetData[1]);
	SetEvent(Handle_UWRetData);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_reach_out);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_out);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_ack);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_reach_in);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_forklift_reach);//停止UW的持续等待动作
	SetEvent(Handle_UWRetData_material_position_info);//停止UW的持续等待动作

	ResetEvent(Handle_FinishPOS[1]);//机器人手动停止
	ResetEvent(Handle_UWRetData);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_reach_out);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_out);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_ack);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_reach_in);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_forklift_reach);//停止UW的持续等待动作
	ResetEvent(Handle_UWRetData_material_position_info);//停止UW的持续等待动作

	GetDlgItem(IDC_TAB_Mian)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_InitialALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_RunMain)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_CycleStop)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTM_Stop)->EnableWindow(FALSE);
}


void CJIMIDlg::OnBnClickedBtmInitialall()
{
	// TODO: 初始化函数
	//视觉在初始化的时候直接连接
	if (true == bVisionCon)
	{
		if (true == pGlobal->VisMarkSocekt.m_bConnected)
		{

		}
		else
		{
			pGlobal->VisMarkSocekt.Config();
			pGlobal->Visiondlg.GetDlgItem(IDC_BTN_ConVisonSocket)->SetWindowText(_T("断开"));
		//	Sleep(10);
		}
	}
	//if (true == bUWCon)
	//{
	//	if (true == pGlobal->UWSocekt.m_bConnected)
	//	{

	//	}
	//	else
	//	{
	//		pGlobal->UWSocekt.Config();
	//		pGlobal->UWdlg.GetDlgItem(IDC_BTN_Connect)->SetWindowText(_T("断开"));
	//		Sleep(10);
	//		//pGlobal->UWdlg.UW_Login_Send(_T("ur"));
	//	}
	//}
	bmark = true;
	bInitialALL = true;
	GetDlgItem(IDC_BTM_InitialALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTM_RunMain)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTM_CycleStop)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTM_Stop)->EnableWindow(TRUE);
}

void CJIMIDlg::OnStnClickedStaticlogo()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}


BOOL CJIMIDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CJIMIDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		m_VisionView.GreenOrRed(bVisionCon);
		m_UWView.GreenOrRed(bUWCon);
	}
	CDialogEx::OnTimer(nIDEvent);
}

int CJIMIDlg::UW_OUT_IN_ROBOT_Process()
{
	CString sMsg, str;
	CString sRunGetPos[7];
	CString sRunPutPos[7];
	CString sMidTransPos[7];
	CString sGetAngle = _T("0");
	CString sPutAngle = _T("0");
	CString slen;
	int ret;//位置返回值
	bool bret;
	int i;//for循环用
	int itimes;//第几次加工
	int row;
	int cor;
	//int igetpos;
	//int iputpos;

////////////////IO夹松开紧开始//////////////////////////
	Sleep(100);//此处可以添加夹料IO处理
	ret = pGlobal->RBTCTdlg.OpenClamp();
	if (!ret)
	{
		ret = pGlobal->RBTCTdlg.OpenClamp();
	}
	if (!ret || bCycleStop)
	{
		return 1;
	}
	////////////////IO夹爪松开结束//////////////////////////
	/////////////////////////////功能位置开始循环取放料处理//////////////////////
	/////////////////////////////功能位置开始循环取放料处理//////////////////////
	//	for (itimes = 0; itimes < pGlobal->RBTCTdlg.iProcessNum; itimes++)
	str.Format(_T("需要取放料的位置组数量 = %d"), pGlobal->UWdlg.UW_ListPosNum);
	pGlobal->AddToRunList(str);
	GetPrivateProfileString(_T("ProcessDATA"), _T("UWStartPos "), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	iStartPos = _ttoi(str);//从历史记录的数据开始计数
	for (itimes = iStartPos; itimes < pGlobal->UWdlg.UW_ListPosNum; itimes++)//
	{
		row = pGlobal->UWdlg.UW_OutPos.row[itimes];//行 
		cor = pGlobal->UWdlg.UW_OutPos.col[itimes];//列，从1，1开始
		igetpos = (cor - 1) * 40 + row * 2 - 1;
		iputpos = (cor - 1) * 40 + row * 2;
		if (row>20 || row<0 ||cor >2 || cor<0 ||iputpos>80)
		{
			str.Format(_T("位置信息错误：行row = %d,列cor = %d"), row, cor);
			pGlobal->AddToErrorList(str);
			return 1;
		}
		str.Format(_T("当前位置信息：行row = %d,列cor = %d"), row, cor);
		pGlobal->AddToRunList(str);
		for (i = 0; i < 7; i++)
		{			
			if (sUWCmdCode == _T("out"))
			{
				sRunGetPos[i] = pGlobal->RBTCTdlg.sFunctionPos[igetpos][i];
				sRunPutPos[i] = pGlobal->RBTCTdlg.sFunctionPos[iputpos][i];
			}
			else if (sUWCmdCode == _T("reach_in"))//取放料位置颠倒过来
			{
				sRunGetPos[i] = pGlobal->RBTCTdlg.sFunctionPos[iputpos][i];
				sRunPutPos[i] = pGlobal->RBTCTdlg.sFunctionPos[igetpos][i];
			}
			else
			{
				pGlobal->AddToErrorList(_T("出入库sUWCmdCode 错误：")+sUWCmdCode);
				return 1;
			}
			//sRunGetPos[i] = pGlobal->RBTCTdlg.sFunctionPos[itimes * 2 + 1][i];
			//sRunPutPos[i] = pGlobal->RBTCTdlg.sFunctionPos[itimes * 2 + 2][i];
			sMidTransPos[i] = pGlobal->RBTCTdlg.sFunctionPos[0][i];//中转点位用固定点位
		}
		str.Format(_T("%d"), itimes + 1);
		if (true == bVisionCon)
		{
			///////*****************1、取料定位*************////////////////
			//pGlobal->AddToRunList(_T("--------2、前往第") + str + _T("个取料位置视觉定位"));
			//pGlobal->iRbtStatue = RbtMarkGet;
			//ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunGetPos, 100);
			//if (!ret || bCycleStop)
			//{
			//	return 1;
			//}
			//Sleep(1500);
			//pGlobal->AddToRunList(_T("将位置发送给相机"));
			//ret = pGlobal->Visiondlg.SendAndGetVisRetPos(sRunGetPos);
			//if (ret == 0 || ret == 2 || bCycleStop)
			//{
			//	return 1;
			//}
			//for (i = 0; i < 7; i++)
			//{
			//	sRunGetPos[i] = pGlobal->Visiondlg.sRecvPos[i];//定好视觉更新后的取料位置
			//}
			//sGetAngle = pGlobal->Visiondlg.sRomateAngle;
			//Sleep(100);
			/////*****************2、放料定位*************////////////////
			pGlobal->AddToRunList(_T("--------1、前往第") + str + _T("个放料料位置视觉定位"));
			pGlobal->iRbtStatue = RbtMarkPut;
			ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunPutPos, 100);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			Sleep(1500);
			pGlobal->AddToRunList(_T("将位置发送给相机"));
			ret = pGlobal->Visiondlg.SendAndGetVisRetPos(sRunPutPos);
			if (ret == 0 || ret == 2 || ret == 3 || bCycleStop)
			{
				return 1;
			}
			for (i = 0; i < 7; i++)
			{
				sRunPutPos[i] = pGlobal->Visiondlg.sRecvPos[i];//定好视觉更新后的取料位置
			}
			sPutAngle = pGlobal->Visiondlg.sRomateAngle;
			Sleep(100);
			/////*****************1、取料定位//先定放料位的点，节省行程时间*************////////////////
			pGlobal->AddToRunList(_T("--------2、前往第") + str + _T("个取料位置视觉定位"));
			pGlobal->iRbtStatue = RbtMarkGet;
			ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunGetPos, 100);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			Sleep(1500);
			pGlobal->AddToRunList(_T("将位置发送给相机"));
			ret = pGlobal->Visiondlg.SendAndGetVisRetPos(sRunGetPos);
			if (ret == 0 || ret == 2 || bCycleStop)
			{
				return 1;
			}
			for (i = 0; i < 7; i++)
			{
				sRunGetPos[i] = pGlobal->Visiondlg.sRecvPos[i];//定好视觉更新后的取料位置
			}
			sGetAngle = pGlobal->Visiondlg.sRomateAngle;
			Sleep(100);
		}
		/////*****************3、取料位取料*************////////////////
		pGlobal->AddToRunList(_T("--------3、前往定位后第") + str + _T("个取料位置取料"));
		pGlobal->iRbtStatue = RbtGet;
		ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunGetPos, 100);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		Sleep(100);
		if (true == bVisionCon)//旋转视觉返回的旋转角度
		{
			ret = pGlobal->RBTCTdlg.SingleAxisMove(Axis_6_RZ, sGetAngle);
			if (!ret || bCycleStop)
			{
				return 1;
			}
		}
		slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis);
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		//ret = pGlobal->RBTCTdlg.MoveToPostion(Approch_L, sRunGetPos, 0 - pGlobal->RBTCTdlg.dbGetProDis);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		////////////////IO夹爪夹紧开始//////////////////////////
		Sleep(200);//此处可以添加夹料IO处理
		ret = pGlobal->RBTCTdlg.CloseClamp();
		if (!ret)
		{
			ret = pGlobal->RBTCTdlg.CloseClamp();
		}
		if (!ret || bCycleStop)
		{
			return 1;
		}
		Sleep(200);
		////////////////IO夹爪夹紧结束//////////////////////////
		slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbGetProDis);
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		//ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunGetPos, 100);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		/////////////////////判断夹爪是否取料////////////////
		if (true == bVisionCon)//旋转视觉返回的旋转角度
		{
			if (0 == pGlobal->Visiondlg.bSuccessGet())
			{
				//如果没有取料成功，那就再夹一次；
				ret = pGlobal->RBTCTdlg.OpenClamp();
				if (!ret)
				{
					ret = pGlobal->RBTCTdlg.OpenClamp();
				}
				slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis);
				ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
				if (!ret || bCycleStop)
				{
					return 1;
				}
				////////////////IO夹爪夹紧开始//////////////////////////
				Sleep(200);//此处可以添加夹料IO处理
				ret = pGlobal->RBTCTdlg.CloseClamp();
				if (!ret)
				{
					ret = pGlobal->RBTCTdlg.CloseClamp();
				}
				if (!ret || bCycleStop)
				{
					return 1;
				}
				Sleep(200);
				////////////////IO夹爪夹紧结束//////////////////////////
				slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbGetProDis);
				ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);

				//pGlobal->AddToErrorList(_T("夹爪未成功取料"));
				//return 1;
			}
		}
		/////////////////////判断夹爪是否取料////////////////
		pGlobal->AddToRunList(_T("取料成功"));
		Sleep(100);
		/////*****************3、中转位置*************////////////////
		if (true == pGlobal->RBTCTdlg.bNeedTransPos)//是否启用中转位置
		{
			/////*****************3.1、中转放料*************////////////////
			pGlobal->AddToRunList(_T("--------3.1、前往中转位置放料"));

			ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sMidTransPos, 100);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			Sleep(100);

			ret = pGlobal->RBTCTdlg.MoveToPostion(Approch_L, sMidTransPos, 0 - pGlobal->RBTCTdlg.dbGetProDis - 10);//要比取料高度高个10，防止撞到料盒
																												   //slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis - 10);
																												   //ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			////////////////IO夹松开紧开始//////////////////////////
			Sleep(100);//此处可以添加夹料IO处理
			ret = pGlobal->RBTCTdlg.OpenClamp();
			if (!ret)
			{
				ret = pGlobal->RBTCTdlg.OpenClamp();
			}
			if (!ret || bCycleStop)
			{
				return 1;
			}
			////////////////IO夹爪松开结束//////////////////////////

			pGlobal->AddToRunList(_T("中转位置放料成功"));
			Sleep(100);
			/////*****************3.2、中转取料*************////////////////
			pGlobal->AddToRunList(_T("--------3.2、前往中转位置取料"));

			ret = pGlobal->RBTCTdlg.MoveToPostion(Approch_L, sMidTransPos, 0 - pGlobal->RBTCTdlg.dbGetProDis - 83);
			//slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis - 83);
			//ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			////////////////IO夹爪夹紧开始//////////////////////////
			Sleep(200);//此处可以添加夹料IO处理
			ret = pGlobal->RBTCTdlg.CloseClamp();
			if (!ret)
			{
				ret = pGlobal->RBTCTdlg.CloseClamp();
			}
			if (!ret || bCycleStop)
			{
				return 1;
			}
			Sleep(200);
			////////////////IO夹爪夹紧结束//////////////////////////
			ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sMidTransPos, 100);
			if (!ret || bCycleStop)
			{
				return 1;
			}
			/////////////////////判断夹爪是否取料////////////////
			if (true == bVisionCon)//旋转视觉返回的旋转角度
			{
				if (0 == pGlobal->Visiondlg.bSuccessGet())
				{
					//如果没有取料成功，那就再夹一次；
					ret = pGlobal->RBTCTdlg.OpenClamp();
					if (!ret)
					{
						ret = pGlobal->RBTCTdlg.OpenClamp();
					}
					slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis);
					ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
					if (!ret || bCycleStop)
					{
						return 1;
					}
					////////////////IO夹爪夹紧开始//////////////////////////
					Sleep(200);//此处可以添加夹料IO处理
					ret = pGlobal->RBTCTdlg.CloseClamp();
					if (!ret)
					{
						ret = pGlobal->RBTCTdlg.CloseClamp();
					}
					if (!ret || bCycleStop)
					{
						return 1;
					}
					Sleep(200);
					////////////////IO夹爪夹紧结束//////////////////////////
					slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbGetProDis);
					ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
					//pGlobal->AddToErrorList(_T("夹爪未成功取料"));
					//return 1;
				}
			}
			/////////////////////判断夹爪是否取料////////////////
			pGlobal->AddToRunList(_T("中转位置取料成功"));
			Sleep(100);
		}
		/////*****************4、放料位放料*************////////////////
		pGlobal->AddToRunList(_T("--------4、前往定位后第") + str + _T("个放料位置放料"));
		pGlobal->iRbtStatue = RbtPut;
		ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunPutPos, 100);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		Sleep(100);
		if (true == bVisionCon)//旋转视觉返回的旋转角度
		{
			ret = pGlobal->RBTCTdlg.SingleAxisMove(Axis_6_RZ, sPutAngle);
			if (!ret || bCycleStop)
			{
				return 1;
			}
		}

		slen.Format(_T("%f"), 10 - pGlobal->RBTCTdlg.dbGetProDis);
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		//ret = pGlobal->RBTCTdlg.MoveToPostion(Approch_L, sRunPutPos, 10 - pGlobal->RBTCTdlg.dbGetProDis);//要比取料高度高个10，防止撞到料盒
		if (!ret || bCycleStop)
		{
			return 1;
		}
		////////////////IO夹松开紧开始//////////////////////////
		Sleep(100);//此处可以添加夹料IO处理
		ret = pGlobal->RBTCTdlg.OpenClamp();
		if (!ret)
		{
			ret = pGlobal->RBTCTdlg.OpenClamp();
		}
		if (!ret || bCycleStop)
		{
			return 1;
		}
		////////////////IO夹爪松开结束//////////////////////////
		slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbGetProDis - 10);
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		//ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunPutPos, 100);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		pGlobal->AddToRunList(_T("下料位置放料成功"));
		Sleep(100);

		//位置记录，当前已经执行完哪个点，然后后续的动作，依旧按照上次那个点位运行
		str.Format(_T("%d"), itimes);
		WritePrivateProfileString(_T("ProcessDATA"), _T("UWStartPos"), str, _T(".\\SystemInfo.ini"));
	}
	str.Format(_T("%d"), 0);//正常执行完，则写0
	WritePrivateProfileString(_T("ProcessDATA"), _T("UWStartPos"), str, _T(".\\SystemInfo.ini"));
	return 0;
}

int CJIMIDlg::UW_Num_Code_Check_Process()
{
	CString sMsg, str;
	CString sRunGetPos[7];
	CString sRunPutPos[7];
	CString sMidTransPos[7];
	CString sGetAngle = _T("0");
	CString sPutAngle = _T("0");
	CString slen,strMSG;
	int ret;//位置返回值
	bool bret;
	int i;//for循环用
	int itimes;//第几次加工
	int row;
	int cor;
	//int igetpos;
	//int iputpos;

	////////////////IO夹松开紧开始//////////////////////////
	//Sleep(100);//此处可以添加夹料IO处理
	ret = pGlobal->RBTCTdlg.OpenClamp();
	if (!ret)
	{
		ret = pGlobal->RBTCTdlg.OpenClamp();
	}
	if (!ret || bCycleStop)
	{
		return 1;
	}
	////////////////IO夹爪松开结束//////////////////////////
	/////////////////////////////功能位置开始循环取放料处理//////////////////////
	/////////////////////////////功能位置开始循环取放料处理/////////////////////
	row = pGlobal->UWdlg.iXpos;//行 
	cor = pGlobal->UWdlg.iYpos;//列，从0，0开始
	igetpos = cor * 40 + row * 2 + 1;
	iputpos = cor * 40 + row * 2 + 2;
	iCSTgetpos = cor * 20 + row;
	if (row>20 || row<0 || cor >2 || cor<0 || iputpos>80)
	{
		str.Format(_T("位置信息错误：行row = %d,列cor = %d"), row, cor);
		pGlobal->AddToErrorList(str);
		return 1;
	}
	str.Format(_T("当前位置信息：行row = %d,列cor = %d，第%d个位置取料"), row, cor,iCSTgetpos);
	pGlobal->AddToRunList(str);
	if (pGlobal->Visiondlg.sVisGetResult[iCSTgetpos]==Vis_True)//1、有料可夹；2、有料不可夹；3、无料；
	{
		pGlobal->AddToRunList(_T("视觉判断刀卡位置正常，有料可夹!!!!"));
	}
	else if (pGlobal->Visiondlg.sVisGetResult[iCSTgetpos] == Vis_False)
	{
		pGlobal->AddToErrorList(_T("视觉判断刀卡位置危险，有料不可夹!!!!!!!!!!"));
		//return 1;
	}
	else if (pGlobal->Visiondlg.sVisGetResult[iCSTgetpos] == Vis_Null)
	{
		pGlobal->AddToErrorList(_T("视觉判断刀卡位置位置为空，不可夹!!!!!!!!"));
		return 1;
	}
	////////////////////////////////////////////////////////////////////
	//////////////////-------出库或者盘点判断-------------///////////
	if (1 == UWdlg.itype)//1出库2盘点
	{
		pGlobal->RBTCTdlg.iWorkType = 0;
	}
	else if(2 == UWdlg.itype)
	{
		pGlobal->RBTCTdlg.iWorkType = 1;
	}
	else
	{
		pGlobal->AddToErrorList(_T(" UW type任务错误！！"));
		return 1;
	}
	//////////////////-------出库或者盘点判断-------------///////////
	////////////////////////////////////////////////////////////////////
	for (i = 0; i < 7; i++)
	{
		sRunGetPos[i] = pGlobal->RBTCTdlg.sFunctionPos[igetpos][i];
		sRunPutPos[i] = pGlobal->RBTCTdlg.sFunctionPos[iputpos][i];
		sMidTransPos[i] = pGlobal->RBTCTdlg.sFunctionPos[0][i];//中转点位用固定点位
	}
	if (true == bVisionCon)
	{
		/////*****************2、放料定位，盘点不需要放料定位，出库也暂时不需要定位*************////////////////

		/////*****************1、取料定位//先定放料位的点，节省行程时间*************////////////////
		/////*****************2.0.0版本已在前期定好位*************////////////////

		for (i = 0; i < 7; i++)
		{
			sRunGetPos[i] = pGlobal->Visiondlg.sVisGetPos[iCSTgetpos][i];//定好视觉更新后的取料位置
		}
		/////////基于视觉定位高度，取放料要比它稍微低一点点，因此需要z方向，下降当前高度；//////////
		double dbdata = _ttof(sRunGetPos[2]) - pGlobal->RBTCTdlg.dbGetPutDownDis;
		sRunGetPos[2].Format(_T("%f"), dbdata);
		sRunPutPos[2].Format(_T("%f"), dbdata);

		sGetAngle = pGlobal->Visiondlg.sVisGetAngle[iCSTgetpos];
		Sleep(10);
		if (1 == pGlobal->RBTCTdlg.iWorkType)
		{
			for (i = 0; i < 7; i++)
			{
				sRunPutPos[i] = sRunGetPos[i];//定好视觉更新后的取料位置
			}
			sPutAngle = sGetAngle;//取放料同一个位置
		}
	}
	/////*****************3、取料位取料*************////////////////
	pGlobal->AddToRunList(_T("--------3、前往定位后取料位置取料"));
	pGlobal->iRbtStatue = RbtGet;
	ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunGetPos, 100);
	if (!ret || bCycleStop)
	{
		return 1;
	}
	Sleep(50);
	if (true == bVisionCon)//旋转视觉返回的旋转角度
	{
		ret = pGlobal->RBTCTdlg.SingleAxisMove(Axis_6_RZ, sGetAngle);
		if (!ret || bCycleStop)
		{
			return 1;
		}
	}
	/////////////////速度减慢////////////
	Sleep(50);
	int ispeed = _tstoi(pGlobal->RBTCTdlg.CurSpeed);
	ispeed = (ispeed *3)/ 4;
	CString sspeed;
	sspeed.Format(_T("%d"), ispeed);
	strMSG = _T("#,V,2,") + sspeed + _T(",@");
	pGlobal->MoveRbtSend(strMSG);//速度减半
	Sleep(50);
    /////////////////速度减慢////////////
	/////////////////下降////////////
	slen.Format(_T("%f"), 0 - pGlobal->RBTCTdlg.dbGetProDis + pGlobal->RBTCTdlg.dbGetPutDownDis);
	ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);	
	if (!ret || bCycleStop)
	{
		return 1;
	}
	/////////////////速度减慢////////////
	Sleep(50);
	strMSG = _T("#,V,2,") + pGlobal->RBTCTdlg.CurSpeed + _T(",@");
	pGlobal->MoveRbtSend(strMSG);//速度恢复
	 /////////////////速度减慢////////////
	////////////////IO夹爪夹紧开始//////////////////////////
	Sleep(200);//此处可以添加夹料IO处理
	ret = pGlobal->RBTCTdlg.CloseClamp();
	if (!ret)
	{
		ret = pGlobal->RBTCTdlg.CloseClamp();
	}
	if (!ret || bCycleStop)
	{
		return 1;
	}
	Sleep(200);//此处可以添加夹料IO处理
	////////////////IO夹爪夹紧结束//////////////////////////
	//slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbGetProDis);
	slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbPutProDis);//这个地方不需要完全起来
	ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
	//ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunGetPos, 100);
	if (!ret || bCycleStop)
	{
		return 1;
	}
	pGlobal->AddToRunList(_T("取料成功"));
	Sleep(10);

	/////*********************************************////////////////		
	/////****   此处添加扫码处理             *********////////////////
//	if (1 == pGlobal->RBTCTdlg.iWorkType)//如果是盘点，则要进行扫码，，，，盘点和出库都要扫码
	{
		ret = UW_ScanCode_Process();
		switch (ret)
		{
		case 0://扫码正常
			break;
		case 1://1为物料总数量异常
			return 1;
			break;
		case 2://2为未扫码到与UW匹配的物料ID
			return 1;
			break;
		case 3://扫码超时，移动料盘位置再扫一次则再扫一次
			ret = UW_ReMoveANDScanCode_Process();
			if (ret != 0)
			{
				ret = UW_ReMoveANDScanCode_Process();
				if (ret != 0)
				{
					return 1;
				}
			}
			break;
		default:
			break;
		}
	}
	
	/////******此处添加扫码处理**********************////////////////
	/////*********************************************////////////////

	/////*****************3、中转位置，目前已确认，暂时不需要中转位置*************////////////////
	/////*****************4、放料位放料*************////////////////
	if (1 == pGlobal->RBTCTdlg.iWorkType)//盘点
	{
		pGlobal->AddToRunList(_T("--------4、盘点---位置放料"));
		//slen.Format(_T("%f"), 10 - pGlobal->RBTCTdlg.dbGetProDis);
		slen.Format(_T("%f"), 10 - pGlobal->RBTCTdlg.dbPutProDis);//可用于扫码盘点
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		if (!ret || bCycleStop)
		{
			return 1;
		}
	}
	else if (0 == pGlobal->RBTCTdlg.iWorkType)//如果不是盘点，是出库，先直线升高，再移动到放料位置并且角度
	{
		//取料位置上升
		pGlobal->AddToRunList(_T("--------4.1、出库---升高到安全位"));
		//slen.Format(_T("%f"), 10 - pGlobal->RBTCTdlg.dbGetProDis);
		slen.Format(_T("%f"), 10 - pGlobal->RBTCTdlg.dbPutProDis + pGlobal->RBTCTdlg.dbGetProDis - pGlobal->RBTCTdlg.dbGetPutDownDis);
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);		
		if (!ret || bCycleStop)
		{
			return 1;
		}
		//移动到放料位置
		pGlobal->AddToRunList(_T("--------4.2、前往定位后第") + str + _T("个放料位置放料"));
		pGlobal->iRbtStatue = RbtPut;
		ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunPutPos, 100);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		//放料位置下降
		slen.Format(_T("%f"), 10 - pGlobal->RBTCTdlg.dbGetProDis + pGlobal->RBTCTdlg.dbGetPutDownDis);
		ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
		//ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunPutPos, 100);
		if (!ret || bCycleStop)
		{
			return 1;
		}
		//放料暂时未用到视觉，到指定位置直接放

		//Sleep(100);
		//if (true == bVisionCon)//旋转视觉返回的旋转角度
		//{
		//	ret = pGlobal->RBTCTdlg.SingleAxisMove(Axis_6_RZ, sPutAngle);
		//	if (!ret || bCycleStop)
		//	{
		//		return 1;
		//	}
		//}
	}
	////////////////IO夹松开紧开始//////////////////////////
	Sleep(200);//此处可以添加夹料IO处理
	ret = pGlobal->RBTCTdlg.OpenClamp();
	if (!ret)
	{
		ret = pGlobal->RBTCTdlg.OpenClamp();
	}
	if (!ret || bCycleStop)
	{
		return 1;
	}
	Sleep(200);
	////////////////IO夹爪松开结束//////////////////////////
	slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbGetProDis - 10 - pGlobal->RBTCTdlg.dbGetPutDownDis);
	ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
	//ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRunPutPos, 100);
	if (!ret || bCycleStop)
	{
		return 1;
	}
	pGlobal->AddToRunList(_T("下料位置放料成功"));
	Sleep(20);

	return 0;
}

int CJIMIDlg::UW_ScanCode_Process()
{
	ResetEvent(pGlobal->Handle_CSRetData[0]);
	ResetEvent(pGlobal->Handle_CSRetData[1]);
	ResetEvent(pGlobal->Handle_CSRetData[2]);
	pGlobal->CSSocekt.ReadCode();//发送扫码命令
	DWORD  dwReturn = WaitForMultipleObjects(3, pGlobal->Handle_CSRetData, FALSE, 4000);//4s的到位超时
	if (dwReturn - WAIT_OBJECT_0 == 0)
	{
		pGlobal->AddToRunList(_T("扫到的码与UW的物料编码--匹配成功！！！"));
		ResetEvent(pGlobal->Handle_CSRetData[0]);
		pGlobal->UWdlg.iErrorCode = 0;
		return 0;
	}
	else if (dwReturn - WAIT_OBJECT_0 == 1)
	{
		pGlobal->AddToErrorList(_T("扫到的码与UW的物料编码数量异常！！！"));
		ResetEvent(pGlobal->Handle_CSRetData[1]);

		pGlobal->UWdlg.iErrorCode = 4;
		return 1;
	}
	else if (dwReturn - WAIT_OBJECT_0 == 2)
	{
		pGlobal->AddToErrorList(_T("扫到的码与UW的物料编码--匹配异常！！！"));
		ResetEvent(pGlobal->Handle_CSRetData[1]);
		pGlobal->UWdlg.iErrorCode = 2;
		return 2;
	}
	else if (WAIT_TIMEOUT == dwReturn)
	{
		pGlobal->CSSocekt.StopReadCode();//停止发送扫码命令
		pGlobal->AddToErrorList(_T("扫码枪4s超时,码未匹配成功或者未扫到码"));
		ResetEvent(pGlobal->Handle_CSRetData[0]);
		ResetEvent(pGlobal->Handle_CSRetData[1]);
		ResetEvent(pGlobal->Handle_CSRetData[2]);
		pGlobal->UWdlg.iErrorCode = 1;
		return 3;
	}
}

int CJIMIDlg::UW_ReMoveANDScanCode_Process()
{
	int ret;
	CString slen;
	CString str,strMSG;
	//GetPrivateProfileString(_T("ProcessDATA"), _T("SCMovePos"), _T("7"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	str = _T("9");
	strMSG = _T("#,V,2,30,@");             
	pGlobal->MoveRbtSend(strMSG);//速度降低
	Sleep(20);
	//pGlobal->AddToRunList(_T("扫码不倒，需要移动的距离，文件保存数据为：") + str);
	if (pGlobal->igetpos <41)
	{
		slen = _T("-")+ str;//需要移动的距离

	}
	else
	{
		slen = str;//需要移动的距离
	}	
	ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_1_X, slen);//移动一个位置，让料盘下去
	//pGlobal->AddToRunList(_T("扫码不倒，需要移动的距离为：") + str);

	//这样料盘就发生了旋转，再下去夹料，再拍
	slen.Format(_T("%f"), 0-pGlobal->RBTCTdlg.dbPutProDis);
	ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);//下降过程擦着边框会导致料盘旋转
	Sleep(300);
	if (pGlobal->igetpos <41)
	{
		slen = str;//需要移动的距离
	}
	else
	{
		slen = _T("-") + str;//需要移动的距离
	}
	ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_1_X, slen);//移动一个位置，让料盘下去

	slen.Format(_T("%f"), pGlobal->RBTCTdlg.dbPutProDis);//这个地方不需要完全起来
	ret = pGlobal->RBTCTdlg.X_YSpaceAxisMove(Axis_3_Z, slen);
	//到位后再重新扫码
	Sleep(100);
	strMSG = _T("#,V,2,") + pGlobal->RBTCTdlg.CurSpeed + _T(",@");
	pGlobal->MoveRbtSend(strMSG);//速度恢复
	/////****   此处添加扫码处理             *********////////////////
	str.ReleaseBuffer();
	ret = UW_ScanCode_Process();
	switch (ret)
	{
	case 0://扫码正常
		break;
	case 1://1为物料总数量异常
		return 1;
		break;
	case 2://2为未扫码到与UW匹配的物料ID
		return 1;
		break;
	case 3://超时，不再做进一步的处理
		return 1;
	default:
		break;
	}
	return 0;
	
}

int CJIMIDlg::BackToStartPos()
{
	int ret;
	CString startPos[7];
	for (int i = 0; i < 7; i++)
	{
		startPos[i] = pGlobal->RBTCTdlg.sFunctionPos[0][i];//中转点位用固定点位
	}
	ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, startPos, 100);
	return 0;
}