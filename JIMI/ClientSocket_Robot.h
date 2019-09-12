#pragma once
#include "JIMIDlg.h"
// ClientSocket_Robot ����Ŀ��

class ClientSocket_Robot : public CAsyncSocket
{
public:
	ClientSocket_Robot();
	virtual ~ClientSocket_Robot();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

	BOOL m_bConnected;	 //�Ƿ�����
	char cRecvData[255];
	char cSendData[255];
	UINT iSendLen;

public:
	CString sIP;
	int iPort;
	CString sIPSettingIniPath;
	

	DWORD dwReceiveHeartBeatTime;
	DWORD dwSendHeatBeatTime;
	BOOL bAlive;
	bool Config();
	void CloseSocket();
	bool SendMSG(CString str);
	void DataProcess();
	
};


