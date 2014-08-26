/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-08-24
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 */

#include <windows.h>
#include "GTASA.h"
#include "Memory.h"
#include "Areas.h"

extern Memory _Memory;

struct GTACities cities[MAX_CITIES];
struct GTAZones zones[MAX_ZONES];

int AirplaneModels[20] = {
	417, 425, 447, 460, 469, 476, 487, 488, 497, 511, 512, 513, 519, 520, 548, 553, 563, 577, 592, 593
};

/**
 * int API_GetCPEDPointer()
 *
 * @author			Slider
 * @date			2014-08-24
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
DWORD GTASA::API_GetCPEDPointer() {
	if (_Memory.CheckHandles() == 1) {
		DWORD buffer;

		_Memory.Read((DWORD*)GTA_CPED_POINTER_ADDR, &buffer, sizeof(buffer));
		return buffer;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerMoney()
 *
 * @author			Slider
 * @date			2014-08-16
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerMoney() {
	if (_Memory.CheckHandles() == 1) {
		int money;

		_Memory.Read((DWORD*)GTA_PLAYER_MONEY, &money, sizeof(money));
		return money;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerHealth()
 *
 * @author			Slider
 * @date			2014-05-09
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerHealth() {
	if (_Memory.CheckHandles() == 1) {
		float health;

		_Memory.Read((DWORD*)(GTASA::API_GetCPEDPointer() + GTA_PLAYER_HEALTH_ADDR), &health, sizeof(health));
		return (int)health;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerArmour()
 *
 * @author			Slider
 * @date			2014-05-09
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerArmour() {
	if (_Memory.CheckHandles() == 1) {
		float armour;

		_Memory.Read((DWORD*)(GTASA::API_GetCPEDPointer() + GTA_PLAYER_ARMOUR_ADDR), &armour, sizeof(armour));
		return (int)armour;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerPos(float &x, float &y, float &z)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerPos(float &x, float &y, float &z) {
	if (_Memory.CheckHandles() == 1) {
		_Memory.Read((DWORD*)GTA_PLAYER_POS_X, &x, sizeof(x));
		_Memory.Read((DWORD*)GTA_PLAYER_POS_Y, &y, sizeof(y));
		_Memory.Read((DWORD*)GTA_PLAYER_POS_Z, &z, sizeof(z));
		
		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerPosX(float &x)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerPosX(float &x) {
	if (_Memory.CheckHandles() == 1) {
		_Memory.Read((DWORD*)GTA_PLAYER_POS_X, &x, sizeof(x));
		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerPosY(float &y)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerPosY(float &y) {
	if (_Memory.CheckHandles() == 1) {
		_Memory.Read((DWORD*)GTA_PLAYER_POS_Y, &y, sizeof(y));
		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerPosZ(float &z)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerPosZ(float &z) {
	if (_Memory.CheckHandles() == 1) {
		_Memory.Read((DWORD*)GTA_PLAYER_POS_Z, &z, sizeof(z));
		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInAnyInterior()
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInAnyInterior() {
	if (_Memory.CheckHandles() == 1) {
		int intid = 0;
		_Memory.Read((DWORD*)GTA_PLAYER_INTERIOR_ADDR, &intid, sizeof(intid));

		if (intid) {
			return 1;
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerInteriorID()
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerInteriorID() {
	if (_Memory.CheckHandles() == 1) {
		int intid = 0;

		_Memory.Read((DWORD*)GTA_PLAYER_INTERIOR_ADDR, &intid, sizeof(intid));
		return intid;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInRangeOfPoint(float, float, float, float)
 *
 * @author			Slider
 * @date			2014-05-10
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInRangeOfPoint(float radius, float x, float y, float z) {
	if (_Memory.CheckHandles() == 1) {
		float x1 = 0.0, y1 = 0.0, z1 = 0.0, posX = 0.0, posY = 0.0, posZ = 0.0;
		API_GetPlayerPos(x1, y1, z1);

		posX = x1 - x;
		posY = y1 - y;
		posZ = z1 - z;

		if (((posX < radius) && (posX > -radius)) && ((posY < radius) && (posY > -radius)) && ((posZ < radius) && (posZ > -radius))) {
			return 1;
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerWeaponID()
 *
 * @author			Slider
 * @date			2014-07-05
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerWeaponID() {
	if (_Memory.CheckHandles() == 1) {
		BYTE weaponid = 0;

		_Memory.Read((DWORD*)(GTASA::API_GetCPEDPointer() + GTA_PLAYER_WEAPONID_ADDR), &weaponid, sizeof(weaponid));
		return GTASA::API_GetRealWeaponID((int)weaponid);
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerWeaponSlot()
 *
 * @author			Dreamer
 * @date			2014-07-05
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerWeaponSlot() {
	if (_Memory.CheckHandles() == 1) {
		int slot = 0;

		_Memory.Read((DWORD*)GTA_PLAYER_WEAPON_SLOT_ADDR, &slot, sizeof(slot));
		return slot;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetPlayerWeaponClipAmmo()
 *
 * @author			Grab
 * @date			2014-08-05
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetPlayerWeaponClipAmmo() {
	if (_Memory.CheckHandles() == 1) {
		DWORD buffer = NULL;
		DWORD offset = NULL;
		int ammo = 0;

		_Memory.Read((DWORD*)GTA_PLAYER_WEAPON_CLIP_AMMO_ADDR, &buffer, sizeof(buffer));
		switch (GTASA::API_GetPlayerWeaponID()) {
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

		_Memory.Read((DWORD*)(buffer + 0x5E0 + offset), &ammo, sizeof(ammo));
		return ammo;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInArea(float, float, float, float)
 *
 * @author			Slider
 * @date			2014-08-22
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInArea(float minx, float miny, float maxx, float maxy) {
	if (_Memory.CheckHandles() == 1) {
		float x = 0.0, y = 0.0, z = 0.0;
		GTASA::API_GetPlayerPos(x, y, z);

		if (x >= minx && x <= maxx && y >= miny && y <= maxy) {
			return 1;
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetCityName(char*&)
 *
 * @author			Slider
 * @date			2014-08-22
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetCityName(char*& cityname) {
	if (_Memory.CheckHandles() == 1) {
		float x = 0.0, y = 0.0, z = 0.0;
		GTASA::API_GetPlayerPos(x, y, z);

		for (int i = 0; i < MAX_CITIES; i++) {
			if ((double)x >= cities[i]._cityX1 && (double)y >= cities[i]._cityY1 && (double)z >= cities[i]._cityZ1 && (double)x <= cities[i]._cityX2 && (double)y <= cities[i]._cityY2 && (double)z <= cities[i]._cityZ2) {
				memcpy(cityname, cities[i]._cityname, sizeof(cities[i]._cityname));
				return 1;
			}
		}

		memcpy(cityname, "Unbekannt", 9);
		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetZoneName(char*&)
 *
 * @author			Slider
 * @date			2014-08-22
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetZoneName(char*& zonename) {
	if (_Memory.CheckHandles() == 1) {
		float x = 0.0, y = 0.0, z = 0.0;
		API_GetPlayerPos(x, y, z);

		for (int i = 0; i < MAX_ZONES; i++) {
			if ((double)x >= zones[i]._zoneX1 && (double)y >= zones[i]._zoneY1 && (double)z >= zones[i]._zoneZ1 && (double)x <= zones[i]._zoneX2 && (double)y <= zones[i]._zoneY2 && (double)z <= zones[i]._zoneZ2) {
				memcpy(zonename, zones[i]._zonename, sizeof(zones[i]._zonename));
				return 1;
			}
		}

		memcpy(zonename, "Unbekannt", 9);
		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetVehiclePointer()
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
DWORD GTASA::API_GetVehiclePointer() {
	if (_Memory.CheckHandles() == 1) {
		DWORD buffer = 0;
		_Memory.Read((DWORD*)GTA_VEHICLE_POINTER_ADDR, &buffer, sizeof(buffer));

		return buffer;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetVehicleHealth()
 *
 * @author			Slider
 * @date			2014-05-26
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetVehicleHealth() {
	if (_Memory.CheckHandles() == 1) {
		float health = 0.0;

		_Memory.Read((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_HEALTH_ADDR), &health, sizeof(health));
		return (int)health;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInAnyVehicle()
 *
 * @author			Slider
 * @date			2014-05-26
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInAnyVehicle() {
	if (_Memory.CheckHandles() == 1) {
		int value = 0;

		_Memory.Read((DWORD*)(API_GetCPEDPointer() + GTA_PLAYERSTATE_INCAR_ADDR), &value, sizeof(value));
		if (value == 50) {
			return 1;
		}
		
		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_VehicleSirenStateChange()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_VehicleSirenStateChange() {
	if (_Memory.CheckHandles() == 1) {
		BYTE value = 0;

		_Memory.Read((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_SIREN_STATE_ADDR), &value, sizeof(value));

		// on to off
		if ((int)value == 208) {
			value = 80;
			_Memory.Write((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_SIREN_STATE_ADDR), &value, sizeof(value));
		}
		// off to on
		else if ((int)value == 80) {
			value = 208;
			_Memory.Write((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_SIREN_STATE_ADDR), &value, sizeof(value));
		}

		return 1;

	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetVehicleSirenState()
 *
 * @author			Slider
 * @date			2014-07-05
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetVehicleSirenState() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			BYTE value;
			_Memory.Read((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_SIREN_STATE_ADDR), &value, sizeof(value));

			if ((int)value == 208) {
				return 1;
			}
			else if ((int)value == 80) {
				return 0;
			}
		}
		
		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetVehicleLockState()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetVehicleLockState() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			DWORD value;
			_Memory.Read((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_DOORSTATE_ADDR), &value, sizeof(value));

			if (value == 2) {
				return 1;
			}
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetVehicleEngineState()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetVehicleEngineState() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			BYTE value;
			_Memory.Read((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_ENGINESTATE_ADDR), &value, sizeof(value));

			if ((int)value == 24 || (int)value == 88) {
				return 1;
			}
			else if ((int)value == 8 || (int)value == 72) {
				return 0;
			}
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetVehicleLightState()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetVehicleLightState() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			DWORD value;
			_Memory.Read((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_LIGHTSTATE_ADDR), &value, sizeof(value));

			if ((int)value > 0) {
				return 1;
			}

			return 0;
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetVehicleModelID()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetVehicleModelID() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			short modelid;

			_Memory.Read((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_MODEL_ADDR), &modelid, sizeof(modelid));
			return (int)modelid;
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetVehicleType()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetVehicleType() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			int type = 0;
			BYTE value;

			_Memory.Read((DWORD*)(API_GetVehiclePointer() + GTA_VEHICLE_TYPE_ADDR), &value, sizeof(value));

			switch ((int)value) {
				// car/plane
				case 0:
				{
					type = 1;
					break;
				}

				// boat
				case 5:
				{
					type = 2;
					break;
				}

				// train
				case 6:
				{
					type = 3;
					break;
				}

				// bike/bicycle
				case 9:
				{
					type = 4;
					break;
				}
			}

			// car or plane?
			if (type == 1) {
				for (int i = 0; i < sizeof(AirplaneModels); i++) {
					if (AirplaneModels[i] == API_GetVehicleModelID()) {
						type = 5;
						break;
					}
				}
			}
			// bike or bicycle?
			else if (type == 4) {
				if (API_GetVehicleModelID() == 481 || API_GetVehicleModelID() == 509 || API_GetVehicleModelID() == 510) {
					type = 6;
				}
			}

			return type;
		}

		return 0;
	}
	
	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInACar()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInACar() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			if (API_GetVehicleType() == 1) {
				for (int i = 0; i < sizeof(AirplaneModels); i++) {
					if (AirplaneModels[i] == API_GetVehicleModelID()) {
						return 0;
					}
				}
			}

			return 1;
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInABoat()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInABoat() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			if (API_GetVehicleType() == 2) {
				return 1;
			}
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInATrain()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInATrain() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			if (API_GetVehicleType() == 3) {
				return 1;
			}
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInABike()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInABike() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			if (API_GetVehicleType() == 4) {
				return 1;
			}
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInAPlane()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInAPlane() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			if (API_GetVehicleType() == 5) {
				return 1;
			}
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_IsPlayerInABicycle()
 *
 * @author			Slider
 * @date			2014-08-23
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_IsPlayerInABicycle() {
	if (_Memory.CheckHandles() == 1) {
		if (API_IsPlayerInAnyVehicle()) {
			if (API_GetVehicleType() == 6) {
				return 1;
			}
		}

		return 0;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_GetRealWeaponID()
 *
 * @author			Slider
 * @date			2014-08-04
 * @category		GTA
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int GTASA::API_GetRealWeaponID(int weaponid) {
	switch (weaponid) {
		case 255: return 0; // Faust
		case 75: return 1; // Schlagring
		case 77: return 2; // Golfschläger
		case 78: return 3; // Schlagstock
		case 79: return 4; // Messer
		case 80: return 5; // Baseball Schläger
		case 81: return 6; // Baseball Schläger
		case 82: return 7; // Cue
		case 83: return 8; // Katana
		case 85: return 9; // Kettensäge
		case 65: return 10; // Double-End-Dildo
		case 66: return 11; // Dildo
		case 67: return 12; // Vibrator
		case 68: return 13; // Silberner Vibrator
		case 69: return 14; // Blumen
		case 70: return 15; // Stock
		case 86: return 16; // Granate
		case 87: return 17; // Tränengas
		case 88: return 18; // Molotow Cocktail
		case 90: return 22; // 9mm
		case 91: return 23; // 9mm Schalldämpfer
		case 92: return 24; // Desert Eagle
		case 93: return 25; // Shotgun
		case 94: return 26; // Abgesägte Schrotflinte
		case 95: return 27; // Combat Shotgun
		case 96: return 28; // Uzi
		case 97: return 29; // MP5
		case 99: return 30; // AK 47
		case 100: return 31; // M4
		case 116: return 32; // TEC 9
		case 101: return 33; // Rifle
		case 102: return 34; // Sniper
		case 103: return 35; // RPG
		case 104: return 36; // HS Rocket
		case 105: return 37; // Flammenwerfer
		case 106: return 38; // Minigun
		case 107: return 39; // Satchel Charge
		case 108: return 40; // Detonator
		case 109: return 41; // Spraycan
		case 110: return 42; // Feuerlöscher
		case 111: return 43; // Kamera
		case 112: return 44; // Nachtsichtgerät
		case 113: return 45; // Thermalsichtgerät
		case 115: return 46; // Fallschirm
	}

	return -1;
}