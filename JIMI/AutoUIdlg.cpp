// AutoUIdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "AutoUIdlg.h"
#include "afxdialogex.h"


// AutoUIdlg 对话框

IMPLEMENT_DYNAMIC(AutoUIdlg, CDialogEx)

AutoUIdlg::AutoUIdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTOUIDLG, pParent)
{

}

AutoUIdlg::~AutoUIdlg()
{
}

void AutoUIdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AutoUIdlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// AutoUIdlg 消息处理程序


BOOL AutoUIdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
//	SetTimer(1,500,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void AutoUIdlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDlgItem(IDC_STATIC_RBTPIC)->GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pDC);//创建兼容DC
	BITMAP bs;//BITMAP结构变量
	CBitmap *m_pBmp[6];//位图指针数组
	
	m_pBmp[0] = new CBitmap;
	m_pBmp[0]->LoadBitmap(IDB_BITMAP_RBT_L);
	m_pBmp[1] = new CBitmap;
	m_pBmp[1]->LoadBitmap(IDB_BITMAP_RBT_R);

	m_pBmp[0]->GetBitmap(&bs);

	if (nIDEvent == 1)
	{

		switch (pGlobal->iRbtStatue)
		{
		case RbtReady:
			dc.SelectObject(m_pBmp[0]);//加载位图
	        pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue,_T("准备好"));
			break;
		case RbtMarkGet:
			dc.SelectObject(m_pBmp[0]);//加载位图
			pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("取料定位中"));
			break;
		case RbtMarkPut:
			dc.SelectObject(m_pBmp[1]);//加载位图
			pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("放料定位中"));
			break;
		case RbtGet:
			dc.SelectObject(m_pBmp[0]);//加载位图
			pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("取料流程"));
			break;
		case RbtPut:
			dc.SelectObject(m_pBmp[1]);//加载位图
			pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("放料流程"));
			break;
		default:
			break;
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
