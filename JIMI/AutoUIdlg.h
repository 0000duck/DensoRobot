#pragma once
#include "JIMIDlg.h"
#include "afxcmn.h"
#include "afxwin.h"

// AutoUIdlg 对话框

class AutoUIdlg : public CDialogEx
{
	DECLARE_DYNAMIC(AutoUIdlg)

public:
	AutoUIdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AutoUIdlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOUIDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
