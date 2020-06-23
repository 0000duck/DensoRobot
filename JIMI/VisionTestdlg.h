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
	void IniMarklist();
	void WidgetStatue(BOOL bShow);
    
	int ithread;
	int TryCount;//最大连接次数
	static UINT VisionDlgThread(LPVOID lparam);
	void VisionGetCurPosFromSocekt();
	int VisionReturnPos();
	int GoVisionReturnPos();
	int SendAndGetVisRetPos(CString sendpos[7]);
	int bSuccessGet();//视觉判断是否取料成功，1成功，0异常
	CString sVisRetPos;

	int iPosNum;//返回的点位个数，//一般为5个点位，一拍三为3个
	CString sVisGetPos[40][7];//视觉返回的点位
	CString sVisGetAngle[40];//旋转角度
	CString sVisGetResult[40];///1、有料可夹；2、有料不可夹；3、无料；
	int iVisGetResult[40];////1、有料可夹；2、有料不可夹；3、无料；

	CString sRecvPos[7];
	CString sRomateAngle;
	int GoGetPosAndMark(int iPos);//去拍照位置，并告知是否是最后一个，目前是一个位置拍5个，20200423wade
	int GetDataProcess();
	void GoSelPos();
 
	int GoGetShowMarkPos();
	afx_msg void OnBnClickedBtnConvisonsocket();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckbviscon();

	CListCtrl m_listMarkPos;// 视觉返回校准后的位置，一共五组
	CComboBox m_combPos;// 视觉标定位置选择
	afx_msg void OnBnClickedBtnMark2();
	afx_msg void OnBnClickedBtnGomarkpos();
};
