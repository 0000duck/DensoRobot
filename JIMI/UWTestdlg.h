#pragma once


// UWTestdlg �Ի���

class UWTestdlg : public CDialogEx
{
	DECLARE_DYNAMIC(UWTestdlg)

public:
	UWTestdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~UWTestdlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_UW_Test };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnHttpsend();
	afx_msg void OnBnClickedBtnConnect();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRetack();
	afx_msg void OnBnClickedBtnOutfinish();
	afx_msg void OnBnClickedBtninfinish();

	int ithread;
	CString sRecvCmdCode;//�ж��յ���ָ������
	int iCmdid;
	int itaskId;
	
	static UINT UWDlgThread(LPVOID lparam);

	int UW_Ack_Send();//�ظ�UWACK����ź�
	int UW_OutFinish_Send(CString message);//�����˳���ȡ������ź�
	int UW_InFinish_Send();//�����ɣ���ȡ�����������UW
	int UW_Login_Send(CString name);//�����˳���ȡ������ź�

	int UW_Read_cmdcode_DealData(CString str);//��ȡcmdcode�����봦�����ݣ���һ�������жϵ�

	int UW_Read_ack_DealData(CString str);//��ȡack�����봦������
	int UW_Read_out_DealData(CString str);//��ȡout�����봦������
	int UW_Read_reach_out_DealData(CString str);//��ȡreach_out�����봦������
	int UW_Read_reach_in_DealData(CString str);//��ȡreach_in�����봦������

	int UW_ListPosNum;//����
	
	//UW_OutPos_struct UW_OutPos;
 //   CString cmdcode;
	//int cmdid;
	//CString supplier;
	//int taskId;
	//CString materialNo[40];
	//int quantity[40];
	//int row[40];//,row�����(��)
	//int col[40];//column�����(��)
	//CString productionTime[40];
	//CString materialTypeId[40];
	struct UW_OutPos_struct
	{
		CString cmdcode;
		int cmdid;
		CString supplier;
		int taskId;
		CString materialNo[40];
		int quantity[40];
		int row[40];//,row�����(��)
		int col[40];//column�����(��)
		CString productionTime[40];
		int materialTypeId[40];
	}UW_OutPos;
	afx_msg void OnBnClickedCheckUw();
	afx_msg void OnBnClickedBtnRetlogin();
};
