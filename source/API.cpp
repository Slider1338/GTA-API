/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-05-09
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
*/

#include "API.h"
#include "SAMP.h"
#include "GTASA.h"
#include "Areas.h"
#include "ChatlogManagement.h"
#include "Interface.h"
#include "Utilities.h"

SAMP _SAMP;
GTASA _GTASA;
Cities _Cities;
Zones _Zones;
ChatlogManagement _ChatlogManagement;
Interface _Interface;
extern Utilities _Utilities;

#pragma comment(lib, "Shell32.lib")
#pragma comment (lib, "wininet.lib")

// DLL Main
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		// fill array
		for (int i = 0; i < MAX_PLAYERS; i++) {
			memcpy(_PlayerDatas[i]._PlayerData_Name, "Unbekannt", 9);
			_PlayerDatas[i]._PlayerData_Score = 0;
			_PlayerDatas[i]._PlayerData_Ping = 0;
		}

		// load cities & zones
		_Cities.LoadCities();
		_Zones.LoadZones();

		// chatlog shit
		_ChatlogManagement.CreateChatlogPath();
		_ChatlogManagement.LoadChatlogs();
	}

	return TRUE;
}

// SA:MP
int GetServerName(char *&servername) {
	return _SAMP.API_GetServerName(servername);
}

int GetServerIP(char *&serverip) {
	return _SAMP.API_GetServerIP(serverip);
}

int CountOnlinePlayers() {
	return _SAMP.API_CountOnlinePlayers();
}

int GetPlayerName(char *&playername) {
	return _SAMP.API_GetPlayerName(playername);
}

int GetPlayerID() {
	return _SAMP.API_GetPlayerID();
}

int GetPlayerScore() {
	return _SAMP.API_GetPlayerScore();
}

int GetPlayerPing() {
	return _SAMP.API_GetPlayerPing();
}

int IsPlayerConnected(int playerid) {
	return _SAMP.API_IsPlayerConnected(playerid);
}

int GetPlayerIDByName(char *playername) {
	return _SAMP.API_GetPlayerIDByName(playername);
}

int GetPlayerNameByID(int playerid, char *&playername) {
	return _SAMP.API_GetPlayerNameByID(playerid, playername);
}

int GetPlayerScoreByID(int playerid) {
	return _SAMP.API_GetPlayerScoreByID(playerid);
}

int GetPlayerPingByID(int playerid) {
	return _SAMP.API_GetPlayerPingByID(playerid);
}

int UpdateServerData() {
	return _SAMP.API_UpdateServerData();
}

int SendChat(char *text) {
	return _SAMP.API_SendChat(text);
}

int AddChatMessage(char *text) {
	return _SAMP.API_AddChatMessage(text);
}

int ShowDialog(int style, const char *caption, const char *info, const char *button) {
	return _SAMP.API_ShowDialog(style, caption, info, button);
}

int ShowGameText(const char *text, int time, int style) {
	return _SAMP.API_ShowGameText(text, time, style);
}

int GetChatLine(int line, char *&content) {
	return _ChatlogManagement.API_GetChatLine(line, content);
}

int IsInChat() {
	return _SAMP.API_IsInChat();
}

// GTA
int GetPlayerMoney() {
	return _GTASA.API_GetPlayerMoney();
}

int GetPlayerHealth() {
	return _GTASA.API_GetPlayerHealth();
}

int GetPlayerArmour() {
	return _GTASA.API_GetPlayerArmour();
}

int GetPlayerPos(float &x, float &y, float &z) {
	return _GTASA.API_GetPlayerPos(x, y, z);
}

int GetPlayerPosX(float &x) {
	return _GTASA.API_GetPlayerPosX(x);
}

int GetPlayerPosY(float &y) {
	return _GTASA.API_GetPlayerPosY(y);
}

int GetPlayerPosZ(float &z) {
	return _GTASA.API_GetPlayerPosZ(z);
}

int IsPlayerInAnyInterior() {
	return _GTASA.API_IsPlayerInAnyInterior();
}

int GetPlayerInteriorID() {
	return _GTASA.API_GetPlayerInteriorID();
}

int IsPlayerInRangeOfPoint(float radius, float x, float y, float z) {
	return _GTASA.API_IsPlayerInRangeOfPoint(radius, x, y, z);
}

int GetPlayerWeaponID() {
	return _GTASA.API_GetPlayerWeaponID();
}

int GetPlayerWeaponSlot() {
	return _GTASA.API_GetPlayerWeaponSlot();
}

int GetPlayerWeaponClipAmmo() {
	return _GTASA.API_GetPlayerWeaponClipAmmo();
}

int IsPlayerInArea(float minx, float miny, float maxx, float maxy) {
	return _GTASA.API_IsPlayerInArea(minx, miny, maxx, maxy);
}

int GetCityName(char *&cityname) {
	return _GTASA.API_GetCityName(cityname);
}

int GetZoneName(char *&zonename) {
	return _GTASA.API_GetZoneName(zonename);
}

int GetVehicleHealth() {
	return _GTASA.API_GetVehicleHealth();
}

int IsPlayerInAnyVehicle() {
	return _GTASA.API_IsPlayerInAnyVehicle();
}

int VehicleSirenStateChange() {
	return _GTASA.API_VehicleSirenStateChange();
}

int GetVehicleSirenState() {
	return _GTASA.API_GetVehicleSirenState();
}

int GetVehicleLockState() {
	return _GTASA.API_GetVehicleLockState();
}

int GetVehicleEngineState() {
	return _GTASA.API_GetVehicleEngineState();
}

int GetVehicleLightState() {
	return _GTASA.API_GetVehicleLightState();
}

int GetVehicleModelID() {
	return _GTASA.API_GetVehicleModelID();
}

int GetVehicleType() {
	return _GTASA.API_GetVehicleType();
}

int IsPlayerInACar() {
	return _GTASA.API_IsPlayerInACar();
}

int IsPlayerInABoat() {
	return _GTASA.API_IsPlayerInABoat();
}

int IsPlayerInATrain() {
	return _GTASA.API_IsPlayerInATrain();
}

int IsPlayerInABike() {
	return _GTASA.API_IsPlayerInABike();
}

int IsPlayerInAPlane() {
	return _GTASA.API_IsPlayerInAPlane();
}

int IsPlayerInABicycle() {
	return _GTASA.API_IsPlayerInABicycle();
}

// Interface
int SetInterfaceHealthColor(int color) {
	return _Interface.API_SetInterfaceHealthColor(color);
}

int SetInterfaceMoneyColor(int color) {
	return _Interface.API_SetInterfaceMoneyColor(color);
}

int SetInterfaceWantedLevelColor(int color) {
	return _Interface.API_SetInterfaceWantedLevelColor(color);
}

// Utilities
int IsAPIUpdateAvailable() {
	return _Utilities.API_IsAPIUpdateAvailable();
}

int GetAPIVersion(char *&version) {
	return _Utilities.API_GetAPIVersion(version);
}

int GetTimestamp() {
	return _Utilities.API_GetTimestamp();
}

int GetAPIRuntime() {
	return _Utilities.API_GetAPIRuntime();
}