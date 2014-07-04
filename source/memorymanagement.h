// includes
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <Windows.h>

// namespaces
using namespace std;

// prototypes
DWORD FindProcessID(const std::wstring&);
DWORD GetModuleBaseAddress(LPCWSTR, LPCWSTR);
//DWORD GetModuleLen(HMODULE);