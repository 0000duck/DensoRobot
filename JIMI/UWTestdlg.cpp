// UWTestdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "UWTestdlg.h"
#include "afxdialogex.h"
#include <afxinet.h> 
#include <iostream>
#include <fstream>
#include "json/json.h"
#pragma comment(lib,"json_vc71_libmtd.lib")
using namespace std;

// UWTestdlg 对话框

IMPLEMENT_DYNAMIC(UWTestdlg, CDialogEx)

UWTestdlg::UWTestdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_UW_Test, pParent)
{
	itaskId = 1;
	UW_ListPosNum = 1;
	UW_OutPos.cmdcode = "in";
	UW_OutPos.supplier = "JIMI_IOT";
	UW_OutPos.cmdid = 1;
	UW_OutPos.taskId = 1;
	for (int i = 0; i < 40; i++)
	{
		UW_OutPos.materialNo[i] = "132443242";
		UW_OutPos.quantity[i] = 100;
		UW_OutPos.row[i] =1;
		UW_OutPos.col[i] = 1;
		UW_OutPos.productionTime[i] = "2019-11-12";
		UW_OutPos.materialTypeId[i] = 103;
	}
}

UWTestdlg::~UWTestdlg()
{
}

void UWTestdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(UWTestdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_HttpSEND, &UWTestdlg::OnBnClickedBtnHttpsend)
	ON_BN_CLICKED(IDC_BTN_Connect, &UWTestdlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_RetAck, &UWTestdlg::OnBnClickedBtnRetack)
	ON_BN_CLICKED(IDC_BTN_OutFinish, &UWTestdlg::OnBnClickedBtnOutfinish)
	ON_BN_CLICKED(IDC_BTN_inFinish, &UWTestdlg::OnBnClickedBtninfinish)
	ON_BN_CLICKED(IDC_CHECK_UW, &UWTestdlg::OnBnClickedCheckUw)
	ON_BN_CLICKED(IDC_BTN_RetLogin, &UWTestdlg::OnBnClickedBtnRetlogin)
END_MESSAGE_MAP()


// UWTestdlg 消息处理程序


BOOL UWTestdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str;
	GetPrivateProfileString(_T("UWSocekt"), _T("bConnect"), _T("0"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	((CButton *)GetDlgItem(IDC_CHECK_UW))->SetCheck(_ttoi(str));
	if (_T("1") == str)
	{
		pGlobal->bUWCon = true;
	}
	else
	{
		pGlobal->bUWCon = false;
	}
	GetDlgItem(IDC_BTN_HttpSEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Send)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_RetLogin)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_RetAck)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OutFinish)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_inFinish)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void UWTestdlg::OnBnClickedBtnHttpsend()
{
	CString str;
	GetDlgItemText(IDC_EDIT_Send, str);// 0, 0, 0, 0, 0, 0, 0
	
	pGlobal->UWSocekt.UW_Send(str);
	pGlobal->AddToRunList(_T("给UW发送:") + str);
}

void UWTestdlg::OnBnClickedBtnConnect()
{
	CString sText;
	GetDlgItemText(IDC_BTN_Connect, sText);
	if (_T("连接") == sText)
	{
	
		pGlobal->UWSocekt.Config();

		SetDlgItemText(IDC_BTN_Connect, _T("断开"));
		GetDlgItem(IDC_BTN_HttpSEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_Send)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_RetLogin)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_RetAck)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OutFinish)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_inFinish)->EnableWindow(TRUE);

	}
	else
	{
		pGlobal->UWSocekt.CloseSocket();
		SetDlgItemText(IDC_BTN_Connect, _T("连接"));
		GetDlgItem(IDC_BTN_HttpSEND)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Send)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RetLogin)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RetAck)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_OutFinish)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_inFinish)->EnableWindow(FALSE);
	}
}



void UWTestdlg::OnBnClickedBtnRetack()
{
	ithread = 1;
	AfxBeginThread(UWDlgThread, this);
}


void UWTestdlg::OnBnClickedBtnOutfinish()
{
	ithread = 2;
	AfxBeginThread(UWDlgThread, this);
}


void UWTestdlg::OnBnClickedBtninfinish()
{
	ithread = 3;
	AfxBeginThread(UWDlgThread, this);
}

