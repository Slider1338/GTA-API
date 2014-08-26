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

#pragma once

#define INTERFACE_HEALTH_COLOR_ADDR 0xBAB22C
#define INTERFACE_MONEY_COLOR_ADDR 0xBAB230
#define INTERFACE_WANTEDLEVEL_COLOR_ADDR 0xBAB244

class Interface {
public:
	int API_SetInterfaceHealthColor(int color);
	int API_SetInterfaceMoneyColor(int color);
	int API_SetInterfaceWantedLevelColor(int color);
	void ConvertHexToRGB(int hex, int &r, int &g, int &b);
};