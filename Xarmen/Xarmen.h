
// Xarmen.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CXarmenApp:
// See Xarmen.cpp for the implementation of this class
//

class CXarmenApp : public CWinApp
{
public:
	CXarmenApp();

// Overrides
public:
	virtual BOOL InitInstance();
	HACCEL m_hAccelTable;

// Implementation
	DECLARE_MESSAGE_MAP()
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
};

extern CXarmenApp theApp;
