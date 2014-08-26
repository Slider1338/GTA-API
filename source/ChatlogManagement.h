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

#pragma once

#include <iostream>
#include <string>
#include <vector>

#define MAX_CHATLINES 300

using namespace std;

struct ChatLines {
	char _chatline[256];
};

extern struct ChatLines chatlines[MAX_CHATLINES];

class ChatlogManagement {
public:
	// variables
	char chatlogPath[350];
	int chatlogSize = 0;
	vector<string> chatlog;

	// prototypes
	void CreateChatlogPath();
	void LoadChatlogs();
	int API_GetChatLine(int line, char *&content);
};