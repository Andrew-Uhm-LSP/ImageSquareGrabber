
// ImageSquareGrabberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageSquareGrabber.h"
#include "ImageSquareGrabberDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageSquareGrabberDlg dialog



CImageSquareGrabberDlg::CImageSquareGrabberDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGESQUAREGRABBER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageSquareGrabberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_WIDTH, m_labelWidth);
	DDX_Control(pDX, IDC_LABEL_HEIGHT, m_labelHeight);
	DDX_Control(pDX, IDC_ENTER_WIDTH, m_enterWidth);
	DDX_Control(pDX, IDC_ENTER_HEIGHT, m_enterHeight);
	DDX_Control(pDX, IDC_IMAGE_AREA, m_imageArea);
}

BEGIN_MESSAGE_MAP(CImageSquareGrabberDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_QUERYDRAGICON()
	ON_STN_DBLCLK(IDC_IMAGE_AREA, &CImageSquareGrabberDlg::OnStnDblclickImageArea)
	ON_BN_CLICKED(IDC_APPLY_BUTTON, &CImageSquareGrabberDlg::OnBnClickedApplyButton)
END_MESSAGE_MAP()


// CImageSquareGrabberDlg message handlers

BOOL CImageSquareGrabberDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Add extra initialization here
	CString widthText;
	widthText.Format(_T("Current Width: %d"), INIT_SQUARE);
	m_labelWidth.SetWindowText(widthText);
	CString heightText;
	heightText.Format(_T("Current Height: %d"), INIT_SQUARE);
	m_labelHeight.SetWindowText(heightText);

	return TRUE;
}

void CImageSquareGrabberDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageSquareGrabberDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		// image repaint
		CStatic* pStatic = (CStatic*)GetDlgItem(IDC_IMAGE_AREA);
		if (pStatic && m_curImage) {
			CDC* pDC = pStatic->GetDC();
			if (pDC && m_curImage->GetWidth() > 0 && m_curImage->GetHeight() > 0)
			{
				CRect rect;
				pStatic->GetClientRect(&rect);

				int srcWidth = m_curImage->GetWidth();
				int srcHeight = m_curImage->GetHeight();
				int destWidth = rect.Width();
				int destHeight = (srcHeight * destWidth) / srcWidth; // Maintain aspect ratio

				m_curImage->StretchBlt(*pDC, 0, 0, destWidth, destHeight, SRCCOPY);
			}
		}

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageSquareGrabberDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageSquareGrabberDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// switch focus here
	//TRACE(_T("mouse moved in parent"));
	SetFocus();
	CDialog::OnMouseMove(nFlags, point);
}

void CImageSquareGrabberDlg::OnStnDblclickImageArea()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("All Files (*.*)|*.*||"));

	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();
		if (m_curImage) {
			m_curImage->Detach();
		}
		else {
			m_curImage = new CImage();
		}

		if (SUCCEEDED(m_curImage->Load(filePath))) {
			m_imageArea.SetFileName(filePath);
			m_imageArea.m_image = m_curImage;
			CStatic* pStatic = (CStatic*)GetDlgItem(IDC_IMAGE_AREA);
			CDC* pDC = pStatic->GetDC();
			if (pDC && m_curImage->GetWidth() > 0 && m_curImage->GetHeight() > 0)
			{
				CRect rect;
				pStatic->GetClientRect(&rect);

				int srcWidth = m_curImage->GetWidth();
				int srcHeight = m_curImage->GetHeight();
				int destWidth = rect.Width();
				int destHeight = (srcHeight * destWidth) / srcWidth; // Maintain aspect ratio

				m_curImage->StretchBlt(*pDC, 0, 0, destWidth, destHeight, SRCCOPY);
				/*int bitDepth = m_curImage->GetBPP();
				TRACE(_T("Bit Depth: %d\n"), bitDepth);*/
			}
		}
	}
}



void CImageSquareGrabberDlg::OnBnClickedApplyButton()
{
	int bitDepth = m_curImage->GetBPP();
	TRACE(_T("Bit Depth: %d\n"), bitDepth);

	CString width;
	CString widthText;
	m_enterWidth.GetWindowText(width);
	if (width.IsEmpty()) {
		m_imageArea.SetWidth(INIT_SQUARE);
		widthText.Format(_T("Current Width: %d"), INIT_SQUARE);
		m_labelWidth.SetWindowText(widthText);
	}
	else {
		UINT val = _ttoi(width);
		m_imageArea.SetWidth(val);
		widthText.Format(_T("Current Width: %d"), val);
		m_labelWidth.SetWindowText(widthText);
	}
		

	CString height;
	CString heightText;
	m_enterHeight.GetWindowText(height);
	if (height.IsEmpty()) {
		m_imageArea.SetHeight(INIT_SQUARE);
		heightText.Format(_T("Current Height: %d"), INIT_SQUARE);
		m_labelHeight.SetWindowText(heightText);
	}
	else {
		UINT val = _ttoi(height);
		m_imageArea.SetHeight(val);
		heightText.Format(_T("Current Height: %d"), val);
		m_labelHeight.SetWindowText(heightText);
	}
}
