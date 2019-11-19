// RobotControldlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JIMI.h"
#include "RobotControldlg.h"
#include "afxdialogex.h"

extern CRITICAL_SECTION Sec_MoveRbtSocket;
// RobotControldlg �Ի���

IMPLEMENT_DYNAMIC(RobotControldlg, CDialogEx)

RobotControldlg::RobotControldlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_RobotControl, pParent)
{
}

RobotControldlg::~RobotControldlg()
{
}

void RobotControldlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_SlidSpeed);
	DDX_Control(pDX, IDC_COMBO_AxisModle, m_CombAxisModle);
	DDX_Control(pDX, IDC_LIST_PosShow, m_PosShow);
	DDX_Control(pDX, IDC_BTN_IO0, m_IO0);
	DDX_Control(pDX, IDC_BTN_IO1, m_IO1);
	DDX_Control(pDX, IDC_BTN_IO2, m_IO2);
	DDX_Control(pDX, IDC_BTN_IO3, m_IO3);
	DDX_Control(pDX, IDC_BTN_IO4, m_IO4);
	DDX_Control(pDX, IDC_BTN_IO5, m_IO5);
	DDX_Control(pDX, IDC_BTN_IO6, m_IO6);
	DDX_Control(pDX, IDC_BTN_IO7, m_IO7);
	DDX_Control(pDX, IDC_BTN_IO8, m_IO8);
	DDX_Control(pDX, IDC_BTN_IO9, m_IO9);
	DDX_Control(pDX, IDC_BTN_IO10, m_IO10);
	DDX_Control(pDX, IDC_BTN_IO11, m_IO11);
	DDX_Control(pDX, IDC_BTN_IO12, m_IO12);
	DDX_Control(pDX, IDC_BTN_IO13, m_IO13);
	DDX_Control(pDX, IDC_BTN_IO14, m_IO14);
	DDX_Control(pDX, IDC_BTN_IO15, m_IO15);
	DDX_Control(pDX, IDC_BTN_IO16, m_IO16);
	DDX_Control(pDX, IDC_BTN_IO17, m_IO17);
	DDX_Control(pDX, IDC_BTN_IO18, m_IO18);
	DDX_Control(pDX, IDC_BTN_IO19, m_IO19);
	DDX_Control(pDX, IDC_BTN_IO20, m_IO20);
	DDX_Control(pDX, IDC_BTN_IO21, m_IO21);
	DDX_Control(pDX, IDC_BTN_IO22, m_IO22);
	DDX_Control(pDX, IDC_BTN_IO23, m_IO23);
	DDX_Control(pDX, IDC_BTN_IO24, m_IO24);
	DDX_Control(pDX, IDC_BTN_IO25, m_IO25);
	DDX_Control(pDX, IDC_BTN_IO26, m_IO26);
	DDX_Control(pDX, IDC_BTN_IO27, m_IO27);
	DDX_Control(pDX, IDC_BTN_IO28, m_IO28);
	DDX_Control(pDX, IDC_BTN_IO29, m_IO29);
	DDX_Control(pDX, IDC_BTN_IO30, m_IO30);
	DDX_Control(pDX, IDC_BTN_IO31, m_IO31);
}


BEGIN_MESSAGE_MAP(RobotControldlg, CDialogEx)

	ON_BN_CLICKED(IDC_BTN_IPConnect, &RobotControldlg::OnBnClickedBtnIpconnect)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_AxisModle, &RobotControldlg::OnSelchangeComboAxismodle)
	ON_BN_CLICKED(IDC_BTN_J1Xadd, &RobotControldlg::OnBnClickedBtnJ1xadd)
	ON_BN_CLICKED(IDC_BTN_J1Xsub, &RobotControldlg::OnBnClickedBtnJ1xsub)
	ON_BN_CLICKED(IDC_BTN_J2Yadd, &RobotControldlg::OnBnClickedBtnJ2yadd)
	ON_BN_CLICKED(IDC_BTN_J2Ysub, &RobotControldlg::OnBnClickedBtnJ2ysub)
	ON_BN_CLICKED(IDC_BTN_J3Zadd, &RobotControldlg::OnBnClickedBtnJ3zadd)
	ON_BN_CLICKED(IDC_BTN_J3Zsub, &RobotControldlg::OnBnClickedBtnJ3zsub)
	ON_BN_CLICKED(IDC_BTN_J4RXadd, &RobotControldlg::OnBnClickedBtnJ4rxadd)
	ON_BN_CLICKED(IDC_BTN_J4RXsub, &RobotControldlg::OnBnClickedBtnJ4rxsub)
	ON_BN_CLICKED(IDC_BTN_J5RYadd, &RobotControldlg::OnBnClickedBtnJ5ryadd)
	ON_BN_CLICKED(IDC_BTN_J5RYsub, &RobotControldlg::OnBnClickedBtnJ5rysub)
	ON_BN_CLICKED(IDC_BTN_J6RZadd, &RobotControldlg::OnBnClickedBtnJ6rzadd)
	ON_BN_CLICKED(IDC_BTN_J6RZsub, &RobotControldlg::OnBnClickedBtnJ6rzsub)
	ON_BN_CLICKED(IDC_BTN_RBTSEND, &RobotControldlg::OnBnClickedBtnRbtsend)

	ON_BN_CLICKED(IDC_BTN_GoPOS, &RobotControldlg::OnBnClickedBtnGopos)
	ON_BN_CLICKED(IDC_BTN_GET, &RobotControldlg::OnBnClickedBtnGet)
	ON_BN_CLICKED(IDC_BTN_SAVEPOS, &RobotControldlg::OnBnClickedBtnSavepos)
	ON_BN_CLICKED(IDC_BTN_UPDATAPOS, &RobotControldlg::OnBnClickedBtnUpdatapos)
	ON_BN_CLICKED(IDC_StartBaseSocket, &RobotControldlg::OnBnClickedStartbasesocket)
	ON_BN_CLICKED(IDC_BTN_BaseRBTSEND, &RobotControldlg::OnBnClickedBtnBaserbtsend)
	ON_BN_CLICKED(IDC_BTN_Start, &RobotControldlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_Suspend, &RobotControldlg::OnBnClickedBtnSuspend)
	ON_BN_CLICKED(IDC_BTN_STOP, &RobotControldlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_MotorON, &RobotControldlg::OnBnClickedBtnMotoron)
	ON_BN_CLICKED(IDC_BTN_GETCURPOS, &RobotControldlg::OnBnClickedBtnGetcurpos)
	ON_BN_CLICKED(IDC_BTN_UpdataIOBtnStatue, &RobotControldlg::OnBnClickedBtnUpdataiobtnstatue)
	ON_BN_CLICKED(IDC_BTN_IO24, &RobotControldlg::OnBnClickedBtnIo24)
	ON_BN_CLICKED(IDC_BTN_IO25, &RobotControldlg::OnBnClickedBtnIo25)
	ON_BN_CLICKED(IDC_BTN_IO26, &RobotControldlg::OnBnClickedBtnIo26)
	ON_BN_CLICKED(IDC_BTN_IO27, &RobotControldlg::OnBnClickedBtnIo27)
	ON_BN_CLICKED(IDC_BTN_IO28, &RobotControldlg::OnBnClickedBtnIo28)
	ON_BN_CLICKED(IDC_BTN_IO29, &RobotControldlg::OnBnClickedBtnIo29)
	ON_BN_CLICKED(IDC_BTN_IO30, &RobotControldlg::OnBnClickedBtnIo30)
	ON_BN_CLICKED(IDC_BTN_IO31, &RobotControldlg::OnBnClickedBtnIo31)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SETGETDIS, &RobotControldlg::OnBnClickedBtnSetgetdis)
	ON_BN_CLICKED(IDC_BTN_CloseClamp, &RobotControldlg::OnBnClickedBtnCloseclamp)
	ON_BN_CLICKED(IDC_BTN_OpenClamp, &RobotControldlg::OnBnClickedBtnOpenclamp)
	ON_BN_CLICKED(IDC_BTN_IniClamp, &RobotControldlg::OnBnClickedBtnIniclamp)
	ON_BN_CLICKED(IDC_BTN_SETProcessNum, &RobotControldlg::OnBnClickedBtnSetprocessnum)
	ON_BN_CLICKED(IDC_CHECK_OpenTransPOS, &RobotControldlg::OnBnClickedCheckOpentranspos)
