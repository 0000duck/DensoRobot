
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


//string���͵�utf-8�ַ���תΪCString���͵�unicode�ַ���
CString ConvertUTF8ToCString(std::string utf8str)
{
	/* Ԥת�����õ�����ռ�Ĵ�С */
	int nLen = ::MultiByteToWideChar(CP_UTF8, NULL,
		utf8str.data(), utf8str.size(), NULL, 0);
	/* ת��ΪUnicode */
	std::wstring wbuffer;
	wbuffer.resize(nLen);
	::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
		(LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
	return(CString(wbuffer.data(), wbuffer.length()));
#else
	/*
	* ת��ΪANSI
	* �õ�ת���󳤶�
	*/
	nLen = WideCharToMultiByte(CP_ACP, 0,
		wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

	std::string ansistr;
	ansistr.resize(nLen);

	/* ��unicodeת��ansi */
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
		(LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
	return(CString(ansistr.data(), ansistr.length()));
#endif
}

//CString���͵�unicode�ַ���תΪstring���͵�utf-8�ַ���
string _UnicodeToUtf8(CString Unicodestr)
{
	wchar_t* unicode = Unicodestr.AllocSysString();
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
	string result = szUtf8;
	free(szUtf8);
	return result;
}

//�ж�ɨ��������Ƿ�Ϊ����
BOOL IsNumber(const CString& strTest)
{
	CString str = strTest;
	// ������Ҫ�������Ƿ�Ҫȥ���ִ����˿ո�TAB���з�
	str.TrimLeft();
	str.TrimRight();

	if (str.IsEmpty())
		return FALSE;

	str.TrimLeft(L"0123456789.-");
	str.TrimRight(L"0123456789.-");
	// ���ȥ�����֣��ִ�Ϊ�գ�˵���ִ���ȫ��������
	// ����������һ���ַ�Ϊ0��ǰ���ټ�һ���ж�if(str.GetAt(0) != '0') return FALSE;
	//if ((str.GetAt(0) < '0'||str.GetAt(0)>'9')&& str!="") 
	//return FALSE;
	if (str.IsEmpty())
		return TRUE;

	return FALSE;
}

