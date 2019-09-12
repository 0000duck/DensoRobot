#include "stdafx.h"
#include "ADOManage.h"
#include "iostream"   
#include "vector"
#include <string>
#include "JIMIDLG.h"


//全局变量需在类外进行初始化

ADOManage::ADOManage() :
m_DataSource(_T("10.10.11.90")),
m_Port(_T("6033")),
m_UserName(_T("sa")),
m_Password(_T("jiminewpower")),
m_Firstdbname(_T("GPSTest")),
m_Seconddbname(_T("GPSTest")),
m_Firstformname(_T("Gps_WeightNetOrderResult")),
m_Secondformname(_T("Gps_ManuPrintParam"))
{

}


ADOManage::~ADOManage()
{
}

//连接数据库
bool ADOManage::ConnSQL()
{
	CoInitialize(NULL); //初始化COM环境           
	m_pConnection.CreateInstance(_T("ADODB.Connection"));//初始化Connection指针 
//	GetDBINFO();//获取数据库信息
/*打开数据库“SQLServer”，这里需要根据数据库的情况 */
	CString m_ConnectStr;//连接字符串
	//要注意连接字符串有三种模式，这里应该选择网络模式
	m_ConnectStr = _T("Provider=SQLOLEDB.1;Data Source=") + m_DataSource + _T(",") + m_Port + _T(";Network Library=DBMSSOCN;Initial Catalog=") + m_Firstdbname;
	try
	{
		m_pConnection->Open(_bstr_t(m_ConnectStr), _bstr_t(m_UserName), _bstr_t(m_Password), adConnectUnspecified);
	}
	catch (_com_error &e)
	{
		::MessageBox(NULL, _T("数据库连接错误"), _T("异常信息"), NULL); /*打印出异常原因*/
		return 0;
	}
	return 1;
}

//连接数据库
bool ADOManage::ConndbSQL()
{
	CoInitialize(NULL); //初始化COM环境           
	m_pConnection.CreateInstance(_T("ADODB.Connection"));//初始化Connection指针 
	try
	{
		/*打开数据库“SQLServer”，这里需要根据数据库的情况 */
		CString m_ConnectStr;//连接字符串

		//要注意连接字符串有三种模式，这里应该选择网络模式
		m_ConnectStr = _T("Provider=SQLOLEDB.1;Data Source=") + m_DataSource + _T(",") + m_Port + _T(";Network Library=DBMSSOCN;Initial Catalog=") + m_Firstdbname;
		m_pConnection->Open(_bstr_t(m_ConnectStr), _bstr_t(m_UserName), _bstr_t(m_Password), adConnectUnspecified);
	}
	catch (_com_error &e)
	{
		::MessageBox(NULL, _T("数据库连接错误"), _T("异常信息"), NULL); /*打印出异常原因*/
		return 0;
	}
	return 1;
}

//关闭数据库连接
bool ADOManage::CloseAll()
{
	if (m_pRecordSet->GetState() == adStateOpen)
	{
		m_pRecordSet->Close();
	}
	if (m_pRecordSet)
	{
		m_pRecordSet.Release();
		m_pRecordSet = NULL;
	}
	if (m_pConnection->GetState() == adStateOpen)
	{
		m_pConnection->Close();
	}
	if (m_pConnection)
	{
		m_pConnection.Release();
		m_pConnection = NULL;
	}
	return 1;
}