END_MESSAGE_MAP()


// RobotControldlg ��Ϣ�������

BOOL RobotControldlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//�����ʼ��
	m_SlidSpeed.SetRange(1, 99);
	m_SlidSpeed.SetPageSize(1);
	SetDlgItemText(IDC_EDIT_SPEEDVIEW, _T("0"));
	SetDlgItemText(IDC_EDIT_JOGDis, _T("10"));
	//��Ͽ��ʼ��
	m_CombAxisModle.SetCurSel(0);
	iAxisModle = Sigle_MOLDE;
	StaticEXChange(iAxisModle);

	//���水ť״̬����
	MoveWidgetStatue(FALSE);
	BaseWidgetStatue(FALSE);
	ConWidgetStatue(FALSE);
	bIOUpdata = false;

	CString str;
	int iret;
	GetPrivateProfileString(_T("ProcessDATA"), _T("RbtDownDis"), _T("220"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	dbGetProDis = _ttof(str);
	SetDlgItemText(IDC_EDIT_GetProDis, str);
	GetPrivateProfileString(_T("ProcessDATA"), _T("ProcessNum"), _T("11"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	iProcessNum = _ttoi(str);
	SetDlgItemText(IDC_EDIT_ProcessNum, str);
	GetPrivateProfileString(_T("ProcessDATA"), _T("NeedTransPos"), _T("1"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	iret = _ttoi(str);
	if (iret == 1)
	{
		bNeedTransPos = true;
		((CButton *)GetDlgItem(IDC_CHECK_OpenTransPOS))->SetCheck(1);
	}
	else
	{
		bNeedTransPos = false;
		((CButton *)GetDlgItem(IDC_CHECK_OpenTransPOS))->SetCheck(0);
	}

	//λ��list���ʼ��
	PosListIni();
	ReadPosFromINI();
	InsertDataPosList();

	AfxBeginThread(IOUpdatdaThread, this);//

	return TRUE;  
}

void RobotControldlg::OnBnClickedBtnIpconnect()
{
	// ������˳��򴴽��ķ���������
	bool ret;
	CString str;
	GetDlgItemText(IDC_BTN_IPConnect, str);
	if (_T("����") == str)
	{
		ret = pGlobal->RbtSocket.Config();
		if (ret)
		{
		//	pGlobal->AddToRunList(_T("������SOCKET���ӳɹ�����"));
			SetDlgItemText(IDC_BTN_IPConnect, _T("�Ͽ�"));
		//	pGlobal->BaseRbtSocket.SendMSG(_T("#,B,3,0,@"));//�˶�����������
			pGlobal->RbtSocket.SendMSG(_T("#,V,1,0,@"));//�ٶȻ�ȡ
			Sleep(20);
		//	Rbtstep = 5;//��צ��ʼ���߳�
		//	AfxBeginThread(RobotMotion, this);//

			BaseWidgetStatue(TRUE);
			MoveWidgetStatue(TRUE);
			bIOUpdata = true;
			//SetTimer(1, 500, NULL);

		}
		else
		{
			bIOUpdata = false;
			pGlobal->AddToRunList(_T("������SOCKET����ʧ�ܣ���"));
			pGlobal->RbtSocket.CloseSocket();
			//KillTimer(1);
		}
	}
	else if (_T("�Ͽ�") == str)
	{
		bIOUpdata = false;
		BaseWidgetStatue(FALSE);
		MoveWidgetStatue(FALSE);
		pGlobal->RbtSocket.CloseSocket();
		pGlobal->AddToRunList(_T("������SOCKET�Ͽ����ӣ���"));
		SetDlgItemText(IDC_BTN_IPConnect, _T("����"));		
		pGlobal->RbtSocket.m_bConnected = FALSE;
		KillTimer(1);
	}	
}


void RobotControldlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int iPos;
	CString sPos;
	CString tempPos;
	CString strMSG;
	
	if (nSBCode == SB_ENDSCROLL)
	{
		if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_SPEED)
		{
			iPos = m_SlidSpeed.GetPos();
			sPos.Format(_T("%d"), iPos);
			SetDlgItemText(IDC_EDIT_SPEEDVIEW, sPos);
			pGlobal->Autouidlg.SetDlgItemText(IDC_EDIT_rbtSpeed, pGlobal->RBTCTdlg.CurSpeed);
			strMSG = _T("#,V,2,") + sPos + _T(",@");
            bool ret = pGlobal->RbtSocket.SendMSG(strMSG);
		}
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void RobotControldlg::OnSelchangeComboAxismodle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	iAxisModle = m_CombAxisModle.GetCurSel();
	StaticEXChange(iAxisModle);
}

void RobotControldlg::StaticEXChange(int iAxisModle)
{
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		SetDlgItemText(IDC_STATIC_J1, _T("J1"));
		SetDlgItemText(IDC_STATIC_J2, _T("J2"));
		SetDlgItemText(IDC_STATIC_J3, _T("J3"));
		SetDlgItemText(IDC_STATIC_J4, _T("J4"));
		SetDlgItemText(IDC_STATIC_J5, _T("J5"));
		SetDlgItemText(IDC_STATIC_J6, _T("J6"));
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		SetDlgItemText(IDC_STATIC_J1, _T("X"));
		SetDlgItemText(IDC_STATIC_J2, _T("Y"));
		SetDlgItemText(IDC_STATIC_J3, _T("Z"));
		SetDlgItemText(IDC_STATIC_J4, _T("RX"));
		SetDlgItemText(IDC_STATIC_J5, _T("RY"));
		SetDlgItemText(IDC_STATIC_J6, _T("RZ"));
	}

}

void RobotControldlg::OnBnClickedBtnJ1xadd()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE ==iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,1,")+ sDistance+ _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,1,") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ1xsub()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,1,-") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,1,-") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ2yadd()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,2,") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,2,") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ2ysub()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,2,-") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,2,-") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ3zadd()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,3,") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,3,") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ3zsub()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}

	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,3,-") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,3,-") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ4rxadd()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,4,") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,4,") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}

