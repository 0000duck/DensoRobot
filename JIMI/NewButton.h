#if !defined(AFX_NEWBUTTON_H__DCB615AB_3299_4298_BBD5_5D45EEC0CE94__INCLUDED_)
#define AFX_NEWBUTTON_H__DCB615AB_3299_4298_BBD5_5D45EEC0CE94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewButton window

class CNewButton : public CButton
{
	// Construction
	
public:
	CNewButton();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewButton)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	void Blank();
	void Yellow();
	void Green();
	void Red();
	void Brown();
	void Gray();
	void GreenOrRed(int iret);
	void ChangeColor(int ColorNo);
	void SetFont(int TextSize, TCHAR* TestName);
	void SetBkColor(COLORREF rgb);
	void SetTextColor(COLORREF rgb);
	virtual ~CNewButton();
	virtual void DrawButton(CDC* pDC);
	// Generated message map functions
public:
	int Status;
	
protected:
	CFont* p_Font;
	CBrush m_brBk;
	COLORREF m_crBk;
	COLORREF m_crText;
	CString m_BtText;
	int nStyle;
	CRect rect;
	BOOL bInRect;
	//{{AFX_MSG(CNewButton)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWBUTTON_H__DCB615AB_3299_4298_BBD5_5D45EEC0CE94__INCLUDED_)
