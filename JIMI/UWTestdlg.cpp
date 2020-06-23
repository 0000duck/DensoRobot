// UWTestdlg.cpp : ʵ���ļ�
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

// UWTestdlg �Ի���

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
	ON_BN_CLICKED(IDC_BTN_Ready, &UWTestdlg::OnBnClickedBtnReady)
	ON_BN_CLICKED(IDC_BTN_PosAsk, &UWTestdlg::OnBnClickedBtnPosask)
	ON_BN_CLICKED(IDC_BTN_CodeRes, &UWTestdlg::OnBnClickedBtnCoderes)
	ON_BN_CLICKED(IDC_BTN_CodeError, &UWTestdlg::OnBnClickedBtnCodeerror)
	ON_BN_CLICKED(IDC_BTN_ManuClear, &UWTestdlg::OnBnClickedBtnManuclear)
END_MESSAGE_MAP()


// UWTestdlg ��Ϣ�������


BOOL UWTestdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	WidgetStatue(FALSE);
	iCmdid = 1;
	iboxId = 1;
	itaskId = 1;
	itype = 1;
	sMaterialId = _T("NO materialID get");
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void UWTestdlg::OnBnClickedBtnHttpsend()
{
	CString str;
	GetDlgItemText(IDC_EDIT_Send, str);// 0, 0, 0, 0, 0, 0, 0
	
	pGlobal->UWSocekt.UW_Send(str);
	pGlobal->AddToRunList(_T("��UW����:") + str);
}

void UWTestdlg::OnBnClickedBtnConnect()
{
	CString sText;
	GetDlgItemText(IDC_BTN_Connect, sText);
	if (_T("����") == sText)
	{	
		pGlobal->UWSocekt.Config();

		SetDlgItemText(IDC_BTN_Connect, _T("�Ͽ�"));
		WidgetStatue(TRUE);
	}
	else
	{
		pGlobal->UWSocekt.CloseSocket();
		SetDlgItemText(IDC_BTN_Connect, _T("����"));
		WidgetStatue(FALSE);
	}
}

void UWTestdlg::WidgetStatue(BOOL bstatue)
{
	GetDlgItem(IDC_BTN_HttpSEND)->EnableWindow(bstatue);
	GetDlgItem(IDC_EDIT_Send)->EnableWindow(bstatue);
	GetDlgItem(IDC_BTN_RetLogin)->EnableWindow(bstatue);
	GetDlgItem(IDC_BTN_RetAck)->EnableWindow(bstatue);
	GetDlgItem(IDC_BTN_OutFinish)->EnableWindow(bstatue);
	GetDlgItem(IDC_BTN_inFinish)->EnableWindow(bstatue);

	GetDlgItem(IDC_BTN_Ready)->EnableWindow(bstatue);
	GetDlgItem(IDC_BTN_PosAsk)->EnableWindow(bstatue);
	GetDlgItem(IDC_BTN_CodeRes)->EnableWindow(bstatue);
	GetDlgItem(IDC_BTN_CodeError)->EnableWindow(bstatue);
}

void UWTestdlg::OnBnClickedBtnRetack()
{
	ithread = 1;
	AfxBeginThread(UWDlgThread, this);
}


void UWTestdlg::OnBnClickedBtnOutfinish()
{
	ithread = 9;
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
	case 1:  		pdlg->UW_Ack_Send();		                           break; //�ظ�ACK
	case 2:  		pdlg->UW_OutFinish_Send(_T("success"));                break; //�������
	case 3:  		pdlg->UW_InFinish_Send();		                       break; //������
	case 4:  		pdlg->UW_Login_Send(_T("robot1"));		               break; //��¼
	case 5:  		pdlg->UW_Ready_Send();	                               break; //׼������
	case 6:  		pdlg->UW_AskPostion_Send();		                       break; //λ������
	case 7:  		pdlg->UW_ScanMaterilaInfo_Send(pGlobal->UWdlg.sMaterialId,1000);       break; //������ɨ�������
	case 8:  		pdlg->UW_ScanMaterilaInfo_Error_Send(pGlobal->UWdlg.sMaterialId,4);	   break; //�����˴�����
	case 9:  		pdlg->UW_ReadMessage_Send(pGlobal->UWdlg.sMaterialId,0,0,1000,1,0);   break; //�������̵����ݷ���,test
	default:
		break;
	}
	return 1;
}

