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
#include <string>
#include <sstream>
#include <Windows.h>
#include <tlhelp32.h>
#include <cstdint>
#include <fstream>
#include <Lmcons.h>
#include <tchar.h>
#include <ctime>
#include "main.h"
#include "MemoryManager.h"

// Settings
#define MAX_PLAYER_NAME 35
#define FUNCTION_ERROR_CODE -1
#define API_VERSION "1.0.0 RC1"

// SA:MP Addresses
#define SAMP_SERVERIP_ADDR 0x2121F5
#define SAMP_PLAYERNAME_ADDR 0x2123F7

// SA:MP Function Addresses
#define SAMP_SENDCHAT_FUNC_ADDR 0x4CA0
#define SAMP_SENDCMD_FUNC_ADDR 0x7BDD0

// GTA Addresses
#define GTA_CPED_POINTER_ADDR 0xB6F5F0
#define GTA_PLAYER_HEALTH_ADDR 0x540
#define GTA_PLAYER_ARMOUR_ADDR 0x548
#define GTA_PLAYER_POS_X 0xB6F2E4
#define GTA_PLAYER_POS_Y 0xB6F2E8
#define GTA_PLAYER_POS_Z 0xB6F2EC
#define GTA_PLAYER_INTERIOR_ADDR 0xA4ACE8
#define GTA_PLAYER_WEAPONID_ADDR 0x740
#define GTA_PLAYER_WEAPON_SLOT_ADDR 0xB7CDBC
#define GTA_VEHICLE_POINTER_ADDR 0xBA18FC
#define GTA_VEHICLE_HEALTH_ADDR 0x4C0
#define GTA_VEHICLE_SIREN_STATE_ADDR 0x42D

// Interface Addresses
#define INTERFACE_HEALTH_COLOR_ADDR 0xBAB22C
#define INTERFACE_MONEY_COLOR_ADDR 0xBAB230
#define INTERFACE_WANTEDLEVEL_COLOR_ADDR 0xBAB244

// variables
DWORD addr;
DWORD buffer;
DWORD sampDLL;
DWORD gtaProcessID;
HANDLE gtaHandle;

// prototypes
void ConvertHexToRGB(int, int&, int&, int&);
int CheckHandles();
int GetGTAProcessID();

/**
 * int API_GetServerIP(char *&serverip)
 *
 * @author			Slider
 * @date			2014-05-30
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 *
 * @params			serverip			char*&
 */
int API_GetServerIP(char *&serverip) {
	char ip[15] = { "Unknown" };

	if (CheckHandles()) {
		addr = sampDLL + SAMP_SERVERIP_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)(addr), (LPVOID)ip, sizeof(ip), NULL);

		memcpy(serverip, ip, sizeof(ip));

		return 1;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerName(char*& playername)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 *
 * @params			playername			char*&
 */
int API_GetPlayerName(char *&playername) {
	char name[MAX_PLAYER_NAME] = { "Unknown" };

	if (CheckHandles()) {
		addr = sampDLL + SAMP_PLAYERNAME_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)(addr), (LPVOID)name, sizeof(name), NULL);

		memcpy(playername, name, sizeof(name));
		
		return 1;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_SendChat(char* text)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 *
 * @params			text			char*
 */
