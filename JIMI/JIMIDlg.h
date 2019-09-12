
// JIMIDlg.h : 头文件
//

#pragma once
#include "ADOManage.h"
#include "DBConfig.h"
#include "UserLogin.h"
#include "AutoCombox.h"
#include "NewButton.h"
#include "RobotControldlg.h"
#include "VisionTestdlg.h"
#include "AutoUIdlg.h"
#include "ClientSocket_Robot.h"
#include "ClientSocket_BaseRBT.h"
#include "ClientSocket_VisionMark.h"
#include <map>

#include "afxwin.h"

#include <sapi.h>//语音添加
#include <sphelper.h>//语音添加
#include "afxcmn.h"
#pragma comment(lib,"sapi.lib") //语音添加

using namespace std;


/*全局变量*/
extern BOOL Imei3Flag;

// CJIMIDlg 对话框
class CJIMIDlg : public CDialogEx
{
	// 构造
public:
	CJIMIDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CJIMIDlg(void);

									// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JIMI_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//定义要使用类的对象
public:
	ADOManage ado_SQL;
	ClientSocket_Robot RbtSocket;
	ClientSocket_BaseRBT BaseRbtSocket;
	ClientSocket_VisionMark VisMarkSocekt;
	bool bVisionCon;//是否启用视觉
	//串口模块
	HANDLE port1handler;
	HANDLE InitCom(CString comName);//初始化串口
	CString sComPort;
	int CloseCom(HANDLE handler);//关闭串口
	void GetCommPort(CComboBox *pComboBox, CString &ComNo);//获取当前串口号
	void FindCommPort(CComboBox *pComboBox, CString &ComNo, int PortNO);//从注册表中寻找串口号
	int GetLocalHostIPName(CString &sLocalName, CString &sIpAddress);//获取IP地址
	void IniSystemini();//读取本地配置文件
	static UINT ComRxThread(LPVOID pParam);//串口接收数据线程
	OVERLAPPED m_osRead; //用于读取控制
	OVERLAPPED m_osWrite; //用于发送控制
	CWinThread *pJimiThread[10];
	bool bJimiAPPStart;
	bool bInitialALL;
	bool bRunAutoThread;
	bool bCycleStop;
	bool bRunStop;
	static UINT InitialALLThread(LPVOID pParam);
	static UINT AutoRunThread(LPVOID pParam);
	static UINT CheckRbtMoveSocketAliveThread(LPVOID pParam);
	int MainRunProgram();//return 1234567分别对应相应点位，则显示到位异常
	bool InitialALL();//return 1234567分别对应相应点位，则显示到位异常
	int iRbtStatue;//机器人状态，0123456

	CString m_PCName, m_PCIP;
	void FontInit();//初始化字体
	CFont Font1;
	CFont Font2;
	CFont Font3; 
	CFont Font4;

	//系统语音库;
	ISpVoice * pVoice;
	bool IniVoice();
	HRESULT hr;
	//运行日志
	void AddToRunList(CString str);
	void AddToErrorList(CString str);
	void PlayVoice(CString str);
	void BaseRbtSend(CString str);//线程内部用函数，处理线程里面无法用send的问题
	void MoveRbtSend(CString str);//线程内部用函数，处理线程里面无法用send的问题
	void VisionSend(CString str);//线程内部用函数，处理线程里面无法用send的问题
	//初始化事件
	void EventInitial();

	CListBox m_LIST_Run;
	CListBox m_LIST_Warning;
	BOOL IsNumber(const CString& strTest);
	//主tab模块
	CTabCtrl m_Maintab;
	void initMainTab();
	RobotControldlg RBTCTdlg;
	VisionTestdlg Visiondlg;
	AutoUIdlg Autouidlg;

protected:
	afx_msg LRESULT OnRunlog(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVoice(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBaseRbtSend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMoveRbtSend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVisionSend(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnClearerror();
	CComboBox c_PortCom;
	afx_msg void OnDropdownComboCom();



public:
	static map<int, CString>SyllableMap;//存放用户所选字段
	static map<int, CString>BindMap;//存放用户所选绑定

	CString strpcip, strpcname;//主机名称和ip

	CNewButton m_StateView;
	CNewButton m_OKView;
	CNewButton m_OverView;
	CNewButton m_NullView;
	CNewButton m_DownView;
	

	afx_msg void OnSelchangeTabMian(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);

	HANDLE Handle_GetPOS;
	HANDLE Handle_FinishPOS[2];//0为正常返回，1为停止返回事件触发
	HANDLE Handle_RBTReadIO[3];//1为正常ON ，0为OFF，3为读取全部IO
	HANDLE Handle_VisionRetPOS;

	afx_msg void OnBnClickedButtonComok2();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedBtmRunmain();
	afx_msg void OnBnClickedBtmCyclestop();
	afx_msg void OnBnClickedBtmStop();
	afx_msg void OnBnClickedBtmInitialall();
	afx_msg void OnStnClickedStaticlogo();
};

