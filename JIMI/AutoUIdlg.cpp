// AutoUIdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JIMI.h"
#include "AutoUIdlg.h"
#include "afxdialogex.h"


// AutoUIdlg �Ի���

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


// AutoUIdlg ��Ϣ�������


BOOL AutoUIdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//	SetTimer(1,500,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void AutoUIdlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC = GetDlgItem(IDC_STATIC_RBTPIC)->GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pDC);//��������DC
	BITMAP bs;//BITMAP�ṹ����
	CBitmap *m_pBmp[6];//λͼָ������
	
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
			dc.SelectObject(m_pBmp[0]);//����λͼ
	        pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//��ʾλͼ
			SetDlgItemText(IDC_STATIC_RbtStatue,_T("׼����"));
			break;
		case RbtMarkGet:
			dc.SelectObject(m_pBmp[0]);//����λͼ
			pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//��ʾλͼ
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("ȡ�϶�λ��"));
			break;
		case RbtMarkPut:
			dc.SelectObject(m_pBmp[1]);//����λͼ
			pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//��ʾλͼ
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("���϶�λ��"));
			break;
		case RbtGet:
			dc.SelectObject(m_pBmp[0]);//����λͼ
			pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//��ʾλͼ
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("ȡ������"));
			break;
		case RbtPut:
			dc.SelectObject(m_pBmp[1]);//����λͼ
			pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//��ʾλͼ
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("��������"));
			break;
		default:
			break;
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
