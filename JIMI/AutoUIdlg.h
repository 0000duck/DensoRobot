#pragma once
#include "JIMIDlg.h"
#include "afxcmn.h"
#include "afxwin.h"

// AutoUIdlg �Ի���

class AutoUIdlg : public CDialogEx
{
	DECLARE_DYNAMIC(AutoUIdlg)

public:
	AutoUIdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AutoUIdlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOUIDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
