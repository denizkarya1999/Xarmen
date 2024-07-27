#pragma once
#include "afxdialogex.h"


// FileProcessor dialog

class FileProcessor : public CDialogEx
{
	DECLARE_DYNAMIC(FileProcessor)

public:
	FileProcessor(CWnd* pParent = nullptr);   // standard constructor
	virtual ~FileProcessor();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_PROCESSING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenButton();
	afx_msg void OnBnClickedSaveButton();
	CEdit m_editCtrl;
	CString m_strEdit;
	afx_msg void OnBnClickedNewButton();
};
