// ClientSocket_VisionMark.cpp : ʵ���ļ�
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


// ClientSocket_VisionMark ��Ա����


void ClientSocket_VisionMark::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ����ר�ô����/����û���
	try
	{
		Send(cSendData, iSendLen, 0);//��������
	}
	catch (const std::exception&)
	{
		pGlobal->AddToErrorList(_T("Vision Socket�����쳣"));
	}

	iSendLen = 0;
	memset(cSendData, 0, sizeof(cSendData));//�������������											//��������һ��"��"�������¼�������Server��Ϣ
	AsyncSelect(FD_READ);
	CAsyncSocket::OnSend(nErrorCode);
}


void ClientSocket_VisionMark::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (nErrorCode == 0)//���ӳɹ�
	{
		bAlive = TRUE;
		pGlobal->AddToRunList(_T("VsionSocket���ӳɹ�"));
		//AsyncSelect(FD_READ);  //����һ��"��"�������¼���׼������
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
		AsyncSelect(FD_WRITE);//����Socket��OnSend����
		pGlobal->AddToRunList(_T("��Vision Socket����:") + str);
	}
	else
	{
		pGlobal->AddToErrorList(_T("������������δ���ӣ�������Ч"));
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
	sRecvData.Replace(_T(" "), _T(""));//ȥ���ڲ��ո����
	pGlobal->AddToRunList(_T("��Vision Socket����:") + sRecvData); //
	int Recvlen = sRecvData.GetLength();
	int strpos = sRecvData.Find(_T("#"));

	pGlobal->Visiondlg.sVisRetPos = sRecvData;
	SetEvent(pGlobal->Handle_VisionRetPOS);

	return;
}