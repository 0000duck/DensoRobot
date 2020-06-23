#pragma once
#include "JIMIDlg.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "NewButton.h"
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


	CNewButton m_VCST_1;
	CNewButton m_VCST_2;
	CNewButton m_VCST_3;
	CNewButton m_VCST_4;
	CNewButton m_VCST_5;
	CNewButton m_VCST_6;
	CNewButton m_VCST_7;
	CNewButton m_VCST_8;
	CNewButton m_VCST_9;
	CNewButton m_VCST_10;
	CNewButton m_VCST_11;
	CNewButton m_VCST_12;
	CNewButton m_VCST_13;
	CNewButton m_VCST_14;
	CNewButton m_VCST_15;
	CNewButton m_VCST_16;
	CNewButton m_VCST_17;
	CNewButton m_VCST_18;
	CNewButton m_VCST_19;
	CNewButton m_VCST_20;
	CNewButton m_VCST_21;
	CNewButton m_VCST_22;
	CNewButton m_VCST_23;
	CNewButton m_VCST_24;
	CNewButton m_VCST_25;
	CNewButton m_VCST_26;
	CNewButton m_VCST_27;
	CNewButton m_VCST_28;
	CNewButton m_VCST_29;
	CNewButton m_VCST_30;
	CNewButton m_VCST_31;
	CNewButton m_VCST_32;
	CNewButton m_VCST_33;
	CNewButton m_VCST_34;
	CNewButton m_VCST_35;
	CNewButton m_VCST_36;
	CNewButton m_VCST_37;
	CNewButton m_VCST_38;
	CNewButton m_VCST_39;
	CNewButton m_VCST_40;

	CNewButton m_VStaue_1;
	CNewButton m_VStaue_2;
	CNewButton m_VStaue_3;

	CNewButton m_UWCST_1;
	CNewButton m_UWCST_2;
	CNewButton m_UWCST_3;
	CNewButton m_UWCST_4;
	CNewButton m_UWCST_5;
	CNewButton m_UWCST_6;
	CNewButton m_UWCST_7;
	CNewButton m_UWCST_8;
	CNewButton m_UWCST_9;
	CNewButton m_UWCST_10;
	CNewButton m_UWCST_11;
	CNewButton m_UWCST_12;
	CNewButton m_UWCST_13;
	CNewButton m_UWCST_14;
	CNewButton m_UWCST_15;
	CNewButton m_UWCST_16;
	CNewButton m_UWCST_17;
	CNewButton m_UWCST_18;
	CNewButton m_UWCST_19;
	CNewButton m_UWCST_20;
	CNewButton m_UWCST_21;
	CNewButton m_UWCST_22;
	CNewButton m_UWCST_23;
	CNewButton m_UWCST_24;
	CNewButton m_UWCST_25;
	CNewButton m_UWCST_26;
	CNewButton m_UWCST_27;
	CNewButton m_UWCST_28;
	CNewButton m_UWCST_29;
	CNewButton m_UWCST_30;
	CNewButton m_UWCST_31;
	CNewButton m_UWCST_32;
	CNewButton m_UWCST_33;
	CNewButton m_UWCST_34;
	CNewButton m_UWCST_35;
	CNewButton m_UWCST_36;
	CNewButton m_UWCST_37;
	CNewButton m_UWCST_38;
	CNewButton m_UWCST_39;
	CNewButton m_UWCST_40;
	
	CNewButton m_UWStaue_1;
	CNewButton m_UWStaue_2;
	CNewButton m_UWStaue_3;
	CNewButton m_UWStaue_4;

	void UpdataVisBTNstatue();
	void UpdataUWBTNstatue();
};