void UWTestdlg::OnBnClickedBtnRetlogin()
{
	ithread = 4;
	AfxBeginThread(UWDlgThread, this);
}

UINT UWTestdlg::UWDlgThread(LPVOID lparam)
{
	UWTestdlg *pdlg = (UWTestdlg *)lparam;
	switch (pdlg->ithread)
	{
	case 1:  		pdlg->UW_Ack_Send();		                    break; //回复ACK
	case 2:  		pdlg->UW_OutFinish_Send(_T("success"));            break; //出库完成
	case 3:  		pdlg->UW_InFinish_Send();		                break; //入库完成
	case 4:  		pdlg->UW_Login_Send(_T("ur"));		            break; //登录
	default:
		break;
	}
	return 1;
}

int UWTestdlg::UW_Ack_Send()
{
	CString sJsonText;
	//const char* str = "{ \"cmdcode\":\"ack\",\"cmdid\":\"1\"}";

	//sJsonText = "{ \"cmdcode\":\"ack\",\"cmdid\":\"1\"}";
	///////////////////json/////////////////////
	Json::Value root;

	// 组装json内容
	root["cmdcode"] = "ack";
	root["cmdid"] = iCmdid;

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("给UW发送:") + sJsonText);
	///////////////////json/////////////////////

	return 0;
}
int UWTestdlg::UW_OutFinish_Send(CString message)
{

	CString sJsonText;
	Json::Value root;

	// 组装json内容
	root["cmdcode"] = "result";
	root["cmdid"] = pGlobal->iProcessTimes;//iCmdid;
	root["aimid"] = iCmdid;
	root["result"] = 200;
	root["message"] = toString(message);

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("给UW发送:") + sJsonText);
	return 0;
}
int UWTestdlg::UW_InFinish_Send()
{
	CString sJsonText;
	Json::Value root;

	// 组装json内容
	root["cmdcode"] = "in";
	root["cmdid"] = iCmdid;
	root["supplier"] = "ZHIRUIDE";
	root["taskId"] = itaskId;

	for (int i = 0; i < UW_ListPosNum; i++)
	{
		root["list"][i]["materialNo"] = toString(UW_OutPos.materialNo[i]);
		root["list"][i]["quantity"] = UW_OutPos.quantity[i];
		root["list"][i]["row"] = UW_OutPos.row[i];
		root["list"][i]["col"] = UW_OutPos.col[i];
		root["list"][i]["productionTime"] = toString(UW_OutPos.productionTime[i]);
		root["list"][i]["materialTypeId"] = UW_OutPos.materialTypeId[i];
	}
	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("给UW发送:") + sJsonText);
	return 0;
}

int UWTestdlg::UW_Login_Send(CString name)
{

	CString sJsonText;
	Json::Value root;

	// 组装json内容
	root["cmdcode"] = "login";
	root["cmdid"] = 1;
	root["name"] = toString(name);

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("给UW发送:") + sJsonText);
	return 0;
}

int UWTestdlg::UW_Read_cmdcode_DealData(CString str)
{
	Json::Reader reader;// 解析json用Json::Reader   
	Json::Value root; // Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array         
	std::string sJsonRet = toString(str);
	int iret;
	if (reader.parse(sJsonRet, root))
	{
		std::string code;
		//if (!root["cmdcode"].isNull())  // 访问节点，Access an object value by name, create a null member if it does not exist.  
		//{
		//	pGlobal->AddToErrorList(_T("接收的数据无cmdcode数据,数据错误!!!!!!"));
		//	return 0;
		//}
		code = root["cmdcode"].asString();  //UP000000  asInt()返回整形
		
		CString csCode = toCString(code);
		sRecvCmdCode = csCode;//赋值给当前的
		iCmdid = root["cmdid"].asInt();//暂时做其他用
		if (code == "ack")
		{
			iret = UW_Read_ack_DealData(str);
			SetEvent(pGlobal->Handle_UWRetData_ack);
			return 1;
		}
		else if (code == "out")
		{
			iret = UW_Read_out_DealData(str);
			SetEvent(pGlobal->Handle_UWRetData_out);
			return 2;
		}
		else if (code == "reach_out")
		{
			iret = UW_Read_reach_out_DealData(str);
			SetEvent(pGlobal->Handle_UWRetData_reach_out);
			return 3;
		}
		else if (code == "reach_in")
		{
			iret = UW_Read_reach_in_DealData(str);
			SetEvent(pGlobal->Handle_UWRetData_reach_in);
			return 4;
		}
		else
		{
			pGlobal->AddToErrorList(_T("收到未定义的cmdcode数据：")+csCode);
			return 0;
		}
	}
	return 0;
}

