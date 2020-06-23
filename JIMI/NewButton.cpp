// NewButton.cpp : implementation file
//

#include "stdafx.h"
#include "NewButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewButton

CNewButton::CNewButton()
{
	nStyle = 0;
	bInRect = FALSE;
	m_BtText = _T("");
	m_crText = RGB(0,0,0);
	m_crBk   = RGB(255,255,255);
	p_Font = NULL;
	Status = 5;

}

CNewButton::~CNewButton()
{
}


BEGIN_MESSAGE_MAP(CNewButton, CButton)
	//{{AFX_MSG_MAP(CNewButton)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewButton message handlers

void CNewButton::SetTextColor(COLORREF rgb)
{
	m_crText = rgb;
	Invalidate(TRUE);
}

void CNewButton::SetBkColor(COLORREF rgb)
{
	m_crBk = rgb;
	if(m_brBk.GetSafeHandle())
		m_brBk.DeleteObject();
	m_brBk.CreateSolidBrush(rgb);
	Invalidate(TRUE);

}

void CNewButton::SetFont(int TextSize, TCHAR *TestName)
{
	if (p_Font) delete p_Font;
	p_Font = new CFont;
    p_Font->CreatePointFont(TextSize, TestName);
	CButton::SetFont(p_Font);
	Invalidate(TRUE);
}



void CNewButton::Red()
{
	
	if (Status != 0)
	{
		SetFont(110, _T("黑体"));
		SetTextColor(RGB(20,20,20));
		SetBkColor(RGB(254,67,0));
		Status = 0;
	}	
}

void CNewButton::Gray()
{
	
	if (Status != 0)
	{
		SetFont(110, _T("隶书"));
		SetTextColor(RGB(20,20,20));
		SetBkColor(RGB(53,53,53));
		Status = 0;
	}	
}


void CNewButton::Green()
{
	if (Status != 1)
	{
		SetFont(110, _T("黑体"));
		SetTextColor(RGB(20,20,20));
		SetBkColor(RGB(6,255,67));
		Status = 1;
	}
	
}

void CNewButton::Yellow()
{
	if (Status != 2)
	{
		SetFont(110, _T("隶书"));
		SetTextColor(RGB(20,20,20));
		SetBkColor(RGB(255,255,0));
		Status = 2;
	}
	
}

void CNewButton::Blank()
{
	if (Status != 3)
	{
		SetFont(110, _T("黑体"));
		SetTextColor(RGB(20,20,20));
		SetBkColor(RGB(235,235,235));
		Status = 3;
	}
	
}
void CNewButton::Brown()
{
	if (Status != 4)
	{
		SetFont(130, _T("隶书"));
		SetTextColor(RGB(20,20,20));
		SetBkColor(RGB(90,106,50));
		Status = 4;
	}
	
}




void CNewButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC* pDc = CDC::FromHandle(lpDrawItemStruct->hDC);
	rect =  lpDrawItemStruct->rcItem;
	
	if (m_BtText.IsEmpty())
	{
		GetWindowText(m_BtText);
	}
	
	int nSaveDc = pDc->SaveDC();
	DrawButton(pDc);
	pDc->RestoreDC(nSaveDc);
}

void CNewButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

void CNewButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	nStyle = 1;
	Invalidate();

	CButton::OnLButtonUp(nFlags, point);
}

void CNewButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	nStyle = 2;
	Invalidate();

	CButton::OnLButtonDown(nFlags, point);
}

void CNewButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!bInRect || GetCapture()!=this)
	{
		bInRect = TRUE;
		SetCapture();
		nStyle = 1;
		Invalidate();
	}
	else
	{
		if (!rect.PtInRect(point))
		{
			bInRect = FALSE;
			ReleaseCapture();
			nStyle = 0;
			Invalidate();
		}
	}
	CButton::OnMouseMove(nFlags, point);
}
void CNewButton::DrawButton(CDC* pDC)
{
	if (nStyle == 3) nStyle = 0; 
	if (GetStyle()&WS_DISABLED) nStyle = 3;
	
	COLORREF bColor, fColor;
	switch(nStyle)
		{	
			case 0: bColor = RGB(101,0,0); fColor = m_crText; break;
			case 1: bColor = RGB(101,0,101); fColor = m_crText; break;
			case 2: bColor = RGB(102,102,102); fColor = m_crText; break;
			case 3: bColor = RGB(0,0,0);	   fColor = GetSysColor(COLOR_GRAYTEXT);break;
		}
	CBrush Brush;
	Brush.CreateSolidBrush(m_crBk);
	
	pDC->SelectObject(&Brush);
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, bColor);
	pDC->SelectObject(&pen);
	//pDC->SetBkMode(TRANSPARENT);
/*	pDC->FillRect(&rect, &Brush);*/
// 	rect.left -= 10;
// 	rect.top  -= 10;
// 	rect.right += 10;
// 	rect.bottom += 10;
	
	pDC->RoundRect(&rect, CPoint(10, 10));
	
	if (nStyle!=2)
	{
		CRect rc;
		rc.SetRect(rect.left+3, rect.top+3,rect.right-3, rect.bottom-3);
		pDC->DrawEdge(&rc, BDR_RAISEDOUTER, BF_RECT);
	}

	pDC->SetTextColor(fColor);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(m_BtText, &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_EDITCONTROL);

// 	if (GetFocus()==this)
// 	{
// 		CRect rc;
// 		rc.SetRect(rect.left+5, rect.top+5 ,rect.right-5, rect.bottom-5);
// 		pDC->DrawFocusRect(&rc);
// 	}

}
void CNewButton::GreenOrRed(int iret)
{
	if(iret == 1)
	{
		Green();
	}
	else if (iret == 0)
	{
		Red();
	}
	
}
void CNewButton::VisChangeColor(int iret)
{
	switch (iret)
	{
	case 0:         Blank();      break;
	case 1:         Green();      break;
	case 2:         Red();      break;
	case 3:         Blank();      break;
	default:
		break;
	}

}

void CNewButton::UWChangeColor(int iret)
{
	switch (iret)
	{
	case 0:         Blank();      break;
	case 1:         Green();      break;
	case 2:         Red();        break;
	case 3:         Yellow();      break;
	case 4:         Blank();      break;
	default:
		break;
	}

}
