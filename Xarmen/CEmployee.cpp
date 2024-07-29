#include "pch.h"
#include "CEmployee.h"

IMPLEMENT_SERIAL(CEmployee, CObject, 0)
CEmployee::CEmployee(void) {

}

CEmployee::~CEmployee(void) {

}

void CEmployee::Serialize(CArchive& ar) {
    CObject::Serialize(ar);

    if (ar.IsStoring())
        ar << empID << empName << age;
    else
        ar >> empID >> empName >> age;
}