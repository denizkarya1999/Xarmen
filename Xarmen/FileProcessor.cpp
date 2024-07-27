// FileProcessor.cpp : implementation file
//

#include "pch.h"
#include "Xarmen.h"
#include "afxdialogex.h"
#include "FileProcessor.h"


// FileProcessor dialog

IMPLEMENT_DYNAMIC(FileProcessor, CDialogEx)

FileProcessor::FileProcessor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILE_PROCESSING_DIALOG, pParent)
	, m_strEdit(_T(""))
{

}

FileProcessor::~FileProcessor()
{
}

void FileProcessor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_READER, m_editCtrl);
	DDX_Text(pDX, IDC_EDIT_READER, m_strEdit);
}


BEGIN_MESSAGE_MAP(FileProcessor, CDialogEx)
	ON_BN_CLICKED(IDC_OPEN_BUTTON1, &FileProcessor::OnBnClickedOpenButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &FileProcessor::OnBnClickedSaveButton)
    ON_BN_CLICKED(IDC_NEW_BUTTON, &FileProcessor::OnBnClickedNewButton)
END_MESSAGE_MAP()


// FileProcessor message handlers


void FileProcessor::OnBnClickedOpenButton()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    CStdioFile file;
    if (!file.Open(L"C:\\Users\\deniz\\NewTextFile.txt", CFile::modeRead | CFile::typeText))
    {
        AfxMessageBox(L"Failed to open file for reading.");
        return;
    }

    CString strLine;
    m_editCtrl.SetWindowTextW(_T("")); // Clear the edit control
    CString fileContent;
    while (file.ReadString(strLine))
    {
        fileContent += strLine;
        fileContent += _T("\r\n"); // Add newline character after each line
    }
    file.Close();

    m_editCtrl.SetWindowTextW(fileContent); // Set the read content to the edit control
    UpdateData(FALSE);
}


void FileProcessor::OnBnClickedSaveButton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_strEdit.GetLength() == 0) {
		AfxMessageBox(L"You must enter the name of the text.");
		return;
	}
	CFile file;

	file.Open(L"C:\\Users\\deniz\\NewTextFile.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	ar << m_strEdit;

	ar.Close();
	file.Close();
}


void FileProcessor::OnBnClickedNewButton()
{
    // Define the path and name of the new text file
    CString strFilePath = _T("C:\\Users\\deniz\\NewTextFile.txt");

    // Open the file for writing (will create if it does not exist)
    CFile file;
    if (!file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite))
    {
        AfxMessageBox(_T("Failed to create file."));
        return;
    }

    // Write some content to the file
    CString strContent = _T("This is a newly created text file.");
    file.Write((LPCTSTR)strContent, strContent.GetLength() * sizeof(TCHAR));

    // Close the file
    file.Close();

    // Update the static text control to indicate the file has been created
    AfxMessageBox(_T("New text file created."));
}
