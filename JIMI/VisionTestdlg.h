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
    
	int ithread;
	int TryCount;//������Ӵ���
	static UINT VisionDlgThread(LPVOID lparam);
	void VisionGetCurPosFromSocekt();
	int VisionReturnPos();
	int GoVisionReturnPos();
	int SendAndGetVisRetPos(CString sendpos[7]);
	int bSuccessGet();//�Ӿ��ж��Ƿ�ȡ�ϳɹ���1�ɹ���0�쳣
	CString sVisRetPos;
	CString sRecvPos[7];
	CString sRomateAngle;
	afx_msg void OnBnClickedBtnConvisonsocket();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckbviscon();
};
