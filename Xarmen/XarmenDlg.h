
// XarmenDlg.h : header file
//

#pragma once


// CXarmenDlg dialog
class CXarmenDlg : public CDialogEx
{
// Construction
public:
	CXarmenDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XARMEN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CToolBar m_wndToolBar;
	BOOL butD;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnFileNew();
	BOOL m_enableDisableCheckAction;
	CEdit m_myEditControl;
	afx_msg void OnBnClickedCheck1();
};
