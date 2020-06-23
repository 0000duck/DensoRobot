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

	void WidgetStatue(BOOL bstatue);
	int ithread;
	CString sRecvCmdCode;//�ж��յ���ָ������
	int iCmdid;//��������ͻ����������͵İ�������ȷ�ϰ���cmdId����
	int itaskId; //�����
	int iboxId; //�Ϻк�
	int itype;//���ֳ��⻹���̵���1�����⣻2���̵�
	int iXpos;
	int iYpos;
	CString sMaterialId;//uw��������id��Ȼ��������Ҫƥ���ID,�����ȷ�����������ȥ
	CString sQuantity;//��Ҫ����UW��������
	int iQuantity;
	int iErrorCode; //0�����쳣1���п�2���벻��Ӧ3�������쳣���Ҳ�������������С��0��4: ������ƥ�� 5����е���쳣
	
	static UINT UWDlgThread(LPVOID lparam);
/////////////////////////////////////////
	int UW_Ack_Send();//�ظ�UWACK����ź�
	int UW_OutFinish_Send(CString message);//�����˳���ȡ������ź�
	int UW_InFinish_Send();//�����ɣ���ȡ�����������UW

	int UW_Login_Send(CString name);//�����˳���ȡ������ź�
	//----- 19121901 wade add UW�ֿ��̵� ��е�۷��ͺ���--------//
	int bNeedReady;//�Ƿ���Ҫ���з���ready�źţ�����������泵�ĵ�վ��//�浽���أ���ֹ����������ݶ�ʧ
	int UW_Ready_Send();//��е����׼���ã���UW���룬�ȵ�UW��
	int UW_AskPostion_Send();//��е����UW��������
	int UW_ScanMaterilaInfo_Send(CString sCode, int iQuantity);//�����ɨ�����뷢�͸�UW����������
	int UW_ScanMaterilaInfo_Error_Send(CString sCode, int ierrorCode);//�����쳣����������� 1���пգ�2���벻��Ӧ��3�������쳣���Ҳ�������������С��0����4����е���쳣
    //---------------------------------------//
//////////////////////////////////////////////
	int UW_Read_cmdcode_DealData(CString str);//��ȡcmdcode�����봦�����ݣ���һ�������жϵ�

	int UW_Read_ack_DealData(CString str);//��ȡack�����봦�����ݣ�
	int UW_Read_out_DealData(CString str);//��ȡout�����봦������
	int UW_Read_reach_out_DealData(CString str);//��ȡreach_out�����봦������
	int UW_Read_reach_in_DealData(CString str);//��ȡreach_in�����봦������	
	int UW_ListPosNum;//����
	//----- 19121901 wade add UW�ֿ��̵� ��е���յ�UW���ݣ����ݴ�������ACK����ͨ��--------//
	int UW_Read_forklift_reach_DealData(CString str);//�泵��վ�ź�
	int UW_Read_forklift_position_info_DealData(CString str);//���������λ����Ϣ//��ȷ���ߴ�������ط���Ҫ�ж�


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
	afx_msg void OnBnClickedBtnReady();
	afx_msg void OnBnClickedBtnPosask();
	afx_msg void OnBnClickedBtnCoderes();
	afx_msg void OnBnClickedBtnCodeerror();
	afx_msg void OnBnClickedBtnManuclear();
};
