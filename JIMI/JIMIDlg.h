
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
#include "AutoUIdlg.h"
#include "ClientSocket_Robot.h"
#include "ClientSocket_BaseRBT.h"
#include "ClientSocket_VisionMark.h"
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
	bool bVisionCon;//�Ƿ������Ӿ�
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
	bool bCycleStop;
	bool bRunStop;
	static UINT InitialALLThread(LPVOID pParam);
	static UINT AutoRunThread(LPVOID pParam);
	static UINT CheckRbtMoveSocketAliveThread(LPVOID pParam);
	int MainRunProgram();//return 1234567�ֱ��Ӧ��Ӧ��λ������ʾ��λ�쳣
	bool InitialALL();//return 1234567�ֱ��Ӧ��Ӧ��λ������ʾ��λ�쳣
	int iRbtStatue;//������״̬��0123456

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
	//��ʼ���¼�
	void EventInitial();

	CListBox m_LIST_Run;
	CListBox m_LIST_Warning;
	BOOL IsNumber(const CString& strTest);
	//��tabģ��
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
	static map<int, CString>SyllableMap;//����û���ѡ�ֶ�
	static map<int, CString>BindMap;//����û���ѡ��

	CString strpcip, strpcname;//�������ƺ�ip

	CNewButton m_StateView;
	CNewButton m_OKView;
	CNewButton m_OverView;
	CNewButton m_NullView;
	CNewButton m_DownView;
	

	afx_msg void OnSelchangeTabMian(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);

	HANDLE Handle_GetPOS;
	HANDLE Handle_FinishPOS[2];//0Ϊ�������أ�1Ϊֹͣ�����¼�����
	HANDLE Handle_RBTReadIO[3];//1Ϊ����ON ��0ΪOFF��3Ϊ��ȡȫ��IO
	HANDLE Handle_VisionRetPOS;

	afx_msg void OnBnClickedButtonComok2();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedBtmRunmain();
	afx_msg void OnBnClickedBtmCyclestop();
	afx_msg void OnBnClickedBtmStop();
	afx_msg void OnBnClickedBtmInitialall();
	afx_msg void OnStnClickedStaticlogo();
};

