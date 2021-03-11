// CodeScanTestdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "CodeScanTestdlg.h"
#include "afxdialogex.h"


// CodeScanTestdlg 对话框

IMPLEMENT_DYNAMIC(CodeScanTestdlg, CDialogEx)

CodeScanTestdlg::CodeScanTestdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_CodeScan, pParent)
{

}

CodeScanTestdlg::~CodeScanTestdlg()
{
}

void CodeScanTestdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CodeScanTestdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ConScanSocket, &CodeScanTestdlg::OnBnClickedBtnConscansocket)
	ON_BN_CLICKED(IDC_BTN_GETCode, &CodeScanTestdlg::OnBnClickedBtnGetcode)
	ON_BN_CLICKED(IDC_BTN_DealCode, &CodeScanTestdlg::OnBnClickedBtnDealcode)
	ON_BN_CLICKED(IDC_BTN_StopGETCode, &CodeScanTestdlg::OnBnClickedBtnStopgetcode)
END_MESSAGE_MAP()


// CodeScanTestdlg 消息处理程序





BOOL CodeScanTestdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	WidgetStatue(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CodeScanTestdlg::OnBnClickedBtnConscansocket()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sText;
	GetDlgItemText(IDC_BTN_ConScanSocket, sText);
	if (_T("连接") == sText)
	{
		pGlobal->CSSocekt.Config();
		SetDlgItemText(IDC_BTN_ConScanSocket, _T("断开"));
		WidgetStatue(TRUE);
	}
	else
	{
		pGlobal->CSSocekt.CloseSocket();
		SetDlgItemText(IDC_BTN_ConScanSocket, _T("连接"));
		WidgetStatue(FALSE);
	}
}

void CodeScanTestdlg::WidgetStatue(BOOL bstatue)
{
	GetDlgItem(IDC_BTN_GETCode)->EnableWindow(bstatue);
	//GetDlgItem(IDC_EDIT_CodeVal)->EnableWindow(bstatue);
	//GetDlgItem(IDC_BTN_DealCode)->EnableWindow(bstatue);

}

void CodeScanTestdlg::OnBnClickedBtnGetcode()
{
	pGlobal->CSSocekt.ReadCode();
}


void CodeScanTestdlg::OnBnClickedBtnDealcode()
{
	// TODO: 在此添加控件通知处理程序代码
	CString trimtext,str;
	GetDlgItemText(IDC_EDIT_CodeVal, trimtext);
	GetDlgItemText(IDC_EDIT_Val, str);
	CString stext[90];//考虑多个@

	CStringSplit(trimtext, stext, _T("@"));//#
	for (int i = 0; i < 90; i++)
	{
		if (stext[i] == str)
		{
			SetDlgItemText(IDC_EDIT_MaterialId, stext[i]);
			SetDlgItemText(IDC_EDIT_Quantity, stext[i-1]);			
			return;
		}
		else
		{
			continue;
		}
	}
	SetDlgItemText(IDC_EDIT_MaterialId,_T("料号解码错误"));
	SetDlgItemText(IDC_EDIT_Quantity, _T("数量解码错误"));
}


void CodeScanTestdlg::OnBnClickedBtnStopgetcode()
{
	pGlobal->CSSocekt.StopReadCode();
}
