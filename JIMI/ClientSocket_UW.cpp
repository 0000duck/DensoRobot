// ClientSocket_UW.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "ClientSocket_UW.h"
#include <afxpriv.h>
#include <afxsock.h>

// ClientSocket_UW

ClientSocket_UW::ClientSocket_UW()
{
	sRecvMid = _T("");
	bAlive = FALSE;
	m_bConnected =FALSE;
}

ClientSocket_UW::~ClientSocket_UW()
{
}

// ClientSocket_UW 成员函数
bool ClientSocket_UW::Config()
{
	CString str;
	GetPrivateProfileString(_T("UWSocekt"), _T("IP"), _T("10.10.11.90"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	sIP = str;
	GetPrivateProfileString(_T("UWSocekt"), _T("Port"), _T("8080"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
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
void ClientSocket_UW::DataProcess()
{
	CJIMIDlg *parent = (CJIMIDlg*)AfxGetApp()->GetMainWnd();
	CString sRecvData, str;
	sRecvData = cRecvData;
	//////数据尾部加入校验位，做结束符#////
	if (sRecvData.Find(_T("#"))==-1)
	{
		pGlobal->AddToRunList(_T("从UW Socket接收数据不全，正在继续接收") + sRecvData); //
		sRecvMid = sRecvMid + sRecvData;//中转数据计入累加
		return;
	}
	else
	{
		sRecvData = sRecvMid + sRecvData;
		sRecvMid = _T("");//清空中转数据

		CString stext[4];//最多粘包4个
		CString trimtext;
		iJsonNum = sRecvData.Replace(_T("#"), _T("#"));
		CStringSplit(sRecvData, stext, _T("#"));//#
		for (int i = 0; i < iJsonNum; i++)
		{
			stext[i].Trim(_T("#"));
			pGlobal->AddToRunList(_T("从UW Socket接收:") + stext[i]); //
			pGlobal->UWdlg.UW_Read_cmdcode_DealData(stext[i]);
		}
		//sRecvData.Trim(_T("#"));			
		//pGlobal->AddToRunList(_T("从UW Socket接收:") + sRecvData); //
		//sJsonDATA = sRecvData;
		//pGlobal->UWdlg.UW_Read_cmdcode_DealData(sRecvData);
		SetEvent(pGlobal->Handle_UWRetData);
	}
}

void ClientSocket_UW::UW_Send(CString str)
{
	USES_CONVERSION;
	CJIMIDlg *parent = (CJIMIDlg*)AfxGetApp()->GetMainWnd();
	CString smsg;
	smsg = str + _T("#");

	char buffer[8192];
	memset(buffer, 0, 8192);
	strcpy(buffer, T2A(smsg));
	int ilen = strlen(buffer);
	Send(buffer, ilen);
}

void ClientSocket_UW::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (nErrorCode == 0)//连接成功
	{
		bAlive = TRUE;
		pGlobal->AddToRunList(_T("UWSocket连接成功"));
		pGlobal->UWdlg.UW_Login_Send(_T("robot1"));
		AsyncSelect(FD_READ);  //提请一个"读"的网络事件，准备接收
	}
	else
	{
		bAlive = FALSE;
	}
	CAsyncSocket::OnConnect(nErrorCode);
}


void ClientSocket_UW::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	memset(cRecvData, 0, 8192);
	int iLen = Receive((void*)cRecvData, 8192);
	AsyncSelect(FD_READ);  //提请一个"读"的网络事件，准备接收
	if (iLen > 0)
	{
		DataProcess();
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

void ClientSocket_UW::CloseSocket()
{
	m_bConnected = FALSE;
	pGlobal->AddToRunList(_T("UW_Socekt连接关闭!!!"));
	Close();
}