void RobotControldlg::OnBnClickedBtnJ4rxsub()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,4,-") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,4,-") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ5ryadd()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,5,") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,5,") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ5rysub()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,5,-") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,5,-") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ6rzadd()
{

	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,6,") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,6,") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}


void RobotControldlg::OnBnClickedBtnJ6rzsub()
{
	CString sDistance;
	CString sMSG;
	GetDlgItemText(IDC_EDIT_JOGDis, sDistance);
	if (FALSE == pGlobal->IsDoubleNumber(sDistance))
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if (Sigle_MOLDE == iAxisModle)//�����˵����˶�
	{
		sMSG = _T("#,S,6,-") + sDistance + _T(",@");
	}
	else if (X_Y_MOLDE == iAxisModle)//�����˶���X-Y�˶�
	{
		sMSG = _T("#,M,6,-") + sDistance + _T(",@");
	}
	pGlobal->RbtSocket.SendMSG(sMSG);
}

void RobotControldlg::OnBnClickedBtnRbtsend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString stext;
	GetDlgItemText(IDC_EDIT_RBTTEXT, stext);
	bool ret = pGlobal->RbtSocket.SendMSG(stext);
}

void RobotControldlg::PosListIni()
{
	LONG lStyle;
	CString str;
	lStyle = GetWindowLong(m_PosShow.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_PosShow.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_PosShow.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	//dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_PosShow.SetExtendedStyle(dwStyle); //������չ���

	m_PosShow.InsertColumn(0, _T("����λ��"), LVCFMT_LEFT, 120);//������
	m_PosShow.InsertColumn(1, _T("X"), LVCFMT_LEFT, 80);//������
	m_PosShow.InsertColumn(2, _T("Y"), LVCFMT_LEFT, 80);//������
	m_PosShow.InsertColumn(3, _T("Z"), LVCFMT_LEFT, 80);//������
	m_PosShow.InsertColumn(4, _T("RX"), LVCFMT_LEFT, 80);//������
	m_PosShow.InsertColumn(5, _T("RY"), LVCFMT_LEFT, 80);//������
	m_PosShow.InsertColumn(6, _T("RZ"), LVCFMT_LEFT, 80);//������
	m_PosShow.InsertColumn(7, _T("Fig"), LVCFMT_LEFT, 80);//������

	m_PosShow.InsertItem(0, _T("������תλ��0"));//������
	for (int i = 0; i < 40; i++)
	{
		if (i<20)
		{
			str.Format(_T("%d"), i+1);
		    m_PosShow.InsertItem(i*2+ 1, _T("ȡ��(����1_")+str+_T(")"));//������
		    m_PosShow.InsertItem(i*2 + 2, _T("����(���1_")+str+_T(")"));//������
		}
		else
		{
			str.Format(_T("%d"), i - 20 + 1);
			m_PosShow.InsertItem(i * 2 + 1, _T("ȡ��(����2_") + str + _T(")"));//������
			m_PosShow.InsertItem(i * 2 + 2, _T("����(���2_") + str + _T(")"));//������
		}		
	}
}

void RobotControldlg::InsertDataPosList()
{
	for (int i = 0; i < 81; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			m_PosShow.SetItemText(i, j+1, sFunctionPos[i][j]);//��������
		}
	}

}
void RobotControldlg::ReadPosFromINI()
{
	CFileFind finder;
	CString str;
	CString sSection, sKeyname;
	//for (int i = 0; i < iProcessNum * 2 + 1; i++)//��ˢ��ȫ�����ݣ�ֻ���浱ǰҪ�õ����ݣ����򱣴��ʱ��̫����
	for (int i = 0; i < 81; i++)	
	{
		sSection.Format(_T("Funtion_POS_%d"), i);
		for (int j = 0; j < 7; j++)
		{
			sKeyname.Format(_T("Mark_%d"), j);
			GetPrivateProfileString(sSection, sKeyname, _T("0"), str.GetBuffer(50), 50, _T(".\\FunctionPos.ini"));
			sFunctionPos[i][j] = str;
			str.ReleaseBuffer();
		}
	}
	return;
}

void RobotControldlg::WritePosToINI()
{
	CFileFind finder;
	CString str;
	CString sSection, sKeyname;
	//for (int i = 0; i < iProcessNum*2+1; i++)//������ȫ�����ݣ�ֻ���浱ǰҪ�õ����ݣ����򱣴��ʱ��̫����
	for (int i = 0; i < 81; i++)
	{
		sSection.Format(_T("Funtion_POS_%d"), i);
		for (int j = 0; j < 7; j++)
		{
			sKeyname.Format(_T("Mark_%d"), j);
			str = m_PosShow.GetItemText(i,j+1);
			sFunctionPos[i][j] = str;
			WritePrivateProfileString(sSection, sKeyname, str, _T(".\\FunctionPos.ini"));			
		}
	}
	return;
}


