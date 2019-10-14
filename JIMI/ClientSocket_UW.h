#pragma once
#include "JIMIDlg.h"
// ClientSocket_UW ����Ŀ��

class ClientSocket_UW : public CAsyncSocket
{
public:
	ClientSocket_UW();
	virtual ~ClientSocket_UW();

public:
	CString sIP;
	int iPort;
	BOOL m_bConnected;	 //�Ƿ�����
	char cRecvData[8192];//���ݹ���
	char cSendData[8192];
	UINT iSendLen;
	BOOL bAlive;
	bool Config();
	void DataProcess();
	void CloseSocket();

	CString sRecvMid;//���ݲ�ȫ��������ת��
	CString sJsonDATA;//�Ѿ������������
	int iJsonNum;//��������json����
	void UW_Send(CString str);//��cstring���char��ʽ�ٷ��ͣ�Ȼ���ټ���У��λ
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
   
};


