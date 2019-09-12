// ClientSocket_BaseRBT.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
//#include "ClientSocket_BaseRBT.h"
#include <afxpriv.h>
#include <afxsock.h>

extern CRITICAL_SECTION Sec_BaseRbtSocket;
// ClientSocket_BaseRBT

ClientSocket_BaseRBT::ClientSocket_BaseRBT()
{
	sIP = _T("");
	m_bConnected = FALSE;
}

ClientSocket_BaseRBT::~ClientSocket_BaseRBT()
{
}


// ClientSocket_BaseRBT 成员函数
//void ClientSocket_BaseRBT::OnConnect(int nErrorCode)
//{
//	// TODO: 在此添加专用代码和 / 或调用基类
//	if (nErrorCode == 0)//连接成功
//	{
//		m_bConnected = TRUE;
//
//		pGlobal->AddToRunList(_T("RbtBaseSocket连接成功"));
//		//AsyncSelect(FD_READ);  //提请一个"读"的网络事件，准备接收
//	}
//	else
//	{
//		m_bConnected = FALSE;
//	}
//	CAsyncSocket::OnConnect(nErrorCode);
//}

void ClientSocket_BaseRBT::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	memset(cRecvData, 0, 255);
	int iLen = Receive((void*)cRecvData, 255);
	if (iLen > 0)
	{
		DataProcess();
	}
	//	AsyncSelect(FD_READ);  //每次都要读这个时间，AsyncSelect(FD_WRITE)用于触发onsend这个虚函数，但是此处没有写
	CAsyncSocket::OnReceive(nErrorCode);
}

void ClientSocket_BaseRBT::OnSend(int nErrorCode)
{
	try
	{
		Send(cSendData, iSendLen, 0);//发送数据
	}
	catch (const std::exception&)
	{
		pGlobal->AddToErrorList(_T("基础服务器网络连接异常"));
	}
	iSendLen = 0;
	memset(cSendData, 0, sizeof(cSendData));//清除缓冲区数据
											//继续提请一个"读"的网络事件，接收Server消息
	AsyncSelect(FD_READ);
	CAsyncSocket::OnSend(nErrorCode);
}

bool ClientSocket_BaseRBT::Config()
{
	//bool bcon = false;
	CString str;
	GetPrivateProfileString(_T("RbtBaseSocekt"), _T("IP"), _T("192.168.0.1"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	sIP = str;
	GetPrivateProfileString(_T("RbtBaseSocekt"), _T("Port"), _T("49153"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	iPort = _ttoi(str);
	//sIP = _T("192.168.0.1");//ROBOT SERVER IP	
	//iPort = 49153;//49152,49153,49154,49155,对应机器人线路编号 4、5、6、7，机器人程序暂时一直默认用4
				  //sIP = _T("10.10.11.128");//ROBOT SERVER IP
				  //iPort = 60000;
	if (Create(0, SOCK_STREAM, FD_CONNECT))
	{
		BOOL Bret = Connect(sIP, iPort);
		DWORD nErrno = GetLastError();
		m_bConnected = TRUE;
		return true;
	}
	return false;
}
void ClientSocket_BaseRBT::CloseSocket()
{
	m_bConnected = FALSE;
	Close();
}
bool ClientSocket_BaseRBT::SendMSG(CString str)
{
	EnterCriticalSection(&Sec_BaseRbtSocket);
	USES_CONVERSION;
	CJIMIDlg *parent = (CJIMIDlg*)AfxGetApp()->GetMainWnd();
	CString smsg;
	smsg = str + _T("\r\n");//\r\n
							//char * buffer = new char[256];
							//memset(buffer, 0, 256);
							//buffer = CstringToChar(smsg);
	iSendLen = smsg.GetLength();
	memset(cSendData, 0, 256);
	//memcpy(cSendData, smsg, iSendLen);
	strcpy(cSendData, T2A(smsg));	
	if (TRUE == m_bConnected)
	{
		AsyncSelect(FD_WRITE);//触发Socket的OnSend函数
	}
	else
	{
		pGlobal->AddToErrorList(_T("RBT基础服务器尚未连接，发送无效"));
	}
	
	//pGlobal->AddToRunList(_T("给服务器Robot发送:") + str);

	LeaveCriticalSection(&Sec_BaseRbtSocket);
	return true;
}
void ClientSocket_BaseRBT::DataProcess()
{
	CJIMIDlg *parent = (CJIMIDlg*)AfxGetApp()->GetMainWnd();
	CString sRecvData, str;
	sRecvData = cRecvData;
	sRecvData.Trim();
	sRecvData.Replace(_T(" "), _T(""));//去掉内部空格符号
	//pGlobal->AddToRunList(_T("从服务器Robot接收:") + sRecvData); //
	int Recvlen = sRecvData.GetLength();
	int strpos = sRecvData.Find(_T(":"));

	CString sText = sRecvData.Mid(strpos - 5, 4);
	if (_T("RETV") == sText)
	{  //速度返回处理
		pGlobal->RBTCTdlg.CurSpeed = sRecvData.Mid(strpos + 1, Recvlen - strpos);
		pGlobal->RBTCTdlg.SetDlgItemText(IDC_EDIT_SPEEDVIEW, pGlobal->RBTCTdlg.CurSpeed);
		pGlobal->RBTCTdlg.m_SlidSpeed.SetPos(_tstoi(pGlobal->RBTCTdlg.CurSpeed));//设置滑条位置		
	}
	else if (_T("RETP") == sText)
	{  //点位返回处理
		pGlobal->RBTCTdlg.CurPos = sRecvData.Mid(strpos + 1, Recvlen - strpos);
		pGlobal->RBTCTdlg.SetDlgItemText(IDC_STATIC_CURPOS, pGlobal->RBTCTdlg.CurPos);
		SetEvent(pGlobal->Handle_GetPOS);
	}
	else if (_T("RETI") == sText)
	{   //运动返回处理
		str = sRecvData.Mid(strpos + 1, Recvlen - strpos);
		if (_T("1") == str)
		{
			SetEvent(pGlobal->Handle_RBTReadIO[1]);
		}
		else if (_T("0") == str)
		{
			SetEvent(pGlobal->Handle_RBTReadIO[0]);
		}
		else  //RETI:00000000000000001101110010000000
		{
			pGlobal->RBTCTdlg.sCurFullIOVal = str;
			SetEvent(pGlobal->Handle_RBTReadIO[2]);
		}
	}
	return;
}




void ClientSocket_BaseRBT::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (nErrorCode == 0)//连接成功
	{
		bAlive = TRUE;
		pGlobal->AddToRunList(_T("RbtBaseSocket连接成功"));
	}
	else
	{
		bAlive = FALSE;
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