void RobotControldlg::OnBnClickedBtnGopos()
{
	POSITION pos = m_PosShow.GetFirstSelectedItemPosition();
	CString spos[7];
	if (pos == NULL)
	{
		AfxMessageBox(_T("��ѡ����Ӧ��λ"));
		return;
	}
	int iget = m_PosShow.GetNextSelectedItem(pos);
	for (int i = 0; i < 7; i++)
	{
		spos[i] = m_PosShow.GetItemText(iget, i+1);
	}

	//
	//if (!pGlobal->RbtSocket.m_bConnected)
	//{
	//	pGlobal->AddToRunList(_T("socketδ���ӣ�"));
	//	return;
	//}
	CString str = _T("#,MOV,5,") + spos[0] + _T(",") + spos[1] + _T(",") + spos[2] + _T(",") + spos[3] + _T(",") + spos[4] + _T(",") + spos[5] + _T(",") + spos[6] + _T(",") + _T("30@");//#,MOV,4,740, 0, 480, 180, 0, 180, -1,30@
	bool ret = pGlobal->RbtSocket.SendMSG(str);
	return;
}



void RobotControldlg::OnBnClickedBtnGet()
{
	POSITION pos = m_PosShow.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("��ѡ����Ӧ��λ"));
		return;
	}

	CString str = _T("#,P,1,0,@");//��ȡ��ǰ����	
	bool ret = pGlobal->RbtSocket.SendMSG(str);
	Rbtstep = 1;
	AfxBeginThread(RobotMotion, this);
}
bool RobotControldlg::IOupdata()
{
	GetIOSetIOBtm();
	return true;
}
UINT RobotControldlg::IOUpdatdaThread(LPVOID lparam)
{
	RobotControldlg *RBTdlg = (RobotControldlg *)lparam;
	while (true)
	{
		if (true == RBTdlg->bIOUpdata)
		{
			//RBTdlg->IOupdata();
			//CString str, sMSG;
			//sMSG = _T("#,IO,4,0,@");
			//try
			//{
			//	pGlobal->BaseRbtSend(sMSG);//�û����̷߳���
			//}
			//catch (const std::exception&)
			//{
			//	//return 0;
			//}
			RBTdlg->GetIOSetIOBtm();

		}
		Sleep(1000);
	}
	return 1;
}
UINT RobotControldlg::RobotMotion(LPVOID lparam)
{
	RobotControldlg *RBTdlg = (RobotControldlg *)lparam;

	switch (RBTdlg->Rbtstep)
	{
	case 1:  		RBTdlg->GetCurPosFromSocekt();		            break;
	case 2:  		RBTdlg->GetIOSetIOBtm();		                break;
	case 3:  		RBTdlg->CloseClamp();		                    break;
	case 4:  		RBTdlg->OpenClamp();		                    break;
	case 5:  		RBTdlg->IniIOClamp();		                    break;
	default:
		break;
	}

	return 1;
}
int RobotControldlg::GetIOSetIOBtm()
{
	RBTIOReadALL();
	SetIOBtmStatue();
	return 1;
}
int RobotControldlg::GetCurPosFromSocekt()
{
	//if (!pGlobal->RbtSocket.m_bConnected)
	//{
	//	AfxMessageBox(_T("socketδ���ӣ�"));
	//	pGlobal->AddToRunList(_T("socketδ���ӣ�"));
	//	return 0;
	//}
	//�����ݲ��뵽�����
	POSITION pos = m_PosShow.GetFirstSelectedItemPosition();
	int iget = m_PosShow.GetNextSelectedItem(pos);

    ResetEvent(pGlobal->Handle_GetPOS);
//	CString str = _T("#,P,1,0,@");//��ȡ��ǰ����	
//	bool ret = pGlobal->RbtSocket.SendMSG(str);
	DWORD dwState = WaitForSingleObject(pGlobal->Handle_GetPOS, 2000);
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_GetPOS);
		CurPos.Trim(_T("P()"));
		CStringSplit(CurPos,sCurPos,_T(","));//P(51.43818, 340.9811, 864.1849, -172.2437, -8.488414, 29.29736, 13)		
		for (int i = 0; i < 7; i++)
		{
			m_PosShow.SetItemText(iget, i + 1, sCurPos[i]);//��������
		}
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_GetPOS);
		pGlobal->AddToRunList(_T("��ȡ������λ�ó�ʱ��"));
		AfxMessageBox(_T("��ȡ������λ�ó�ʱ"));
		return 0;
	}	
	return 1;
}

int RobotControldlg::MoveToPostion(int MovModle, CString sPOS[7], double dbLen)
{
	CString slen;
	slen.Format(_T("%f"), dbLen);
	CString str = sPOS[0] + _T(",") + sPOS[1] + _T(",") + sPOS[2] + _T(",") + sPOS[3] + _T(",") + sPOS[4] + _T(",") + sPOS[5] + _T(",") + sPOS[6] + _T(",") + slen + _T(",") + _T("@");//#,MOV,4,740, 0, 480, 180, 0, 180, -1,30,@
	CString sMSG;
	switch (MovModle)
	{
	case Approch_P:	  sMSG = _T("#,MOV,1,") + str;	break;
	case Approch_L:	  sMSG = _T("#,MOV,2,") + str;	break;
	case Depart_P:	  sMSG = _T("#,MOV,3,") + str;	break;
	case Move_P:	  sMSG = _T("#,MOV,4,") + str;  break;
	case Move_L:	  sMSG = _T("#,MOV,5,") + str;  break;
	default:		  return 0;		                break;
	}
	//bool ret = pGlobal->RbtSocket.SendMSG(sMSG);
	pGlobal->MoveRbtSend(sMSG);
	ResetEvent(pGlobal->Handle_FinishPOS[0]);
	ResetEvent(pGlobal->Handle_FinishPOS[1]);
	DWORD  dwReturn = WaitForMultipleObjects(2,pGlobal->Handle_FinishPOS, FALSE,20000);//20s�ĵ�λ��ʱ
	if (dwReturn - WAIT_OBJECT_0 == 0)
	{
		pGlobal->AddToRunList(_T("�����˵�ָ����λ"));
		ResetEvent(pGlobal->Handle_FinishPOS[0]);
		return 1;
	}
	else if (dwReturn - WAIT_OBJECT_0 == 1)
	{
		pGlobal->AddToErrorList(_T("�������ֶ�ֹͣ"));
		ResetEvent(pGlobal->Handle_FinishPOS[1]);
		return 0;
	}
	else if (WAIT_TIMEOUT == dwReturn)
	{
		pGlobal->AddToErrorList(_T("�ƶ���ָ����λ��ʱ"));
		ResetEvent(pGlobal->Handle_FinishPOS[0]);
		ResetEvent(pGlobal->Handle_FinishPOS[1]);
		return 0;
	}
}

