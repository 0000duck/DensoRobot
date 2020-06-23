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

	void WidgetStatue(BOOL bstatue);
	int ithread;
	CString sRecvCmdCode;//判断收到的指令内容
	int iCmdid;//服务器与客户端主动发送的包（即非确认包）cmdId递增
	int itaskId; //任务号
	int iboxId; //料盒号
	int itype;//区分出库还是盘点用1、出库；2、盘点
	int iXpos;
	int iYpos;
	CString sMaterialId;//uw传过来的id，然后我们需要匹配的ID,如果正确，则继续传过去
	CString sQuantity;//需要传给UW的总数量
	int iQuantity;
	int iErrorCode; //0：无异常1：夹空2：码不对应3：数量异常（找不到，或者数量小于0）4: 数量不匹配 5：机械臂异常
	
	static UINT UWDlgThread(LPVOID lparam);
/////////////////////////////////////////
	int UW_Ack_Send();//回复UWACK完成信号
	int UW_OutFinish_Send(CString message);//机器人出库取放完成信号
	int UW_InFinish_Send();//入库完成，夹取完后发送入库包给UW

	int UW_Login_Send(CString name);//机器人出库取放完成信号
	//----- 19121901 wade add UW仓库盘点 机械臂发送函数--------//
	int bNeedReady;//是否需要进行发送ready信号，是用来请求叉车的到站的//存到本地，防止软件重启数据丢失
	int UW_Ready_Send();//机械臂已准备好，向UW申请，等到UW送
	int UW_AskPostion_Send();//机械臂向UW请求坐标
	int UW_ScanMaterilaInfo_Send(CString sCode, int iQuantity);//如果把扫到得码发送给UW，动作正常
	int UW_ScanMaterilaInfo_Error_Send(CString sCode, int ierrorCode);//动作异常，比如错误码 1：夹空；2：码不对应；3：数量异常（找不到，或者数量小于0）；4：机械臂异常
    //---------------------------------------//
//////////////////////////////////////////////
	int UW_Read_cmdcode_DealData(CString str);//读取cmdcode数据与处理数据，第一步做总判断的

	int UW_Read_ack_DealData(CString str);//读取ack数据与处理数据，
	int UW_Read_out_DealData(CString str);//读取out数据与处理数据
	int UW_Read_reach_out_DealData(CString str);//读取reach_out数据与处理数据
	int UW_Read_reach_in_DealData(CString str);//读取reach_in数据与处理数据	
	int UW_ListPosNum;//组数
	//----- 19121901 wade add UW仓库盘点 机械臂收到UW数据，数据处理函数，ACK函数通用--------//
	int UW_Read_forklift_reach_DealData(CString str);//叉车到站信号
	int UW_Read_forklift_position_info_DealData(CString str);//请求回来的位置信息//正确或者错误，这个地方需要判断


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
	afx_msg void OnBnClickedBtnReady();
	afx_msg void OnBnClickedBtnPosask();
	afx_msg void OnBnClickedBtnCoderes();
	afx_msg void OnBnClickedBtnCodeerror();
	afx_msg void OnBnClickedBtnManuclear();
};
