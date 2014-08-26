/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-08-26
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 *
 * This is the class for the interface functions
*/

#include "Interface.h"
#include "Memory.h"
#include <Windows.h>

extern Memory _Memory;

/**
 * int API_SetInterfaceHealthColor()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		Interface
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Interface::API_SetInterfaceHealthColor(int color) {
	if (_Memory.CheckHandles() == 1) {
		int r, g, b;
		ConvertHexToRGB(color, r, g, b);

		byte write[] = { r, g, b, 1 };

		_Memory.Write((DWORD*)INTERFACE_HEALTH_COLOR_ADDR, &write, sizeof(write));
		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_SetInterfaceMoneyColor()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		Interface
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Interface::API_SetInterfaceMoneyColor(int color) {
	if (_Memory.CheckHandles() == 1) {
		int r, g, b;
		ConvertHexToRGB(color, r, g, b);

		byte write[] = { r, g, b, 1 };
		_Memory.Write((DWORD*)INTERFACE_MONEY_COLOR_ADDR, &write, sizeof(write));

		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int API_SetInterfaceWantedLevelColor()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		Interface
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Interface::API_SetInterfaceWantedLevelColor(int color) {
	if (_Memory.CheckHandles() == 1) {
		int r, g, b;
		ConvertHexToRGB(color, r, g, b);

		byte write[] = { r, g, b, 1 };

		_Memory.Write((DWORD*)INTERFACE_WANTEDLEVEL_COLOR_ADDR, &write, sizeof(write));
		return 1;
	}

	return _Memory.CheckHandlesErrorCode;
}

/**
 * int ConvertHexToRGB()
 *
 * @author			Slider
 * @date			2014-05-31
 * @category		Interface
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
void Interface::ConvertHexToRGB(int hex, int &r, int &g, int &b) {
	 r = (hex & 0xFF0000) >> 16;
	 g = (hex & 0xFF00) >> 8;
	 b = hex & 0xFF;
}