int RobotControldlg::SingleAxisMove(int iAxis, CString sAngle)
{
	CString sMSG;
	switch (iAxis)
	{
	case Axis_1_X:	  sMSG = _T("#,S,1,") + sAngle + _T(",@");	break;
	case Axis_2_Y:	  sMSG = _T("#,S,2,") + sAngle + _T(",@");	break;
	case Axis_3_Z:	  sMSG = _T("#,S,3,") + sAngle + _T(",@");	break;
	case Axis_4_RX:	  sMSG = _T("#,S,4,") + sAngle + _T(",@");  break;
	case Axis_5_RY:	  sMSG = _T("#,S,5,") + sAngle + _T(",@");  break;
	case Axis_6_RZ:	  sMSG = _T("#,S,6,") + sAngle + _T(",@");  break;
	default:		  return 0;		                break;
	}
	//bool ret = pGlobal->RbtSocket.SendMSG(sMSG);
	pGlobal->MoveRbtSend(sMSG);
	ResetEvent(pGlobal->Handle_FinishPOS[0]);
	ResetEvent(pGlobal->Handle_FinishPOS[1]);
	DWORD  dwReturn = WaitForMultipleObjects(2, pGlobal->Handle_FinishPOS, FALSE, 20000);//20s�ĵ�λ��ʱ
	if (dwReturn - WAIT_OBJECT_0 == 0)
	{
		pGlobal->AddToRunList(_T("�����˵��ᵽָ����λ"));
		ResetEvent(pGlobal->Handle_FinishPOS[0]);
		return 1;
	}
	else if (dwReturn - WAIT_OBJECT_0 == 1)
	{
		pGlobal->AddToErrorList(_T("�������ֶ�ֹͣ"));
		ResetEvent(pGlobal->Handle_FinishPOS[1]);
		return 0;
	}
	else if (WAIT_TIMEOUT == dwReturn)
	{
		pGlobal->AddToErrorList(_T("�ƶ���ָ����λ��ʱ"));
		ResetEvent(pGlobal->Handle_FinishPOS[0]);
		ResetEvent(pGlobal->Handle_FinishPOS[1]);
		return 0;
	}
}

int RobotControldlg::X_YSpaceAxisMove(int iAxis, CString slen)
{
	CString sMSG;
	switch (iAxis)
	{
	case Axis_1_X:	  sMSG = _T("#,M,1,") + slen + _T(",@");	break;
	case Axis_2_Y:	  sMSG = _T("#,M,2,") + slen + _T(",@");	break;
	case Axis_3_Z:	  sMSG = _T("#,M,3,") + slen + _T(",@");	break;
	case Axis_4_RX:	  sMSG = _T("#,M,4,") + slen + _T(",@");  break;
	case Axis_5_RY:	  sMSG = _T("#,M,5,") + slen + _T(",@");  break;
	case Axis_6_RZ:	  sMSG = _T("#,M,6,") + slen + _T(",@");  break;
	default:		  return 0;		                break;
	}
	//bool ret = pGlobal->RbtSocket.SendMSG(sMSG);
	pGlobal->MoveRbtSend(sMSG);
	ResetEvent(pGlobal->Handle_FinishPOS[0]);
	ResetEvent(pGlobal->Handle_FinishPOS[1]);
	DWORD  dwReturn = WaitForMultipleObjects(2, pGlobal->Handle_FinishPOS, FALSE, 20000);//20s�ĵ�λ��ʱ
	if (dwReturn - WAIT_OBJECT_0 == 0)
	{
		pGlobal->AddToRunList(_T("�����˵��ᵽָ����λ"));
		ResetEvent(pGlobal->Handle_FinishPOS[0]);
		return 1;
	}
	else if (dwReturn - WAIT_OBJECT_0 == 1)
	{
		pGlobal->AddToErrorList(_T("�������ֶ�ֹͣ"));
		ResetEvent(pGlobal->Handle_FinishPOS[1]);
		return 0;
	}
	else if (WAIT_TIMEOUT == dwReturn)
	{
		pGlobal->AddToErrorList(_T("�ƶ���ָ����λ��ʱ"));
		ResetEvent(pGlobal->Handle_FinishPOS[0]);
		ResetEvent(pGlobal->Handle_FinishPOS[1]);
		return 0;
	}
}

int RobotControldlg::RBTIORead(int IONum)
{
	CString str, sMSG;
	str.Format(_T("%d"), IONum);
	sMSG = _T("#,IO,3,") + str + _T(",@");
	//bool ret = pGlobal->RbtSocket.SendMSG(sMSG);
	pGlobal->MoveRbtSend(sMSG);
	ResetEvent(pGlobal->Handle_RBTReadIO[0]);
	ResetEvent(pGlobal->Handle_RBTReadIO[1]);
	DWORD  dwReturn = WaitForMultipleObjects(3, pGlobal->Handle_RBTReadIO, FALSE, 6000);//20s�ĵ�λ��ʱ
	if (dwReturn - WAIT_OBJECT_0 == 0)
	{
		//pGlobal->AddToRunList(_T("������IO����ΪOFF"));
		ResetEvent(pGlobal->Handle_RBTReadIO[0]);
		return 0;
	}
	else if (dwReturn - WAIT_OBJECT_0 == 1)
	{
		//pGlobal->AddToErrorList(_T("������IO����ΪOFF"));
		ResetEvent(pGlobal->Handle_RBTReadIO[1]);
		return 1;
	}
	else if (WAIT_TIMEOUT == dwReturn)
	{
		pGlobal->AddToErrorList(_T("������IO 2s ��ȡ��ʱ"));
		ResetEvent(pGlobal->Handle_RBTReadIO[0]);
		ResetEvent(pGlobal->Handle_RBTReadIO[1]);
		return 0;
	}
}