//获取数据库信息
void ADOManage::GetDBINFO()
{
	CString str;

	GetPrivateProfileString(_T("DatabaseInfo"), _T("DataSource"), _T(""), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ADOManage::m_DataSource = str;
	str.ReleaseBuffer();
	GetPrivateProfileString(_T("DatabaseInfo"), _T("Port"), _T(""), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ADOManage::m_Port = str;
	str.ReleaseBuffer();
	GetPrivateProfileString(_T("DatabaseInfo"), _T("UserName"), _T(""), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ADOManage::m_UserName = str;
	str.ReleaseBuffer();
	GetPrivateProfileString(_T("DatabaseInfo"), _T("Password"), _T(""), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ADOManage::m_Password = str;
	str.ReleaseBuffer();
	GetPrivateProfileString(_T("DatabaseInfo"), _T("Firstdbname"), _T(""), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ADOManage::m_Firstdbname = str;
	str.ReleaseBuffer();
	GetPrivateProfileString(_T("DatabaseInfo"), _T("Firstformname"), _T(""), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ADOManage::m_Firstformname = str;
	str.ReleaseBuffer();
	GetPrivateProfileString(_T("DatabaseInfo"), _T("Seconddbname"), _T(""), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ADOManage::m_Seconddbname = str;
	str.ReleaseBuffer();
	GetPrivateProfileString(_T("DatabaseInfo"), _T("Secondformname"), _T(""), str.GetBuffer(50), 50, _T(".\\SystemInfo.ini"));
	ADOManage::m_Secondformname = str;
	str.ReleaseBuffer();
}


_RecordsetPtr ADOManage::GetRst()
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针 
	CString strSql;
	strSql = "Truncate table [testLD].[dbo].[testld]";
	//strSql = "select * from BLEStatus";//具体执行的SQL语句

	m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//将查询数据导入m_pRecordset数据容器
	return m_pRecordSet;
}

//根据其它号段寻找IMEI
int ADOManage::CpImeiByNo(CString Syllablesqlstr, CString noname, CString no, CString strzhidan)
{
	//初始化Recordset指针
	m_pRecordSet.CreateInstance(__uuidof(Recordset));

	//参数
	//_variant_t a;
	CString strSql;

	//根据用户选择的字段去将IMEI号转换出来
	strSql = _T("SELECT * FROM [") + m_Seconddbname + _T("].[dbo].[Gps_ManuPrintParam] WHERE ZhiDan ='")+strzhidan+_T("' AND( ");
	strSql += Syllablesqlstr+L")";
	strSql.Replace(L"InputNumber",no);//然后将里面的预设字符串替换掉成具体的数据

	try 
	{
		m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	}
	catch (_com_error &e)
	{
		//不要弹框，工厂没时间点
		//::MessageBox(NULL, _T("自动匹配字段关系出错"), _T("异常信息"), NULL); /*打印出异常原因*/
	}

	////查找IMEI是否存在，不存在返回0代表未找到IMEI
	//strSql = _T("SELECT [IMEI] FROM [") + m_Seconddbname + _T("].[dbo].[") + m_Secondformname + _T("] WHERE [") + noname + _T("] =") + _T("'") + no + _T("'") + _T("AND ZhiDan='") + strzhidan + _T("'");
	//m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句

	//代表不存在此号段
	if (m_pRecordSet->adoEOF)
	{
		//不要弹框，工厂没时间点
		//::MessageBox(NULL, _T("Gps_ManuPrintParam字段未匹配到相应IMEI"), _T("异常信息"), NULL); /*打印出异常原因*/
		return 0;
	}

	return 2;//上面都没问题就返回2代表成功
}

//判断IMEI号是否存在
int ADOManage::JudgeImei(CString imei)
{
	//初始化Recordset指针
	m_pRecordSet.CreateInstance(__uuidof(Recordset));

	//参数
	_variant_t a;
	CString strSql;

	//查找IMEI是否存在，不存在返回0代表未找到IMEI
	strSql = _T("SELECT [IMEI] FROM [") + m_Seconddbname + _T("].[dbo].[") + m_Secondformname + _T("] WHERE [IMEI] =") + _T("'") + imei + _T("'");
	m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句

	if (m_pRecordSet->adoEOF)
	{
		return 0;
	}

	return 1;
}

//判断制单号是否对得上
int ADOManage::JudgeZhidan(CString imei,CString Zhidan)
{
	//初始化Recordset指针
	m_pRecordSet.CreateInstance(__uuidof(Recordset));

	//参数
	_variant_t a;
	CString strSql;

	//查找IMEI是否存在，不存在返回0代表未找到IMEI
	strSql = _T("SELECT [ZhiDan],[IMEI] FROM [") + m_Seconddbname + _T("].[dbo].[") + m_Secondformname + _T("] WHERE [IMEI] ='") + imei + _T("' AND [ZhiDan]='") + Zhidan+_T("'");
	m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句


	//找不到那就返回1
	if (m_pRecordSet->adoEOF)
	{
		return 1;
	}

	return 0;//返回0就代表对得上
}


//插入正确数据到表中
int ADOManage::InsertResultLog(CString zhidan, CString imei, CString weight,CString uplimit, CString downlimit, CString result, CString ip, CString username, CString remarkerror)
{
	//初始化Recordset指针
	m_pRecordSet.CreateInstance(__uuidof(Recordset));

	remarkerror = GetTime() +_T(" ") + remarkerror + _T("!!!!!");//给结果加上时间
	//参数
	_variant_t Affectline;
	int AffectLine = 0;
	CString strSql;
	strSql = _T("SELECT * FROM [") + m_Firstdbname + _T("].[dbo].[") + m_Firstformname + _T("] WHERE [IMEI]='") + imei + _T("'");
	m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	if (m_pRecordSet->adoEOF)//如果没有该项就插入，有就刷新
	{
		remarkerror = _T("1. ") + remarkerror;
		//将数据插入表中
		strSql = _T("insert into[") + m_Firstdbname + _T("].[dbo].[") + m_Firstformname + _T("]([ZhiDan],[IMEI], [Weight],[UpperLimit],[DownLimit], [RESULT], [RecordTime], [IP], [UserName],[Remark],[ReadTimes])values('")
			+ zhidan + _T("', '") + imei + _T("', '") + weight + _T("', '") + uplimit + _T("', '") + downlimit + _T("', '") + result + _T("', '")  + GetTime() + _T("', '") + ip + _T("', '") + username + _T("', '") + remarkerror +_T("', '1'") + _T(")");//具体执行的SQL语句
		try{
		m_pConnection->Execute(_bstr_t(strSql), &Affectline, adCmdText);//直接执行语句
		}
		catch (_com_error &e)
		{
			//不要弹框，工厂没时间点
			//::MessageBox(NULL, _T("数据库插入更新错误"), _T("异常信息"), NULL); /*打印出异常原因*/
		}
	}
	else//刷新数据
	{
		CString sRemark = m_pRecordSet->GetCollect("Remark");
		//重扫统计
		CString str = m_pRecordSet->GetCollect("ReadTimes");//扫描次数统计
		int itimes = _wtoi(str.GetBuffer());
		itimes = itimes + 1;
		str.Format(_T("%d"), itimes);



		sRemark = str+_T(".重扫")+ remarkerror + sRemark;  //将此前旧的错误内容，累加再重新写入
		strSql = _T("UPDATE[") + m_Firstdbname + _T("].[dbo].[") + m_Firstformname + _T("]") + _T("SET Weight='") + weight + _T("',RESULT ='") + result + _T("', RecordTime='") + GetTime() + _T("',IP ='") + ip + _T("',UserName ='") + username + _T("',Remark='") + sRemark + _T("',ReadTimes ='") + str + _T("' where[IMEI] = '") + imei + _T("'");

		try {
			m_pConnection->Execute(_bstr_t(strSql), &Affectline, adCmdText);//直接执行语句
		}
		catch (_com_error &e)
		{
			//不要弹框，工厂没时间点
			//::MessageBox(NULL, _T("数据库刷新错误，或数据长度过长"), _T("异常信息"), NULL); /*打印出异常原因*/
		}
	}
	return AffectLine;
}

//获取订单号码
_RecordsetPtr ADOManage::GetOrderNumber()
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针
	CString strSql = _T("SELECT [ZhiDan] FROM [") + m_Seconddbname + _T("].[dbo].[Gps_ManuOrderParam] WHERE Status='0' OR Status='1' order by ZhiDan" );
	//CString strSql = _T("SELECT [ZhiDan] FROM [") + m_Seconddbname + _T("].[dbo].[orderld]");
	try
	{
		m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	}
	catch (_com_error &e)
	{
		::MessageBox(NULL, _T("读取订单信息错误"), _T("异常信息"), NULL); /*打印出异常原因*/
	}
	
	return m_pRecordSet;
}

//根据订单号获取IMEI号
_RecordsetPtr ADOManage::GetIMEIByOrderNumber(CString ordernumber)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针
//	CString strSql = _T("SELECT * FROM [") + m_Seconddbname + _T("].[dbo].[Gps_ManuOrderParam] WHERE [ZhiDan] =") + _T("'") + ordernumber + _T("'");
	CString strSql = _T("SELECT [IMEIStart],[IMEIEnd] FROM [") + m_Seconddbname + _T("].[dbo].[Gps_ManuOrderParam] WHERE [ZhiDan] =") + _T("'") + ordernumber + _T("'");	
	try
	{
		m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句

	}
	catch (_com_error &e)
	{
		::MessageBox(NULL, _T("读取订单信息错误"), _T("异常信息"), NULL); /*打印出异常原因*/
	}
	return m_pRecordSet;
}

//判断订单号是否存在
_RecordsetPtr ADOManage::JudgeOrderNumber(CString ordernumber)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针

	CString strSql = _T("SELECT [ZhiDan] FROM [") + m_Seconddbname + _T("].[dbo].[Gps_ManuOrderParam] WHERE [ZhiDan] =") + _T("'") + ordernumber + _T("'");
	//	CString strSql = _T("SELECT * FROM [") + m_Seconddbname + _T("].[dbo].[orderld] WHERE [ZhiDan] =") + _T("'") + ordernumber + _T("'");

	m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句

	return m_pRecordSet;

}


//保存订单所选择的字段和限位设置
void ADOManage::Savesyllable(CString order, int IMEI, int SN, int SIM, int VIP, int ICCID, int BAT, int MAC, int Equipment, int RFID, int IMEI2, CString uplimit, CString downlimit, CString disuplimit,CString disdownlimit)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针
	//CString a;

	_variant_t Affectline;
//	CString strSql;

	CString strSql = _T("SELECT [IMEISyllable] FROM [") + m_Seconddbname + _T("].[dbo].[Gps_WeightNetOrderRelationParam] WHERE [ZhiDan]='") + order + _T("'");
	m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	if (m_pRecordSet->adoEOF)//如果没有该项就插入，有就刷新
	{
	  //将数据插入表中
		strSql.Format(_T("insert into[" + m_Firstdbname + "].[dbo].[Gps_WeightNetOrderRelationParam]([ZhiDan],[IMEISyllable], [SNSyllable], [SIMSyllable], [VIPSyllable], [ICCIDSyllable], [BATSyllable], [MACSyllable], [EquipmentSyllable],[RFIDSyllable],[IMEISyllable],[UpperLimit],[DownLimit],[DisUpperLimit],[DisDownLimit])values('")
			+ order + _T("', %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s)"), IMEI, SN, SIM, VIP, ICCID, BAT, MAC, Equipment,RFID,IMEI2,uplimit,downlimit,disuplimit,disdownlimit);
		try{
			m_pConnection->Execute(_bstr_t(strSql), &Affectline, adCmdText);//直接执行语句
		}
		catch (_com_error &e)
		{
		}
	}
	else
	{
		//Affectline是insert操作返回的影响行数，如果为0代表插入失败，也就是说之前已经插入过这条数据
	    //	if (Affectline.vt == 0)
		try
		{
			strSql.Format(_T("UPDATE[" + m_Firstdbname + "].[dbo].[Gps_WeightNetOrderRelationParam] SET [IMEISyllable]=%d, [SNSyllable]=%d, [SIMSyllable]=%d, [VIPSyllable]=%d, [ICCIDSyllable]=%d, [BATSyllable]=%d, [MACSyllable]=%d, [EquipmentSyllable]=%d,[RFIDSyllable]=%d,[UpperLimit]=%s,[DownLimit]=%s,[DisUpperLimit]=%s,[DisDownLimit]=%s WHERE [ZhiDan]='") + order + _T("'"), IMEI, SN, SIM, VIP, ICCID, BAT, MAC, Equipment,RFID, uplimit, downlimit, disuplimit, disdownlimit);
			m_pConnection->Execute(_bstr_t(strSql), &Affectline, adCmdText);//直接执行语句
		}
		catch (_com_error &e)
		{
		}
	}	
}

//读取订单所选择的字段
void ADOManage::Readsyllable(CString order)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针
//	CString strSql = _T("SELECT  * FROM [" + m_Firstdbname + "].[dbo].[Gps_ManuCpOrderRelationParam] WHERE [ZhiDan]='") + order + _T("'");
	CString strSql = _T("SELECT * FROM [" + m_Firstdbname + "].[dbo].[Gps_WeightNetOrderRelationParam] WHERE [ZhiDan]='") + order + _T("'");
	try
	{
		m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	}
	catch (_com_error &e)
	{
		AfxMessageBox(_T("读取数据库Gps_WeightNetOrderRelationParam失败"));
	}
	

}

//保存订单所绑定的字段
void ADOManage::Savebind(CString order, int SIM, int VIP, int ICCID, int BAT, int MAC, int Equipment, int RFID)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针

	//参数
	_variant_t Affectline;
	CString strSql;
	strSql = _T("SELECT [IMEISyllable] FROM [") + m_Seconddbname + _T("].[dbo].[Gps_WeightNetOrderRelationParam] WHERE [ZhiDan]='") + order + _T("'");
	m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	if (m_pRecordSet->adoEOF)//如果没有该项就插入，有就刷新
	{
		//将数据插入表中
		strSql.Format(_T("insert into[" + m_Firstdbname + "].[dbo].[Gps_WeightNetOrderRelationParam]([ZhiDan],[SIMBind], [VIPBind], [ICCIDBind], [BATBind], [MACBind], [EquipmentBind],[RFIDBind])values('")
			+ order + _T("', %d,%d,%d,%d,%d,%d,%d)"), SIM, VIP, ICCID, BAT, MAC, Equipment,RFID);
		try{
			m_pConnection->Execute(_bstr_t(strSql), &Affectline, adCmdText);//直接执行语句
		}
		catch (_com_error &e)
		{
		}
	}
	else
	{
		//Affectline是insert操作返回的影响行数，如果为0代表插入失败，也就是说之前已经插入过这条数据
	//	if (Affectline.vt == 0)
		try
		{
			strSql.Format(_T("UPDATE[" + m_Firstdbname + "].[dbo].[Gps_WeightNetOrderRelationParam] SET [SIMBind]=%d, [VIPBind]=%d, [ICCIDBind]=%d, [BATBind]=%d, [MACBind]=%d, [EquipmentBind]=%d,[RFIDBind]=%d  WHERE [ZhiDan]='") + order + _T("'"), SIM, VIP, ICCID, BAT, MAC, Equipment,RFID);
			m_pConnection->Execute(_bstr_t(strSql), &Affectline, adCmdText);//直接执行语句
		}
		catch (_com_error &e)
	   {
		}

	}

	
}