int UWTestdlg::UW_Ack_Send()
{
	CString sJsonText;
	//const char* str = "{ \"cmdCode\":\"ack\",\"cmdId\":\"1\"}";

	//sJsonText = "{ \"cmdCode\":\"ack\",\"cmdId\":\"1\"}";
	///////////////////json/////////////////////
	Json::Value root;

	// ��װjson����
	root["cmdCode"] = "ack";
	root["cmdId"] = iCmdid;

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("��UW����:") + sJsonText);
	///////////////////json/////////////////////

	return 0;
}
int UWTestdlg::UW_OutFinish_Send(CString message)
{

	CString sJsonText;
	Json::Value root;

	// ��װjson����
	root["cmdCode"] = "result";
	root["cmdId"] = pGlobal->iProcessTimes;//iCmdid;
	root["aimid"] = iCmdid;
	root["result"] = 200;
	root["message"] = toString(message);

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("��UW����:") + sJsonText);
	return 0;
}
int UWTestdlg::UW_InFinish_Send()
{
	ifstream is("UWtest.json", ios::binary);

	CString sJsonText;
	Json::Value root;
	Json::Reader reader;

	// ����json����
	if (reader.parse(is, root))
	{
		// ��װjson����
		root["cmdCode"] = "in";
		root["cmdId"] = iCmdid + 1;
		//root["supplier"] = "ZHIRUIDE";
		root["taskId"] = itaskId;

		std::string DevStr = root.toStyledString();
		sJsonText = toCString(DevStr);
		pGlobal->UWSocekt.UW_Send(sJsonText);
		pGlobal->AddToRunList(_T("��UW����:") + sJsonText);
		return 0;
	}
	return 0;
}

int UWTestdlg::UW_Login_Send(CString name)
{

	CString sJsonText;
	Json::Value root;

	// ��װjson����
	root["cmdCode"] = "login";
	root["cmdId"] = iCmdid;
	root["name"] = toString(name);

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("��UW����:") + sJsonText);
	return 0;
}

int UWTestdlg::UW_Ready_Send()
{
	CString sJsonText;

	Json::Value root;

	// ��װjson����
	root["cmdCode"] = "ready";
	root["cmdId"] = iCmdid + 1;

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("��UW����:") + sJsonText);
	///////////////////json/////////////////////
	return 0;
}

int UWTestdlg::UW_AskPostion_Send()
{
	CString sJsonText;

	Json::Value root;

	// ��װjson����
	root["cmdCode"] = "ask_position";
	root["cmdId"] = iCmdid + 1;
	root["taskId"] = itaskId;
	root["boxId"] = iboxId;

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("��UW����:") + sJsonText);
	///////////////////json/////////////////////
	return 0;
}

int UWTestdlg::UW_ScanMaterilaInfo_Send(CString sCode, int iQuantity)
{
	CString sJsonText;

	Json::Value root;

	// ��װjson����
	root["cmdCode"] = "scan_material_info";
	root["cmdId"] = iCmdid + 1;
	root["taskId"] = itaskId;
	root["boxId"] = iboxId;
	root["materialId"] = toString(sCode);
	root["quantity"] = iQuantity;
	root["xPosition"] = iXpos;
	root["yPosition"] = iYpos;

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("��UW����:") + sJsonText);
	///////////////////json/////////////////////
	return 0;
}