int RobotControldlg::RBTIOReadALL()
{
	CString str, sMSG;
	sMSG = _T("#,IO,4,0,@");
	pGlobal->BaseRbtSend(sMSG);//�û����̷߳���
	//bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û����̷߳���

	ResetEvent(pGlobal->Handle_RBTReadIO[0]);
	ResetEvent(pGlobal->Handle_RBTReadIO[1]);
	ResetEvent(pGlobal->Handle_RBTReadIO[2]);
	DWORD  dwReturn = WaitForMultipleObjects(3, pGlobal->Handle_RBTReadIO, FALSE, 5000);//20s�ĵ�λ��ʱ
	if (dwReturn - WAIT_OBJECT_0 == 2)
	{
		//pGlobal->AddToRunList(_T(""));
		for (int i = 0; i < 32; i++)
		{
			sCurSingleIO[i] = sCurFullIOVal.Mid(i,1);
			iCurSingleIO[i] = _ttoi(sCurSingleIO[i]);
		}		
		ResetEvent(pGlobal->Handle_RBTReadIO[2]);
		return 1;
	}
	else if (WAIT_TIMEOUT == dwReturn)
	{
		pGlobal->AddToErrorList(_T("������SOCKET�����쳣���봦��....."));
		ResetEvent(pGlobal->Handle_RBTReadIO[2]);
		return 0;
	}
}

int RobotControldlg::RBTIOSet(int IONum)
{
	CString str,sMSG;
	str.Format(_T("%d"), IONum);
	sMSG = _T("#,IO,1,") + str + _T(",@");
	//bool ret = pGlobal->RbtSocket.SendMSG(sMSG);
	pGlobal->MoveRbtSend(sMSG);
	return 1;
}

int RobotControldlg::RBTIOReset(int IONum)
{
	CString str, sMSG;
	str.Format(_T("%d"), IONum);
	sMSG = _T("#,IO,2,") + str + _T(",@");
	//bool ret = pGlobal->RbtSocket.SendMSG(sMSG);
	pGlobal->MoveRbtSend(sMSG);
	return 1;
}


void RobotControldlg::OnBnClickedBtnSavepos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BTN_SAVEPOS)->EnableWindow(FALSE);
	pGlobal->AddToRunList(_T("��ʼ�����������ȴ����"));
	WritePosToINI();
	pGlobal->AddToRunList(_T("�����λ�������"));
	GetDlgItem(IDC_BTN_SAVEPOS)->EnableWindow(TRUE);
}


void RobotControldlg::OnBnClickedBtnUpdatapos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BTN_UPDATAPOS)->EnableWindow(FALSE);
	m_PosShow.DeleteAllItems();
	PosListIni();
	ReadPosFromINI();	
	InsertDataPosList();
	pGlobal->AddToRunList(_T("ˢ�µ�λ����"));
	GetDlgItem(IDC_BTN_UPDATAPOS)->EnableWindow(TRUE);
}


void RobotControldlg::OnBnClickedStartbasesocket()
{
	// ������˳��򴴽��ķ���������
	bool ret;
	CString str;
	GetDlgItemText(IDC_StartBaseSocket, str);
	if (_T("����������") == str)
	{
		ret = pGlobal->BaseRbtSocket.Config();
		if (ret)
		{
		//	pGlobal->AddToRunList(_T("�����˷��������ӳɹ�����"));
		//	pGlobal->BaseRbtSocket.SendMSG(_T("#,B,1,0,@"));//����ϵ�
			pGlobal->BaseRbtSocket.SendMSG(_T("#,B,3,0,@"));//�˶�����������
			SetDlgItemText(IDC_StartBaseSocket, _T("�رշ�����"));
			ConWidgetStatue(TRUE);
		}
		else
		{
			pGlobal->AddToRunList(_T("�����˷���������ʧ�ܣ���"));
			pGlobal->BaseRbtSocket.CloseSocket();
		}
	}
	else if (_T("�رշ�����") == str)
	{
		ConWidgetStatue(FALSE);
		MoveWidgetStatue(FALSE);
		BaseWidgetStatue(FALSE);
		pGlobal->BaseRbtSocket.CloseSocket();
		pGlobal->AddToRunList(_T("�����˷������Ͽ����ӣ���"));
		SetDlgItemText(IDC_StartBaseSocket, _T("����������"));
		pGlobal->BaseRbtSocket.m_bConnected = FALSE;
		KillTimer(1);
	}
}

void RobotControldlg::OnBnClickedBtnBaserbtsend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString stext;
	GetDlgItemText(IDC_EDIT_BaseRBTTEXT, stext);
	bool ret = pGlobal->BaseRbtSocket.SendMSG(stext);
}


void RobotControldlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pGlobal->BaseRbtSocket.SendMSG(_T("#,B,3,0,@"));//�˶�����������
}

void RobotControldlg::OnBnClickedBtnSuspend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pGlobal->BaseRbtSocket.SendMSG(_T("#,B,4,0,@"));//�˶���������ͣ
}

void RobotControldlg::OnBnClickedBtnStop()
{
	pGlobal->bRunAutoThread = false;
	pGlobal->bCycleStop = true;
	pGlobal->bRunStop = true;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pGlobal->BaseRbtSocket.SendMSG(_T("#,B,5,0,@"));//�˶�������ֹͣ
}


void RobotControldlg::OnBnClickedBtnMotoron()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_BTN_MotorON, str);
	if (_T("Motor_ON") == str)
	{
		pGlobal->BaseRbtSocket.SendMSG(_T("#,B,1,0,@"));//����ϵ�
		SetDlgItemText(IDC_BTN_MotorON, _T("Motor_OFF"));
		//MoveWidgetStatue(TRUE);
	}
	else if (_T("Motor_OFF") == str)
	{
		//MoveWidgetStatue(FALSE);
		pGlobal->BaseRbtSocket.SendMSG(_T("#,B,2,0,@"));//����ϵ�
		SetDlgItemText(IDC_BTN_MotorON, _T("Motor_ON"));
	}
}


void RobotControldlg::OnBnClickedBtnGetcurpos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("#,P,1,0,@");//��ȡ��ǰ����	
	bool ret = pGlobal->RbtSocket.SendMSG(str);
}

