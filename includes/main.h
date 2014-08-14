/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-05-09
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 */

// SA:MP
extern "C" __declspec(dllimport) int API_GetServerName(char*&);
extern "C" __declspec(dllimport) int API_GetServerIP(char*&);
extern "C" __declspec(dllimport) int API_CountOnlinePlayers();
extern "C" __declspec(dllimport) int API_GetPlayerName(char*&);
extern "C" __declspec(dllimport) int API_SendChat(char*);
extern "C" __declspec(dllimport) int API_AddChatMessage(char*);
extern "C" __declspec(dllimport) int API_ShowDialog(int, const char*, const char*, const char*);
extern "C" __declspec(dllimport) int API_IsInChat();

// GTA
extern "C" __declspec(dllimport) int API_GetPlayerHealth();
extern "C" __declspec(dllimport) int API_GetPlayerArmour();
extern "C" __declspec(dllimport) int API_GetPlayerPos(float&, float&, float&);
extern "C" __declspec(dllimport) int API_GetPlayerPosX(float&);
extern "C" __declspec(dllimport) int API_GetPlayerPosY(float&);
extern "C" __declspec(dllimport) int API_GetPlayerPosZ(float&);
extern "C" __declspec(dllimport) int API_IsPlayerInAnyInterior();
extern "C" __declspec(dllimport) int API_GetPlayerInteriorID();
extern "C" __declspec(dllimport) int API_IsPlayerInRangeOfPoint(float, float, float, float);
extern "C" __declspec(dllimport) int API_GetPlayerWeaponID();
extern "C" __declspec(dllimport) int API_GetPlayerWeaponSlot();
extern "C" __declspec(dllimport) int API_GetPlayerWeaponClipAmmo();
extern "C" __declspec(dllimport) int API_GetVehicleHealth();
extern "C" __declspec(dllimport) int API_IsPlayerInAnyVehicle();
extern "C" __declspec(dllimport) int API_VehicleSirenStateChange();
extern "C" __declspec(dllimport) int API_GetVehicleSirenState();

// Interface
extern "C" __declspec(dllimport) int API_SetInterfaceHealthColor(int);
extern "C" __declspec(dllimport) int API_SetInterfaceMoneyColor(int);
extern "C" __declspec(dllimport) int API_SetInterfaceWantedLevelColor(int);

// Randomshit
extern "C" __declspec(dllimport) int API_GetVersion(char*&);
extern "C" __declspec(dllimport) int API_GetTimestamp();