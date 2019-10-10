
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// JIMI.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"
#include "JIMIDlg.h"
#include <afxpriv.h>
#include <afxsock.h>
#include <string.h>
CJIMIDlg* pGlobal = NULL;

//CJIMIDlg* pGlobal = (CJIMIDlg*)AfxGetApp()->GetMainWnd();


char * CstringToChar(CString str)
{
	char * buffer = new char[1024];
	memset(buffer, 0, 1024);

	va_list list;
	va_start(list, str);

	const char* cstr;
	char temp[100];
	::wsprintfA(temp, "%ls", (LPCTSTR)str);
	cstr = temp;
	vsprintf_s(buffer, 1024, cstr, list);
	va_end(list);
	return buffer;
}

void CStringSplit(CString &strSource, CString *strDes, CString strSplitChar)
{
	int d_len = strSplitChar.GetLength();
	int j = 0;
	int n = 0;
	int m_pos;
	int iIndex;
	while (1)
	{
		m_pos = strSource.Find(strSplitChar, j);
		if (m_pos == -1 && j == 0)
		{
			iIndex = -1;
			break;
		}
		if (m_pos == -1 && j != 0)
		{
			strDes[n] = strSource.Mid(j, strSource.GetLength() - j);
			iIndex = n;
			break;
		}
		if (j == 0)
		{
			strDes[n] = strSource.Mid(0, m_pos);
			j = m_pos + d_len;
		}
		else
		{
			strDes[n] = strSource.Mid(j, m_pos - j);
			j = m_pos + d_len;
		}
		n++;
	}
}

string toString(CString cs) 
{
#ifdef _UNICODE

	//�����unicode����
	USES_CONVERSION;
	std::string str(W2A(cs));
	return str;
#else
	//����Ƕ��ֽڹ��� 
	std::string str(cs.GetBuffer());
	cs.ReleaseBuffer();
	return str;

#endif // _UNICODE 
}

CString toCString(string str) 
{
#ifdef _UNICODE
	//�����unicode����
	USES_CONVERSION; CString s(str.c_str());
	CString ans(str.c_str());
	return ans;
#else
	//����Ƕ��ֽڹ��� 
	//string ת CString
	CString ans;
	ans.Format("%s", str.c_str());
	return ans;
#endif // _UNICODE  
}