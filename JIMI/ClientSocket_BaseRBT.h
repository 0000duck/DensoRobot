#pragma once
#include "JIMIDlg.h"
// ClientSocket_BaseRBT 命令目标

class ClientSocket_BaseRBT : public CAsyncSocket
{
public:
	ClientSocket_BaseRBT();
	virtual ~ClientSocket_BaseRBT();
//	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

	BOOL m_bConnected;	 //是否连接
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
	//	CSocket m_sockReceive;
	bool Config();
	void CloseSocket();
	bool SendMSG(CString str);
	void DataProcess();
	//virtual void OnConnect(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
};


