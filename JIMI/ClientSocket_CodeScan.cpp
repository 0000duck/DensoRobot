// ClientSocket_CodeScan.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "ClientSocket_CodeScan.h"


// ClientSocket_CodeScan

ClientSocket_CodeScan::ClientSocket_CodeScan()
{
}

ClientSocket_CodeScan::~ClientSocket_CodeScan()
{
}


// ClientSocket_CodeScan 成员函数


void ClientSocket_CodeScan::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (nErrorCode == 0)//连接成功
	{
		bAlive = TRUE;
		pGlobal->AddToRunList(_T("CSSocket连接成功"));
		AsyncSelect(FD_READ);  //提请一个"读"的网络事件，准备接收
	}
	else
	{
		bAlive = FALSE;
	}
	CAsyncSocket::OnConnect(nErrorCode);
}


void ClientSocket_CodeScan::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	memset(cRecvData, 0, 2048);
	int iLen = Receive((void*)cRecvData, 2048);
	AsyncSelect(FD_READ);  //提请一个"读"的网络事件，准备接收
	if (iLen > 0)
	{
		DataProcess();
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

// ClientSocket_CodeScan 成员函数
bool ClientSocket_CodeScan::Config()
{
	CString str;
	GetPrivateProfileString(_T("CSSocekt"), _T("IP"), _T("192.168.0.100"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	sIP = str;
	GetPrivateProfileString(_T("CSSocekt"), _T("Port"), _T("4096"), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
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
void ClientSocket_CodeScan::DataProcess()
{
	CJIMIDlg *parent = (CJIMIDlg*)AfxGetApp()->GetMainWnd();
	CString sRecvData, str;
	sRecvData = cRecvData;

	if (sRecvData.Find(_T("%")) != -1)
	{
		sRecvData.Replace(_T("%"), _T("")); //
	}
	pGlobal->AddToRunList(_T("从CSSocket接收数据:") + sRecvData); //
	
	if (sRecvData.Find(_T("@")) == -1 /*|| sRecvData.Find(_T("NR")) != -1*/)
	{
		//pGlobal->AddToRunList(_T("从CS Socket未接收到正确的码") + sRecvData); //
	}
	else
	{
		CString stext[90];//考虑多个@
		CString trimtext;
		CStringSplit(sRecvData, stext, _T("@"));//#
		pGlobal->CSdlg.SetDlgItemText(IDC_EDIT_CodeVal, sRecvData);
		for (int i = 0; i < 90; i++)
		{
			if (stext[i] == pGlobal->UWdlg.sMaterialId)//康凯斯
			{   
				StopReadCode();//扫到了，就发送停止扫码的命令
				pGlobal->AddToRunList(_T("从CS Socket扫码物料ID正确:") + stext[i]);
				if (stext[i-1] == pGlobal->UWdlg.sQuantity)
				{
					SetEvent(pGlobal->Handle_CSRetData[0]);
					pGlobal->AddToRunList(_T("从CS Socket扫码物料数量正确:") + stext[i-1]);							
				}
				else
				{
					pGlobal->AddToRunList(_T("从扫码物料数量错误:") + stext[i - 1] + _T(",UW数据:") + pGlobal->UWdlg.sQuantity);
					pGlobal->AddToErrorList(_T("从扫码物料数量错误:") + stext[i - 1]+_T(",UW数据:")+ pGlobal->UWdlg.sQuantity);
					SetEvent(pGlobal->Handle_CSRetData[1]);
				}
				return;
			}
			else
			{
				continue;
			}
		}				
	}
//	SetEvent(pGlobal->Handle_CSRetData[2]);
//	pGlobal->AddToErrorList(_T("未扫到与UW匹配的的二维码"));
}

void ClientSocket_CodeScan::CS_Send(CString str)
{
	USES_CONVERSION;
	CJIMIDlg *parent = (CJIMIDlg*)AfxGetApp()->GetMainWnd();
	CString smsg;
	smsg = str;
	char buffer[2048];
	memset(buffer, 0, 2048);
	strcpy(buffer, T2A(smsg));
	int ilen = strlen(buffer);
	Send(buffer, ilen);
}

void ClientSocket_CodeScan::CloseSocket()
{
	m_bConnected = FALSE;
	pGlobal->AddToRunList(_T("CS_Socekt连接关闭!!!"));
	Close();
}

void ClientSocket_CodeScan::ReadCode()
{
	CString str;
	str = _T("LON\r\n");
	CS_Send(str);
}

void ClientSocket_CodeScan::StopReadCode()
{
	CString str;
	str = _T("LOFF\r\n");
	CS_Send(str);
}