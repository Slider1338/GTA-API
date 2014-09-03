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

#include <iostream>
#include <Windows.h>
#include <WinInet.h>
#include <ctime>
#include "Utilities.h"

using namespace std;

bool Utilities::DataCompare(const BYTE* OpCodes, const BYTE* Mask, const char* StrMask)
{
	//solange bis String zuende 
	while (*StrMask)
	{
		//wenn Byte ungleich --> false 
		if (*StrMask == 'x' && *OpCodes != *Mask)
			return false;

		++StrMask;
		++OpCodes;
		++Mask;
	}

	return true;  //wenn alle Bytes gleich 
}

DWORD Utilities::FindPattern(DWORD StartAddress, DWORD CodeLen, BYTE* Mask, char* StrMask, unsigned short ignore)
{
	unsigned short Ign = 0;
	DWORD i = 0;

	while (Ign <= ignore)
	{
		if (DataCompare((BYTE*)(StartAddress + i++), Mask, StrMask))
			++Ign;

		else if (i >= CodeLen)
			return 0;
	}

	return StartAddress + i - 1;
}

/**
 * int API_IsUpdateAvailable()
 *
 * @author			Slider
 * @date			2014-08-22
 * @category		Utilities
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Utilities::API_IsAPIUpdateAvailable() {
	if ((lastUpdateCheck + NEXT_UPDATE_CHECK) < GetTickCount()) {
		string response;
		char buffer[1024];
		BOOL bKeepReading = true;
		DWORD dwBytesRead = -1;
		const char* parrAcceptTypes[] = { "text/*", NULL };

		// connection
		HINTERNET hInternet = InternetOpen("SAMP API", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		HINTERNET hConnect = InternetConnect(hInternet, UPDATE_SERVER_ADDR, 80, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
		HINTERNET hRequest = HttpOpenRequest(hConnect, "GET", "/index.php", NULL, NULL, parrAcceptTypes, 0, 0);
		HttpSendRequest(hRequest, NULL, 0, NULL, 0);

		// read
		while (bKeepReading && dwBytesRead != 0) {
			bKeepReading = InternetReadFile(hRequest, buffer, sizeof(buffer), &dwBytesRead);
			response.append(buffer, dwBytesRead);
		}

		// close
		InternetCloseHandle(hRequest);
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hInternet);

		// set last checktime
		lastUpdateCheck = GetTickCount();

		// is update available?
		if (API_VERSION != response) {
			updateAvailable = 1;
		}
		else {
			updateAvailable = 0;
		}
	}

	return updateAvailable;
}

/**
 * int API_GetVersion()
 *
 * @author			Slider
 * @date			2014-08-04
 * @category		Utilities
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Utilities::API_GetAPIVersion(char *&version) {
	memcpy(version, API_VERSION, sizeof(API_VERSION));
	return 1;
}

/**
 * int API_GetTimestamp()
 *
 * @author			Slider
 * @date			2014-05-29
 * @category		Utilities
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Utilities::API_GetTimestamp() {
	return (int)time(0);
}

/**
 * int API_GetAPIRuntime()
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		Utilities
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int Utilities::API_GetAPIRuntime() {
	return GetTickCount();
}