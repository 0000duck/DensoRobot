#include "stdafx.h"
#include "ADOFunction.h"


ADOFunction::ADOFunction()
{
	sDataSource = (_T("10.10.11.90"));
	sPort = (_T("6033"));
	sUserName = (_T("sa"));
	sPassword = (_T("jiminewpower"));
	sSQLName = (_T("GPSTest"));
}


ADOFunction::~ADOFunction()
{
}

bool ADOFunction::ConnSQL()
{
	CoInitialize(NULL); //初始化COM环境           
	m_pConnection.CreateInstance(_T("ADODB.Connection"));//初始化Connection指针 
	//	GetDBINFO();//获取数据库信息
	CString sConnectStr;//连接字符串
	sConnectStr = _T("Provider=SQLOLEDB.1;Data Source=") + sDataSource + _T(",") + sPort + _T(";Network Library=DBMSSOCN;Initial Catalog=") + sSQLName;
	try
	{
		m_pConnection->Open(_bstr_t(sConnectStr), _bstr_t(sUserName), _bstr_t(sPassword), adConnectUnspecified);
	}
	catch (_com_error &e)
	{
		::MessageBox(NULL, _T("数据库连接错误"), _T("异常信息"), NULL); /*打印出异常原因*/
		return false;
	}
	return true;
}

bool ADOFunction::CloseSQL()
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
	return true;
}

CString ADOFunction::CheckUser(CString username, CString userpswd)
{
	if (!ConnSQL())
	{
		return _T("");

	}
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	CString strSql = _T("SELECT UserDes From Gps_User WHERE UserName = '") + username + _T("' AND UserPwd = '") + userpswd + _T("'");
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