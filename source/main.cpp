/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-05-09
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
#include "SAMP.hpp"

// Settings
#define MAX_PLAYER_NAME 35
#define MAX_SERVERNAME_LENGTH 50
#define FUNCTION_ERROR_CODE -1
#define API_VERSION "1.0.0 Beta 3"

// SA:MP Addresses
#define SAMP_SERVERNAME_ADDR 0x212A80
#define SAMP_SERVERIP_ADDR 0x2121F5
#define SAMP_PLAYERNAME_ADDR 0x2123F7
#define SAMP_PLAYERSONLINE_ADDR 0x212A3C
#define SAMP_ISINCHAT_ADDR 0x212A94

// SA:MP Function Addresses
#define SAMP_SENDCHAT_FUNC_ADDR 0x4CA0
#define SAMP_SENDCMD_FUNC_ADDR 0x7BDD0
#define SAMP_PLAYAUDIOSTREAM_FUNC_ADDR 0x79300

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
#define GTA_PLAYER_WEAPON_CLIP_AMMO_ADDR 0x1207F0
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

// agrippa1994 SAMP Class
SAMP::SAMP samp;

// prototypes
int GetRealWeaponID(int);
void ConvertHexToRGB(int, int&, int&, int&);
int CheckHandles();

/**
 * int API_GetServerName(char *&servername)
 *
 * @author			Grab
 * @date			2014-08-04
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 *
 * @params			servername			char*&
 */
