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

#pragma once

#define MAX_PLAYERS 1000
#define AUTO_SCOREBOARD_REFRESH 10000
#define MAX_PLAYER_NAME 30
#define MAX_SERVERNAME_LENGTH 50

#define SAMP_SERVERNAME_ADDR 0x21A0F8 //updated
#define SAMP_SERVERIP_ADDR 0x2121F5 //not updated
#define SAMP_PLAYERSONLINE_OFFSET 0x4 //not updated
#define SAMP_PLAYERSONLINE_ADDR 0x212A3C //not updated
#define SAMP_PLAYERNAME_ADDR 0x219A6F //updated
#define SAMP_SENDCHAT_FUNC_ADDR 0x57F0 //updated
#define SAMP_SENDCMD_FUNC_ADDR 0x65C60 //updated
#define SAMP_PLAYERID_OFFSET 0x4 
#define SAMP_PLAYERSCORE_OFFSET 0x2A
#define SAMP_PLAYERPING_OFFSET 0x26
#define SAMP_SCOREBOARD_OFFSET 0x8A10 //not tested
#define SAMP_SCOREBOARD_PLAYERPOOLS_OFFSET 0x3CD //updated
#define SAMP_SCOREBOARD_PLAYERPOOL_OFFSET 0x18 // updated
#define SAMP_SCOREBOARD_PLAYER_OFFSET 0x2E // not tested
#define SAMP_SCOREBOARD_PLAYER_NAME_OFFSET 0xC // updated
#define SAMP_SCOREBOARD_PLAYER_NAMELNG_OFFSET 0x1C // updated
#define SAMP_SCOREBOARD_PLAYER_SCORE_OFFSET 0x24 // updated
#define SAMP_SCOREBOARD_PLAYER_PING_OFFSET 0x28 // updated
#define SAMP_ISINCHAT_ADDR 0x21A10C // updated
#define SAMP_ISINCHAT_OFFSET 0x55 
#define SAMP_SERVERNAME_ADDR 0x21A0F8 //not tested
#define SAMP_SERVERNAME_OFFSET 0x2C6 //not updated 
#define SAMP_DIALOG_OBJECT 0x21A0B8
#define SAMP_CHATINFO_OBJECT 0x21A0E4
#define SAMP_ADDCHATMESSAGE_FUNC_ADDR 0x64520

struct PlayerDatas {
	char _PlayerData_Name[MAX_PLAYER_NAME];
	int _PlayerData_Ping;
	int _PlayerData_Score;
};

extern struct PlayerDatas _PlayerDatas[MAX_PLAYERS];

class SAMP {
public:
	int LocalPlayerID = -1;
	int LocalPlayerScore = -1;
	int LocalPlayerPing = -1;
	int LastScoreboardUpdate = 0;
	int LastLocalPlayerInfoUpdate = 0;

	int API_GetServerName(char *&servername);
	int API_GetServerIP(char *&serverip);
	int API_CountOnlinePlayers();
	int API_UpdateServerData();
	int API_ReadScoreboard();
	int API_UpdateLocalPlayerInfo();
	int API_GetPlayerName(char *&playername);
	int API_GetPlayerID();
	int API_GetPlayerScore();
	int API_GetPlayerPing();
	int API_IsPlayerConnected(int playerid);
	int API_GetPlayerIDByName(char *playername);
	int API_GetPlayerNameByID(int playerid, char *&playername);
	int API_GetPlayerScoreByID(int playerid);
	int API_GetPlayerPingByID(int playerid);
	int API_SendChat(char*);
	int API_AddChatMessage(char *text);
	int API_ShowDialog(int style, const char *caption, const char *info, const char *button);
	int API_ShowGameText(const char *text, int time, int style);
	int API_IsInChat();
};
