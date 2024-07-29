#pragma once
#include "afxdialogex.h"
#include <string>
#include <string>

class CEmployee : public CObject {
public:
    int empID;
    CString empName;
    int age;
    CEmployee(void);
    ~CEmployee(void);
private:

public:
    void Serialize(CArchive& ar);
    DECLARE_SERIAL(CEmployee);
};
