/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-08-26
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 *
 * this class contains all standart SA:MP Functions
 */

#include <windows.h>
#include "SAMP.h"
#include "Memory.h"

Memory _Memory;

struct PlayerDatas _PlayerDatas[MAX_PLAYERS];

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
int SAMP::API_GetServerName(char *&servername) {
	char name[MAX_SERVERNAME_LENGTH] = { "Unbekannt" };

	if (_Memory.CheckHandles() == 1) {
		DWORD buffer;

		_Memory.Read((DWORD*)(_Memory.GetSAMPBaseAddress() + SAMP_SERVERNAME_ADDR), &buffer, sizeof(buffer));
		_Memory.Read((DWORD*)(buffer + SAMP_SERVERNAME_OFFSET), &name, sizeof(name));
	}

	memcpy(servername, name, sizeof(name));
	return _Memory.CheckHandlesErrorCode;
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
int SAMP::API_GetServerIP(char *&serverip) {
	char ip[15] = { "Unbekannt" };

	if (_Memory.CheckHandles() == 1) {
		_Memory.Read((DWORD*)(_Memory.GetSAMPBaseAddress() + SAMP_SERVERIP_ADDR), &ip, sizeof(ip));
	}

	memcpy(serverip, ip, sizeof(ip));
	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_CountOnlinePlayers()
 *
 * @author			Grab
 * @date			2014-08-05
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_CountOnlinePlayers() {
	if (_Memory.CheckHandles() == 1) {
		int players = 0;
		DWORD buffer = NULL;

		_Memory.Read((DWORD*)(_Memory.GetSAMPBaseAddress() + SAMP_PLAYERSONLINE_ADDR), &buffer, sizeof(buffer));
		_Memory.Read((DWORD*)(buffer + SAMP_PLAYERSONLINE_OFFSET), &players, sizeof(players));

		return players;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard()
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_UpdatePlayerDatas() {
	if (_Memory.CheckHandles() == 1) {
		SAMP::API_ReadScoreboard();
		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard()
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_ReadScoreboard() {
	if (_Memory.CheckHandles() == 1) {
		int index = 0;
		DWORD dwAddress;
		DWORD _dwAddress;
		DWORD dwPlayers;
		DWORD dwPing;
		DWORD dwScore;
		DWORD dwPlayerNameLength;
		DWORD dwRemotePlayer;
		DWORD tmpAddress;
		char PlayerName[30] = { 0 };

		_Memory.Read((DWORD*)(_Memory.sampDLL + SAMP_SCOREBOARD_OFFSET), &dwAddress, sizeof(dwAddress));
		_Memory.Read((DWORD*)(dwAddress + SAMP_SCOREBOARD_PLAYERPOOL_OFFSET), &_dwAddress, sizeof(_dwAddress));
		_Memory.Read((DWORD*)(_dwAddress + SAMP_SCOREBOARD_PLAYERPOOL_OFFSET), &dwPlayers, sizeof(dwPlayers));

		while (index < 1000) {
			memcpy(_PlayerDatas[index]._PlayerData_Name, "Unbekannt", 0);
			_PlayerDatas[index]._PlayerData_Score = -1;
			_PlayerDatas[index]._PlayerData_Ping = -1;

			_Memory.Read((DWORD*)(dwPlayers + SAMP_SCOREBOARD_PLAYER_OFFSET + index * 4), &dwRemotePlayer, sizeof(dwRemotePlayer));
			if (!dwRemotePlayer) {
				index++;
				continue;
			}

			_Memory.Read((DWORD*)(dwRemotePlayer + SAMP_SCOREBOARD_PLAYER_SCORE_OFFSET), &dwScore, sizeof(dwScore));
			_Memory.Read((DWORD*)(dwRemotePlayer + SAMP_SCOREBOARD_PLAYER_PING_OFFSET), &dwPing, sizeof(dwPing));
			_Memory.Read((DWORD*)(dwRemotePlayer + SAMP_SCOREBOARD_PLAYER_NAMELNG_OFFSET), &dwPlayerNameLength, sizeof(dwPlayerNameLength));

			if (dwPlayerNameLength <= 0xF) {
				_Memory.Read((DWORD*)(dwRemotePlayer + 0x14), &PlayerName, sizeof(PlayerName));
			}
			else {
				_Memory.Read((DWORD*)(dwRemotePlayer + 0x14), &tmpAddress, sizeof(tmpAddress));
				_Memory.Read((DWORD*)(dwRemotePlayer + tmpAddress), PlayerName, sizeof(PlayerName));
			}

			if (dwPing > 65535) {
				memcpy(_PlayerDatas[index]._PlayerData_Name, "Unbekannt", 0);
				_PlayerDatas[index]._PlayerData_Score = -1;
				_PlayerDatas[index]._PlayerData_Ping = -1;
			}
			else {
				memcpy(_PlayerDatas[index]._PlayerData_Name, PlayerName, sizeof(PlayerName));
				_PlayerDatas[index]._PlayerData_Score = (int)dwScore;
				_PlayerDatas[index]._PlayerData_Ping = (int)dwPing;
			}

			index++;
		}

		SAMP::LastScoreboardUpdate = GetTickCount();

		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard()
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_UpdateLocalPlayerInfo() {
	if (_Memory.CheckHandles() == 1) {
		short playerid = -1;
		int score = -1;
		int ping = -1;
		DWORD dwAddress;
		DWORD _dwAddress;
		DWORD dwPlayers;
		DWORD dwPing;
		DWORD dwScore;

		_Memory.Read((DWORD*)(_Memory.sampDLL + SAMP_SCOREBOARD_OFFSET), &dwAddress, sizeof(dwAddress));
		_Memory.Read((DWORD*)(dwAddress + SAMP_SCOREBOARD_PLAYERPOOLS_OFFSET), &_dwAddress, sizeof(_dwAddress));
		_Memory.Read((DWORD*)(_dwAddress + SAMP_SCOREBOARD_PLAYERPOOL_OFFSET), &dwPlayers, sizeof(dwPlayers));
		_Memory.Read((DWORD*)(dwPlayers + SAMP_PLAYERID_OFFSET), &playerid, sizeof(playerid)); // local player id
		_Memory.Read((DWORD*)(dwPlayers + SAMP_PLAYERSCORE_OFFSET), &score, sizeof(score)); // local player score
		_Memory.Read((DWORD*)(dwPlayers + SAMP_PLAYERPING_OFFSET), &ping, sizeof(ping)); // local player ping

		SAMP::LocalPlayerID = (int)playerid;
		SAMP::LocalPlayerScore = score;
		SAMP::LocalPlayerPing = ping;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard(char*&)
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_GetPlayerName(char *&playername) {
	if (_Memory.CheckHandles() == 1) {
		char _playername[MAX_PLAYER_NAME] = { "Unbekannt" };
		_Memory.Read((DWORD*)(_Memory.sampDLL + SAMP_PLAYERNAME_ADDR), _playername, sizeof(_playername));

		memcpy(playername, _playername, sizeof(playername));
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard()
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_GetPlayerID() {
	if (_Memory.CheckHandles() == 1) {
		SAMP::API_UpdateLocalPlayerInfo();
		return SAMP::LocalPlayerID;
	}
	
	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard()
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_GetPlayerScore() {
	if (_Memory.CheckHandles() == 1) {
		SAMP::API_UpdateLocalPlayerInfo();
		return SAMP::LocalPlayerScore;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard()
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_GetPlayerPing() {
	if (_Memory.CheckHandles() == 1) {
		SAMP::API_UpdateLocalPlayerInfo();
		return SAMP::LocalPlayerPing;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard(int)
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_IsPlayerConnected(int playerid) {
	if (_Memory.CheckHandles() == 1) {
		if ((SAMP::LastScoreboardUpdate + AUTO_SCOREBOARD_REFRESH) < GetTickCount()) {
			SAMP::API_UpdatePlayerDatas();
		}

		if (playerid < 0 || playerid > (MAX_PLAYERS - 1)) {
			return 0;
		}
		else {
			if (_PlayerDatas[playerid]._PlayerData_Ping == -1) {
				return 0;
			}
		}

		return 1;
	}
	
	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard(int, char*&)
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_GetPlayerNameByID(int playerid, char *&playername) {
	if (_Memory.CheckHandles() == 1) {
		if ((SAMP::LastScoreboardUpdate + AUTO_SCOREBOARD_REFRESH) < GetTickCount()) {
			SAMP::API_UpdatePlayerDatas();
		}

		if (playerid < 0 || playerid > (MAX_PLAYERS - 1)) {
			playerid = 0;
		}

		memcpy(playername, _PlayerDatas[playerid]._PlayerData_Name, sizeof(_PlayerDatas[playerid]._PlayerData_Name));

		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_UpdateScoreboard(int)
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_GetPlayerScoreByID(int playerid) {
	if (_Memory.CheckHandles() == 1) {
		if ((SAMP::LastScoreboardUpdate + AUTO_SCOREBOARD_REFRESH) < GetTickCount()) {
			SAMP::API_UpdatePlayerDatas();
		}

		if (playerid < 0 || playerid > (MAX_PLAYERS - 1)) {
			playerid = 0;
		}

		return _PlayerDatas[playerid]._PlayerData_Score;
	}
	
	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerPingByID(int)
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_GetPlayerPingByID(int playerid) {
	if (_Memory.CheckHandles() == 1) {
		if ((SAMP::LastScoreboardUpdate + AUTO_SCOREBOARD_REFRESH) < GetTickCount()) {
			SAMP::API_UpdatePlayerDatas();
		}

		if (playerid < 0 || playerid > (MAX_PLAYERS - 1)) {
			playerid = 0;
		}

		return _PlayerDatas[playerid]._PlayerData_Ping;
	}

	return _Memory.CheckHandlesErrorCode;
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
int SAMP::API_SendChat(char *text) {
	if (_Memory.CheckHandles() == 1) {
		int length = strlen(text) + 1;
		if (text[0] != '/') {
			PVOID cmd = VirtualAllocEx(_Memory.processHandle, 0, length, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			WriteProcessMemory(_Memory.processHandle, cmd, text, length, 0);

			HANDLE hThread = CreateRemoteThread(_Memory.processHandle, 0, 0, (LPTHREAD_START_ROUTINE)(_Memory.sampDLL + SAMP_SENDCHAT_FUNC_ADDR), cmd, 0, 0);
			DWORD dwExitCode = 0;
			
			if (hThread) {
				WaitForSingleObject(hThread, INFINITE);
				GetExitCodeThread(hThread, &dwExitCode);
			}
 
			VirtualFreeEx(_Memory.processHandle, cmd, length, MEM_RELEASE);
			CloseHandle(hThread);
		}
		else {
			PVOID cmd = VirtualAllocEx(_Memory.processHandle, 0, length, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			WriteProcessMemory(_Memory.processHandle, cmd, text, length, 0);

			HANDLE hThread = CreateRemoteThread(_Memory.processHandle, 0, 0, (LPTHREAD_START_ROUTINE)(_Memory.sampDLL + SAMP_SENDCMD_FUNC_ADDR), cmd, 0, 0);
			DWORD dwExitCode = 0;

			if (hThread) {
				WaitForSingleObject(hThread, INFINITE);
				GetExitCodeThread(hThread, &dwExitCode);
			}

			VirtualFreeEx(_Memory.processHandle, cmd, length, MEM_RELEASE);
			CloseHandle(hThread);
		}

		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsInChat()
 *
 * @author			Slider
 * @date			2014-08-14
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int SAMP::API_IsInChat() {
	if (_Memory.CheckHandles() == 1) {
		DWORD value = 0, buffer = 0;
		_Memory.Read((DWORD*)(_Memory.GetSAMPBaseAddress() + SAMP_ISINCHAT_ADDR), &buffer, sizeof(buffer));
		_Memory.Read((DWORD*)(buffer + SAMP_ISINCHAT_OFFSET), &value, sizeof(value));

		if (value > 0) {
			return 1;
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}