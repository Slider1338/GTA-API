/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-08-26
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 *
 * This class contains all chatlog functions
*/

#include <Windows.h>
#include <Shlobj.h>
#include <fstream>
#include "ChatlogManagement.h"
#include "Memory.h"

extern Memory _Memory;

struct ChatLines chatlines[MAX_CHATLINES];

/**
 * void CreateChatlogPath()
 *
 * @author			Slider
 * @date			2014-08-26
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
void ChatlogManagement::CreateChatlogPath() {
	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, chatlogPath);
	strcat_s(chatlogPath, "\\GTA San Andreas User Files\\SAMP\\chatlog.txt");
}

/**
 * void LoadChatLogs()
 *
 * @author			Slider
 * @date			2014-08-22
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
void ChatlogManagement::LoadChatlogs() {
	ifstream filesize(ChatlogManagement::chatlogPath, ifstream::ate | ifstream::binary);
	if (filesize.is_open()) {
		ChatlogManagement::chatlogSize = (int)filesize.tellg();
		filesize.close();
	}

	ifstream file(ChatlogManagement::chatlogPath);
	if (file.is_open()) {
		string _line;
		while (getline(file, _line)) {
			_line = _line.substr(11);
			ChatlogManagement::chatlog.push_back(_line);
		}
		
		reverse(ChatlogManagement::chatlog.begin(), ChatlogManagement::chatlog.end());
		file.close();
	}
}

/**
 * int API_GetChatLine(int, char*&)
 *
 * @author			Slider
 * @date			2014-08-22
 * @category		SA:MP
 * @license			General Public License <https://www.gnu.org/licenses/gpl>
 */
int ChatlogManagement::API_GetChatLine(int line, char *&content) {
	if (_Memory.CheckHandles() == 1) {
		char _tmpchar[256];
		int _tmpsize;

		ifstream filesize(chatlogPath, ifstream::ate | ifstream::binary);
		if (filesize.is_open()) {
			_tmpsize = (int)filesize.tellg();
			filesize.close();
		}

		ifstream file(chatlogPath);
		if (file.is_open()) {
			if (_tmpsize != chatlogSize) {
				file.seekg(chatlogSize, ios_base::beg);

				string _line;
				while (getline(file, _line)) {
					_line = _line.substr(11);
					chatlog.insert(chatlog.begin(), _line);
				}
			}

			file.close();

			chatlogSize = _tmpsize;

			sprintf_s(_tmpchar, "%s", chatlog[line]);
			memcpy(content, _tmpchar, sizeof(_tmpchar));

			return 1;
		}
	}

	return _Memory.CheckHandlesErrorCode;
}