#pragma once
#include "afxwin.h"

class CImageAreaEx : public CStatic
{
	DECLARE_DYNAMIC(CImageAreaEx)

public:
	CImageAreaEx();
	virtual ~CImageAreaEx();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void SetWidth(UINT newWidth);
	void SetHeight(UINT newHeight);
	void SetFileName(CString newFileName);

	void CropCapture(const CString& filePath);

	CPoint m_curMousePos;
	CPoint m_mousePos;
	UINT m_picWidth;
	UINT m_picHeight;
	CString m_fileName;
	CImage* m_image;
};

