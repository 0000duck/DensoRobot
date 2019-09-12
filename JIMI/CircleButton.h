#if !defined(AFX_CIRCLEBUTTON_H__76C4FD0F_423D_40EC_A605_3807B51446E8__INCLUDED_)
#define AFX_CIRCLEBUTTON_H__76C4FD0F_423D_40EC_A605_3807B51446E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CircleButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCircleButton window
#include "NewButton.h"
class CCircleButton : public CNewButton
{
	// Construction
public:
	CCircleButton();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCircleButton)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CCircleButton();
	virtual void DrawButton(CDC* pDC);
	// Generated message map functions
	
protected:
	//{{AFX_MSG(CCircleButton)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CIRCLEBUTTON_H__76C4FD0F_423D_40EC_A605_3807B51446E8__INCLUDED_)
