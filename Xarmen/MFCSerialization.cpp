// MFCSerialization.cpp : implementation file
//

#include "pch.h"
#include "Xarmen.h"
#include "afxdialogex.h"
#include "MFCSerialization.h"
#include "CEmployee.h"


// MFCSerialization dialog

IMPLEMENT_DYNAMIC(MFCSerialization, CDialogEx)

MFCSerialization::MFCSerialization(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SERIALIZATION, pParent)
	, m_id(0)
	, m_name(_T(""))
	, m_age(0)
{

}

MFCSerialization::~MFCSerialization()
{
}

void MFCSerialization::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EMP_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_AGE, m_age);
}


BEGIN_MESSAGE_MAP(MFCSerialization, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &MFCSerialization::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &MFCSerialization::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// MFCSerialization message handlers


void MFCSerialization::OnBnClickedButtonOpen()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CFile file;

	file.Open(L"EmployeeInfo.hse", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	CEmployee employee;

	employee.Serialize(ar);

	m_id = employee.empID;
	m_name = employee.empName;
	m_age = employee.age;

	ar.Close();
	file.Close();

	UpdateData(FALSE);
}


void MFCSerialization::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CEmployee employee;
	CFile file;

	file.Open(L"EmployeeInfo.hse", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);

	employee.empID = m_id;
	employee.empName = m_name;
	employee.age = m_age;

	employee.Serialize(ar);
	ar.Close();
}
