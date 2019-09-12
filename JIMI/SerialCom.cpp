#include "stdafx.h"
#include "SerialCom.h"
#include <afxpriv.h>

SerialCom::SerialCom()
{
	iByteSize = 8;
	iParity = NOPARITY;
	iStopBits = ONESTOPBIT;

	bHexSend = false;//16进制，默认设置为不需要，需要的时候置为true
}


SerialCom::~SerialCom()
{
}

HANDLE SerialCom::InitCom(CString comName, int comBaud)
{
	HANDLE hCom;
	hCom = CreateFile(L"\\\\.\\" + comName,//COM口
		GENERIC_READ | GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,
		OPEN_EXISTING, //打开而不是创建
		0, //同步方式
		NULL);
	if (hCom == INVALID_HANDLE_VALUE)
	{
		//SetRicheditText(comName+L"串口初始化失败！", 1);
		AfxMessageBox(L"串口初始化失败！");
		return NULL;
	}
	SetupComm(hCom, 100, 100); //输入缓冲区和输出缓冲区的大小都是100
	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	//在读一次输入缓冲区的内容后读操作就立即返回，
	//而不管是否读入了要求的字符。
	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier = 1500;
	TimeOuts.WriteTotalTimeoutConstant = 1500;
	SetCommTimeouts(hCom, &TimeOuts); //设置超时

	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = comBaud; //波特率为9600
	dcb.ByteSize = iByteSize; //每个字节有8位
	dcb.Parity = iParity; //无奇偶校验位 NOPARITY
	dcb.StopBits = iStopBits; //1个停止位ONESTOPBIT
	SetCommState(hCom, &dcb);
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	return hCom;
}

int SerialCom::CloseCom()
{
	return CloseHandle(porthandler);
}

bool SerialCom::WriteCommand(CString cmd)
{
	PurgeComm(porthandler, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_TXABORT);

	//串口变量
	DWORD dwBytesWrite;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat, bReadStatus;
	char *buffer;

	ClearCommError(porthandler, &dwErrorFlags, &ComStat);

	if (bHexSend == false)
	{
	//	buffer = cmd.GetBuffer(cmd.GetLength());
		USES_CONVERSION;//cstring转char*
		buffer = T2A(cmd);
		
		bWriteStat = WriteFile(porthandler, buffer, cmd.GetLength(), &dwBytesWrite, NULL);
	}
	else if (bHexSend == true)
	{
		//先转十六进制
		cmd.Replace(_T(" "), _T(""));
		int len = cmd.GetLength() / 2 - 1;
		BYTE *pBData = new BYTE[len];
		pBData = CStrToByte(len, cmd);

		//发送十六进制数据
		bWriteStat = WriteFile(porthandler, (LPVOID)pBData, len, &dwBytesWrite, NULL);
	}
	Sleep(1);
	return true;
}

CString SerialCom::ReadCommand()
{
	DWORD dwReadSize = 0;
	char *RxBuffer, buf[1024];;
	BOOL bRet;
	CString str, temp;
	str = _T("");
	temp = _T("");
	//设置接收时间掩码
	if (SetCommMask(porthandler, EV_RXCHAR) == 0) 
	{
		//AfxMessageBox(_T("设置接收时间掩码出错"));
		AfxMessageBox(_T("串口异常"));
		return _T("");
	}	
	memset(buf, 0, sizeof(buf));
	RxBuffer = buf;
	bRet = ReadFile(porthandler, RxBuffer, 512, &dwReadSize, NULL);
	if (bRet)
	{
		if (dwReadSize != 0)
		{
			str = RxBuffer;
			str.Trim();//清除空格等
			str.Replace(_T("\r"), _T(""));//清除换行符号等
			str.Replace(_T("\n"), _T(""));//清除换行符号等
		}
		else
		{
			return _T("");
		}
	}
	else
	{
		return _T("");
		OutputDebugString(_T("ReadFile 读文件出错/r/n"));
	}
	PurgeComm(porthandler, PURGE_RXABORT | PURGE_RXCLEAR);
	return str;
}

CString SerialCom::RunCommand(CString cmd)
{
	WriteCommand(cmd);
	CString str = _T("");

	for (int i = 0; i < 30; i++)
	{
		str = ReadCommand();
		if (_T("") == str)
		{
			Sleep(100);//3s的延迟
			continue;
		}
		else
		{
			return str;
		}
	}
	return _T("");
}

void SerialCom::GetCommPort(CComboBox *pComboBox, CString &ComNo)
{
	int nSel;
	nSel = pComboBox->GetCurSel();
	pComboBox->GetLBText(nSel, ComNo);

	if (ComNo == "")
	{
		AfxMessageBox(L"请先选择串口号！");
	}
}

//CString转Byte
BYTE * SerialCom::CStrToByte(int len, CString str)
{
	BYTE *Buf = new BYTE[len];
	CString StrSub;
	for (int iSrc = 0, iDst = 0; iDst<len; iSrc += 2, iDst++)
	{
		StrSub = str.Mid(iSrc, 2);
		Buf[iDst] = (BYTE)_tcstoul(StrSub, NULL, 16);//16是十六进制的意思
	}
	return Buf;
}


/*串口通用操作*/
//从注册表中寻找已经注册串口号然后展示出来
void SerialCom::FindCommPort(CComboBox *pComboBox, CString &ComNo)
{
	//先获取当前串口号
	int cur = 0;
	int nSel;
	BOOL curflag = TRUE;
	nSel = pComboBox->GetCurSel();
	if (nSel >= 0)
	{
		pComboBox->GetLBText(nSel, ComNo);
	}

	//先清空一下列表
	pComboBox->ResetContent();

	HKEY hKey;
#ifdef _DEBUG
	ASSERT(pComboBox != NULL);
	pComboBox->AssertValid();
#endif
	if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey) == ERROR_SUCCESS) // 打开串口注册表
	{
		int i = 0;
		char portName[256], commName[256];
		DWORD dwLong, dwSize;
		while (1)
		{
			dwLong = dwSize = sizeof(portName);
			if (::RegEnumValue(hKey, i, LPWSTR(portName), &dwLong, NULL, NULL, (PUCHAR)commName, &dwSize) == ERROR_NO_MORE_ITEMS) // 枚举串口
			{
				break;
			}
			cur = i;
			pComboBox->AddString(LPWSTR(commName));
			i++;
		}
		pComboBox->SetCurSel(cur);
		RegCloseKey(hKey);
	}
}
