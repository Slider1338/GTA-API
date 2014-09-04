/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-05-09
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 *
 * this class is the memory management class
 */

#pragma once

#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <Windows.h>
#include <TlHelp32.h>
//#include "RemoteFunctionCaller.h"

#define NO_OBJECT 0

class Memory {
public:
	// variables
	DWORD processID = 0;
	DWORD sampDLL = 0;
	HANDLE processHandle = 0;
	int CheckHandlesErrorCode = 0;

	// prototypes
	DWORD GetGTAProcessID();
	DWORD GetSAMPBaseAddress();
	DWORD GetSAMPModuleLength();
	int CheckHandles();
	int Read(LPVOID, LPVOID, DWORD);
	int Write(LPVOID, LPVOID, DWORD);
	bool DataCompare(const BYTE* OpCodes, const BYTE* Mask, const char* StrMask);
	DWORD FindPattern(DWORD StartAddress, DWORD CodeLen, BYTE* Mask, char* StrMask, unsigned short ignore);
};