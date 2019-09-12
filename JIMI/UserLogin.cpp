// UserLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "UserLogin.h"
#include "afxdialogex.h"
#include "ADOManage.h"
#include "JIMIDLG.h"


// UserLogin 对话框

IMPLEMENT_DYNAMIC(UserLogin, CDialogEx)

UserLogin::UserLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_UserName(_T(""))
	, m_UserPswd(_T(""))
	, sUSER(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_JIMI);
}

UserLogin::~UserLogin()
{
}

void UserLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UserName, m_UserName);
	DDX_Text(pDX, IDC_EDIT_UserPswd, m_UserPswd);
}


BEGIN_MESSAGE_MAP(UserLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &UserLogin::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// UserLogin 消息处理程序


void UserLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (_T("") == m_UserName || _T("") == m_UserPswd)
	{
		AfxMessageBox(_T("账号密码不能为空"));
		return;
	}

	ADOManage adoManage;
	if (!adoManage.ConnSQL())
	{
		return;
	}	
	sUSER = adoManage.CheckUser(m_UserName, m_UserPswd);
	if (_T("") == sUSER)
	{
		AfxMessageBox(_T("账号密码错误"));
		return;
	}

	UpdateData(FALSE);

	CDialogEx::OnOK();
}


BOOL UserLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	GetDlgItem(IDC_EDIT_UserName)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void UserLogin::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