void RobotControldlg::SetIOBtmStatue()
{
	for (int i = 0; i < 32; i++)
	{
		switch (i)
		{
		case 0:        m_IO0.GreenOrRed(iCurSingleIO[i]);        break;
		case 1:        m_IO1.GreenOrRed(iCurSingleIO[i]);        break;
		case 2:        m_IO2.GreenOrRed(iCurSingleIO[i]);        break;
		case 3:        m_IO3.GreenOrRed(iCurSingleIO[i]);        break;
		case 4:        m_IO4.GreenOrRed(iCurSingleIO[i]);        break;
		case 5:        m_IO5.GreenOrRed(iCurSingleIO[i]);        break;
		case 6:        m_IO6.GreenOrRed(iCurSingleIO[i]);        break;
		case 7:        m_IO7.GreenOrRed(iCurSingleIO[i]);        break;
		case 8:        m_IO8.GreenOrRed(iCurSingleIO[i]);        break;
		case 9:        m_IO9.GreenOrRed(iCurSingleIO[i]);        break;
		case 10:       m_IO10.GreenOrRed(iCurSingleIO[i]);       break;
		case 11:       m_IO11.GreenOrRed(iCurSingleIO[i]);       break;
		case 12:       m_IO12.GreenOrRed(iCurSingleIO[i]);       break;
		case 13:       m_IO13.GreenOrRed(iCurSingleIO[i]);       break;
		case 14:       m_IO14.GreenOrRed(iCurSingleIO[i]);       break;
		case 15:       m_IO15.GreenOrRed(iCurSingleIO[i]);       break;
		case 16:       m_IO16.GreenOrRed(iCurSingleIO[i]);       break;
		case 17:       m_IO17.GreenOrRed(iCurSingleIO[i]);       break;
		case 18:       m_IO18.GreenOrRed(iCurSingleIO[i]);       break;
		case 19:       m_IO19.GreenOrRed(iCurSingleIO[i]);       break;
		case 20:       m_IO20.GreenOrRed(iCurSingleIO[i]);       break;
		case 21:       m_IO21.GreenOrRed(iCurSingleIO[i]);       break;
		case 22:       m_IO22.GreenOrRed(iCurSingleIO[i]);       break;
		case 23:       m_IO23.GreenOrRed(iCurSingleIO[i]);       break;
		case 24:       m_IO24.GreenOrRed(iCurSingleIO[i]);       break;
		case 25:       m_IO25.GreenOrRed(iCurSingleIO[i]);       break;
		case 26:       m_IO26.GreenOrRed(iCurSingleIO[i]);       break;
		case 27:       m_IO27.GreenOrRed(iCurSingleIO[i]);       break;
		case 28:       m_IO28.GreenOrRed(iCurSingleIO[i]);       break;
		case 29:       m_IO29.GreenOrRed(iCurSingleIO[i]);       break;
		case 30:       m_IO30.GreenOrRed(iCurSingleIO[i]);       break;
		case 31:       m_IO31.GreenOrRed(iCurSingleIO[i]);       break;
		default:
			break;
		}
	}
   
}

bool RobotControldlg::OpenClamp()
{
	CString sMSG;
	int ret;
//	RBTIOReset(29);//�ر��˶�
//	Sleep(50);
	RBTIOReset(31);//��צ�н�����
	Sleep(100);

	RBTIOSet(30); // ��צ�ɿ�
	Sleep(100);
//	RBTIOSet(29); // ��צ�ɿ�
//	Sleep(100);
	for (int i = 0; i < 8; i++)
	{
		
		if (iCurSingleIO[14] == 1 )
	//	if (RBTIORead(14) == 1)
		{
			pGlobal->AddToRunList(_T("��צ�򿪳ɹ�"));
			RBTIOReset(30); // ��צ�ɿ�����
			Sleep(100);
			return true;
		}
		else
		{
			Sleep(500);
		}
	}
	pGlobal->AddToErrorList(_T("��צ��4s��ʱ"));
	return false;
}

bool RobotControldlg::CloseClamp()
{
	CString sMSG;
	bool ret;
	//if (iCurSingleIO[29] == 1)
	//{
	//	pGlobal->AddToRunList(_T("��צ�Ѵ��ڼн�״̬"));
	//	return true;
	//}
//	RBTIOReset(29);//��צ�˶���0
//	Sleep(100);
	RBTIOReset(30);//��צ�ɿ���0
	Sleep(100);

	RBTIOSet(31);//��צ�н�
	Sleep(100);
//	RBTIOSet(29);//��צ�н�
//	Sleep(100);
//	Sleep(2000);
	for (int i = 0; i < 8; i++)
	{
		if (iCurSingleIO[15] == 1)//���н���λ�ź�
		//if (RBTIORead(15) == 1)
		{
			pGlobal->AddToRunList(_T("��צ�н��ɹ�"));
			RBTIOReset(31); // ��צ�ɿ�����
			Sleep(100);
			return true;
		}
		else
		{
			Sleep(500);
		}
	}
	pGlobal->AddToErrorList(_T("��צ�н�4S��ʱ����ȷ�ϼ�צ���Ƿ�����"));
	return false;
}

bool RobotControldlg::IniIOClamp()
{
	CString sMSG;
	int ret;
	//RBTIOSet(25);//ֹͣ
	//Sleep(50);
	RBTIOSet(28);//������λ
	Sleep(100);
	RBTIOSet(27);//��צ�ŷ�ON
	Sleep(100);
	RBTIOReset(25);//ֹͣ�ź����
	Sleep(100);
	RBTIOReset(28);//������λ�ź����
	Sleep(100);
//	RBTIOReset(29);//�˶��ź����
//	Sleep(50);
	RBTIOReset(30);//�ɿ��ź����
	Sleep(100);
	RBTIOReset(31);//�н��ź����
	Sleep(100);
	RBTIOReset(25);//ֹͣ
	Sleep(100);
	RBTIOSet(24);//��ԭ��/��λ
	Sleep(100);
	for (int i = 0; i < 10; i++)
	{
		if (iCurSingleIO[10] == 1)
		{
			pGlobal->AddToRunList(_T("��צ��ʼ����λ���"));
			RBTIOReset(24);//��ԭ���ź����
			Sleep(100);
			OpenClamp();
			break;
		}
		else
		{
			if (i == 9)
			{
				pGlobal->AddToErrorList(_T("��צ��λ5s��ʱ"));
				return false;
			}
			Sleep(500);
		}
	}
	//OpenClamp();
	return true;
}
void RobotControldlg::OnBnClickedBtnUpdataiobtnstatue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Rbtstep = 2;
	CString str, sMSG;
	sMSG = _T("#,IO,4,0,@");
	bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û����̷߳���
	AfxBeginThread(RobotMotion, this);
}


void RobotControldlg::OnBnClickedBtnIo24()
{
	CString sMSG;
	if (1 == iCurSingleIO[24])
	{
		sMSG = _T("#,IO,2,24,@");
		//m_IO24.Red();
	}
	else
	{
		sMSG = _T("#,IO,1,24,@");
		//m_IO24.Green();
	}
	bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û����̷߳���
}


