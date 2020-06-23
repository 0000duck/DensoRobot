// VisionTestdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JIMI.h"
#include "VisionTestdlg.h"
#include "afxdialogex.h"
#include <afxinet.h> 
#include <iostream>
#include <fstream>
#include "json/json.h"
#pragma comment(lib,"json_vc71_libmtd.lib")
using namespace std;

// VisionTestdlg �Ի���

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
	DDX_Control(pDX, IDC_LIST_MarkPos, m_listMarkPos);
	DDX_Control(pDX, IDC_COMBO_POS, m_combPos);
}


BEGIN_MESSAGE_MAP(VisionTestdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_GETCURPOS, &VisionTestdlg::OnBnClickedBtnGetcurpos)
	ON_BN_CLICKED(IDC_BTN_SendPosToCam, &VisionTestdlg::OnBnClickedBtnSendpostocam)
	ON_BN_CLICKED(IDC_BTN_MoveToRetPOS, &VisionTestdlg::OnBnClickedBtnMovetoretpos)
	ON_BN_CLICKED(IDC_BTN_ConVisonSocket, &VisionTestdlg::OnBnClickedBtnConvisonsocket)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_bVisCon, &VisionTestdlg::OnBnClickedCheckbviscon)
	ON_BN_CLICKED(IDC_BTN_Mark2, &VisionTestdlg::OnBnClickedBtnMark2)
	ON_BN_CLICKED(IDC_BTN_GoMarkPos, &VisionTestdlg::OnBnClickedBtnGomarkpos)
END_MESSAGE_MAP()


// VisionTestdlg ��Ϣ�������
BOOL VisionTestdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	//�Ӿ�����λ�ó�ʼ��������λ����ȡ��λ����ȣ�
	sVisGetPos;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			sVisGetPos[i][j] = pGlobal->RBTCTdlg.sFunctionPos[i*2+1][j];
		}
		iVisGetResult[i] = Vis_Null;//��ʼ��Ϊ��
		sVisGetResult[i] = _T("3");
	}
	iPosNum = 3;//��ʼ��Ĭ��ֵΪ3
	IniMarklist();
	m_combPos.SetCurSel(0);
	WidgetStatue(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void VisionTestdlg::IniMarklist()
{
	LONG lStyle;
	CString str;
	lStyle = GetWindowLong(m_listMarkPos.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_listMarkPos.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_listMarkPos.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
								//dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_listMarkPos.SetExtendedStyle(dwStyle); //������չ���

	m_listMarkPos.InsertColumn(0, _T("У׼���λ"), LVCFMT_LEFT, 120);//������
	m_listMarkPos.InsertColumn(1, _T("У׼���"), LVCFMT_LEFT, 80);//������
	m_listMarkPos.InsertColumn(2, _T("У׼�Ƕ�"), LVCFMT_LEFT, 80);//������
	m_listMarkPos.InsertColumn(3, _T("X"), LVCFMT_LEFT, 80);//������
	m_listMarkPos.InsertColumn(4, _T("Y"), LVCFMT_LEFT, 80);//������
	m_listMarkPos.InsertColumn(5, _T("Z"), LVCFMT_LEFT, 80);//������
	m_listMarkPos.InsertColumn(6, _T("RX"), LVCFMT_LEFT, 80);//������
	m_listMarkPos.InsertColumn(7, _T("RY"), LVCFMT_LEFT, 80);//������
	m_listMarkPos.InsertColumn(8, _T("RZ"), LVCFMT_LEFT, 80);//������
	m_listMarkPos.InsertColumn(9, _T("Fig"), LVCFMT_LEFT, 80);//������
	return;
}

void VisionTestdlg::WidgetStatue(BOOL bShow)
{
	GetDlgItem(IDC_BTN_GETCURPOS)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_SendPosToCam)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_MoveToRetPOS)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_Mark2)->EnableWindow(bShow);
	GetDlgItem(IDC_BTN_GoMarkPos)->EnableWindow(bShow);
}

