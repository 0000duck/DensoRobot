#pragma once


// UserLogin 对话框

class UserLogin : public CDialogEx
{
	DECLARE_DYNAMIC(UserLogin)

public:
	UserLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UserLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_UserName;
	CString m_UserPswd;

	CString sUSER;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
