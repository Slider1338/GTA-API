/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-08-26
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 *
 * This is a class with some useful functions
*/

#pragma once

#define API_VERSION "1.0.0 RC1"
#define UPDATE_SERVER_ADDR "update.gta-api.de"
#define NEXT_UPDATE_CHECK 300000

class Utilities {
public:
	int lastUpdateCheck = 0;
	int updateAvailable = 0;

	bool DataCompare(const BYTE* OpCodes, const BYTE* Mask, const char* StrMask);
	DWORD FindPattern(DWORD StartAddress, DWORD CodeLen, BYTE* Mask, char* StrMask, unsigned short ignore);
	int API_IsAPIUpdateAvailable();
	int API_GetAPIVersion(char *&version);
	int API_GetTimestamp();
	int API_GetAPIRuntime();
};