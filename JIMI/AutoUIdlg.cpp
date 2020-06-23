// AutoUIdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JIMI.h"
#include "AutoUIdlg.h"
#include "afxdialogex.h"


// AutoUIdlg 对话框

IMPLEMENT_DYNAMIC(AutoUIdlg, CDialogEx)

AutoUIdlg::AutoUIdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTOUIDLG, pParent)
{

}

AutoUIdlg::~AutoUIdlg()
{
}

void AutoUIdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CST1, m_VCST_1);
	DDX_Control(pDX, IDC_BTN_CST2, m_VCST_2);
	DDX_Control(pDX, IDC_BTN_CST3, m_VCST_3);
	DDX_Control(pDX, IDC_BTN_CST4, m_VCST_4);
	DDX_Control(pDX, IDC_BTN_CST5, m_VCST_5);
	DDX_Control(pDX, IDC_BTN_CST6, m_VCST_6);
	DDX_Control(pDX, IDC_BTN_CST7, m_VCST_7);
	DDX_Control(pDX, IDC_BTN_CST8, m_VCST_8);
	DDX_Control(pDX, IDC_BTN_CST9, m_VCST_9);
	DDX_Control(pDX, IDC_BTN_CST10, m_VCST_10);
	DDX_Control(pDX, IDC_BTN_CST11, m_VCST_11);
	DDX_Control(pDX, IDC_BTN_CST12, m_VCST_12);
	DDX_Control(pDX, IDC_BTN_CST13, m_VCST_13);
	DDX_Control(pDX, IDC_BTN_CST14, m_VCST_14);
	DDX_Control(pDX, IDC_BTN_CST15, m_VCST_15);
	DDX_Control(pDX, IDC_BTN_CST16, m_VCST_16);
	DDX_Control(pDX, IDC_BTN_CST17, m_VCST_17);
	DDX_Control(pDX, IDC_BTN_CST18, m_VCST_18);
	DDX_Control(pDX, IDC_BTN_CST19, m_VCST_19);
	DDX_Control(pDX, IDC_BTN_CST20, m_VCST_20);
	DDX_Control(pDX, IDC_BTN_CST21, m_VCST_21);
	DDX_Control(pDX, IDC_BTN_CST22, m_VCST_22);
	DDX_Control(pDX, IDC_BTN_CST23, m_VCST_23);
	DDX_Control(pDX, IDC_BTN_CST24, m_VCST_24);
	DDX_Control(pDX, IDC_BTN_CST25, m_VCST_25);
	DDX_Control(pDX, IDC_BTN_CST26, m_VCST_26);
	DDX_Control(pDX, IDC_BTN_CST27, m_VCST_27);
	DDX_Control(pDX, IDC_BTN_CST28, m_VCST_28);
	DDX_Control(pDX, IDC_BTN_CST29, m_VCST_29);
	DDX_Control(pDX, IDC_BTN_CST30, m_VCST_30);
	DDX_Control(pDX, IDC_BTN_CST31, m_VCST_31);
	DDX_Control(pDX, IDC_BTN_CST32, m_VCST_32);
	DDX_Control(pDX, IDC_BTN_CST33, m_VCST_33);
	DDX_Control(pDX, IDC_BTN_CST34, m_VCST_34);
	DDX_Control(pDX, IDC_BTN_CST35, m_VCST_35);
	DDX_Control(pDX, IDC_BTN_CST36, m_VCST_36);
	DDX_Control(pDX, IDC_BTN_CST37, m_VCST_37);
	DDX_Control(pDX, IDC_BTN_CST38, m_VCST_38);
	DDX_Control(pDX, IDC_BTN_CST39, m_VCST_39);
	DDX_Control(pDX, IDC_BTN_CST40, m_VCST_40);

	DDX_Control(pDX, IDC_BTN_VisStaue1, m_VStaue_1);
	DDX_Control(pDX, IDC_BTN_VisStaue2, m_VStaue_2);
	DDX_Control(pDX, IDC_BTN_VisStaue3, m_VStaue_3);

	DDX_Control(pDX, IDC_BTN_UWCST1, m_UWCST_1);
	DDX_Control(pDX, IDC_BTN_UWCST2, m_UWCST_2);
	DDX_Control(pDX, IDC_BTN_UWCST3, m_UWCST_3);
	DDX_Control(pDX, IDC_BTN_UWCST4, m_UWCST_4);
	DDX_Control(pDX, IDC_BTN_UWCST5, m_UWCST_5);
	DDX_Control(pDX, IDC_BTN_UWCST6, m_UWCST_6);
	DDX_Control(pDX, IDC_BTN_UWCST7, m_UWCST_7);
	DDX_Control(pDX, IDC_BTN_UWCST8, m_UWCST_8);
	DDX_Control(pDX, IDC_BTN_UWCST9, m_UWCST_9);
	DDX_Control(pDX, IDC_BTN_UWCST10, m_UWCST_10);
	DDX_Control(pDX, IDC_BTN_UWCST11, m_UWCST_11);
	DDX_Control(pDX, IDC_BTN_UWCST12, m_UWCST_12);
	DDX_Control(pDX, IDC_BTN_UWCST13, m_UWCST_13);
	DDX_Control(pDX, IDC_BTN_UWCST14, m_UWCST_14);
	DDX_Control(pDX, IDC_BTN_UWCST15, m_UWCST_15);
	DDX_Control(pDX, IDC_BTN_UWCST16, m_UWCST_16);
	DDX_Control(pDX, IDC_BTN_UWCST17, m_UWCST_17);
	DDX_Control(pDX, IDC_BTN_UWCST18, m_UWCST_18);
	DDX_Control(pDX, IDC_BTN_UWCST19, m_UWCST_19);
	DDX_Control(pDX, IDC_BTN_UWCST20, m_UWCST_20);
	DDX_Control(pDX, IDC_BTN_UWCST21, m_UWCST_21);
	DDX_Control(pDX, IDC_BTN_UWCST22, m_UWCST_22);
	DDX_Control(pDX, IDC_BTN_UWCST23, m_UWCST_23);
	DDX_Control(pDX, IDC_BTN_UWCST24, m_UWCST_24);
	DDX_Control(pDX, IDC_BTN_UWCST25, m_UWCST_25);
	DDX_Control(pDX, IDC_BTN_UWCST26, m_UWCST_26);
	DDX_Control(pDX, IDC_BTN_UWCST27, m_UWCST_27);
	DDX_Control(pDX, IDC_BTN_UWCST28, m_UWCST_28);
	DDX_Control(pDX, IDC_BTN_UWCST29, m_UWCST_29);
	DDX_Control(pDX, IDC_BTN_UWCST30, m_UWCST_30);
	DDX_Control(pDX, IDC_BTN_UWCST31, m_UWCST_31);
	DDX_Control(pDX, IDC_BTN_UWCST32, m_UWCST_32);
	DDX_Control(pDX, IDC_BTN_UWCST33, m_UWCST_33);
	DDX_Control(pDX, IDC_BTN_UWCST34, m_UWCST_34);
	DDX_Control(pDX, IDC_BTN_UWCST35, m_UWCST_35);
	DDX_Control(pDX, IDC_BTN_UWCST36, m_UWCST_36);
	DDX_Control(pDX, IDC_BTN_UWCST37, m_UWCST_37);
	DDX_Control(pDX, IDC_BTN_UWCST38, m_UWCST_38);
	DDX_Control(pDX, IDC_BTN_UWCST39, m_UWCST_39);
	DDX_Control(pDX, IDC_BTN_UWCST40, m_UWCST_40);

	DDX_Control(pDX, IDC_BTN_UWStaue1, m_UWStaue_1);
	DDX_Control(pDX, IDC_BTN_UWStaue2, m_UWStaue_2);
	DDX_Control(pDX, IDC_BTN_UWStaue3, m_UWStaue_3);
	DDX_Control(pDX, IDC_BTN_UWStaue4, m_UWStaue_4);
}


