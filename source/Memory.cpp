/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-05-09
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 *
 * this file contains all functions for the MemoryManagement class
*/

// includes
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include "Memory.h"

/**
 * DWORD GetGTAProcessID()
 *
 * @author			Slider
 * @date			2014-05-09
 * @category		MemoryManagement
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
DWORD Memory::GetGTAProcessID() {
	DWORD processID;
	GetWindowThreadProcessId(FindWindow(0, "GTA:SA:MP"), &processID);

	return processID;
}

/**
 * DWORD GetSAMPBaseAddress
 * @author			agrippa1994
 * @date			2014-07-31
 * @category		MemoryManagement
 * @license			agrippa1994 License <https://github.com/agrippa1994/CPP-SAMP-API/blob/master/LICENSE>
*/
DWORD Memory::GetSAMPBaseAddress() {
	DWORD m_dwSAMPBase = 0;

	if (GetGTAProcessID()) {
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetGTAProcessID());

		if (hSnapshot != INVALID_HANDLE_VALUE) {
			MODULEENTRY32 entry;
			entry.dwSize = sizeof(MODULEENTRY32);

			Module32First(hSnapshot, &entry);
			do {
				if (_stricmp(entry.szModule, "samp.dll") == 0) {
					m_dwSAMPBase = (DWORD)entry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &entry));

			CloseHandle(hSnapshot);
		}
	}

	return m_dwSAMPBase;
}

/**
 * int CheckHandles()
 *
 * @author			Slider
 * @date			2014-08-24
 * @category		MemoryManagement
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Memory::CheckHandles() {
	// get the gta_sa.exe process id
	Memory::processID = Memory::GetGTAProcessID();
	if (!Memory::processID) {
		Memory::CheckHandlesErrorCode = -1;
		return Memory::CheckHandlesErrorCode;
	}

	// try to open the process handle
	Memory::processHandle = OpenProcess(STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFF, FALSE, Memory::processID);
	if (!Memory::processHandle) {
		Memory::CheckHandlesErrorCode = -2;
		return Memory::CheckHandlesErrorCode;
	}

	// get the samp.dll base address
	Memory::sampDLL = Memory::GetSAMPBaseAddress();
	if (!Memory::sampDLL) {
		Memory::CheckHandlesErrorCode = -3;
		return Memory::CheckHandlesErrorCode;
	}

	// success returncode
	Memory::CheckHandlesErrorCode = 1;
	return Memory::CheckHandlesErrorCode;
}

/**
 * int Read(LPCVOID, LPVOID)
 *
 * @author			Slider
 * @date			2014-08-24
 * @category		MemoryManagement
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Memory::Read(LPVOID address, LPVOID buffer, DWORD size) {
	if (Memory::CheckHandles() == 1) {
		ReadProcessMemory(Memory::processHandle, address, buffer, size, NULL);
		return 1;
	}

	return 0;
}

/**
 * int Write(LPCVOID, LPVOID)
 *
 * @author			Slider
 * @date			2014-08-24
 * @category		MemoryManagement
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Memory::Write(LPVOID address, LPVOID buffer, DWORD size) {
	if (Memory::CheckHandles() == 1) {
		WriteProcessMemory(Memory::processHandle, address, buffer, size, NULL);
		return 1;
	}

	return 0;
}