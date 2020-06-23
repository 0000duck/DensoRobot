#pragma once
#include "JIMIDlg.h"
// ClientSocket_VisionMark ����Ŀ��

class ClientSocket_VisionMark : public CAsyncSocket
{
public:
	ClientSocket_VisionMark();
	virtual ~ClientSocket_VisionMark();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);

	BOOL m_bConnected;	 //�Ƿ�����
	char cRecvData[8192];
	char cSendData[8192];
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