BEGIN_MESSAGE_MAP(AutoUIdlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// AutoUIdlg 消息处理程序


BOOL AutoUIdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//UpdataVisBTNstatue();
	m_VStaue_1.VisChangeColor(Vis_True);
	m_VStaue_2.VisChangeColor(Vis_False);
	m_VStaue_3.VisChangeColor(Vis_Null);
	m_UWStaue_1.UWChangeColor(UW_True);
	m_UWStaue_2.UWChangeColor(UW_False);
	m_UWStaue_3.UWChangeColor(UW_Error);
	m_UWStaue_4.UWChangeColor(UW_Null);

	SetTimer(1,500,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void AutoUIdlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CDC *pDC = GetDlgItem(IDC_STATIC_RBTPIC)->GetDC();
	//CDC dc;
	//dc.CreateCompatibleDC(pDC);//创建兼容DC
	//BITMAP bs;//BITMAP结构变量
	//CBitmap *m_pBmp[6];//位图指针数组
	//
	//m_pBmp[0] = new CBitmap;
	//m_pBmp[0]->LoadBitmap(IDB_BITMAP_RBT_L);
	//m_pBmp[1] = new CBitmap;
	//m_pBmp[1]->LoadBitmap(IDB_BITMAP_RBT_R);

	//m_pBmp[0]->GetBitmap(&bs);
	CString str;
	if (nIDEvent == 1)
	{
		str.Format(_T("%d"), pGlobal->iProcessTimes);
		SetDlgItemText(IDC_EDIT_LoopTimes, str);
		switch (pGlobal->iRbtStatue)
		{
		case RbtReady:
			//dc.SelectObject(m_pBmp[0]);//加载位图
	       // pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue,_T("准备好"));
			break;
		case RbtMarkGet:
			//dc.SelectObject(m_pBmp[0]);//加载位图
			//pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("取料定位中"));
			break;
		case RbtMarkPut:
			//dc.SelectObject(m_pBmp[1]);//加载位图
			//pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("放料定位中"));
			break;
		case RbtGet:
			//dc.SelectObject(m_pBmp[0]);//加载位图
			//pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("取料流程"));
			break;
		case RbtPut:
			//dc.SelectObject(m_pBmp[1]);//加载位图
			//pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//显示位图
			SetDlgItemText(IDC_STATIC_RbtStatue, _T("放料流程"));
			break;
		default:
			break;
		}
		//pDC->DeleteDC();
		//dc.DeleteDC();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void AutoUIdlg::UpdataVisBTNstatue()
{
	try
	{
		int ret[40];
		for (int i = 0; i < 40; i++)
		{
			ret[i] = pGlobal->Visiondlg.iVisGetResult[i];//1、有料可夹；2、有料不可夹；3、无料；
		}
		m_VCST_1.VisChangeColor(ret[0]);
		m_VCST_2.VisChangeColor(ret[1]);
		m_VCST_3.VisChangeColor(ret[2]);
		m_VCST_4.VisChangeColor(ret[3]);
		m_VCST_5.VisChangeColor(ret[4]);
		m_VCST_6.VisChangeColor(ret[5]);
		m_VCST_7.VisChangeColor(ret[6]);
		m_VCST_8.VisChangeColor(ret[7]);
		m_VCST_9.VisChangeColor(ret[8]);
		m_VCST_10.VisChangeColor(ret[9]);
		m_VCST_11.VisChangeColor(ret[10]);
		m_VCST_12.VisChangeColor(ret[11]);
		m_VCST_13.VisChangeColor(ret[12]);
		m_VCST_14.VisChangeColor(ret[13]);
		m_VCST_15.VisChangeColor(ret[14]);
		m_VCST_16.VisChangeColor(ret[15]);
		m_VCST_17.VisChangeColor(ret[16]);
		m_VCST_18.VisChangeColor(ret[17]);
		m_VCST_19.VisChangeColor(ret[18]);
		m_VCST_20.VisChangeColor(ret[19]);
		m_VCST_21.VisChangeColor(ret[20]);
		m_VCST_22.VisChangeColor(ret[21]);
		m_VCST_23.VisChangeColor(ret[22]);
		m_VCST_24.VisChangeColor(ret[23]);
		m_VCST_25.VisChangeColor(ret[24]);
		m_VCST_26.VisChangeColor(ret[25]);
		m_VCST_27.VisChangeColor(ret[26]);
		m_VCST_28.VisChangeColor(ret[27]);
		m_VCST_29.VisChangeColor(ret[28]);
		m_VCST_30.VisChangeColor(ret[29]);
		m_VCST_31.VisChangeColor(ret[30]);
		m_VCST_32.VisChangeColor(ret[31]);
		m_VCST_33.VisChangeColor(ret[32]);
		m_VCST_34.VisChangeColor(ret[33]);
		m_VCST_35.VisChangeColor(ret[34]);
		m_VCST_36.VisChangeColor(ret[35]);
		m_VCST_37.VisChangeColor(ret[36]);
		m_VCST_38.VisChangeColor(ret[37]);
		m_VCST_39.VisChangeColor(ret[38]);
		m_VCST_40.VisChangeColor(ret[39]);
	}
	catch (const std::exception&)
	{

	}
	
}

void AutoUIdlg::UpdataUWBTNstatue()
{
	try
	{
		int ret[40];
		for (int i = 0; i < 40; i++)
		{
			ret[i] = pGlobal->iUWetResult[i];//1、扫码成功；2、扫码失败、3、刀卡不可夹；4、无料；
		}
		m_UWCST_1.UWChangeColor(ret[0]);
		m_UWCST_2.UWChangeColor(ret[1]);
		m_UWCST_3.UWChangeColor(ret[2]);
		m_UWCST_4.UWChangeColor(ret[3]);
		m_UWCST_5.UWChangeColor(ret[4]);
		m_UWCST_6.UWChangeColor(ret[5]);
		m_UWCST_7.UWChangeColor(ret[6]);
		m_UWCST_8.UWChangeColor(ret[7]);
		m_UWCST_9.UWChangeColor(ret[8]);
		m_UWCST_10.UWChangeColor(ret[9]);
		m_UWCST_11.UWChangeColor(ret[10]);
		m_UWCST_12.UWChangeColor(ret[11]);
		m_UWCST_13.UWChangeColor(ret[12]);
		m_UWCST_14.UWChangeColor(ret[13]);
		m_UWCST_15.UWChangeColor(ret[14]);
		m_UWCST_16.UWChangeColor(ret[15]);
		m_UWCST_17.UWChangeColor(ret[16]);
		m_UWCST_18.UWChangeColor(ret[17]);
		m_UWCST_19.UWChangeColor(ret[18]);
		m_UWCST_20.UWChangeColor(ret[19]);
		m_UWCST_21.UWChangeColor(ret[20]);
		m_UWCST_22.UWChangeColor(ret[21]);
		m_UWCST_23.UWChangeColor(ret[22]);
		m_UWCST_24.UWChangeColor(ret[23]);
		m_UWCST_25.UWChangeColor(ret[24]);
		m_UWCST_26.UWChangeColor(ret[25]);
		m_UWCST_27.UWChangeColor(ret[26]);
		m_UWCST_28.UWChangeColor(ret[27]);
		m_UWCST_29.UWChangeColor(ret[28]);
		m_UWCST_30.UWChangeColor(ret[29]);
		m_UWCST_31.UWChangeColor(ret[30]);
		m_UWCST_32.UWChangeColor(ret[31]);
		m_UWCST_33.UWChangeColor(ret[32]);
		m_UWCST_34.UWChangeColor(ret[33]);
		m_UWCST_35.UWChangeColor(ret[34]);
		m_UWCST_36.UWChangeColor(ret[35]);
		m_UWCST_37.UWChangeColor(ret[36]);
		m_UWCST_38.UWChangeColor(ret[37]);
		m_UWCST_39.UWChangeColor(ret[38]);
		m_UWCST_40.UWChangeColor(ret[39]);

	}
	catch (const std::exception&)
	{

	}
}