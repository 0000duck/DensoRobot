#pragma once

// ClientSocket_CodeScan ����Ŀ��

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
	BOOL m_bConnected;	 //�Ƿ�����
	char cRecvData[2048];//���ݹ���
	char cSendData[2048];
	UINT iSendLen;
	BOOL bAlive;
	bool Config();
	void DataProcess();
	void CloseSocket();
	void CS_Send(CString str);//��cstring���char��ʽ�ٷ��ͣ�Ȼ���ټ���У��λ
	void ReadCode();//�������ʼ����
	void StopReadCode();//ֹͣ����
};