void RobotControldlg::OnBnClickedBtnIo25()
{
	CString sMSG;
	if (1 == iCurSingleIO[25])
	{
		sMSG = _T("#,IO,2,25,@");
		//m_IO25.Red();
	}
	else
	{
		sMSG = _T("#,IO,1,25,@");
		//m_IO25.Green();
	}
	bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û����̷߳���
}


void RobotControldlg::OnBnClickedBtnIo26()
{
	CString sMSG;
	if (1 == iCurSingleIO[26])
	{
		sMSG = _T("#,IO,2,26,@");
		//m_IO26.Red();
	}
	else
	{
		sMSG = _T("#,IO,1,26,@");
		//m_IO26.Green();
	}
	bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û����̷߳���
}


void RobotControldlg::OnBnClickedBtnIo27()
{
	CString sMSG;
	if (1 == iCurSingleIO[27])
	{
		sMSG = _T("#,IO,2,27,@");
		//m_IO27.Red();
	}
	else
	{
		sMSG = _T("#,IO,1,27,@");
		//m_IO27.Green();
	}
	bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û����̷߳���

}


void RobotControldlg::OnBnClickedBtnIo28()
{
	CString sMSG;
	if (1 == iCurSingleIO[28])
	{
		sMSG = _T("#,IO,2,28,@");
		//m_IO28.Red();
	}
	else
	{
		sMSG = _T("#,IO,1,28,@");
		//m_IO28.Green();
	}
	bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û����̷߳���
}


void RobotControldlg::OnBnClickedBtnIo29()
{
	CString sMSG;
	if (1 == iCurSingleIO[29])
	{
		sMSG = _T("#,IO,2,29,@");
		//m_IO29.Red();
	}
	else
	{
		sMSG = _T("#,IO,1,29,@");
		//m_IO29.Green();
	}
	bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û�������
}


void RobotControldlg::OnBnClickedBtnIo30()
{
	CString sMSG;
	if (1 == iCurSingleIO[30])
	{
		sMSG = _T("#,IO,2,30,@");
	//	m_IO30.Red();
	}
	else
	{
		sMSG = _T("#,IO,1,30,@");
	//	m_IO30.Green();
	}
	bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û���socket����
}


void RobotControldlg::OnBnClickedBtnIo31()
{
	CString sMSG;
	if (1 == iCurSingleIO[31])
	{
		sMSG = _T("#,IO,2,31,@");
	//	m_IO31.Red();
	}
	else
	{
		sMSG = _T("#,IO,1,31,@");
	//	m_IO31.Green();
	}
	bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û���socket����
}

void RobotControldlg::ConWidgetStatue(BOOL bShow)
{
	GetDlgItem(IDC_BTN_IPConnect)->EnableWindow(bShow);
}
void RobotControldlg::MoveWidgetStatue(BOOL bShow)
{
	GetDlgItem(IDC_COMBO_AxisModle)->EnableWindow(bShow);
	GetDlgItem(IDC_SLIDER_SPEED)->EnableWindow(bShow);
	GetDlgItem(IDC_EDIT_JOGDis)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J1Xsub)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J1Xadd)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J2Ysub)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J2Yadd)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J3Zsub)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J3Zadd)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J4RXsub)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J4RXadd)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J5RYsub)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J5RYadd)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J6RZsub)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_J6RZadd)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_GoPOS)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_GET)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_GETCURPOS)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_BaseRBTSEND)->EnableWindow(bShow);
	GetDlgItem(IDC_EDIT_BaseRBTTEXT)->EnableWindow(bShow);

	GetDlgItem(IDC_BTN_IniClamp)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_CloseClamp)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_OpenClamp)->EnableWindow(bShow);

}

void RobotControldlg::BaseWidgetStatue(BOOL bShow)
{
	
	GetDlgItem(IDC_BTN_MotorON)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_Start)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_Suspend)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_RBTSEND)->EnableWindow(bShow);
	GetDlgItem(IDC_EDIT_RBTTEXT)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_IO24)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_IO25)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_IO26)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_IO27)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_IO28)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_IO29)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_IO30)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_IO31)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_UpdataIOBtnStatue)->EnableWindow(bShow);

}

void RobotControldlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1 /*&& pGlobal->BaseRbtSocket.m_bConnected == true*/)
	{
		Rbtstep = 2;
		CString str, sMSG;
		sMSG = _T("#,IO,4,0,@");
		try
		{
			bool ret = pGlobal->BaseRbtSocket.SendMSG(sMSG);//�û����̷߳���
		}
		catch (const std::exception&)
		{
			return;
		}		
		AfxBeginThread(RobotMotion, this);
	}
	else if (nIDEvent == 2 )
	{
		if (iCurSingleIO[14] == 0)
		{
			

		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void RobotControldlg::OnBnClickedBtnSetgetdis()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_EDIT_GetProDis, str);
	dbGetProDis = _ttof(str);
	WritePrivateProfileString(_T("ProcessDATA"), _T("RbtDownDis"), str, _T(".\\SystemInfo.ini"));
}


void RobotControldlg::OnBnClickedBtnCloseclamp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Rbtstep = 3;
	AfxBeginThread(RobotMotion, this);

}


void RobotControldlg::OnBnClickedBtnOpenclamp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Rbtstep = 4;
	AfxBeginThread(RobotMotion, this);
}


void RobotControldlg::OnBnClickedBtnIniclamp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Rbtstep = 5;//��צ��ʼ���߳�
	AfxBeginThread(RobotMotion, this);//
}


void RobotControldlg::OnBnClickedBtnSetprocessnum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	int iret;
	GetDlgItemText(IDC_EDIT_ProcessNum, str);
	iret = _ttoi(str);
	if (iret<1 || iret>40)
	{
		AfxMessageBox(_T("ȡ���ϵ�����Ӧ����1-40��"));
		return;
	}
	iProcessNum = iret;

	WritePrivateProfileString(_T("ProcessDATA"), _T("ProcessNum"), str, _T(".\\SystemInfo.ini"));
}


void RobotControldlg::OnBnClickedCheckOpentranspos()
{
	CString sText;
	int state = ((CButton *)GetDlgItem(IDC_CHECK_OpenTransPOS))->GetCheck();
	if (1 == state)
	{
		bNeedTransPos = true;
		sText = _T("1");
	}
	else
	{
		bNeedTransPos = false;
		sText = _T("0");
	}
	WritePrivateProfileString(_T("ProcessDATA"), _T("NeedTransPos"), sText, _T(".\\SystemInfo.ini"));
}
