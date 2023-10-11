#include "stdafx.h"
#include "ImageSquareGrabber.h"
#include "ImageSquareGrabberDlg.h"
#include "afxdialogex.h"
#include "ImageAreaEx.h"

//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>

using namespace Gdiplus;

IMPLEMENT_DYNAMIC(CImageAreaEx, CStatic)

CImageAreaEx::CImageAreaEx()
{
	m_picWidth = INIT_SQUARE;
	m_picHeight = INIT_SQUARE;
	m_fileName = _T("D:\\CroppedImages\\emptyCrop");
}


CImageAreaEx::~CImageAreaEx()
{
}

BEGIN_MESSAGE_MAP(CImageAreaEx, CStatic)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void CImageAreaEx::OnPaint() 
{
	CPaintDC dc(this);

	// draw 4 lines
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));

	CPen* pOldPen = dc.SelectObject(&pen);

	// left
	dc.MoveTo(m_mousePos.x - m_picWidth / 2, m_mousePos.y - m_picHeight / 2);
	dc.LineTo(m_mousePos.x - m_picWidth / 2, m_mousePos.y + m_picHeight / 2);

	// top
	dc.MoveTo(m_mousePos.x - m_picWidth / 2, m_mousePos.y + m_picHeight / 2);
	dc.LineTo(m_mousePos.x + m_picWidth / 2, m_mousePos.y + m_picHeight / 2);

	// right
	dc.MoveTo(m_mousePos.x + m_picWidth / 2, m_mousePos.y - m_picHeight / 2);
	dc.LineTo(m_mousePos.x + m_picWidth / 2, m_mousePos.y + m_picHeight / 2);

	// bottom
	dc.MoveTo(m_mousePos.x - m_picWidth / 2, m_mousePos.y - m_picHeight / 2);
	dc.LineTo(m_mousePos.x + m_picWidth / 2, m_mousePos.y - m_picHeight / 2);

	dc.SelectObject(pOldPen);

	CStatic::OnPaint();
}

void CImageAreaEx::OnMouseMove(UINT nFlags, CPoint point)
{
	// Handle the mouse move event here
	// You can access the mouse cursor position using the 'point' parameter
	// TRACE(_T("Debug Message: %d, %d\n"), point.x, point.y);
	// Call the base class implementation to ensure proper message handling
	//TRACE(_T("mouse moved in imagearea"));
	SetFocus();

	m_curMousePos = point;
	
	CStatic::OnMouseMove(nFlags, point);
}

void CImageAreaEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_SPACE)
	{
		TRACE(_T("space detected"));
		CropCapture(m_fileName);
	}
	else if (nChar == VK_SHIFT)
	{
		m_mousePos = m_curMousePos;
		Invalidate();
		GetParent()->Invalidate();
	}

	CStatic::OnKeyDown(nChar, nRepCnt, nFlags); 
}

void CImageAreaEx::SetWidth(UINT newWidth) {
	m_picWidth = newWidth;
}

void CImageAreaEx::SetHeight(UINT newHeight) {
	m_picHeight = newHeight;
}

void CImageAreaEx::SetFileName(CString newFileName) {
	m_fileName = newFileName;
}

// helper function
CString GetNewFilePath(CString inputFilepath, CString outputDirectory) {
	int lastBackslashPos = inputFilepath.ReverseFind('\\');
	CString fileName = inputFilepath.Mid(lastBackslashPos + 1);
	CTime currentTime = CTime::GetCurrentTime();
	return outputDirectory + _T("\\") + currentTime.Format(_T("%Y-%m-%d %H-%M-%S ")) + fileName;
}

void CImageAreaEx::CropCapture(const CString& filePath) {
	int bitDepth = m_image->GetBPP();
	TRACE(_T("Bit Depth: %d\n"), bitDepth);	// need to keep it 8

	CDC memDC;
	memDC.CreateCompatibleDC(nullptr);
	CRect rectToCapture = CRect(m_mousePos.x - m_picWidth / 2 + 1, m_mousePos.y - m_picHeight / 2 + 1, m_mousePos.x + m_picWidth / 2 - 1, m_mousePos.y + m_picHeight / 2 - 1);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(GetDC(), rectToCapture.Width(), rectToCapture.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.BitBlt(0, 0, rectToCapture.Width(), rectToCapture.Height(), GetDC(), rectToCapture.left, rectToCapture.top, SRCCOPY);

	CImage image;
	image.Attach(bitmap);
	image.Save(GetNewFilePath(filePath, _T("D:\\CroppedImages")), Gdiplus::ImageFormatJPEG); // save as PNG

	memDC.SelectObject(pOldBitmap);
}