void VisionTestdlg::OnBnClickedBtnGetcurpos()
{
	//if (!pGlobal->RbtSocket.m_bConnected)
	//{
	//	pGlobal->AddToRunList(_T("Robot socketδ���ӣ�"));
	//	return;
	//}
	CString str = _T("#,P,1,0,@");//��ȡ��ǰ����	
	bool ret = pGlobal->RbtSocket.SendMSG(str);
	ithread = 1;
	AfxBeginThread(VisionDlgThread, this);
	GetDlgItem(IDC_BTN_SendPosToCam)->EnableWindow(TRUE);
}

UINT VisionTestdlg::VisionDlgThread(LPVOID lparam)
{
	VisionTestdlg *pVdlg = (VisionTestdlg *)lparam;
	pVdlg->WidgetStatue(FALSE);
	switch (pVdlg->ithread)
	{
	case 1:  		pVdlg->VisionGetCurPosFromSocekt();		        break;
	case 2:  		pVdlg->VisionReturnPos();		                break;
	case 3:  		pVdlg->GoVisionReturnPos();		                break;
	case 4:  		pVdlg->GoGetShowMarkPos();		                break;
	case 5:  		pVdlg->GoSelPos();		                        break;
	default:
		break;
	}
	pVdlg->WidgetStatue(TRUE);
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
		pGlobal->AddToRunList(_T("��ȡ������λ�ó�ʱ��"));
		AfxMessageBox(_T("��ȡ������λ�ó�ʱ"));
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
	//ret = pGlobal->RBTCTdlg.SingleAxisMove(Axis_3_Z, sRomateAngle);
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
			pGlobal->AddToErrorList(_T("VISION�����㷨�������"));
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
			pGlobal->AddToErrorList(_T("VISION����ֵ��ʽ����"));
			return 0;
		}
		
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		pGlobal->AddToRunList(_T("��ȡVision����λ�ó�ʱ��"));
		AfxMessageBox(_T("��ȡVision����λ�ó�ʱ"));
		return 0;
	}
	return 1;
}
int VisionTestdlg::bSuccessGet()
{
	return 1;//ȷ���Ƿ���������ܣ���Ŀǰ��ʱ����
	Sleep(1000);
	CString sret[5];
	CString sMSG = _T("#,G,0,0,@");
	ResetEvent(pGlobal->Handle_VisionRetPOS);
	pGlobal->VisionSend(sMSG);
	DWORD dwState = WaitForSingleObject(pGlobal->Handle_VisionRetPOS, 8000);
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		CStringSplit(sVisRetPos, sret, _T(","));//#,G,1,0,@
		if (_T("1") == sret[2])
		{
			pGlobal->AddToErrorList(_T("VISION���ؼ��ϳɹ�"));
			return 1;
		}
		else 
		{
			pGlobal->AddToErrorList(_T("VISION���ؼ��ϴ���"));
			return 0;
		}
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		pGlobal->AddToRunList(_T("��ȡVision�ж��Ƿ���ϳɹ����س�ʱ��"));
		return 0;
	}
	return 0;
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
			pGlobal->AddToErrorList(_T("VISION�����㷨�������"));
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
			pGlobal->AddToErrorList(_T("VISION����ֵ��ʽ����"));
			return 0;
		}
		
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		pGlobal->AddToRunList(_T("��ȡVision����λ�ó�ʱ��"));
		AfxMessageBox(_T("��ȡVision����λ�ó�ʱ"));
		return 0;
	}

	return 1;
}

void VisionTestdlg::OnBnClickedBtnMovetoretpos()
{
	//if (!pGlobal->RbtSocket.m_bConnected)
	//{
	//	pGlobal->AddToRunList(_T("Vision socketδ���ӣ�"));
	//	return;
	//}
	ithread = 3;
	AfxBeginThread(VisionDlgThread, this);
		
}

