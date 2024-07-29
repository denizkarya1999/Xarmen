// MFCMultithreading.cpp : implementation file
//

#include "pch.h"
#include "Xarmen.h"
#include "afxdialogex.h"
#include "MFCMultithreading.h"


// MFCMultithreading dialog

int currValue;
int maxValue;
BOOL stopNow;

IMPLEMENT_DYNAMIC(MFCMultithreading, CDialogEx)

MFCMultithreading::MFCMultithreading(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_THREADING, pParent)
{

}

MFCMultithreading::~MFCMultithreading()
{
}

void MFCMultithreading::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT_STATUS, m_ctrlStatus);
}



BEGIN_MESSAGE_MAP(MFCMultithreading, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_START_THREAD, &MFCMultithreading::OnBnClickedButtonStartThread)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP_THREAD, &MFCMultithreading::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// MFCMultithreading message handlers
UINT SampleAppThreadProc(LPVOID Param) {
	while (!stopNow && (currValue < maxValue)) {
		currValue++;
		// Do some work here
		Sleep(50);   
	}

	return TRUE;
}

void MFCMultithreading::OnBnClickedButtonStartThread()
{
	// TODO: Add your control notification handler code here
	currValue = 0;
	maxValue = 500;
	stopNow = 0;
	m_ctrlStatus.SetWindowText(L"Starting...");
	SetTimer(1234, 111, 0); // 1 time per second

	AfxBeginThread(SampleAppThreadProc, 0); // <<== START THE THREAD
}

void MFCMultithreading::OnTimer(UINT_PTR nIDEvent) {
	// TODO: Add your message handler code here and/or call default
	CString sStatusMsg;
	sStatusMsg.Format(L"Running: %d", currValue);
	m_ctrlStatus.SetWindowText(sStatusMsg);

	CDialogEx::OnTimer(nIDEvent);
}


void MFCMultithreading::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	stopNow = TRUE;
	KillTimer(1234);
	m_ctrlStatus.SetWindowText(L"Stopped");
}