int UWTestdlg::UW_ScanMaterilaInfo_Error_Send(CString sCode,int ierrorCode)
{
	CString sJsonText;

	Json::Value root;

	// ��װjson����
	root["cmdCode"] = "scan_material_exception";
	root["cmdId"] = iCmdid + 1;
	root["taskId"] = itaskId;
	root["boxId"] = iboxId;
	root["materialId"] = toString(sCode);
	root["exceptionCode"] = ierrorCode;

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("��UW����:") + sJsonText);
	///////////////////json/////////////////////
	return 0;
}
int UWTestdlg::UW_Read_cmdcode_DealData(CString str)
{
	Json::Reader reader;// ����json��Json::Reader   
	Json::Value root; // Json::Value��һ�ֺ���Ҫ�����ͣ����Դ����������͡���int, string, object, array         
	std::string sJsonRet = toString(str);
	int iret;
	if (reader.parse(sJsonRet, root))
	{
		std::string code;
		//if (!root["cmdCode"].isNull())  // ���ʽڵ㣬Access an object value by name, create a null member if it does not exist.  
		//{
		//	pGlobal->AddToErrorList(_T("���յ�������cmdCode����,���ݴ���!!!!!!"));
		//	return 0;
		//}
		code = root["cmdCode"].asString();  //UP000000  asInt()��������
		
		CString csCode = toCString(code);
		sRecvCmdCode = csCode;//��ֵ����ǰ��
		iCmdid = root["cmdId"].asInt();//��ʱ��������
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
			pGlobal->UWdlg.UW_Ack_Send();
			return 2;
		}
		else if (code == "reach_out")
		{
			iret = UW_Read_reach_out_DealData(str);
			SetEvent(pGlobal->Handle_UWRetData_reach_out);
			pGlobal->UWdlg.UW_Ack_Send();
			return 3;
		}
		else if (code == "reach_in")
		{
			iret = UW_Read_reach_in_DealData(str);
			SetEvent(pGlobal->Handle_UWRetData_reach_in);
			pGlobal->UWdlg.UW_Ack_Send();
			return 4;
		}
		else if (code == "forklift_reach")
		{
			iret = UW_Read_forklift_reach_DealData(str);
			SetEvent(pGlobal->Handle_UWRetData_forklift_reach);
			pGlobal->UWdlg.UW_Ack_Send();
			return 5;
		}
		else if (code == "material_position_info")
		{
			iret = UW_Read_forklift_position_info_DealData(str);
			SetEvent(pGlobal->Handle_UWRetData_material_position_info);
			pGlobal->UWdlg.UW_Ack_Send();
			return 6;
		}
		else
		{
			pGlobal->AddToErrorList(_T("�յ�δ�����cmdcode���ݣ�")+csCode);
			return 0;
		}
	}
	return 0;
}

int UWTestdlg::UW_Read_ack_DealData(CString str)
{
	//��ʽ����

	//{
	//	"cmdcode": "ack",
	//		"cmdId" : 1
	//}
	return 0;
}