int UWTestdlg::UW_Read_ack_DealData(CString str)
{
	//格式如下

	//{
	//	"cmdcode": "ack",
	//		"cmdid" : 1
	//}
	return 0;
}

int UWTestdlg::UW_Read_out_DealData(CString str)
{
	//格式如下

	//{
	//	"cmdcode":"out",
	//		"cmdid" : 1,
	//		"supplier" : "智锐得",
	//		"taskId" : 1,
	//		"list" : [
	//	{
	//		"materialNo":"132443242",
	//			"quantity" : 100,
	//			"row" : 4,
	//			"col" : 1,
	//			"productionTime" : "2019-11-12",
	//			"materialTypeId" : "103"
	//	}
	//		]
	//}
	Json::Reader reader;// 解析json用Json::Reader   
	Json::Value root; // 
	std::string sJsonRet = toString(str);
	if (reader.parse(sJsonRet, root))
	{
		std::string code;
		if (root["list"].isNull())  // 访问节点，Access an object value by name, create a null member if it does not exist.  
		{
			pGlobal->AddToErrorList(_T("接收的数据无list位置坐标数据,数据错误!!!!!!"));
			return 0;
		}		
		UW_OutPos.cmdcode =toCString(root["cmdcode"].asString());
		UW_OutPos.supplier = toCString(root["supplier"].asString());
		UW_OutPos.cmdid = root["cmdid"].asInt();		
		UW_OutPos.taskId = root["taskId"].asInt();
		
		UW_ListPosNum = root["list"].size();//list列表
		for (int i = 0; i < UW_ListPosNum; i++)
		{
			UW_OutPos.materialNo[i] = toCString(root["list"][i]["materialNo"].asString());
			UW_OutPos.quantity[i] = root["list"][i]["quantity"].asInt();
			UW_OutPos.row[i] = root["list"][i]["row"].asInt();
			UW_OutPos.col[i] = root["list"][i]["col"].asInt();
			UW_OutPos.productionTime[i] = toCString(root["list"][i]["productionTime"].asString());
			UW_OutPos.materialTypeId[i] = root["list"][i]["materialTypeId"].asInt();
		}
	}
	return 0;
}
int UWTestdlg::UW_Read_reach_out_DealData(CString str)
{
	//格式如下

	//{
	//	"cmdcode":"reach_out",
	//		"cmdid" : 1,
	//		"taskId" : 1
	//}
	Json::Reader reader;// 解析json用Json::Reader   
	Json::Value root; // 
	std::string sJsonRet = toString(str);
	if (reader.parse(sJsonRet, root))
	{
		std::string code;
		itaskId = root["taskId"].asInt();
	}
	return 0;
}
int UWTestdlg::UW_Read_reach_in_DealData(CString str)
{
	//格式如下

	//{
	//	"cmdcode":"reach_in",
	//		"cmdid" : 1,
	//		"taskId" : 1
	//}
	Json::Reader reader;// 解析json用Json::Reader   
	Json::Value root; // 
	std::string sJsonRet = toString(str);
	if (reader.parse(sJsonRet, root))
	{
		std::string code;		
		itaskId = root["taskId"].asInt();
	}
	return 0;
}

void UWTestdlg::OnBnClickedCheckUw()
{
	CString sText;
	int state = ((CButton *)GetDlgItem(IDC_CHECK_UW))->GetCheck();
	if (1 == state)
	{
		pGlobal->bUWCon = true;
		sText = _T("1");
	}
	else
	{
		pGlobal->bUWCon = false;
		sText = _T("0");
	}
	WritePrivateProfileString(_T("UWSocekt"), _T("bConnect"), sText, _T(".\\SystemInfo.ini"));
}



