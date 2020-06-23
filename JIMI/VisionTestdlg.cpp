// VisionTestdlg.cpp : 实现文件
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
	//视觉返回位置初始化，出事位置与取料位置相等；
	sVisGetPos;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			sVisGetPos[i][j] = pGlobal->RBTCTdlg.sFunctionPos[i*2+1][j];
		}
		iVisGetResult[i] = Vis_Null;//初始化为空
		sVisGetResult[i] = _T("3");
	}
	iPosNum = 3;//初始化默认值为3
	IniMarklist();
	m_combPos.SetCurSel(0);
	WidgetStatue(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void VisionTestdlg::IniMarklist()
{
	LONG lStyle;
	CString str;
	lStyle = GetWindowLong(m_listMarkPos.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listMarkPos.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_listMarkPos.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
								//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listMarkPos.SetExtendedStyle(dwStyle); //设置扩展风格

	m_listMarkPos.InsertColumn(0, _T("校准后点位"), LVCFMT_LEFT, 120);//插入列
	m_listMarkPos.InsertColumn(1, _T("校准结果"), LVCFMT_LEFT, 80);//插入列
	m_listMarkPos.InsertColumn(2, _T("校准角度"), LVCFMT_LEFT, 80);//插入列
	m_listMarkPos.InsertColumn(3, _T("X"), LVCFMT_LEFT, 80);//插入列
	m_listMarkPos.InsertColumn(4, _T("Y"), LVCFMT_LEFT, 80);//插入列
	m_listMarkPos.InsertColumn(5, _T("Z"), LVCFMT_LEFT, 80);//插入列
	m_listMarkPos.InsertColumn(6, _T("RX"), LVCFMT_LEFT, 80);//插入列
	m_listMarkPos.InsertColumn(7, _T("RY"), LVCFMT_LEFT, 80);//插入列
	m_listMarkPos.InsertColumn(8, _T("RZ"), LVCFMT_LEFT, 80);//插入列
	m_listMarkPos.InsertColumn(9, _T("Fig"), LVCFMT_LEFT, 80);//插入列
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
int VisionTestdlg::bSuccessGet()
{
	return 1;//确定是否开启这个功能，就目前暂时屏蔽
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
			pGlobal->AddToErrorList(_T("VISION返回夹料成功"));
			return 1;
		}
		else 
		{
			pGlobal->AddToErrorList(_T("VISION返回夹料错误"));
			return 0;
		}
	}
	else if (WAIT_TIMEOUT == dwState)
	{
		ResetEvent(pGlobal->Handle_VisionRetPOS);
		pGlobal->AddToRunList(_T("获取Vision判断是否夹料成功返回超时！"));
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
		WritePrivateProfileString(_T("VisionSocekt"), _T("Port"), sText, _T(".\\SystemInfo.ini"));
		pGlobal->VisMarkSocekt.iPort = _ttoi(sText);
		pGlobal->VisMarkSocekt.Config();
	//	pGlobal->bVisionCon = true;
		TryCount = 0;
		SetDlgItemText(IDC_BTN_ConVisonSocket, _T("断开"));
		WidgetStatue(TRUE);
	}
	else
	{
		pGlobal->VisMarkSocekt.CloseSocket();
	//	pGlobal->bVisionCon = false;
		SetDlgItemText(IDC_BTN_ConVisonSocket, _T("连接"));
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

//去拍照位置，并告知是否是最后一个，目前是一个位置拍5个，20200423wade
//iIsLast 是否是最后一个位置
//iPos  第几个取料位置，总共40个,0开始计数，ipos为2，7，12，17，22，27，32，37//一拍五
//iPos  第几个取料位置，总共40个,0开始计数，ipos为1，4，7，10，13，16，19，21，24，27，30，33，36，39，3个一组一拍三，
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
	Sleep(1500);//视觉休整拍照取图时间

	CString sJsonText;
	//{
	//	"PosId": 2,
	//	"P1" : "1001",
	//	"P2" : "1002",
	//}
	///////////////////json/////////////////////
	Json::Value root;

	// 组装json内容
	root["PosId"] = iPos;
	root["P1"] = toString(sMidTransPos[0]);
	root["P2"] = toString(sMidTransPos[1]);

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->VisionSend(sJsonText);
//	pGlobal->AddToRunList(_T("给视觉发送:") + sJsonText);

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
		pGlobal->AddToErrorList(_T("获取Vision返回位置超时！"));
		AfxMessageBox(_T("获取Vision返回位置超时"));
		return 1;
	}
	return 0;
}

int VisionTestdlg::GetDataProcess()
{
	//数据格式为JSON,数据：sVisRetPos：内容格式如下
	//{
	//	"PosNum": 3,//一拍三为3，一拍五为5
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
		Json::Reader reader;// 解析json用Json::Reader   
		Json::Value root; // 
		std::string sJsonRet = toString(sVisRetPos);
		int iPosId;
		if (reader.parse(sJsonRet, root))
		{
			std::string code;
			iPosNum = root["PosNum"].asInt();//一般为5个点位，一拍三为3个
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
			pGlobal->AddToErrorList(_T("视觉json解析错误，请检测返回格式"));
			return 1;
		}
		pGlobal->VisBtnUpdata();//postmessage 发送更新按钮状态的消息
		return 0;
	}
	catch (const std::exception&)
	{

	}	
	pGlobal->AddToErrorList(_T("视觉json解析错误，请检测返回格式"));
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
	for (int k = 0; k < iPosNum; k++)//一拍三为3，一拍三时，19和39这个位置为2，一拍五为5，
	{
		if (iPosNum == 5)//一拍5
		{
			ret = ipos - 2 + k;
		}
		else if (iPosNum == 2 || iPosNum == 3)//一拍3
		{
			ret = ipos - 1 + k;
		}
		str.Format(_T("%d"), ret);
		m_listMarkPos.InsertItem(k, str);//插入行
		m_listMarkPos.SetItemText(k, 1, sVisGetResult[ret]);//设置数据
		m_listMarkPos.SetItemText(k, 2, sVisGetAngle[ret]);//设置数据
		for (int j = 0; j < 7; j++)
		{
			m_listMarkPos.SetItemText(k, j + 3, sVisGetPos[ret][j]);//设置数据
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
		AfxMessageBox(_T("请选择相应点位"));
		return;
	}
	CString str;
	m_combPos.GetLBText(m_combPos.GetCurSel(), str);
	int ipos = _ttoi(str);
	int iget = m_listMarkPos.GetNextSelectedItem(pos);
	CString sPos[7];
	if (iPosNum == 5)//一拍5
	{
		ipos = ipos - 2 + iget;
	}
	else if (iPosNum == 2 || iPosNum == 3)//一拍3
	{
		ipos = ipos - 1 + iget;
	}
	for (int i = 0; i < 7; i++)
	{
		sPos[i] = sVisGetPos[ipos][i];
	}
	int ret = pGlobal->RBTCTdlg.MoveToPostion(Move_L, sPos, 100);
}