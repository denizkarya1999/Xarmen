#pragma once
#include "afxdialogex.h"
#include <string>
#include <string>


// MFCSerialization dialog

class MFCSerialization : public CDialogEx
{
	DECLARE_DYNAMIC(MFCSerialization)

public:
	MFCSerialization(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MFCSerialization();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERIALIZATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_id;
	CString m_name;
	int m_age;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSave();
};
