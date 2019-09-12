#pragma once
class SerialCom
{
public:
	SerialCom();
	~SerialCom();

	CString	sPort;//���ں�
	int	iBaud;//������
	int	iByteSize;//����λ
	int	iParity;//��żУ��λ
	int	iStopBits;//ֹͣλ

	bool bHexSend;//�Ƿ���16���Ʒ���
	HANDLE porthandler;
	HANDLE InitCom(CString comName, int comBaud);//��ʼ������,���õĿ��ų�ȥ
	int CloseCom();//�رմ���
	bool WriteCommand(CString cmd);//���ʹ���ָ��
	CString ReadCommand();//��ȡ���ڻ�����
	CString RunCommand(CString cmd);//���ʹ���ָ��,����ȡ������

	//�������ڷ��㴦��
	void GetCommPort(CComboBox *pComboBox, CString &ComNo);//��ȡ��ǰ���ں�
	void FindCommPort(CComboBox *pComboBox, CString &ComNo);//��ע�����Ѱ�Ҵ��ں�
	BYTE *CStrToByte(int len, CString str);
	//CreateFile //��
	//CloseHandle //�ر�
	//ReadFile  //��ȡ
	//WriteFile  //д��

};