//读取订单所绑定的字段
void ADOManage::Readbind(CString order)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针
//	CString strSql = _T("SELECT  * FROM [" + m_Firstdbname + "].[dbo].[Gps_ManuCpOrderRelationParam] WHERE [ZhiDan]='") + order + _T("'");
	CString strSql = _T("SELECT  * FROM [" + m_Firstdbname + "].[dbo].[Gps_WeightNetOrderRelationParam] WHERE [ZhiDan]='") + order + _T("'");
	m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
}

//保存一些配置
void ADOManage::SaveConfig(CString order, int imei3Flag)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针

	//参数
	_variant_t Affectline;
	CString strSql;
	strSql = _T("SELECT [IMEISyllable] FROM [") + m_Seconddbname + _T("].[dbo].[Gps_WeightNetOrderRelationParam] WHERE [ZhiDan]='") + order + _T("'");
	m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	if (m_pRecordSet->adoEOF)//如果没有该项就插入，有就刷新
	{
		//将数据插入表中
		strSql.Format(_T("insert into[" + m_Firstdbname + "].[dbo].[Gps_WeightNetOrderRelationParam]([ZhiDan],[IMEI3Flag])values('") + order + _T("', %d)"), imei3Flag);
		try {
			m_pConnection->Execute(_bstr_t(strSql), &Affectline, adCmdText);//直接执行语句
		}
		catch (_com_error &e)
		{
		}
	}
	else
	{
		//Affectline是insert操作返回的影响行数，如果为0代表插入失败，也就是说之前已经插入过这条数据
		//if (Affectline.vt == 0)
		try
		{
			strSql.Format(_T("UPDATE[" + m_Firstdbname + "].[dbo].[Gps_WeightNetOrderRelationParam] SET [IMEI3Flag]=%d WHERE [ZhiDan]='") + order + _T("'"), imei3Flag);
			m_pConnection->Execute(_bstr_t(strSql), &Affectline, adCmdText);//直接执行语句
		}
		catch (_com_error &e)
		{
		}
	}
}

