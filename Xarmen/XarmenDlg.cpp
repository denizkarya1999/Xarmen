
// XarmenDlg.cpp : implementation file
//


#include "pch.h"
#include "framework.h"
#include "Xarmen.h"
#include "XarmenDlg.h"
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


// CXarmenDlg dialog



CXarmenDlg::CXarmenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XARMEN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MYICON);
}

void CXarmenDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDIT1, m_myEditControl);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CXarmenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_NEW32775, &CXarmenDlg::OnFileNew)
	ON_BN_CLICKED(IDC_CHECK1, &CXarmenDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK1, &CXarmenDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CXarmenDlg message handlers

BOOL CXarmenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog. The framework does this automatically
	// // when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);       // Set big icon
	SetIcon(m_hIcon, FALSE);      // Set small icon

	if (!m_wndToolBar.Create(this)
		|| !m_wndToolBar.LoadToolBar(IDR_TOOLBAR1)){
		//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
		// WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS |
		// CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		// !m_wndToolBar.LoadToolBar(IDR_TOOLBAR1)) {
		TRACE0("Failed to Create Dialog Toolbar\n");
		EndDialog(IDCANCEL);
	}
	m_enableDisableCheckAction = true;

	UpdateData(TRUE);
	if (m_enableDisableCheckAction) {
		m_myEditControl.EnableWindow(TRUE);
		m_enableDisableCheckAction = false;
	}
	else if (!m_enableDisableCheckAction) {
		m_myEditControl.EnableWindow(FALSE);
		m_enableDisableCheckAction = true;
	}

	butD = TRUE;
	CRect rcClientOld; // Old Client Rect
	CRect rcClientNew; // New Client Rect with Tollbar Added

	// Retrive the Old Client WindowSize
	  // Called to reposition and resize control bars in the client area of a window
	  // The reposQuery FLAG does not really traw the Toolbar. It only does the calculations.
	  // And puts the new ClientRect values in rcClientNew so we can do the rest of the Math.

	GetClientRect(rcClientOld);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNew);
	// All of the Child Windows (Controls) now need to be moved so the Tollbar does not cover them up.
	// Offest to move all child controls after adding Tollbar 
	CPoint ptOffset(rcClientNew.left - rcClientOld.left, rcClientNew.top - rcClientOld.top);

	CRect rcChild;
	CWnd* pwndChild = GetWindow(GW_CHILD); //Handle to the Dialog Controls

	while (pwndChild){ // Cycle through all child controls {
		pwndChild->GetWindowRect(rcChild); // Get the child control RECT
	ScreenToClient(rcChild);

	// Changes the Child Rect by the values of the claculated offset
	rcChild.OffsetRect(ptOffset);
	pwndChild->MoveWindow(rcChild, FALSE); // Move the Child Control
	pwndChild = pwndChild->GetNextWindow();
	}

	CRect rcWindow;

	// Get the RECT of the Dialog
	GetWindowRect(rcWindow);
	
	// Increase width to new Client Width
	rcWindow.right += rcClientOld.Width() - rcClientNew.Width();

	// Increase height to new Client Height
	rcWindow.bottom += rcClientOld.Height() - rcClientNew.Height();
	
	// Redraw Window
	MoveWindow(rcWindow, FALSE);
	
	// Now we REALLY Redraw the Toolbar
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	
	// TODO: Add extra initialization here
	return TRUE; // return TRUE unless you set the focus to a control

}

void CXarmenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CXarmenDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXarmenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CXarmenDlg::OnFileNew()
{
	// TODO: Add your command handler code here
	MessageBox(L"File > New menu option");
}


void CXarmenDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_enableDisableCheckAction) {
		m_myEditControl.EnableWindow(TRUE);
		m_enableDisableCheckAction = false;
	}
	else if (!m_enableDisableCheckAction) {
		m_myEditControl.EnableWindow(FALSE);
		m_enableDisableCheckAction = true;
	}
}
