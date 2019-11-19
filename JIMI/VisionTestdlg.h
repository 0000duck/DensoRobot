#pragma once
#include "JIMIDlg.h"
#include "afxcmn.h"
#include "afxwin.h"

// VisionTestdlg 对话框

class VisionTestdlg : public CDialogEx
{
	DECLARE_DYNAMIC(VisionTestdlg)

public:
	VisionTestdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~VisionTestdlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_VisionTest };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGetcurpos();	
	afx_msg void OnBnClickedBtnSendpostocam();
	afx_msg void OnBnClickedBtnMovetoretpos();

    virtual BOOL OnInitDialog();
    
	int ithread;
	int TryCount;//最大连接次数
	static UINT VisionDlgThread(LPVOID lparam);
	void VisionGetCurPosFromSocekt();
	int VisionReturnPos();
	int GoVisionReturnPos();
	int SendAndGetVisRetPos(CString sendpos[7]);
	int bSuccessGet();//视觉判断是否取料成功，1成功，0异常
	CString sVisRetPos;
	CString sRecvPos[7];
	CString sRomateAngle;
	afx_msg void OnBnClickedBtnConvisonsocket();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckbviscon();
};
