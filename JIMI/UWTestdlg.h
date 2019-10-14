#pragma once


// UWTestdlg 对话框

class UWTestdlg : public CDialogEx
{
	DECLARE_DYNAMIC(UWTestdlg)

public:
	UWTestdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UWTestdlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_UW_Test };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnHttpsend();
	afx_msg void OnBnClickedBtnConnect();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRetack();
	afx_msg void OnBnClickedBtnOutfinish();
	afx_msg void OnBnClickedBtninfinish();

	int ithread;
	CString sRecvCmdCode;//判断收到的指令内容
	int iCmdid;
	int itaskId;
	
	static UINT UWDlgThread(LPVOID lparam);

	int UW_Ack_Send();//回复UWACK完成信号
	int UW_OutFinish_Send(CString message);//机器人出库取放完成信号
	int UW_InFinish_Send();//入库完成，夹取完后发送入库包给UW
	int UW_Login_Send(CString name);//机器人出库取放完成信号

	int UW_Read_cmdcode_DealData(CString str);//读取cmdcode数据与处理数据，第一步做总判断的

	int UW_Read_ack_DealData(CString str);//读取ack数据与处理数据
	int UW_Read_out_DealData(CString str);//读取out数据与处理数据
	int UW_Read_reach_out_DealData(CString str);//读取reach_out数据与处理数据
	int UW_Read_reach_in_DealData(CString str);//读取reach_in数据与处理数据

	int UW_ListPosNum;//组数
	
	//UW_OutPos_struct UW_OutPos;
 //   CString cmdcode;
	//int cmdid;
	//CString supplier;
	//int taskId;
	//CString materialNo[40];
	//int quantity[40];
	//int row[40];//,row横向的(行)
	//int col[40];//column纵向的(列)
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
		int row[40];//,row横向的(行)
		int col[40];//column纵向的(列)
		CString productionTime[40];
		int materialTypeId[40];
	}UW_OutPos;
	afx_msg void OnBnClickedCheckUw();
	afx_msg void OnBnClickedBtnRetlogin();
};
