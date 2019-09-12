// ClientSocket_BaseRBT.cpp : ʵ���ļ�
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


// ClientSocket_BaseRBT ��Ա����
//void ClientSocket_BaseRBT::OnConnect(int nErrorCode)
//{
//	// TODO: �ڴ����ר�ô���� / ����û���
//	if (nErrorCode == 0)//���ӳɹ�
//	{
//		m_bConnected = TRUE;
//
//		pGlobal->AddToRunList(_T("RbtBaseSocket���ӳɹ�"));
//		//AsyncSelect(FD_READ);  //����һ��"��"�������¼���׼������
//	}
//	else
//	{
//		m_bConnected = FALSE;
//	}
//	CAsyncSocket::OnConnect(nErrorCode);
//}

void ClientSocket_BaseRBT::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	memset(cRecvData, 0, 255);
	int iLen = Receive((void*)cRecvData, 255);
	if (iLen > 0)
	{
		DataProcess();
	}
	//	AsyncSelect(FD_READ);  //ÿ�ζ�Ҫ�����ʱ�䣬AsyncSelect(FD_WRITE)���ڴ���onsend����麯�������Ǵ˴�û��д
	CAsyncSocket::OnReceive(nErrorCode);
}

void ClientSocket_BaseRBT::OnSend(int nErrorCode)
{
	try
	{
		Send(cSendData, iSendLen, 0);//��������
	}
	catch (const std::exception&)
	{
		pGlobal->AddToErrorList(_T("�������������������쳣"));
	}
	iSendLen = 0;
	memset(cSendData, 0, sizeof(cSendData));//�������������
											//��������һ��"��"�������¼�������Server��Ϣ
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
	//iPort = 49153;//49152,49153,49154,49155,��Ӧ��������·��� 4��5��6��7�������˳�����ʱһֱĬ����4
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
		AsyncSelect(FD_WRITE);//����Socket��OnSend����
	}
	else
	{
		pGlobal->AddToErrorList(_T("RBT������������δ���ӣ�������Ч"));
	}
	
	//pGlobal->AddToRunList(_T("��������Robot����:") + str);

	LeaveCriticalSection(&Sec_BaseRbtSocket);
	return true;
}
void ClientSocket_BaseRBT::DataProcess()
{
	CJIMIDlg *parent = (CJIMIDlg*)AfxGetApp()->GetMainWnd();
	CString sRecvData, str;
	sRecvData = cRecvData;
	sRecvData.Trim();
	sRecvData.Replace(_T(" "), _T(""));//ȥ���ڲ��ո����
	//pGlobal->AddToRunList(_T("�ӷ�����Robot����:") + sRecvData); //
	int Recvlen = sRecvData.GetLength();
	int strpos = sRecvData.Find(_T(":"));

	CString sText = sRecvData.Mid(strpos - 5, 4);
	if (_T("RETV") == sText)
	{  //�ٶȷ��ش���
		pGlobal->RBTCTdlg.CurSpeed = sRecvData.Mid(strpos + 1, Recvlen - strpos);
		pGlobal->RBTCTdlg.SetDlgItemText(IDC_EDIT_SPEEDVIEW, pGlobal->RBTCTdlg.CurSpeed);
		pGlobal->RBTCTdlg.m_SlidSpeed.SetPos(_tstoi(pGlobal->RBTCTdlg.CurSpeed));//���û���λ��		
	}
	else if (_T("RETP") == sText)
	{  //��λ���ش���
		pGlobal->RBTCTdlg.CurPos = sRecvData.Mid(strpos + 1, Recvlen - strpos);
		pGlobal->RBTCTdlg.SetDlgItemText(IDC_STATIC_CURPOS, pGlobal->RBTCTdlg.CurPos);
		SetEvent(pGlobal->Handle_GetPOS);
	}
	else if (_T("RETI") == sText)
	{   //�˶����ش���
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
	// TODO: �ڴ����ר�ô����/����û���
	if (nErrorCode == 0)//���ӳɹ�
	{
		bAlive = TRUE;
		pGlobal->AddToRunList(_T("RbtBaseSocket���ӳɹ�"));
	}
	else
	{
		bAlive = FALSE;
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
