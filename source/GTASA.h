/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-08-24
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 *
 * this class contains all standart GTA SA Functions
 */

#pragma once

#include <Windows.h>

#define GTA_CPED_POINTER_ADDR 0xB6F5F0
#define GTA_PLAYER_MONEY 0xB7CE50
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
#define GTA_PLAYERSTATE_INCAR_ADDR 0x530
#define GTA_VEHICLE_DOORSTATE_ADDR 0x4F8
#define GTA_VEHICLE_ENGINESTATE_ADDR 0x428
#define GTA_VEHICLE_LIGHTSTATE_ADDR 0x584
#define GTA_VEHICLE_TYPE_ADDR 0x590
#define GTA_VEHICLE_MODEL_ADDR 0x22

extern int AirplaneModels[20];

class GTASA {
public:
	// Player functions
	DWORD API_GetCPEDPointer();
	int API_GetPlayerMoney();
	int API_GetPlayerHealth();
	int API_GetPlayerArmour();
	int API_GetPlayerPos(float&, float&, float&);
	int API_GetPlayerPosX(float&);
	int API_GetPlayerPosY(float&);
	int API_GetPlayerPosZ(float&);
	int API_IsPlayerInAnyInterior();
	int API_GetPlayerInteriorID();
	int API_IsPlayerInRangeOfPoint(float, float, float, float);
	int API_GetPlayerWeaponID();
	int API_GetPlayerWeaponSlot();
	int API_GetPlayerWeaponClipAmmo();
	int API_IsPlayerInArea(float, float, float, float);
	int API_GetCityName(char*&);
	int API_GetZoneName(char*&);
	int API_GetRealWeaponID(int);

	// Vehicle functions
	DWORD API_GetVehiclePointer();
	int API_GetVehicleHealth();
	int API_IsPlayerInAnyVehicle();
	int API_VehicleSirenStateChange();
	int API_GetVehicleSirenState();
	int API_GetVehicleLockState();
	int API_GetVehicleEngineState();
	int API_GetVehicleLightState();
	int API_GetVehicleModelID();
	int API_GetVehicleType();
	int API_IsPlayerInACar();
	int API_IsPlayerInABoat();
	int API_IsPlayerInATrain();
	int API_IsPlayerInABike();
	int API_IsPlayerInAPlane();
	int API_IsPlayerInABicycle();
};