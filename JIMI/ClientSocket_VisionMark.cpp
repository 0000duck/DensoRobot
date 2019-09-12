// ClientSocket_VisionMark.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "ClientSocket_VisionMark.h"
#include <afxpriv.h>
#include <afxsock.h>
extern CRITICAL_SECTION Sec_VisionSocket;
// ClientSocket_VisionMark

ClientSocket_VisionMark::ClientSocket_VisionMark()
{
	m_bConnected = FALSE;
}

ClientSocket_VisionMark::~ClientSocket_VisionMark()
{
}


// ClientSocket_VisionMark 成员函数


void ClientSocket_VisionMark::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	memset(cRecvData, 0, 255);
	int iLen = Receive((void*)cRecvData, 255);
	if (iLen > 0)
	{
		DataProcess();
	}
	CAsyncSocket::OnReceive(nErrorCode);
}


void ClientSocket_VisionMark::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	try
	{
		Send(cSendData, iSendLen, 0);//发送数据
	}
	catch (const std::exception&)
	{
		pGlobal->AddToErrorList(_T("Vision Socket连接异常"));
	}

	iSendLen = 0;
	memset(cSendData, 0, sizeof(cSendData));//清除缓冲区数据											//继续提请一个"读"的网络事件，接收Server消息
	AsyncSelect(FD_READ);
	CAsyncSocket::OnSend(nErrorCode);
}


void ClientSocket_VisionMark::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (nErrorCode == 0)//连接成功
	{
		bAlive = TRUE;
		pGlobal->AddToRunList(_T("VsionSocket连接成功"));
		//AsyncSelect(FD_READ);  //提请一个"读"的网络事件，准备接收
	}
	else
	{
		bAlive = FALSE;
	}
	CAsyncSocket::OnConnect(nErrorCode);
}


bool ClientSocket_VisionMark::Config()
{
	CString str;
	GetPrivateProfileString(_T("VisionSocekt"), _T("IP"), _T("10.10.11.127"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	sIP = str;
	GetPrivateProfileString(_T("VisionSocekt"), _T("Port"), _T("8989"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	iPort = _ttoi(str);
	if (Create(0, SOCK_STREAM, FD_CONNECT))
	{
		BOOL Bret = Connect(sIP, iPort);
		DWORD nErrno = GetLastError();
		m_bConnected = TRUE;
		return true;
	}
	return false;
}
void ClientSocket_VisionMark::CloseSocket()
{
	m_bConnected = FALSE;
	Close();
}
bool ClientSocket_VisionMark::SendMSG(CString str)
{
	EnterCriticalSection(&Sec_VisionSocket);
	USES_CONVERSION;
	CJIMIDlg *parent = (CJIMIDlg*)AfxGetApp()->GetMainWnd();
	CString smsg;
	//smsg = str + _T("\r\n");//\r\n
	smsg = str;//\r\n

	iSendLen = smsg.GetLength();
	memset(cSendData, 0, 256);

	strcpy(cSendData, T2A(smsg));
	if (TRUE == m_bConnected)
	{
		AsyncSelect(FD_WRITE);//触发Socket的OnSend函数
		pGlobal->AddToRunList(_T("给Vision Socket发送:") + str);
	}
	else
	{
		pGlobal->AddToErrorList(_T("基础服务器尚未连接，发送无效"));
	}

	
	LeaveCriticalSection(&Sec_VisionSocket);
	return true;
}
void ClientSocket_VisionMark::DataProcess()
{
	CJIMIDlg *parent = (CJIMIDlg*)AfxGetApp()->GetMainWnd();
	CString sRecvData, str;
	sRecvData = cRecvData;
	sRecvData.Trim();
	sRecvData.Replace(_T(" "), _T(""));//去掉内部空格符号
	pGlobal->AddToRunList(_T("从Vision Socket接收:") + sRecvData); //
	int Recvlen = sRecvData.GetLength();
	int strpos = sRecvData.Find(_T("#"));

	pGlobal->Visiondlg.sVisRetPos = sRecvData;
	SetEvent(pGlobal->Handle_VisionRetPOS);

	return;
}