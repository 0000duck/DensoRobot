#pragma once


// DBConfig 对话框

class DBConfig : public CDialogEx
{
	DECLARE_DYNAMIC(DBConfig)

public:
	DBConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DBConfig();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DATABASE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_serveripEdit;
	CString m_portEdit;
	CString m_usernameEdit;
	CString m_passwordEdit;
	CString m_firstdbnameEdit;
	CString m_firstformnameEdit;
	CString m_seconddbnameEdit;
	CString m_secondformnameEdit;

	void Readdbini();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