void VisionTestdlg::OnBnClickedBtnConvisonsocket()
{
	CString sText;
	GetDlgItemText(IDC_BTN_ConVisonSocket, sText);
	if (_T("����") == sText)
	{
		GetDlgItemText(IDC_EDIT_VisionIP, sText);
	    pGlobal->VisMarkSocekt.sIP = sText;
		WritePrivateProfileString(_T("VisionSocekt"), _T("IP"), sText, _T(".\\SystemInfo.ini"));
		GetDlgItemText(IDC_EDIT_VisionPort, sText);
		WritePrivateProfileString(_T("VisionSocekt"), _T("Port"), sText, _T(".\\SystemInfo.ini"));
		pGlobal->VisMarkSocekt.iPort = _ttoi(sText);
		pGlobal->VisMarkSocekt.Config();
	//	pGlobal->bVisionCon = true;
		TryCount = 0;
		SetDlgItemText(IDC_BTN_ConVisonSocket, _T("�Ͽ�"));
		WidgetStatue(TRUE);
	}
	else
	{
		pGlobal->VisMarkSocekt.CloseSocket();
	//	pGlobal->bVisionCon = false;
		SetDlgItemText(IDC_BTN_ConVisonSocket, _T("����"));
		WidgetStatue(FALSE);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//ȥ����λ�ã�����֪�Ƿ������һ����Ŀǰ��һ��λ����5����20200423wade
//iIsLast �Ƿ������һ��λ��
//iPos  �ڼ���ȡ��λ�ã��ܹ�40��,0��ʼ������iposΪ2��7��12��17��22��27��32��37//һ����
//iPos  �ڼ���ȡ��λ�ã��ܹ�40��,0��ʼ������iposΪ1��4��7��10��13��16��19��21��24��27��30��33��36��39��3��һ��һ������
int VisionTestdlg::GoGetPosAndMark(int iPos)
{
	int iFuncpos = iPos * 2 + 1;
	CString sMidTransPos[7];
	int ret;
	for (int i = 0; i < 7; i++)
	{
		sMidTransPos[i]  = pGlobal->RBTCTdlg.sFunctionPos[iFuncpos][i];
	}
	ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sMidTransPos, 100);	
	if (ret == 0)
	{
		return 1;
	}
	Sleep(1500);//�Ӿ���������ȡͼʱ��

	CString sJsonText;
	//{
	//	"PosId": 2,
	//	"P1" : "1001",
	//	"P2" : "1002",
	//}
	///////////////////json/////////////////////
	Json::Value root;

	// ��װjson����
	root["PosId"] = iPos;
	root["P1"] = toString(sMidTransPos[0]);
	root["P2"] = toString(sMidTransPos[1]);

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->VisionSend(sJsonText);
//	pGlobal->AddToRunList(_T("���Ӿ�����:") + sJsonText);

	///////////////////json/////////////////////
	ResetEvent(pGlobal->Handle_VisionRetPOS);
	DWORD dwState = WaitForSingleObject(pGlobal->Handle_VisionRetPOS, 8000);
	if (dwState - WAIT_OBJECT_0 == 0)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);	
		ret=GetDataProcess();
		if (ret!=0)
		{
			return 1;
		}
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		pGlobal->AddToErrorList(_T("��ȡVision����λ�ó�ʱ��"));
		AfxMessageBox(_T("��ȡVision����λ�ó�ʱ"));
		return 1;
	}
	return 0;
}

