#pragma once
#include "JIMIDlg.h"
// ClientSocket_UW 命令目标

class ClientSocket_UW : public CAsyncSocket
{
public:
	ClientSocket_UW();
	virtual ~ClientSocket_UW();

public:
	CString sIP;
	int iPort;
	BOOL m_bConnected;	 //是否连接
	char cRecvData[8192];//数据过长
	char cSendData[8192];
	UINT iSendLen;
	BOOL bAlive;
	bool Config();
	void DataProcess();
	void CloseSocket();

	CString sRecvMid;//数据不全是用作中转用
	CString sJsonDATA;//已经处理完的数据
	int iJsonNum;//发过来的json个数
	void UW_Send(CString str);//把cstring变成char格式再发送，然后再加上校验位
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
   
};


