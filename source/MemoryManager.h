/**
* GTA API by Slider (c) www.gta-api.de
*
* @author				Slider
* @date					2014-05-09
* @copyright			(c) by Slider - www.gta-api.de
* @license				General Public License <https://www.gnu.org/licenses/gpl>
*/

// includes
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <Windows.h>

// namespaces
using namespace std;

// prototypes
DWORD GetGTAProcessID();
DWORD GetSAMPBaseAddress();