int VisionTestdlg::GetDataProcess()
{
	//���ݸ�ʽΪJSON,���ݣ�sVisRetPos�����ݸ�ʽ����
	//{
	//	"PosNum": 3,//һ����Ϊ3��һ����Ϊ5
	//		"PosDetail" : [
	//	{
	//		"PosId": 0,
	//			"P1" : "1001",
	//			"P2" : "1002",
	//			"angle" : "15",
	//			"Result" : "1"
	//	},
	//		......................................
	//		{
	//			"PosId": 4,
	//				"P1" : "1001",
	//				"P2" : "1002",
	//				"angle" : "15",
	//				"Result" : "1"
	//		}]
	//}
	try
	{
		Json::Reader reader;// ����json��Json::Reader   
		Json::Value root; // 
		std::string sJsonRet = toString(sVisRetPos);
		int iPosId;
		if (reader.parse(sJsonRet, root))
		{
			std::string code;
			iPosNum = root["PosNum"].asInt();//һ��Ϊ5����λ��һ����Ϊ3��
			int file_size = root["PosDetail"].size();
			for (int i = 0; i < file_size; i++)
			{
				iPosId = root["PosDetail"][i]["PosId"].asInt();
				sVisGetPos[iPosId][0] = toCString(root["PosDetail"][i]["P1"].asString());
				sVisGetPos[iPosId][1] = toCString(root["PosDetail"][i]["P2"].asString());
				sVisGetAngle[iPosId] = toCString(root["PosDetail"][i]["angle"].asString());;
				iVisGetResult[iPosId] = root["PosDetail"][i]["Result"].asInt();
				sVisGetResult[iPosId].Format(_T("%d"), iVisGetResult[iPosId]);
			}
		}
		else
		{
			pGlobal->AddToErrorList(_T("�Ӿ�json�����������ⷵ�ظ�ʽ"));
			return 1;
		}
		pGlobal->VisBtnUpdata();//postmessage ���͸��°�ť״̬����Ϣ
		return 0;
	}
	catch (const std::exception&)
	{

	}	
	pGlobal->AddToErrorList(_T("�Ӿ�json�����������ⷵ�ظ�ʽ"));
	return 1;
	
}


int VisionTestdlg::GoGetShowMarkPos()
{
	int index = m_combPos.GetCurSel();
	CString str;
	m_combPos.GetLBText(index, str);
	int ipos = _ttoi(str);

	GoGetPosAndMark(ipos);
	m_listMarkPos.DeleteAllItems();
	int ret;
	for (int k = 0; k < iPosNum; k++)//һ����Ϊ3��һ����ʱ��19��39���λ��Ϊ2��һ����Ϊ5��
	{
		if (iPosNum == 5)//һ��5
		{
			ret = ipos - 2 + k;
		}
		else if (iPosNum == 2 || iPosNum == 3)//һ��3
		{
			ret = ipos - 1 + k;
		}
		str.Format(_T("%d"), ret);
		m_listMarkPos.InsertItem(k, str);//������
		m_listMarkPos.SetItemText(k, 1, sVisGetResult[ret]);//��������
		m_listMarkPos.SetItemText(k, 2, sVisGetAngle[ret]);//��������
		for (int j = 0; j < 7; j++)
		{
			m_listMarkPos.SetItemText(k, j + 3, sVisGetPos[ret][j]);//��������
		}
	}
	return 0;

}

void VisionTestdlg::OnBnClickedBtnMark2()
{
	ithread = 4;
	AfxBeginThread(VisionDlgThread, this);
}


void VisionTestdlg::OnBnClickedBtnGomarkpos()
{	
	ithread = 5;
	AfxBeginThread(VisionDlgThread, this);
}

void VisionTestdlg::GoSelPos()
{
	POSITION pos = m_listMarkPos.GetFirstSelectedItemPosition();	
	if (pos == NULL)
	{
		AfxMessageBox(_T("��ѡ����Ӧ��λ"));
		return;
	}
	CString str;
	m_combPos.GetLBText(m_combPos.GetCurSel(), str);
	int ipos = _ttoi(str);
	int iget = m_listMarkPos.GetNextSelectedItem(pos);
	CString sPos[7];
	if (iPosNum == 5)//һ��5
	{
		ipos = ipos - 2 + iget;
	}
	else if (iPosNum == 2 || iPosNum == 3)//һ��3
	{
		ipos = ipos - 1 + iget;
	}
	for (int i = 0; i < 7; i++)
	{
		sPos[i] = sVisGetPos[ipos][i];
	}
	int ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sPos, 100);
}