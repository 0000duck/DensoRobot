// VisionTestdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "VisionTestdlg.h"
#include "afxdialogex.h"


// VisionTestdlg 对话框

IMPLEMENT_DYNAMIC(VisionTestdlg, CDialogEx)

VisionTestdlg::VisionTestdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_VisionTest, pParent)
{
	sRomateAngle = _T("0");
}

VisionTestdlg::~VisionTestdlg()
{
}

void VisionTestdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VisionTestdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_GETCURPOS, &VisionTestdlg::OnBnClickedBtnGetcurpos)
	ON_BN_CLICKED(IDC_BTN_SendPosToCam, &VisionTestdlg::OnBnClickedBtnSendpostocam)
	ON_BN_CLICKED(IDC_BTN_MoveToRetPOS, &VisionTestdlg::OnBnClickedBtnMovetoretpos)
	ON_BN_CLICKED(IDC_BTN_ConVisonSocket, &VisionTestdlg::OnBnClickedBtnConvisonsocket)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_bVisCon, &VisionTestdlg::OnBnClickedCheckbviscon)
END_MESSAGE_MAP()


// VisionTestdlg 消息处理程序
BOOL VisionTestdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CString str;
	GetPrivateProfileString(_T("VisionSocekt"), _T("IP"), _T("10.10.11.127"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	SetDlgItemText(IDC_EDIT_VisionIP, str);
	GetPrivateProfileString(_T("VisionSocekt"), _T("Port"), _T("8989"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	SetDlgItemText(IDC_EDIT_VisionPort, str);
	GetPrivateProfileString(_T("VisionSocekt"), _T("bConnect"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	((CButton *)GetDlgItem(IDC_CHECK_bVisCon))->SetCheck(_ttoi(str));
	if (_T("1") == str)
	{
		pGlobal->bVisionCon = true;
	}
	else
	{
		pGlobal->bVisionCon = false;
	}
	GetDlgItem(IDC_BTN_GETCURPOS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SendPosToCam)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_MoveToRetPOS)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void VisionTestdlg::OnBnClickedBtnGetcurpos()
{
	//if (!pGlobal->RbtSocket.m_bConnected)
	//{
	//	pGlobal->AddToRunList(_T("Robot socket未连接！"));
	//	return;
	//}
	CString str = _T("#,P,1,0,@");//获取当前坐标	
	bool ret = pGlobal->RbtSocket.SendMSG(str);
	ithread = 1;
	AfxBeginThread(VisionDlgThread, this);
	GetDlgItem(IDC_BTN_SendPosToCam)->EnableWindow(TRUE);
}

UINT VisionTestdlg::VisionDlgThread(LPVOID lparam)
{
	VisionTestdlg *pVdlg = (VisionTestdlg *)lparam;
	switch (pVdlg->ithread)
	{
	case 1:  		pVdlg->VisionGetCurPosFromSocekt();		        break;
	case 2:  		pVdlg->VisionReturnPos();		                break;
	case 3:  		pVdlg->GoVisionReturnPos();		                break;
	default:
		break;
	}

	return 1;
}

void VisionTestdlg::VisionGetCurPosFromSocekt()
{
	ResetEvent(pGlobal->Handle_GetPOS);
	DWORD dwState = WaitForSingleObject(pGlobal->Handle_GetPOS, 2000);
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_GetPOS);		
		pGlobal->RBTCTdlg.CurPos.Trim(_T("P()"));
		SetDlgItemText(IDC_EDIT_GotPos, pGlobal->RBTCTdlg.CurPos);
		CStringSplit(pGlobal->RBTCTdlg.CurPos, pGlobal->RBTCTdlg.sCurPos, _T(","));//P(51.43818, 340.9811, 864.1849, -172.2437, -8.488414, 29.29736, 13)		
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_GetPOS);
		pGlobal->AddToRunList(_T("获取机器人位置超时！"));
		AfxMessageBox(_T("获取机器人位置超时"));
		return ;
	}
}

void VisionTestdlg::OnBnClickedBtnSendpostocam()
{

	CString sMSG;
	CString str;
	GetDlgItemText(IDC_EDIT_GotPos, str);// 0, 0, 0, 0, 0, 0, 0
	sMSG = _T("#,P,1,") + str + _T(",@");
	pGlobal->VisMarkSocekt.SendMSG(sMSG);
	ithread = 2;
	AfxBeginThread(VisionDlgThread, this);
}
int VisionTestdlg::GoVisionReturnPos()
{
	//CString str = _T("#,MOV,4,") + sRecvPos[0] + _T(",") + sRecvPos[1] + _T(",") + sRecvPos[2] + _T(",") + sRecvPos[3] + _T(",") + sRecvPos[4] + _T(",") + sRecvPos[5] + _T(",") + sRecvPos[6] + _T(",") + _T("30,@");//#,MOV,4,740, 0, 480, 180, 0, 180, -1,30,@
	int ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sRecvPos,100);
	if (!ret)
	{
		return 0;
	}
	//ret = pGlobal->RBTCTdlg.SingleAxisMove(Axis_6_RZ, sRomateAngle);
	//if (!ret)
	//{
	//	return 0;
	//}
	return 1;
}
int VisionTestdlg::VisionReturnPos()
{
	CString sret[12];
	//pGlobal->VisionSend();
	ResetEvent(pGlobal->Handle_VisionRetPOS);
	DWORD dwState = WaitForSingleObject(pGlobal->Handle_VisionRetPOS, 8000);
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		SetDlgItemText(IDC_EDIT_VisionReturnPos, sVisRetPos);
		CStringSplit(sVisRetPos, sret, _T(","));//#,P,1,0,0,0,0,0,0,0,@
		if (_T("2") == sret[2])
		{
			pGlobal->AddToErrorList(_T("VISION返回算法计算错误"));
			return 2;
		}
		else if (_T("1") == sret[2])
		{
			for (int i = 0; i < 7; i++)
			{
				sRecvPos[i] = sret[i + 3];
			}
			sRomateAngle = sret[10];
			return 1;
		}
		else if (_T("3") == sret[2])
		{
			for (int i = 0; i < 7; i++)
			{
				sRecvPos[i] = sret[i + 3];
			}
			sRomateAngle = sret[10];
			return 3;
		}
		else
		{
			pGlobal->AddToErrorList(_T("VISION返回值格式错误"));
			return 0;
		}
		
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		pGlobal->AddToRunList(_T("获取Vision返回位置超时！"));
		AfxMessageBox(_T("获取Vision返回位置超时"));
		return 0;
	}
	return 1;
}