int UWTestdlg::UW_Read_out_DealData(CString str)
{
	//��ʽ����

	//{
	//	"cmdcode":"out",
	//		"cmdid" : 1,
	//		"supplier" : "�����",
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
	Json::Reader reader;// ����json��Json::Reader   
	Json::Value root; // 
	std::string sJsonRet = toString(str);

	if (reader.parse(sJsonRet, root))
	{

		Json::StyledWriter writer;
		ofstream os;
		os.open("UWtest.json");
		os << writer.write(root);
		os.close();

		std::string code;
		if (root["list"].isNull())  // ���ʽڵ㣬Access an object value by name, create a null member if it does not exist.  
		{
			pGlobal->AddToErrorList(_T("���յ�������listλ����������,���ݴ���!!!!!!"));
			return 0;
		}		
		UW_OutPos.cmdcode =toCString(root["cmdCode"].asString());
		UW_OutPos.supplier = toCString(root["supplier"].asString());
		UW_OutPos.cmdid = root["cmdId"].asInt();		
		UW_OutPos.taskId = root["taskId"].asInt();
		
		UW_ListPosNum = root["list"].size();//list�б�
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
	//��ʽ����

	//{
	//	"cmdCode":"reach_out",
	//		"cmdId" : 1,
	//		"taskId" : 1
	//}
	Json::Reader reader;// ����json��Json::Reader   
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
	//��ʽ����

	//{
	//	"cmdCode":"reach_in",
	//		"cmdId" : 1,
	//		"taskId" : 1
	//}
	Json::Reader reader;// ����json��Json::Reader   
	Json::Value root; // 
	std::string sJsonRet = toString(str);
	if (reader.parse(sJsonRet, root))
	{
		std::string code;		
		itaskId = root["taskId"].asInt();
	}
	return 0;
}

int UWTestdlg::UW_Read_forklift_reach_DealData(CString str)
{
	//��ʽ����
	//{
	//	"cmdCode":"forklift_reach",
	//"taskId":123,
	//	"boxId" : 1,
	//		"cmdId" : 1
	//}
	Json::Reader reader;// ����json��Json::Reader   
	Json::Value root; // 
	std::string sJsonRet = toString(str);
	if (reader.parse(sJsonRet, root))
	{
		std::string code;
		iCmdid = root["cmdId"].asInt();
		itaskId = root["taskId"].asInt();
		itype = root["type"].asInt();  //�¿�ܣ��̵������λ��
		iboxId = root["boxId"].asInt();
	}
	return 0;
}
int UWTestdlg::UW_Read_forklift_position_info_DealData(CString str)
{
	//{
	//	"cmdCode":"material_position_info",
	//		"cmdId" : 1
	//		"taskId" : 1234,
	 //"boxId":123,
	//	"type" : 1,
	//		"materialId" : "1111100",
	//		"xPosition" : 1,
	//		"yPosition" : 2,
	//"quantity":1000
	//}
	Json::Reader reader;// ����json��Json::Reader   
	Json::Value root; // 
	std::string sJsonRet = toString(str);
	if (reader.parse(sJsonRet, root))
	{
		std::string code;
		iCmdid = root["cmdId"].asInt();
		itaskId = root["taskId"].asInt();
		sMaterialId = toCString(root["materialId"].asString()); 
		iXpos = root["xPosition"].asInt();
		iYpos = root["yPosition"].asInt();
		iboxId = root["boxId"].asInt();
		iQuantity = root["quantity"].asInt();
		sQuantity.Format(_T("%d"), iQuantity);
		//sQuantity = toCString(root["quantity"].asString());//��������ֵ�� ���õ���
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

void UWTestdlg::OnBnClickedBtnReady()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ithread = 5;
	AfxBeginThread(UWDlgThread, this);
}


void UWTestdlg::OnBnClickedBtnPosask()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ithread = 6;
	AfxBeginThread(UWDlgThread, this);
}


void UWTestdlg::OnBnClickedBtnCoderes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ithread = 7;
	AfxBeginThread(UWDlgThread, this);
}


void UWTestdlg::OnBnClickedBtnCodeerror()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ithread = 8;
	AfxBeginThread(UWDlgThread, this);
}


void UWTestdlg::OnBnClickedBtnManuclear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pGlobal->UWdlg.bNeedReady = 1;
	WritePrivateProfileString(_T("ProcessDATA"), _T("NeedReady"), _T("1"), _T(".\\SystemInfo.ini"));
	pGlobal->AddToRunList(_T("�˹��ֶ��Ƴ��Ϻ���Ϣ�ɹ�������"));
	AfxMessageBox(_T("�˹��ֶ��Ƴ��Ϻ���Ϣ�ɹ�������"));
}

int UWTestdlg::UW_ReadMessage_Send(CString sCode, int iQuantity, int ix, int iy, int ires,int iflag)
{
	//{
	//	   "cmdCode":"send_message",
	//		"cmdId" : 1,
	//		"taskId" : 123,
	//		"boxId" : 1,
	//		"xPosition" : 1,
	//		"yPosition" : 1,
	//		"materialId" : "1111100",
	//		"quantity" : 1245,
	//		"result" : 1,
	//		"endFlag" :0
	//}
	CString sJsonText;

	Json::Value root;

	// ��װjson����
	root["cmdCode"] = "inv_material_scan_info";
	root["cmdId"] = iCmdid + 1;
	root["taskId"] = itaskId;
	root["boxId"] = iboxId;
	root["xPosition"] = ix;
	root["yPosition"] = iy;
	root["materialId"] = toString(sCode);
	root["quantity"] = iQuantity;
	root["result"] = ires;
	root["endFlag"] = iflag;

	std::string DevStr = root.toStyledString();
	sJsonText = toCString(DevStr);
	pGlobal->UWSocekt.UW_Send(sJsonText);
	pGlobal->AddToRunList(_T("��UW����:") + sJsonText);
	///////////////////json/////////////////////
	return 0;
}