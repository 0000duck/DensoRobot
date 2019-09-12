#pragma once
class SerialCom
{
public:
	SerialCom();
	~SerialCom();

	CString	sPort;//串口号
	int	iBaud;//波特率
	int	iByteSize;//数据位
	int	iParity;//奇偶校验位
	int	iStopBits;//停止位

	bool bHexSend;//是否用16进制发送
	HANDLE porthandler;
	HANDLE InitCom(CString comName, int comBaud);//初始化串口,常用的开放出去
	int CloseCom();//关闭串口
	bool WriteCommand(CString cmd);//发送串口指令
	CString ReadCommand();//读取串口缓冲区
	CString RunCommand(CString cmd);//发送串口指令,并读取缓冲区

	//额外用于方便处理
	void GetCommPort(CComboBox *pComboBox, CString &ComNo);//获取当前串口号
	void FindCommPort(CComboBox *pComboBox, CString &ComNo);//从注册表中寻找串口号
	BYTE *CStrToByte(int len, CString str);
	//CreateFile //打开
	//CloseHandle //关闭
	//ReadFile  //读取
	//WriteFile  //写入

};

