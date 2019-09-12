#pragma once

#import "msado15.dll"  no_namespace rename("EOF", "adoEOF")


class ADOManage
{
public:
	ADOManage();
	~ADOManage();

	//自定义参数
public:
	_ConnectionPtr m_pConnection;    //连接参数
	_CommandPtr m_pCommand;          //SQL命令参数
	_RecordsetPtr m_pRecordSet;      //记录集参数


	//自定义函数
public:
	bool ConnSQL();//连接数据库函数
	bool ConndbSQL();//连接数据库函数2,数据库配置那里用来测试连接用
	bool CloseAll();//关闭数据库函数

	CString CheckUser(CString username, CString userpswd);//用户名确认
	int CpCaiheByImei(CString imei, CString ZhiDan);//根据IMEI判断对比工位标志位
	bool CheckCHRESULT(CString imei);//检查对比工位彩盒判断

	//CString 


	int CpImeiByNo(CString Syllablesqlstr, CString noname, CString no, CString strzhidan);//根据其它号段寻找IMEI

	int InsertResultLog(CString zhidan, CString imei, CString weight, CString uplimit, CString downlimit, CString result, CString ip, CString username, CString remarkerror);//插入正确数据到表中
	int JudgeImei(CString imei);//判断IMEI号是否存在
	int JudgeZhidan(CString imei,CString Zhidan);//判断制单号是否对得上
	void Savesyllable(CString order, int IMEI, int SN, int SIM, int VIP, int ICCID, int BAT, int MAC, int Equipment,int RFID, int IMEI2, CString uplimit, CString downlimit, CString disuplimit, CString disdownlimit);//保存订单所选择的字段
	void Readsyllable(CString order);//读取订单所选择的字段
	void Savebind(CString order, int SIM, int VIP, int ICCID, int BAT, int MAC, int Equipment, int RFID);//保存订单所绑定的字段
	void Readbind(CString order);//读取订单所绑定的字段
	void SaveConfig(CString order, int imei3Flag);//保存一些配置
	void ReadConfig(CString order);//读取一些配置
	_RecordsetPtr GetOrderNumber();//获取订单号
	_RecordsetPtr GetIMEIByOrderNumber(CString ordernumber);//根据订单号获取IMEI号
	_RecordsetPtr JudgeOrderNumber(CString ordernumber);//判断订单号是否存在

	CString ADOManage::GetTime();//获取当前系统时间


	//目前还未使用的函数
	_RecordsetPtr GetRst();

	//获取数据库信息，当我们连接数据库的时候就先获取这些数据再连接
public:
	CString m_DataSource;  //服务器IP
	CString m_Port;        //服务器端口
	CString m_UserName;    //用户名
	CString m_Password;    //密码
	CString m_Firstdbname;    //镭雕数据库名称
	CString m_Seconddbname;  //订单数据库名称
	CString m_Firstformname;  //输出结果表格内容
	CString m_Secondformname;//订单数据表名称，自动匹配IMEI号匹配的表格
	void GetDBINFO();//获取数据库信息函数

	//去掉字符串头尾
	void ADOManage::trim(CString &str);

	CString CreateIMEI15(CString imei);
};

