#pragma once

// ClientSocket_CodeScan 命令目标

class ClientSocket_CodeScan : public CAsyncSocket
{
public:
	ClientSocket_CodeScan();
	virtual ~ClientSocket_CodeScan();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

public:
	CString sIP;
	int iPort;
	BOOL m_bConnected;	 //是否连接
	char cRecvData[2048];//数据过长
	char cSendData[2048];
	UINT iSendLen;
	BOOL bAlive;
	bool Config();
	void DataProcess();
	void CloseSocket();
	void CS_Send(CString str);//把cstring变成char格式再发送，然后再加上校验位
	void ReadCode();//发送命令开始读码
	void StopReadCode();//停止读码
};