//读取一些配置
void ADOManage::ReadConfig(CString order)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//初始化Recordset指针
	CString strSql = _T("SELECT  * FROM [" + m_Firstdbname + "].[dbo].[Gps_WeightNetOrderRelationParam] WHERE [ZhiDan]='") + order + _T("'");
	try
	{
        m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	}
	catch (_com_error &e)
	{

	}
	
}


//获取当前时间函数
CString ADOManage::GetTime(){
	SYSTEMTIME time;
	CString strTime;
	GetLocalTime(&time);
	strTime.Format(_T("%d/%d/%d %02d:%02d:%02d"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	return strTime;
}

CString ADOManage::CheckUser(CString username, CString userpswd)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	CString strSql = _T("SELECT UserDes From Gps_User WHERE UserName = '" )+ username + _T("' AND UserPwd = '") + userpswd + _T("'");
	try
	{
		m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	}
	catch (_com_error &e)
	{

	}
	if (!m_pRecordSet->adoEOF)
	{
		return m_pRecordSet->GetCollect("UserDes").bstrVal;	
	}
	return _T("");
}
//根据IMEI判断对比工位彩盒标志位判断
bool ADOManage::CheckCHRESULT(CString imei)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//参数
	_variant_t a;
	CString strSql, strzhidan;

	//查找IMEI是否存在，不存在返回0代表未找到IMEI
	strSql = _T("SELECT [CHResult] FROM [") + m_Seconddbname + _T("].[dbo].[Gps_ManuCpParam] WHERE [IMEI1] =") + _T("'") + imei + _T("'");
	try
	{
		m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	}
	catch (_com_error &e)
	{
		return false;
	}
	if (m_pRecordSet->adoEOF)
	{
		return false;
	}
	else
	{
		CString ret = m_pRecordSet->GetCollect("CHResult");
		//CString ret = m_pRecordSet->adoEOF;
		if ("1" == ret)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
//根据IMEI判断对比工位标志位
int ADOManage::CpCaiheByImei(CString imei, CString ZhiDan)
{
	//初始化Recordset指针
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	//参数
	_variant_t a;
	CString strSql, strzhidan;

	//查找IMEI是否存在，不存在返回0代表未找到IMEI
	strSql = _T("SELECT [CPRESULT] FROM [") + m_Seconddbname + _T("].[dbo].[Gps_ManuCpParam] WHERE [IMEI1] =") + _T("'") + imei + _T("'");
	try
	{
		m_pRecordSet = m_pConnection->Execute(_bstr_t(strSql), NULL, adCmdText);//直接执行语句
	}
	catch (_com_error &e)
	{
		//不要弹框，工厂没时间点
		//AfxMessageBox(_T("Gps_ManuCpParam无此IMEI，匹配出错"));
		return 2;
	}
	if (m_pRecordSet->adoEOF)
	{		
		return 2;
	}
	else
	{
		CString ret = m_pRecordSet->GetCollect("CPRESULT");
		if ("1" == ret)
		{
			return 1;
		}
		return 0;
	}
	return 2;//上面都没问题就返回2代表成功
}