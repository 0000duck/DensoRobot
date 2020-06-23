
// JIMIDlg.h : ͷ�ļ�
//

#pragma once
#include "ADOManage.h"
#include "DBConfig.h"
#include "UserLogin.h"
#include "AutoCombox.h"
#include "NewButton.h"
#include "RobotControldlg.h"
#include "VisionTestdlg.h"
#include "UWTestdlg.h"
#include "ClientSocket_Robot.h"
#include "ClientSocket_BaseRBT.h"
#include "ClientSocket_VisionMark.h"
#include "ClientSocket_UW.h"
#include "ClientSocket_CodeScan.h"
#include "CodeScanTestdlg.h"
#include "AutoUIdlg.h"
#include <map>

#include "afxwin.h"

#include <sapi.h>//�������
#include <sphelper.h>//�������
#include "afxcmn.h"
#pragma comment(lib,"sapi.lib") //�������

using namespace std;


/*ȫ�ֱ���*/
extern BOOL Imei3Flag;

// CJIMIDlg �Ի���
class CJIMIDlg : public CDialogEx
{
	// ����
public:
	CJIMIDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CJIMIDlg(void);

									// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JIMI_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//����Ҫʹ����Ķ���
public:
	ADOManage ado_SQL;
	ClientSocket_Robot RbtSocket;
	ClientSocket_BaseRBT BaseRbtSocket;
	ClientSocket_VisionMark VisMarkSocekt;
	ClientSocket_UW UWSocekt;
	ClientSocket_CodeScan CSSocekt;
	bool bVisionCon;//�Ƿ������Ӿ�
	bool bUWCon;//�Ƿ������Ӿ�
	//����ģ��
	HANDLE port1handler;
	HANDLE InitCom(CString comName);//��ʼ������
	CString sComPort;
	int CloseCom(HANDLE handler);//�رմ���
	void GetCommPort(CComboBox *pComboBox, CString &ComNo);//��ȡ��ǰ���ں�
	void FindCommPort(CComboBox *pComboBox, CString &ComNo, int PortNO);//��ע�����Ѱ�Ҵ��ں�
	int GetLocalHostIPName(CString &sLocalName, CString &sIpAddress);//��ȡIP��ַ
	void IniSystemini();//��ȡ���������ļ�
	static UINT ComRxThread(LPVOID pParam);//���ڽ��������߳�
	OVERLAPPED m_osRead; //���ڶ�ȡ����
	OVERLAPPED m_osWrite; //���ڷ��Ϳ���
	CWinThread *pJimiThread[10];
	bool bJimiAPPStart;
	bool bInitialALL;
	bool bRunAutoThread;
	int iProcessTimes;
	bool bCycleStop;
	bool bRunStop;
	static UINT InitialALLThread(LPVOID pParam);
	static UINT AutoRunThread(LPVOID pParam);
	static UINT CheckRbtMoveSocketAliveThread(LPVOID pParam);
	int UW_OFF_MainRunProgram();//return 1234567�ֱ��Ӧ��Ӧ��λ������ʾ��λ�쳣,����UW�ܵ�
	int UW_ON_MainRunProgram();//20191225 wade add �ֿ��̵���
	int UW_ON_MainRunProgramAsFolow();//return 1234567�ֱ��Ӧ��Ӧ��λ�������ȳ��������

	bool bmark;//����������ߣ������϶�Ҫ���ж�λ
	
	bool InitialALL();//return 1234567�ֱ��Ӧ��Ӧ��λ������ʾ��λ�쳣
	bool InitialResetevent();
	int iRbtStatue;//������״̬��0123456

