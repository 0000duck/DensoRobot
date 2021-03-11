#pragma once
#include "JIMIDlg.h"
#include "afxcmn.h"
#include "afxwin.h"

// CodeScanTestdlg 对话框

class CodeScanTestdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CodeScanTestdlg)

public:
	CodeScanTestdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CodeScanTestdlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CodeScan };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConscansocket();
	virtual BOOL OnInitDialog();

	void WidgetStatue(BOOL bstatue);
	afx_msg void OnBnClickedBtnGetcode();
	afx_msg void OnBnClickedBtnDealcode();
	afx_msg void OnBnClickedBtnStopgetcode();
};
