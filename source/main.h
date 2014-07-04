/**
 * SAMP 0.3z API by Slider
 * 
 * @author			Slider
 * @date			2014-05-09
 * @copyright		(c) by Slider - www.gta-api.de
 */

// SA:MP Functions
extern "C" __declspec(dllimport) int API_GetPlayerName(char*&);
extern "C" __declspec(dllimport) int API_SendChat(char*);
//extern "C" __declspec(dllimport) int API_AddChatMessage(char*); // unfertig
extern "C" __declspec(dllimport) int API_GetServerIP(char*&);
//extern "C" __declspec(dllimport) int API_GetServerPort(); // unfertig
//extern "C" __declspec(dllimport) int API_IsChatOpen(); // unfertig

// GTA Functions
extern "C" __declspec(dllimport) int API_GetPlayerHealth();
extern "C" __declspec(dllimport) int API_GetPlayerArmour();
extern "C" __declspec(dllimport) int API_GetPlayerPos(float&, float&, float&);
extern "C" __declspec(dllimport) int API_GetPlayerPosX(float&);
extern "C" __declspec(dllimport) int API_GetPlayerPosY(float&);
extern "C" __declspec(dllimport) int API_GetPlayerPosZ(float&);
extern "C" __declspec(dllimport) int API_IsPlayerInAnyInterior();
extern "C" __declspec(dllimport) int API_GetPlayerInteriorID();
//extern "C" __declspec(dllimport) int API_GetPlayerSkin(); // unfertig
extern "C" __declspec(dllimport) int API_IsPlayerInRangeOfPoint(float, float, float, float);
//extern "C" __declspec(dllimport) int API_IsPlayerDriver(); // unfertig

// Vehicle Functions
//extern "C" __declspec(dllimport) int API_GetVehicleID(); // unfertig
// extern "C" __declspec(dllimport) int API_GetLastVehicleID(); // unfertig
extern "C" __declspec(dllimport) int API_GetVehicleHealth();
extern "C" __declspec(dllimport) int API_IsPlayerInAnyVehicle();
extern "C" __declspec(dllimport) int API_GetVehicleModelID();
extern "C" __declspec(dllimport) int API_VehicleSirenStateChange();
extern "C" __declspec(dllimport) int API_GetGasPedalState();
extern "C" __declspec(dllimport) int API_GetVehicleLockState();
extern "C" __declspec(dllimport) int API_GetVehicleEngineState();

// Interface Functions
extern "C" __declspec(dllimport) int API_SetInterfaceHealthColor(int);
extern "C" __declspec(dllimport) int API_SetInterfaceMoneyColor(int);
extern "C" __declspec(dllimport) int API_SetInterfaceWantedLevelColor(int);

// Random Shit Functions
//extern "C" __declspec(dllimport) int API_GetChatLine(int); // unfertig
extern "C" __declspec(dllimport) int API_GetVersion(char*&);
extern "C" __declspec(dllimport) int API_GetTimestamp();
extern "C" __declspec(dllimport) int API_SetGTAProcessName(char*);