	int UW_OUT_IN_ROBOT_Process();//UW�����е��ȡ������
	int UW_Num_Code_Check_Process();//20191225 wade add UWϵͳ�̵��ú���
	int UW_ScanCode_Process();//uw��ɨ�붯��������һ�β���Ҫɨ����;//0Ϊ�������ݷ��أ�1Ϊ�����������쳣��2Ϊδɨ�뵽��UWƥ�������ID,3Ϊ��ʱ
	int UW_ReMoveANDScanCode_Process();//��һ��û��ɨ���룬Ȼ��
	int BackToStartPos();//�û�е�ۻص�ԭ��
	CString sUWCmdCode;//UW�������ĳ������Ĵ��ţ�ֻ�г��������Ҫ����Ϊ��λ�ж���
	int iStartPos;//�˴δӵڼ���λ�ÿ�ʼ�У��������쳣����ж�����������ϴεĶ������м�ȡ
	int igetpos;//0-80��λ��
	int iputpos;
	int iCSTgetpos;//����λ��0-39

	CString m_PCName, m_PCIP;
	void FontInit();//��ʼ������
	CFont Font1;
	CFont Font2;
	CFont Font3; 
	CFont Font4;

	//ϵͳ������;
	ISpVoice * pVoice;
	bool IniVoice();
	HRESULT hr;
	//������־
	void AddToRunList(CString str);
	void AddToErrorList(CString str);
	void PlayVoice(CString str);
	void BaseRbtSend(CString str);//�߳��ڲ��ú����������߳������޷���send������
	void MoveRbtSend(CString str);//�߳��ڲ��ú����������߳������޷���send������
	void VisionSend(CString str);//�߳��ڲ��ú����������߳������޷���send������
	void VisBtnUpdata();//�Ӿ�ˢ�µ���״̬��ť����
	//��ʼ���¼�
	void EventInitial();

	void ShowAutouidlg();//�Զ���������£��л����Զ����н���
	CListBox m_LIST_Run;
	CListBox m_LIST_Warning;
	BOOL IsNumber(const CString& strTest);
	BOOL IsDoubleNumber(const CString& strTest);
	//��tabģ��
	CTabCtrl m_Maintab;
	void initMainTab();
	RobotControldlg RBTCTdlg;
	VisionTestdlg Visiondlg;
	UWTestdlg UWdlg;
	CodeScanTestdlg CSdlg;
	AutoUIdlg Autouidlg;

protected:
	afx_msg LRESULT OnRunlog(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVoice(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBaseRbtSend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMoveRbtSend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVisionSend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVisUpdataStatue(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVisLogStatue(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUWLogStatue(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnClearerror();
	CComboBox c_PortCom;
	afx_msg void OnDropdownComboCom();



public:
	static map<int, CString>SyllableMap;//����û���ѡ�ֶ�
	static map<int, CString>BindMap;//����û���ѡ��

	CString strpcip, strpcname;//�������ƺ�ip

	CNewButton m_StateView;
	CNewButton m_UWView;
	CNewButton m_VisionView;
	CNewButton m_NullView;
	CNewButton m_DownView;
	

	afx_msg void OnSelchangeTabMian(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);

	HANDLE Handle_GetPOS;
	HANDLE Handle_FinishPOS[2];//0Ϊ�������أ�1Ϊֹͣ�����¼�����
	HANDLE Handle_RBTReadIO[3];//1Ϊ����ON ��0ΪOFF��3Ϊ��ȡȫ��IO
	HANDLE Handle_VisionRetPOS;
	HANDLE Handle_UWRetData;
	HANDLE Handle_UWRetData_reach_out;
	HANDLE Handle_UWRetData_out;
	HANDLE Handle_UWRetData_ack;
	HANDLE Handle_UWRetData_reach_in;
	HANDLE Handle_UWRetData_forklift_reach;
	HANDLE Handle_UWRetData_material_position_info;
	HANDLE Handle_CSRetData[3];//0Ϊ�������ݷ��أ�1Ϊ�����������쳣��2Ϊδɨ�뵽��UWƥ�������ID

	afx_msg void OnBnClickedButtonComok2();					
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedBtmRunmain();
	afx_msg void OnBnClickedBtmCyclestop();
	afx_msg void OnBnClickedBtmStop();
	afx_msg void OnBnClickedBtmInitialall();
	afx_msg void OnStnClickedStaticlogo();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

