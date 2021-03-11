// CodeScanTestdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JIMI.h"
#include "CodeScanTestdlg.h"
#include "afxdialogex.h"


// CodeScanTestdlg �Ի���

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


// CodeScanTestdlg ��Ϣ�������





BOOL CodeScanTestdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	WidgetStatue(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CodeScanTestdlg::OnBnClickedBtnConscansocket()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sText;
	GetDlgItemText(IDC_BTN_ConScanSocket, sText);
	if (_T("����") == sText)
	{
		pGlobal->CSSocekt.Config();
		SetDlgItemText(IDC_BTN_ConScanSocket, _T("�Ͽ�"));
		WidgetStatue(TRUE);
	}
	else
	{
		pGlobal->CSSocekt.CloseSocket();
		SetDlgItemText(IDC_BTN_ConScanSocket, _T("����"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString trimtext,str;
	GetDlgItemText(IDC_EDIT_CodeVal, trimtext);
	GetDlgItemText(IDC_EDIT_Val, str);
	CString stext[90];//���Ƕ��@

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
	SetDlgItemText(IDC_EDIT_MaterialId,_T("�ϺŽ������"));
	SetDlgItemText(IDC_EDIT_Quantity, _T("�����������"));
}


void CodeScanTestdlg::OnBnClickedBtnStopgetcode()
{
	pGlobal->CSSocekt.StopReadCode();
}
