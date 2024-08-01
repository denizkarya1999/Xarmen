
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
public:
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
	, m_strDrives(_T(""))
	, m_strText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MYICON);
}

void CXarmenDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDIT1, m_myEditControl);
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progBarCtrl);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_strDrives);
	DDX_Text(pDX, IDC_STATIC_TEXT_TWO, m_strText);
}

BEGIN_MESSAGE_MAP(CXarmenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_NEW32775, &CXarmenDlg::OnFileNew)
	ON_BN_CLICKED(IDC_CHECK1, &CXarmenDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON3, &CXarmenDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CXarmenDlg::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, &CXarmenDlg::OnBnClickedButtonMove)
	ON_BN_CLICKED(IDC_BUTTON2, &CXarmenDlg::OnBnClickedButtonDelete)
	ON_COMMAND(ID_FILE_OPEN32776, &CXarmenDlg::OnFileOpen32776)
END_MESSAGE_MAP()


// CXarmenDlg message handlers

BOOL CXarmenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog. The framework does this automatically
	// // when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);       // Set big icon
	SetIcon(m_hIcon, FALSE);      // Set small icon


	m_progBarCtrl.SetScrollRange(0, 100, TRUE);
	m_progBarCtrl.SetPos(53);

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
	CList<CString, CString>m_list;

	//Add items to the list
	m_list.AddTail(_T("Deniz"));
	m_list.AddTail(_T("Jason"));
	m_list.AddTail(_T("Meng"));

	POSITION position = m_list.Find(_T("Jason"));
	m_list.InsertAfter(position, _T("Shin"));
	m_list.InsertAfter(position, _T("Oguzhan"));
	m_list.InsertAfter(position, _T("Berk"));

	position = m_list.Find(_T("Shin"));
	m_list.SetAt(position, _T("Florian"));

	position = m_list.Find(_T("Florian"));
	m_list.RemoveAt(position);

	//iterate the list
	POSITION pos = m_list.GetHeadPosition();
	while (pos) {
		CString nData = m_list.GetNext(pos);
		CString strVal;
		strVal.Format(L"%s\n", nData);
		m_strText.Append(strVal);
	}
	UpdateData(FALSE);
	
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



void CXarmenDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	m_strDrives.Format(_T("%lu"), GetLogicalDrives());

	GetDlgItem(IDC_STATIC_TEXT)->SetWindowTextW(m_strDrives);
}



void CXarmenDlg::OnBnClickedButtonCreate()
{
	// TODO: Add your control notification handler code here
	SECURITY_ATTRIBUTES saPermissions;

	saPermissions.nLength = sizeof(SECURITY_ATTRIBUTES);
	saPermissions.lpSecurityDescriptor = NULL;
	saPermissions.bInheritHandle = TRUE;

	CreateDirectory(L"C:\\Dir1", NULL);

	if (CreateDirectory(L"C:\\", &saPermissions) == TRUE)
		AfxMessageBox(L"The directory was created.");
}

void CXarmenDlg::OnBnClickedButtonMove()
{
	// TODO: Add your control notification handler code here
	SECURITY_ATTRIBUTES saPermissions;

	saPermissions.nLength = sizeof(SECURITY_ATTRIBUTES);
	saPermissions.lpSecurityDescriptor = NULL;
	saPermissions.bInheritHandle = TRUE;

	CreateDirectory(L"C:\\TestDirectory", NULL);

	if (MoveFile(L"C:\\Dir1", L"C:\\TestDirectory\\Dir1") == TRUE)
		AfxMessageBox(L"The directory has been moved");
}


void CXarmenDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	if (RemoveDirectory(L"C:\\Dir1") == TRUE)
		AfxMessageBox(L"The directory has been deleted");
}



void CXarmenDlg::OnFileOpen32776()
{
	// TODO: Add your command handler code here
	MessageBox(L"This opens a new file");
}
