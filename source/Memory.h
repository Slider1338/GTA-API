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
	int CheckHandles();
	int Read(LPVOID, LPVOID, DWORD);
	int Write(LPVOID, LPVOID, DWORD);
};