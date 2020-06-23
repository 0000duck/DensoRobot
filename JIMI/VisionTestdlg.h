#pragma once
#include "JIMIDlg.h"
#include "afxcmn.h"
#include "afxwin.h"

// VisionTestdlg �Ի���

class VisionTestdlg : public CDialogEx
{
	DECLARE_DYNAMIC(VisionTestdlg)

public:
	VisionTestdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~VisionTestdlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_VisionTest };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGetcurpos();	
	afx_msg void OnBnClickedBtnSendpostocam();
	afx_msg void OnBnClickedBtnMovetoretpos();

    virtual BOOL OnInitDialog();
	void IniMarklist();
	void WidgetStatue(BOOL bShow);
    
	int ithread;
	int TryCount;//������Ӵ���
	static UINT VisionDlgThread(LPVOID lparam);
	void VisionGetCurPosFromSocekt();
	int VisionReturnPos();
	int GoVisionReturnPos();
	int SendAndGetVisRetPos(CString sendpos[7]);
	int bSuccessGet();//�Ӿ��ж��Ƿ�ȡ�ϳɹ���1�ɹ���0�쳣
	CString sVisRetPos;

	int iPosNum;//���صĵ�λ������//һ��Ϊ5����λ��һ����Ϊ3��
	CString sVisGetPos[40][7];//�Ӿ����صĵ�λ
	CString sVisGetAngle[40];//��ת�Ƕ�
	CString sVisGetResult[40];///1�����ϿɼУ�2�����ϲ��ɼУ�3�����ϣ�
	int iVisGetResult[40];////1�����ϿɼУ�2�����ϲ��ɼУ�3�����ϣ�

	CString sRecvPos[7];
	CString sRomateAngle;
	int GoGetPosAndMark(int iPos);//ȥ����λ�ã�����֪�Ƿ������һ����Ŀǰ��һ��λ����5����20200423wade
	int GetDataProcess();
	void GoSelPos();
 
	int GoGetShowMarkPos();
	afx_msg void OnBnClickedBtnConvisonsocket();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckbviscon();

	CListCtrl m_listMarkPos;// �Ӿ�����У׼���λ�ã�һ������
	CComboBox m_combPos;// �Ӿ��궨λ��ѡ��
	afx_msg void OnBnClickedBtnMark2();
	afx_msg void OnBnClickedBtnGomarkpos();
};
