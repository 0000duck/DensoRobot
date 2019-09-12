#pragma once
#import "msado15.dll"  no_namespace rename("EOF", "adoEOF")
/////////////////////////-------190615-----用于数据库管理的类-------///////////////
/////////////////基本使用方法：连接数据库-发送命令-断开----////////////////////////
class ADOFunction
{
public:
	ADOFunction();
	virtual ~ADOFunction();

	//自定义参数
public:
	_ConnectionPtr m_pConnection;    //连接参数
	_CommandPtr m_pCommand;          //SQL命令参数
	_RecordsetPtr m_pRecordSet;      //记录集参数

	CString sDataSource;  //服务器IP
	CString sPort;        //服务器端口
	CString sUserName;    //用户名
	CString sPassword;    //密码
	CString sSQLName;    //密码


	bool ConnSQL();//连接数据库函数
	bool CloseSQL();//关闭数据库函数
	CString CheckUser(CString username, CString userpswd);//用户名确认，返回空即登录失败
};

