#pragma once
#include "ClientSocket_Robot.h"
#include "JIMIDlg.h"
#include "afxcmn.h"
#include "afxwin.h"


// RobotControldlg �Ի���

class RobotControldlg : public CDialogEx
{
	DECLARE_DYNAMIC(RobotControldlg)

public:
	RobotControldlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RobotControldlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_RobotControl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CSliderCtrl m_SlidSpeed;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	
	CComboBox m_CombAxisModle;

	int iAxisModle;//Sigle_MOLDE1�������˶�;X-Y_MOLDE2��X-Y�˶�;
	void StaticEXChange(int iAxisModle);//��ͬ�����˶�ģʽ
	void PosListIni();//�б�ؼ���ʼ��
	void InsertDataPosList();//�����ݲ��뵽λ���б���

	void ReadPosFromINI();//�ӱ��������ļ��ж�ȡ��λ��¼
	void WritePosToINI();//������д�뱾�������ļ�

    afx_msg void OnBnClickedBtnIpconnect();
	afx_msg void OnSelchangeComboAxismodle();
	afx_msg void OnBnClickedBtnJ1xadd();
	afx_msg void OnBnClickedBtnJ1xsub();
	afx_msg void OnBnClickedBtnJ2yadd();
	afx_msg void OnBnClickedBtnJ2ysub();
	afx_msg void OnBnClickedBtnJ3zadd();
	afx_msg void OnBnClickedBtnJ3zsub();
	afx_msg void OnBnClickedBtnJ4rxadd();
	afx_msg void OnBnClickedBtnJ4rxsub();
	afx_msg void OnBnClickedBtnJ5ryadd();
	afx_msg void OnBnClickedBtnJ5rysub();
	afx_msg void OnBnClickedBtnJ6rzadd();
	afx_msg void OnBnClickedBtnJ6rzsub();
	afx_msg void OnBnClickedBtnRbtsend();
    afx_msg void OnBnClickedBtnGopos();
	afx_msg void OnBnClickedBtnGet();
    afx_msg void OnBnClickedBtnSavepos();
	afx_msg void OnBnClickedBtnUpdatapos();
    afx_msg void OnBnClickedStartbasesocket();
	afx_msg void OnBnClickedBtnBaserbtsend();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnSuspend();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnMotoron();
	CString CurSpeed;
	CString CurPos;//��ǰλ�ã����仰
	CString  sCurPos[7];//��ǰ���� λ��
	CString  sCurFullIOVal;//��ǰ���� λ��
	CString  sCurSingleIO[32];//ÿ��IO��ֵ
	int  iCurSingleIO[32];//ÿ��IO��ֵ
	int  iWorkType;//0,����ȡ���ϣ�1���̵���
	double dbGetProDis;//ȡ����Ҫ�½��ĸ߶ȣ��Ӿ������ã�
	double dbPutProDis;//������Ҫ�������½��ĸ߶ȣ��̵�ɵ��ã�ɨ��̧��߶Ȼ����Ӿ���λ
	double dbGetPutDownDis;//�����Ӿ���λ�߶�,����λ�ú󣬽������������λ��ȥȡ���ϣ���ʡЧ�ʣ�ֵΪ�Ӿ��߶��½��߶�
	int iProcessNum;//N��ȡ�Ϸ��ϵ�
	bool bNeedTransPos;//�Ƿ�����תλ��

	CListCtrl m_PosShow;

	CString sFunctionPos[81][7];//80�����ܵ�λ��ÿ����λ7������
	double dbFunctionPos[81][7];//80�����ܵ�λ��ÿ����λ7������,double�ͱ���
	
	static UINT RobotMotion(LPVOID lparam);
	static UINT IOUpdatdaThread(LPVOID lparam);
	bool IOupdata();
	bool bIOUpdata;
	int Rbtstep;
	int GetCurPosFromSocekt();//�߳��ú�������ȡ����λ�����µ�ָ�����λ��
	int GetIOSetIOBtm();//�߳��ú�������ȡ������io״̬
	int MoveToPostion(int MovModle, CString sPOS[7], double dbLen);//�߳��ú���,��ָ��ģʽ�ƶ���ָ����
	int SingleAxisMove(int iAxis, CString sAngle);//�����˶����˶����
	int X_YSpaceAxisMove(int iAxis, CString slen);//�����˶����˶����

	int RBTIORead(int IONum);//�߳��ú���,����0Ϊoff��1Ϊon��2Ϊ����
	int RBTIOReadALL();//�߳��ú�������ȡ���е�IOֵ

	int RBTIOSet(int IONum);//���û����˵�ǰIOΪon
	int RBTIOReset(int IONum);//���û����˵�ǰIOΪoff

	void ConWidgetStatue(BOOL bShow);//���ӵĿؼ��Ľ���
	void MoveWidgetStatue(BOOL bShow);//���˶���صĿؼ��Ľ���
	void BaseWidgetStatue(BOOL bShow);//�����ؼ��Ľ���
	void SetIOBtmStatue();//ˢ��IO״̬���������IO ��ȡ
	bool OpenClamp();//�ɿ���צ
	bool CloseClamp();//�н���צ
	bool IniIOClamp();//��ʼ����צ
	afx_msg void OnBnClickedBtnGetcurpos();
	CNewButton m_IO0;
	CNewButton m_IO1;
	CNewButton m_IO2;
	CNewButton m_IO3;
	CNewButton m_IO4;
	CNewButton m_IO5;
	CNewButton m_IO6;
	CNewButton m_IO7;
	CNewButton m_IO8;
	CNewButton m_IO9;
	CNewButton m_IO10;
	CNewButton m_IO11;
	CNewButton m_IO12;
	CNewButton m_IO13;
	CNewButton m_IO14;
	CNewButton m_IO15;
	CNewButton m_IO16;
	CNewButton m_IO17;
	CNewButton m_IO18;
	CNewButton m_IO19;
	CNewButton m_IO20;
	CNewButton m_IO21;
	CNewButton m_IO22;
	CNewButton m_IO23;
	CNewButton m_IO24;
	CNewButton m_IO25;
	CNewButton m_IO26;
	CNewButton m_IO27;
	CNewButton m_IO28;
	CNewButton m_IO29;
	CNewButton m_IO30;
	CNewButton m_IO31;
	afx_msg void OnBnClickedBtnUpdataiobtnstatue();
	afx_msg void OnBnClickedBtnIo24();
	afx_msg void OnBnClickedBtnIo25();
	afx_msg void OnBnClickedBtnIo26();
	afx_msg void OnBnClickedBtnIo27();
	afx_msg void OnBnClickedBtnIo28();
	afx_msg void OnBnClickedBtnIo29();
	afx_msg void OnBnClickedBtnIo30();
	afx_msg void OnBnClickedBtnIo31();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnSetgetdis();
	afx_msg void OnBnClickedBtnCloseclamp();
	afx_msg void OnBnClickedBtnOpenclamp();
	afx_msg void OnBnClickedBtnIniclamp();
	afx_msg void OnBnClickedBtnSetprocessnum();
	afx_msg void OnBnClickedCheckOpentranspos();
	afx_msg void OnBnClickedBtnSetgetdis2();
	afx_msg void OnBnClickedBtnSetgetputdis();
};