int VisionTestdlg::SendAndGetVisRetPos(CString sendpos[7])
{
	CString sret[12];
	CString sMSG = _T("#,P,1,") + sendpos[0] + _T(",") + sendpos[1] + _T(",") + sendpos[2] + _T(",") + sendpos[3] + _T(",") + sendpos[4] + _T(",") + sendpos[5] + _T(",") + sendpos[6] + _T(",@");
	pGlobal->VisionSend(sMSG);
	ResetEvent(pGlobal->Handle_VisionRetPOS);
	DWORD dwState = WaitForSingleObject(pGlobal->Handle_VisionRetPOS, 8000);
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		SetDlgItemText(IDC_EDIT_VisionReturnPos, sVisRetPos);
		CStringSplit(sVisRetPos, sret, _T(","));//#,P,1,0,0,0,0,0,0,0,3,@
		if (_T("2") == sret[2])
		{
			pGlobal->AddToErrorList(_T("VISION返回算法计算错误"));
			return 2;
		}
		else if(_T("1") == sret[2])
		{
			for (int i = 0; i < 7; i++)
			{
				sRecvPos[i] = sret[i + 3];
			}
			sRomateAngle = sret[10];
			return 1;
		}		
		else if (_T("3") == sret[2])
		{
			for (int i = 0; i < 7; i++)
			{
				sRecvPos[i] = sret[i + 3];				
			}
			sRomateAngle = sret[10];
			return 3;
		}
		else
		{
			pGlobal->AddToErrorList(_T("VISION返回值格式错误"));
			return 0;
		}
		
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		pGlobal->AddToRunList(_T("获取Vision返回位置超时！"));
		AfxMessageBox(_T("获取Vision返回位置超时"));
		return 0;
	}

	return 1;
}

void VisionTestdlg::OnBnClickedBtnMovetoretpos()
{
	//if (!pGlobal->RbtSocket.m_bConnected)
	//{
	//	pGlobal->AddToRunList(_T("Vision socket未连接！"));
	//	return;
	//}
	ithread = 3;
	AfxBeginThread(VisionDlgThread, this);
		
}

void VisionTestdlg::OnBnClickedBtnConvisonsocket()
{
	CString sText;
	GetDlgItemText(IDC_BTN_ConVisonSocket, sText);
	if (_T("连接") == sText)
	{
		GetDlgItemText(IDC_EDIT_VisionIP, sText);
	    pGlobal->VisMarkSocekt.sIP = sText;
		WritePrivateProfileString(_T("VisionSocekt"), _T("IP"), sText, _T(".\\SystemInfo.ini"));
		GetDlgItemText(IDC_EDIT_VisionPort, sText);
		WritePrivateProfileString(_T("VisionSocekt"), _T("8989"), sText, _T(".\\SystemInfo.ini"));
		pGlobal->VisMarkSocekt.iPort = _ttoi(sText);
		pGlobal->VisMarkSocekt.Config();
	//	pGlobal->bVisionCon = true;
		TryCount = 0;
		SetDlgItemText(IDC_BTN_ConVisonSocket, _T("断开"));
		GetDlgItem(IDC_BTN_GETCURPOS)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SendPosToCam)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_MoveToRetPOS)->EnableWindow(TRUE);

	}
	else
	{
		pGlobal->VisMarkSocekt.CloseSocket();
	//	pGlobal->bVisionCon = false;
		SetDlgItemText(IDC_BTN_ConVisonSocket, _T("连接"));
		GetDlgItem(IDC_BTN_GETCURPOS)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SendPosToCam)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_MoveToRetPOS)->EnableWindow(FALSE);
	}
	
}


void VisionTestdlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:


	default:
		break;
	}


	CDialogEx::OnTimer(nIDEvent);
}


void VisionTestdlg::OnBnClickedCheckbviscon()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sText;
	int state = ((CButton *)GetDlgItem(IDC_CHECK_bVisCon))->GetCheck();
	if (1 == state)
	{
		pGlobal->bVisionCon = true;
		sText = _T("1");
	}
	else
	{
		pGlobal->bVisionCon = false;
		sText = _T("0");
	}
	WritePrivateProfileString(_T("VisionSocekt"), _T("bConnect"), sText, _T(".\\SystemInfo.ini"));
}