int API_SendChat(char *text) {
	if (CheckHandles()) {
		int length = strlen(text) + 1;

		if (text[0] != '/') {
			PVOID cmd = VirtualAllocEx(gtaHandle, 0, length, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			WriteProcessMemory(gtaHandle, cmd, text, length, 0);
 
			DWORD func = sampDLL + SAMP_SENDCHAT_FUNC_ADDR;

			HANDLE hThread = CreateRemoteThread(gtaHandle, 0, 0, (LPTHREAD_START_ROUTINE)func, cmd, 0, 0);
			DWORD dwExitCode = 0;
			
			if (hThread) {
				WaitForSingleObject(hThread, INFINITE);
				GetExitCodeThread(hThread, &dwExitCode);
			}
 
			VirtualFreeEx(gtaHandle, cmd, length, MEM_RELEASE);
			CloseHandle(hThread);

			return 1;
		}
		else {
			PVOID cmd = VirtualAllocEx(gtaHandle, 0, length, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			WriteProcessMemory(gtaHandle, cmd, text, length, 0);
 
			DWORD func = sampDLL + SAMP_SENDCMD_FUNC_ADDR;

			HANDLE hThread = CreateRemoteThread(gtaHandle, 0, 0, (LPTHREAD_START_ROUTINE)func, cmd, 0, 0);
			DWORD dwExitCode = 0;
			
			if (hThread) {
				WaitForSingleObject(hThread, INFINITE);
				GetExitCodeThread(hThread, &dwExitCode);
			}
 
			VirtualFreeEx(gtaHandle, cmd, length, MEM_RELEASE);
			CloseHandle(hThread);

			return 1;
		}
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerHealth()
 *
 * @author			Slider
 * @date			2014-05-09
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerHealth() {
	float health = 0;

	if (CheckHandles()) {
		DWORD *p = (DWORD*)GTA_CPED_POINTER_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)p, &buffer, sizeof(buffer), NULL);

		addr = buffer + GTA_PLAYER_HEALTH_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)(addr), &health, sizeof(health), NULL);

		return (int)health;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerArmour()
 *
 * @author			Slider
 * @date			2014-05-09
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerArmour() {
	float armour = 0;

	if (CheckHandles()) {
		DWORD *p = (DWORD*)GTA_CPED_POINTER_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)p, &buffer, sizeof(buffer), NULL);

		addr = buffer + GTA_PLAYER_ARMOUR_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)(addr), &armour, sizeof(armour), NULL);

		return (int)armour;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerPos(float &x, float &y, float &z)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerPos(float &x, float &y, float &z) {
	if (CheckHandles()) {
		ReadProcessMemory(gtaHandle, (DWORD*)GTA_PLAYER_POS_X, &x, sizeof(x), NULL);
		ReadProcessMemory(gtaHandle, (DWORD*)GTA_PLAYER_POS_Y, &y, sizeof(y), NULL);
		ReadProcessMemory(gtaHandle, (DWORD*)GTA_PLAYER_POS_Z, &z, sizeof(z), NULL);
		
		return 1;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerPosX(float &x)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerPosX(float &x) {
	if (CheckHandles()) {
		ReadProcessMemory(gtaHandle, (DWORD*)GTA_PLAYER_POS_X, &x, sizeof(x), NULL);
		return 1;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerPosY(float &y)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerPosY(float &y) {
	if (CheckHandles()) {
		ReadProcessMemory(gtaHandle, (DWORD*)GTA_PLAYER_POS_Y, &y, sizeof(y), NULL);
		return 1;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerPosZ(float &z)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerPosZ(float &z) {
	if (CheckHandles()) {
		ReadProcessMemory(gtaHandle, (DWORD*)GTA_PLAYER_POS_Z, &z, sizeof(z), NULL);
		return 1;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_IsPlayerInAnyInterior()
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_IsPlayerInAnyInterior() {
	if (CheckHandles()) {
		int intid;

		ReadProcessMemory(gtaHandle, (DWORD*)GTA_PLAYER_INTERIOR_ADDR, &intid, sizeof(intid), NULL);
		if (intid) {
			return 1;
		}

		return 0;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerInteriorID()
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerInteriorID() {
	if (CheckHandles()) {
		int intid;

		ReadProcessMemory(gtaHandle, (DWORD*)GTA_PLAYER_INTERIOR_ADDR, &intid, sizeof(intid), NULL);
		return intid;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_IsPlayerInRangeOfPoint()
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_IsPlayerInRangeOfPoint(float radius, float x, float y, float z) {
	if (CheckHandles()) {
		float x1;
		float y1;
		float z1;

		float posX;
		float posY;
		float posZ;

		API_GetPlayerPos(x1, y1, z1);

		posX = x1 - x;
		posY = y1 - y;
		posZ = z1 - z;

		if (((posX < radius) && (posX > -radius)) && ((posY < radius) && (posY > -radius)) && ((posZ < radius) && (posZ > -radius))) {
			return 1;
		}
		
		return 0;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerWeaponID()
 *
 * @author			Slider
 * @date			2014-07-05
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerWeaponID() {
	if (CheckHandles()) {
		int weaponid;
		
		ReadProcessMemory(gtaHandle, (LPCVOID)GTA_CPED_POINTER_ADDR, (LPVOID)buffer, sizeof(buffer), NULL);

		addr = buffer + GTA_PLAYER_WEAPONID_ADDR;
		ReadProcessMemory(gtaHandle, (LPCVOID)addr, &weaponid, sizeof(weaponid), NULL);

		return weaponid;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetPlayerWeaponSlot()
 *
 * @author			Dreamer
 * @date			2014-07-05
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerWeaponSlot() {
	if (CheckHandles()) {
		int slot;
		
		ReadProcessMemory(gtaHandle, (DWORD*)(GTA_PLAYER_WEAPON_SLOT_ADDR), &slot, sizeof(slot), NULL);
		return slot;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetVehicleHealth()
 *
 * @author			Slider
 * @date			2014-05-26
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetVehicleHealth() {
	float health = 0.0;
	
	if (CheckHandles()) {
		DWORD *p = (DWORD*)GTA_VEHICLE_POINTER_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)p, &buffer, sizeof(buffer), NULL);

		addr = buffer + GTA_VEHICLE_HEALTH_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)(addr), &health, sizeof(health),NULL);

		return (int)health;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_IsPlayerInAnyVehicle()
 *
 * @author			Slider
 * @date			2014-05-26
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_IsPlayerInAnyVehicle() {
	if (CheckHandles()) {
		if (API_GetVehicleHealth()) {
			return 1;
		}

		return 0;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_VehicleSirenStateChange()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_VehicleSirenStateChange() {
	if (CheckHandles()) {
		if (API_IsPlayerInAnyVehicle()) {
			BYTE value;

			ReadProcessMemory(gtaHandle, (LPCVOID)GTA_VEHICLE_POINTER_ADDR, &buffer, sizeof(buffer), NULL);

			addr = buffer + GTA_VEHICLE_SIREN_STATE_ADDR;
			ReadProcessMemory(gtaHandle, (LPCVOID)(addr), &value, sizeof(value), NULL);
		
			// on to off
			if ((int)value == 208) {
				value = 80;
				WriteProcessMemory(gtaHandle, (LPVOID)addr, (LPCVOID)&value, sizeof(value), &buffer);
			}
			// off to on
			else if ((int)value == 80) {
				value = 208;
				WriteProcessMemory(gtaHandle, (LPVOID)addr, (LPCVOID)&value, sizeof(value), &buffer);
			}

			return 1;
		}

		return 0;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_GetVehicleSirenState()
 *
 * @author			Slider
 * @date			2014-07-05
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetVehicleSirenState() {
	if (CheckHandles()) {
		if (API_IsPlayerInAnyVehicle()) {
			BYTE value;

			ReadProcessMemory(gtaHandle, (LPCVOID)GTA_VEHICLE_POINTER_ADDR, &buffer, sizeof(buffer), NULL);

			addr = buffer + GTA_VEHICLE_SIREN_STATE_ADDR;
			ReadProcessMemory(gtaHandle, (LPCVOID)(addr), &value, sizeof(value), NULL);
		
			if ((int)value == 208) {
				return 1;
			}
			else if ((int)value == 80) {
				return 0;
			}
		}

		return 0;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_SetInterfaceHealthColor()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		Interface
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_SetInterfaceHealthColor(int color) {
	if (CheckHandles()) {
		int r, g, b;
		ConvertHexToRGB(color, r, g, b);

		byte write[] = { r, g, b, 1 };

		WriteProcessMemory(gtaHandle, (DWORD*)INTERFACE_HEALTH_COLOR_ADDR, &write, sizeof(write), &buffer);
		return 1;
	}

	return 0;
}

/**
 * int API_SetInterfaceMoneyColor()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		Interface
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_SetInterfaceMoneyColor(int color) {
	if (CheckHandles()) {
		int r, g, b;
		ConvertHexToRGB(color, r, g, b);

		byte write[] = { r, g, b, 1 };
		WriteProcessMemory(gtaHandle, (DWORD*)INTERFACE_MONEY_COLOR_ADDR, &write, sizeof(write), &buffer);

		return 1;
	}

	return 0;
}

/**
 * int API_SetInterfaceWantedLevelColor()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		Interface
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_SetInterfaceWantedLevelColor(int color) {
	if (CheckHandles()) {
		int r, g, b;
		ConvertHexToRGB(color, r, g, b);

		byte write[] = { r, g, b, 1 };

		WriteProcessMemory(gtaHandle, (DWORD*)INTERFACE_WANTEDLEVEL_COLOR_ADDR, &write, sizeof(write), &buffer);
		return 1;
	}

	return 0;
}

/**
 * int API_GetTimestamp()
 *
 * @author			Slider
 * @date			2014-05-29
 * @category		Randomshit
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetTimestamp() {
	return time(0);
}

/**
 * int ConvertHexToRGB()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		Randomshit
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
void ConvertHexToRGB(int hex, int &r, int &g, int &b) {
	 r = (hex & 0xFF0000) >> 16;
	 g = (hex & 0xFF00) >> 8;
	 b = hex & 0xFF;
}

/**
 * int CheckHandles()
 *
 * @author			Slider
 * @date			2014-05-09
 * @category		API
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int CheckHandles() {
	gtaProcessID = GetGTAProcessID();
	if (!gtaProcessID) return 0;

	// check gta handle
	gtaHandle = OpenProcess(STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFF, FALSE, GetGTAProcessID());
	if (!gtaHandle) return 0;

	// get samp.dll module base address
	sampDLL = GetModuleBaseAddress(L"gta_sa.exe", L"samp.dll");
	if (!sampDLL) return 0;

	return 1;
}

/**
 * int GetGTAProcessID()
 *
 * @author			Slider
 * @date			2014-05-09
 * @category		API
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GetGTAProcessID() {
	DWORD processID = FindProcessID(L"gta_sa.exe");
	return processID;
}