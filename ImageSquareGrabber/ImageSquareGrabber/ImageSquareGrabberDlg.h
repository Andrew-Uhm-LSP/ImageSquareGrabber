
// ImageSquareGrabberDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ImageAreaEx.h"

#define INIT_SQUARE 80

// CImageSquareGrabberDlg dialog
class CImageSquareGrabberDlg : public CDialogEx
{
// Construction
public:
	CImageSquareGrabberDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGESQUAREGRABBER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
public:
	// CRect* m_selectBox;
	CImage* m_curImage;
	UINT m_width;
	UINT m_height;
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_labelWidth;
	CRichEditCtrl m_labelHeight;
	CRichEditCtrl m_enterWidth;
	CRichEditCtrl m_enterHeight;
	CImageAreaEx m_imageArea;
	//CImageAreaEx m_imageAreaTest;
	CPoint m_mousePos;
	afx_msg void OnStnDblclickImageArea();
	afx_msg void OnBnClickedApplyButton();
};
