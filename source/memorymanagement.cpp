// includes
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include "memorymanagement.h"

/**
 * FindProcessId
 * 
 * @params		processName			string
 */
DWORD FindProcessID(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if ( processesSnapshot == INVALID_HANDLE_VALUE )
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if ( !processName.compare(processInfo.szExeFile) )
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while ( Process32Next(processesSnapshot, &processInfo) )
	{
		if ( !processName.compare(processInfo.szExeFile) )
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}
	
	CloseHandle(processesSnapshot);
	return 0;
}

/**
 * GetModuleBaseAddress
 *
 * @params			szProcessName			LPCWSTR
 * @params			szModuleName			LPCWSTR
 */
DWORD GetModuleBaseAddress(LPCWSTR szProcessName, LPCWSTR szModuleName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
 
	if(hSnap == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if(Process32First(hSnap, &pe32) == 0)
	{
		CloseHandle(hSnap);
		return 0;
	}
 
	do 
	{
		if(lstrcmp(pe32.szExeFile, szProcessName)== 0)
		{
			int PID;
			PID = pe32.th32ProcessID;
 
			HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
			MODULEENTRY32 xModule;
 
			if (hSnap == INVALID_HANDLE_VALUE)
			{
				return 0;
			}
			xModule.dwSize = sizeof(MODULEENTRY32);
			if (Module32First(hSnap, &xModule) == 0)
			{
				CloseHandle(hSnap);
				return 0;
			} 
 
			do 
			{
				if (lstrcmp(xModule.szModule, szModuleName) == 0)
				{
					CloseHandle(hSnap);
					return (DWORD)xModule.modBaseAddr;
				}
			} 
			while (Module32Next(hSnap, &xModule));
			CloseHandle(hSnap);
			return 0;
		}
	} 
	while (Process32Next(hSnap, &pe32));
	CloseHandle(hSnap);
	return 0;
}

/**
 * GetModuleLen
 *
 * @params			hMod			HMODULE
 */
/*
DWORD GetModuleLen(HMODULE hMod)
{
	MODULEINFO info;
    GetModuleInformation(GetCurrentProcess(), hMod, &info, sizeof(info));
    return info.SizeOfImage;
}
*/