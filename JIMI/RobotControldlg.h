#pragma once
#include "ClientSocket_Robot.h"
#include "JIMIDlg.h"
#include "afxcmn.h"
#include "afxwin.h"


// RobotControldlg 对话框

class RobotControldlg : public CDialogEx
{
	DECLARE_DYNAMIC(RobotControldlg)

public:
	RobotControldlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RobotControldlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_RobotControl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	CSliderCtrl m_SlidSpeed;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	
	CComboBox m_CombAxisModle;

	int iAxisModle;//Sigle_MOLDE1、单轴运动;X-Y_MOLDE2、X-Y运动;
	void StaticEXChange(int iAxisModle);//不同的轴运动模式
	void PosListIni();//列表控件初始化
	void InsertDataPosList();//把数据插入到位置列表中

	void ReadPosFromINI();//从本地配置文件中读取点位记录
	void WritePosToINI();//将数据写入本地配置文件

    afx_msg void OnBnClickedBtnIpconnect();
	afx_msg void OnSelchangeComboAxismodle();
	afx_msg void OnBnClickedBtnJ1xadd();
	afx_msg void OnBnClickedBtnJ1xsub();
	afx_msg void OnBnClickedBtnJ2yadd();
	afx_msg void OnBnClickedBtnJ2ysub();
	afx_msg void OnBnClickedBtnJ3zadd();
	afx_msg void OnBnClickedBtnJ3zsub();
	afx_msg void OnBnClickedBtnJ4rxadd();
	afx_msg void OnBnClickedBtnJ4rxsub();
	afx_msg void OnBnClickedBtnJ5ryadd();
	afx_msg void OnBnClickedBtnJ5rysub();
	afx_msg void OnBnClickedBtnJ6rzadd();
	afx_msg void OnBnClickedBtnJ6rzsub();
	afx_msg void OnBnClickedBtnRbtsend();
    afx_msg void OnBnClickedBtnGopos();
	afx_msg void OnBnClickedBtnGet();
    afx_msg void OnBnClickedBtnSavepos();
	afx_msg void OnBnClickedBtnUpdatapos();
    afx_msg void OnBnClickedStartbasesocket();
	afx_msg void OnBnClickedBtnBaserbtsend();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnSuspend();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnMotoron();
	CString CurSpeed;
	CString CurPos;//当前位置，整句话
	CString  sCurPos[7];//当前数组 位置
	CString  sCurFullIOVal;//当前数组 位置
	CString  sCurSingleIO[32];//每个IO的值
	int  iCurSingleIO[32];//每个IO的值
	int  iWorkType;//0,正常取放料；1、盘点用
	double dbGetProDis;//取料需要下降的高度，视觉拍照用，
	double dbPutProDis;//放料需要上升和下降的高度，盘点可调用，扫码抬起高度基于视觉定位
	double dbGetPutDownDis;//基于视觉定位高度,定完位置后，接下来都以这个位置去取放料，节省效率，值为视觉高度下降高度
	int iProcessNum;//N组取料放料点
	bool bNeedTransPos;//是否开启中转位置

	CListCtrl m_PosShow;

	CString sFunctionPos[81][7];//80个功能点位，每个点位7个数据
	double dbFunctionPos[81][7];//80个功能点位，每个点位7个数据,double型备用
	
	static UINT RobotMotion(LPVOID lparam);
	static UINT IOUpdatdaThread(LPVOID lparam);
	bool IOupdata();
	bool bIOUpdata;
	int Rbtstep;
	int GetCurPosFromSocekt();//线程用函数，获取表格点位并更新到指定表格位置
	int GetIOSetIOBtm();//线程用函数，获取并设置io状态
	int MoveToPostion(int MovModle, CString sPOS[7], double dbLen);//线程用函数,以指定模式移动到指定点
	int SingleAxisMove(int iAxis, CString sAngle);//单轴运动与运动完成
	int X_YSpaceAxisMove(int iAxis, CString slen);//单轴运动与运动完成

	int RBTIORead(int IONum);//线程用函数,返回0为off，1为on，2为错误
	int RBTIOReadALL();//线程用函数，读取所有的IO值

	int RBTIOSet(int IONum);//设置机器人当前IO为on
	int RBTIOReset(int IONum);//设置机器人当前IO为off

	void ConWidgetStatue(BOOL bShow);//连接的控件的禁用
	void MoveWidgetStatue(BOOL bShow);//跟运动相关的控件的禁用
	void BaseWidgetStatue(BOOL bShow);//基本控件的禁用
	void SetIOBtmStatue();//刷新IO状态，里面包含IO 读取
	bool OpenClamp();//松开夹爪
	bool CloseClamp();//夹紧夹爪
	bool IniIOClamp();//初始化夹爪
	afx_msg void OnBnClickedBtnGetcurpos();
	CNewButton m_IO0;
	CNewButton m_IO1;
	CNewButton m_IO2;
	CNewButton m_IO3;
	CNewButton m_IO4;
	CNewButton m_IO5;
	CNewButton m_IO6;
	CNewButton m_IO7;
	CNewButton m_IO8;
	CNewButton m_IO9;
	CNewButton m_IO10;
	CNewButton m_IO11;
	CNewButton m_IO12;
	CNewButton m_IO13;
	CNewButton m_IO14;
	CNewButton m_IO15;
	CNewButton m_IO16;
	CNewButton m_IO17;
	CNewButton m_IO18;
	CNewButton m_IO19;
	CNewButton m_IO20;
	CNewButton m_IO21;
	CNewButton m_IO22;
	CNewButton m_IO23;
	CNewButton m_IO24;
	CNewButton m_IO25;
	CNewButton m_IO26;
	CNewButton m_IO27;
	CNewButton m_IO28;
	CNewButton m_IO29;
	CNewButton m_IO30;
	CNewButton m_IO31;
	afx_msg void OnBnClickedBtnUpdataiobtnstatue();
	afx_msg void OnBnClickedBtnIo24();
	afx_msg void OnBnClickedBtnIo25();
	afx_msg void OnBnClickedBtnIo26();
	afx_msg void OnBnClickedBtnIo27();
	afx_msg void OnBnClickedBtnIo28();
	afx_msg void OnBnClickedBtnIo29();
	afx_msg void OnBnClickedBtnIo30();
	afx_msg void OnBnClickedBtnIo31();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnSetgetdis();
	afx_msg void OnBnClickedBtnCloseclamp();
	afx_msg void OnBnClickedBtnOpenclamp();
	afx_msg void OnBnClickedBtnIniclamp();
	afx_msg void OnBnClickedBtnSetprocessnum();
	afx_msg void OnBnClickedCheckOpentranspos();
	afx_msg void OnBnClickedBtnSetgetdis2();
	afx_msg void OnBnClickedBtnSetgetputdis();
};
