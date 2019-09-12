// CircleButton.cpp : implementation file
//

#include "stdafx.h"
#include "CircleButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCircleButton

CCircleButton::CCircleButton()
{
	
}

CCircleButton::~CCircleButton()
{
}


BEGIN_MESSAGE_MAP(CCircleButton, CNewButton)
//{{AFX_MSG_MAP(CCircleButton)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCircleButton message handlers
void CCircleButton::DrawButton(CDC* pDC)
{
	CBrush Brush;
	Brush.CreateSolidBrush(m_crBk);
	pDC->SelectObject(&Brush);
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	pDC->SelectObject(&pen);
	pDC->Ellipse(0,0,rect.Width(),rect.Height());
}
