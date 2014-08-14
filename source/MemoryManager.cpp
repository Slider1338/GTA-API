/**
* GTA API by Slider (c) www.gta-api.de
*
* @author				Slider
* @date					2014-05-09
* @copyright			(c) by Slider - www.gta-api.de
* @license				General Public License <https://www.gnu.org/licenses/gpl>
*/

// includes
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include "MemoryManager.h"

/**
 * DWORD GetGTAProcessID()
 *
 * @author			Slider
 * @date			2014-05-09
 * @category		API
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
DWORD GetGTAProcessID() {
	DWORD processID;
	GetWindowThreadProcessId(FindWindow(0, "GTA:SA:MP"), &processID);

	return processID;
}

/**
 * DWORD GetSAMPBaseAddress
 * @author			agrippa1994
 * @date			2014-07-31
 * @category		API
 * @license			agrippa1994 License <https://github.com/agrippa1994/CPP-SAMP-API/blob/master/LICENSE>
*/
DWORD GetSAMPBaseAddress()
{
	DWORD m_dwSAMPBase = 0;

	if (GetGTAProcessID()) {
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetGTAProcessID());
		if (hSnapshot == INVALID_HANDLE_VALUE)
			return false;

		MODULEENTRY32 entry;
		entry.dwSize = sizeof(MODULEENTRY32);

		Module32First(hSnapshot, &entry);
		do
		{
			if (_stricmp(entry.szModule, "samp.dll") == 0)
			{
				m_dwSAMPBase = (DWORD)entry.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &entry));

		CloseHandle(hSnapshot);
	}

	return m_dwSAMPBase;
}