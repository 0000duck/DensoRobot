#pragma once
#import "msado15.dll"  no_namespace rename("EOF", "adoEOF")
/////////////////////////-------190615-----�������ݿ�������-------///////////////
/////////////////����ʹ�÷������������ݿ�-��������-�Ͽ�----////////////////////////
class ADOFunction
{
public:
	ADOFunction();
	virtual ~ADOFunction();

	//�Զ������
public:
	_ConnectionPtr m_pConnection;    //���Ӳ���
	_CommandPtr m_pCommand;          //SQL�������
	_RecordsetPtr m_pRecordSet;      //��¼������

	CString sDataSource;  //������IP
	CString sPort;        //�������˿�
	CString sUserName;    //�û���
	CString sPassword;    //����
	CString sSQLName;    //����


	bool ConnSQL();//�������ݿ⺯��
	bool CloseSQL();//�ر����ݿ⺯��
	CString CheckUser(CString username, CString userpswd);//�û���ȷ�ϣ����ؿռ���¼ʧ��
};

