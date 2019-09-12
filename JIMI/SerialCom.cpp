#include "stdafx.h"
#include "SerialCom.h"
#include <afxpriv.h>

SerialCom::SerialCom()
{
	iByteSize = 8;
	iParity = NOPARITY;
	iStopBits = ONESTOPBIT;

	bHexSend = false;//16���ƣ�Ĭ������Ϊ����Ҫ����Ҫ��ʱ����Ϊtrue
}


SerialCom::~SerialCom()
{
}

HANDLE SerialCom::InitCom(CString comName, int comBaud)
{
	HANDLE hCom;
	hCom = CreateFile(L"\\\\.\\" + comName,//COM��
		GENERIC_READ | GENERIC_WRITE, //�������д
		0, //��ռ��ʽ
		NULL,
		OPEN_EXISTING, //�򿪶����Ǵ���
		0, //ͬ����ʽ
		NULL);
	if (hCom == INVALID_HANDLE_VALUE)
	{
		//SetRicheditText(comName+L"���ڳ�ʼ��ʧ�ܣ�", 1);
		AfxMessageBox(L"���ڳ�ʼ��ʧ�ܣ�");
		return NULL;
	}
	SetupComm(hCom, 100, 100); //���뻺����������������Ĵ�С����100
	COMMTIMEOUTS TimeOuts;
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	//�ڶ�һ�����뻺���������ݺ���������������أ�
	//�������Ƿ������Ҫ����ַ���
	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 1500;
	TimeOuts.WriteTotalTimeoutConstant = 1500;
	SetCommTimeouts(hCom, &TimeOuts); //���ó�ʱ

	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = comBaud; //������Ϊ9600
	dcb.ByteSize = iByteSize; //ÿ���ֽ���8λ
	dcb.Parity = iParity; //����żУ��λ NOPARITY
	dcb.StopBits = iStopBits; //1��ֹͣλONESTOPBIT
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

	//���ڱ���
	DWORD dwBytesWrite;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat, bReadStatus;
	char *buffer;

	ClearCommError(porthandler, &dwErrorFlags, &ComStat);

	if (bHexSend == false)
	{
	//	buffer = cmd.GetBuffer(cmd.GetLength());
		USES_CONVERSION;//cstringתchar*
		buffer = T2A(cmd);
		
		bWriteStat = WriteFile(porthandler, buffer, cmd.GetLength(), &dwBytesWrite, NULL);
	}
	else if (bHexSend == true)
	{
		//��תʮ������
		cmd.Replace(_T(" "), _T(""));
		int len = cmd.GetLength() / 2 - 1;
		BYTE *pBData = new BYTE[len];
		pBData = CStrToByte(len, cmd);

		//����ʮ����������
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
	//���ý���ʱ������
	if (SetCommMask(porthandler, EV_RXCHAR) == 0) 
	{
		//AfxMessageBox(_T("���ý���ʱ���������"));
		AfxMessageBox(_T("�����쳣"));
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
			str.Trim();//����ո��
			str.Replace(_T("\r"), _T(""));//������з��ŵ�
			str.Replace(_T("\n"), _T(""));//������з��ŵ�
		}
		else
		{
			return _T("");
		}
	}
	else
	{
		return _T("");
		OutputDebugString(_T("ReadFile ���ļ�����/r/n"));
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
			Sleep(100);//3s���ӳ�
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
		AfxMessageBox(L"����ѡ�񴮿ںţ�");
	}
}

//CStringתByte
BYTE * SerialCom::CStrToByte(int len, CString str)
{
	BYTE *Buf = new BYTE[len];
	CString StrSub;
	for (int iSrc = 0, iDst = 0; iDst<len; iSrc += 2, iDst++)
	{
		StrSub = str.Mid(iSrc, 2);
		Buf[iDst] = (BYTE)_tcstoul(StrSub, NULL, 16);//16��ʮ�����Ƶ���˼
	}
	return Buf;
}


/*����ͨ�ò���*/
//��ע�����Ѱ���Ѿ�ע�ᴮ�ں�Ȼ��չʾ����
void SerialCom::FindCommPort(CComboBox *pComboBox, CString &ComNo)
{
	//�Ȼ�ȡ��ǰ���ں�
	int cur = 0;
	int nSel;
	BOOL curflag = TRUE;
	nSel = pComboBox->GetCurSel();
	if (nSel >= 0)
	{
		pComboBox->GetLBText(nSel, ComNo);
	}

	//�����һ���б�
	pComboBox->ResetContent();

	HKEY hKey;
#ifdef _DEBUG
	ASSERT(pComboBox != NULL);
	pComboBox->AssertValid();
#endif
	if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey) == ERROR_SUCCESS) // �򿪴���ע���
	{
		int i = 0;
		char portName[256], commName[256];
		DWORD dwLong, dwSize;
		while (1)
		{
			dwLong = dwSize = sizeof(portName);
			if (::RegEnumValue(hKey, i, LPWSTR(portName), &dwLong, NULL, NULL, (PUCHAR)commName, &dwSize) == ERROR_NO_MORE_ITEMS) // ö�ٴ���
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