int API_GetServerName(char *&servername) {
	char name[MAX_SERVERNAME_LENGTH] = { "Unknown" };

	if (CheckHandles()) {
		addr = sampDLL + SAMP_SERVERNAME_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)(addr), &buffer, sizeof(buffer), NULL);
		ReadProcessMemory(gtaHandle, (DWORD*)(buffer + 0x2C6), &name, sizeof(name), NULL);
		
		memcpy(servername, name, sizeof(name));

		return 1;
	}

	return FUNCTION_ERROR_CODE;
}

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
 * int API_CountOnlinePlayers()
 *
 * @author			Grab
 * @date			2014-08-05
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_CountOnlinePlayers() {
	if (CheckHandles()) {
		int players = 0;
		buffer = NULL;

		addr = sampDLL + SAMP_PLAYERSONLINE_ADDR;
		ReadProcessMemory(gtaHandle, (DWORD*)(addr), &buffer, sizeof(buffer), NULL);

		if (buffer != NULL) {
			ReadProcessMemory(gtaHandle, (DWORD*)(buffer + 0x4), &players, sizeof(players), NULL);
			return players;
		}
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
 * int API_AddChatMessage(char* text)
 *
 * @author			agrippa1994
 * @date			2014-07-31
 * @category		SA:MP
 * @license			agrippa1994 License <https://github.com/agrippa1994/CPP-SAMP-API/blob/master/LICENSE>
 *
 * @params			text			char*
 */
int API_AddChatMessage(char *text) {
	if (CheckHandles()) {
		char _text[256] = { "• {ffffff}" };
		strcat_s(_text, text);

		samp.addChatMessage(_text);
		return 1;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_ShowDialog(int style, const char *caption, const char *info, const char *button)
 *
 * @author			agrippa1994
 * @date			2014-07-31
 * @category		SA:MP
 * @license			agrippa1994 License <https://github.com/agrippa1994/CPP-SAMP-API/blob/master/LICENSE>
 *
 * @params			style			int
 * @params			caption			char*
 * @params			text			char*
 * @params			button			char*
 */
int API_ShowDialog(int style, const char *caption, const char *info, const char *button) {
	if (CheckHandles()) {
		char _caption[256] = { "• " };
		strcat_s(_caption, caption);

		samp.showDialog(style, _caption, info, button);
		return 1;
	}

	return FUNCTION_ERROR_CODE;
}

/**
 * int API_IsInChat()
 *
 * @author			Slider
 * @date			2014-08-14
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_IsInChat() {
	DWORD value = 0;

	if (CheckHandles()) {
		ReadProcessMemory(gtaHandle, (DWORD*)(sampDLL + SAMP_ISINCHAT_ADDR), &buffer, sizeof(buffer), NULL);
		addr = buffer + 0x55;

		ReadProcessMemory(gtaHandle, (DWORD*)addr, &value, sizeof(value), NULL);

		if (value > 0) {
			return 1;
		}
		
		return 0;
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
		BYTE weaponid;

		ReadProcessMemory(gtaHandle, (LPCVOID)GTA_CPED_POINTER_ADDR, (LPVOID)buffer, sizeof(buffer), NULL);

		addr = buffer + GTA_PLAYER_WEAPONID_ADDR;
		ReadProcessMemory(gtaHandle, (LPCVOID)(addr), &weaponid, sizeof(weaponid), NULL);

		return GetRealWeaponID((int)weaponid);
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
 * int API_GetPlayerWeaponClipAmmo()
 *
 * @author			Grab
 * @date			2014-08-05
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetPlayerWeaponClipAmmo() {
	if (CheckHandles()) {
		DWORD offset = NULL;
		int ammo = 0;

		ReadProcessMemory(gtaHandle, (DWORD*)GTA_PLAYER_WEAPON_CLIP_AMMO_ADDR, &buffer, sizeof(buffer), NULL);

		switch (API_GetPlayerWeaponID()) {
			case 22: offset = 0x00; break;
			case 23: offset = 0x00; break;
			case 24: offset = 0x00; break;

			case 25: offset = 0x1C; break;
			case 26: offset = 0x1C; break;
			case 27: offset = 0x1C; break;

			case 28: offset = 0x38; break;
			case 29: offset = 0x38; break;
			case 32: offset = 0x38; break;

			case 30: offset = 0x54; break;
			case 31: offset = 0x54; break;

			case 33: offset = 0x70; break;
			case 34: offset = 0x70; break;

			case 38: offset = 0x8C; break;
		}

		ReadProcessMemory(gtaHandle, (DWORD*)(buffer + 0x5E0 + offset), &ammo, sizeof(ammo), NULL);

		return ammo;
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
 * int API_GetVersion()
 *
 * @author			Slider
 * @date			2014-08-04
 * @category		Randomshit
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int API_GetVersion(char *&version) {
	memcpy(version, API_VERSION, sizeof(API_VERSION));
	return 1;
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
 * int GetRealWeaponID()
 *
 * @author			Slider
 * @date			2014-08-04
 * @category		Randomshit
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GetRealWeaponID(int weaponid) {
	switch (weaponid) {
		// Faust
		case 255:
		{
			return 0;
		}

		// Schlagring
		case 75:
		{
			return 1;
		}

		// Golfschläger
		case 77:
		{
			return 2;
		}

		// Schlagstock
		case 78:
		{
			return 3;
		}

		// Messer
		case 79:
		{
			return 4;
		}

		// Baseball Schläger
		case 80:
		{
			return 5;
		}

		// Baseball Schläger
		case 81:
		{
			return 6;
		}

		// Cue
		case 82:
		{
			return 7;
		}

		// Katana
		case 83:
		{
			return 8;
		}

		// Kettensäge
		case 85:
		{
			return 9;
		}

		// Double-End-Dildo
		case 65:
		{
			return 10;
		}

		// Dildo
		case 66:
		{
			return 11;
		}

		// Vibrator
		case 67:
		{
			return 12;
		}

		// Silberner Vibrator
		case 68:
		{
			return 13;
		}

		// Blumen
		case 69:
		{
			return 14;
		}

		// Stock
		case 70:
		{
			return 15;
		}

		// Granate
		case 86:
		{
			return 16;
		}

		// Tränengas
		case 87:
		{
			return 17;
		}

		// Molotow Cocktail
		case 88:
		{
			return 18;
		}

		// 9mm
		case 90:
		{
			return 22;
		}

		// 9mm Schalldämpfer
		case 91:
		{
			return 23;
		}

		// Desert Eagle
		case 92:
		{
			return 24;
		}

		// Shotgun
		case 93:
		{
			return 25;
		}

		// Abgesägte Schrotflinte
		case 94:
		{
			return 26;
		}

		// Combat Shotgun
		case 95:
		{
			return 27;
		}

		// Uzi
		case 96:
		{
			return 28;
		}

		// MP5
		case 97:
		{
			return 29;
		}

		// AK 47
		case 99:
		{
			return 30;
		}

		// M4
		case 100:
		{
			return 31;
		}

		// TEC 9
		case 116:
		{
			return 32;
		}

		// Rifle
		case 101:
		{
			return 33;
		}

		// Sniper
		case 102:
		{
			return 34;
		}

		// RPG
		case 103:
		{
			return 35;
		}

		// HS Rocket
		case 104:
		{
			return 36;
		}

		// Flammenwerfer
		case 105:
		{
			return 37;
		}

		// Minigun
		case 106:
		{
			return 38;
		}

		// Satchel Charge
		case 107:
		{
			return 39;
		}

		// Detonator
		case 108:
		{
			return 40;
		}

		// Spraycan
		case 109:
		{
			return 41;
		}

		// Feuerlöscher
		case 110:
		{
			return 42;
		}

		// Kamera
		case 111:
		{
			return 43;
		}

		// Nachtsichtgerät
		case 112:
		{
			return 44;
		}

		// Thermalsichtgerät
		case 113:
		{
			return 45;
		}

		// Fallschirm
		case 115:
		{
			return 46;
		}
	}

	return FUNCTION_ERROR_CODE;
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
	sampDLL = GetSAMPBaseAddress();
	if (!sampDLL) return 0;

	return 1;
}