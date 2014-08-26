/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-05-09
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 *
 * includefile for c++ projects
 */

#pragma once

// SA:MP
extern "C" __declspec(dllimport) int GetServerName(char*&);
extern "C" __declspec(dllimport) int GetServerIP(char*&);
extern "C" __declspec(dllimport) int CountOnlinePlayers();
extern "C" __declspec(dllimport) int GetPlayerName(char*&);
extern "C" __declspec(dllimport) int GetPlayerID();
extern "C" __declspec(dllimport) int GetPlayerScore();
extern "C" __declspec(dllimport) int GetPlayerPing();
extern "C" __declspec(dllimport) int IsPlayerConnected(int playerid);
extern "C" __declspec(dllimport) int GetPlayerNameByID(int playerid, char *&playername);
extern "C" __declspec(dllimport) int GetPlayerScoreByID(int playerid);
extern "C" __declspec(dllimport) int GetPlayerPingByID(int playerid);
extern "C" __declspec(dllimport) int SendChat(char *text);
extern "C" __declspec(dllimport) int GetChatLine(int line, char *&content);
extern "C" __declspec(dllimport) int IsInChat();

// GTA
extern "C" __declspec(dllimport) int GetPlayerMoney();
extern "C" __declspec(dllimport) int GetPlayerHealth();
extern "C" __declspec(dllimport) int GetPlayerArmour();
extern "C" __declspec(dllimport) int GetPlayerPos(float &x, float &y, float &z);
extern "C" __declspec(dllimport) int GetPlayerPosX(float &x);
extern "C" __declspec(dllimport) int GetPlayerPosY(float &y);
extern "C" __declspec(dllimport) int GetPlayerPosZ(float &z);
extern "C" __declspec(dllimport) int IsPlayerInAnyInterior();
extern "C" __declspec(dllimport) int GetPlayerInteriorID();
extern "C" __declspec(dllimport) int IsPlayerInRangeOfPoint(float radius, float x, float y, float z);
extern "C" __declspec(dllimport) int GetPlayerWeaponID();
extern "C" __declspec(dllimport) int GetPlayerWeaponSlot();
extern "C" __declspec(dllimport) int GetPlayerWeaponClipAmmo();
extern "C" __declspec(dllimport) int IsPlayerInArea(float minx, float miny, float maxx, float maxy);
extern "C" __declspec(dllimport) int GetCityName(char*&);
extern "C" __declspec(dllimport) int GetZoneName(char*&);
extern "C" __declspec(dllimport) int GetVehicleHealth();
extern "C" __declspec(dllimport) int IsPlayerInAnyVehicle();
extern "C" __declspec(dllimport) int VehicleSirenStateChange();
extern "C" __declspec(dllimport) int GetVehicleSirenState();
extern "C" __declspec(dllimport) int GetVehicleLockState();
extern "C" __declspec(dllimport) int GetVehicleEngineState();
extern "C" __declspec(dllimport) int GetVehicleLightState();
extern "C" __declspec(dllimport) int GetVehicleModelID();
extern "C" __declspec(dllimport) int GetVehicleType();
extern "C" __declspec(dllimport) int IsPlayerInACar();
extern "C" __declspec(dllimport) int IsPlayerInABoat();
extern "C" __declspec(dllimport) int IsPlayerInATrain();
extern "C" __declspec(dllimport) int IsPlayerInABike();
extern "C" __declspec(dllimport) int IsPlayerInAPlane();
extern "C" __declspec(dllimport) int IsPlayerInABicycle();

// Interface
extern "C" __declspec(dllimport) int SetInterfaceHealthColor();
extern "C" __declspec(dllimport) int SetInterfaceMoneyColor();
extern "C" __declspec(dllimport) int SetInterfaceWantedLevelColor();

// Utilities
extern "C" __declspec(dllimport) int IsAPIUpdateAvailable();
extern "C" __declspec(dllimport) int GetAPIVersion(char *&version);
extern "C" __declspec(dllimport) int GetTimestamp();
extern "C" __declspec(dllimport) int GetAPIRuntime();