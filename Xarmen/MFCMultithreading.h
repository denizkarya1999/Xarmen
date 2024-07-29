#pragma once
#include "afxdialogex.h"


// MFCMultithreading dialog

class MFCMultithreading : public CDialogEx
{
	DECLARE_DYNAMIC(MFCMultithreading)

public:
	MFCMultithreading(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MFCMultithreading();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_THREADING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrlStatus;
	void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStartThread();
	afx_msg void OnBnClickedButtonStop();
};
