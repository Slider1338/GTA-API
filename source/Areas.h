/**
 * GTA API by Slider (c) www.gta-api.de
 *
 * @author				Slider
 * @date				2014-08-25
 * @copyright			(c) by Slider - www.gta-api.de
 * @license				General Public License <https://www.gnu.org/licenses/gpl>
 *
 * this class contains all informations about the cityies & zones in GTA SA
 */

#pragma once

#define MAX_CITYNAME_LENGTH 20
#define MAX_ZONENAME_LENGTH 40
#define MAX_CITIES 10
#define MAX_ZONES 377

// citys
struct GTACities {
	char _cityname[MAX_CITYNAME_LENGTH];
	double _cityX1;
	double _cityY1;
	double _cityZ1;
	double _cityX2;
	double _cityY2;
	double _cityZ2;
	int _cityused;
};

// zones
struct GTAZones {
	char _zonename[MAX_ZONENAME_LENGTH];
	double _zoneX1;
	double _zoneY1;
	double _zoneZ1;
	double _zoneX2;
	double _zoneY2;
	double _zoneZ2;
	int _zoneused;
};

extern struct GTACities cities[MAX_CITIES];
extern struct GTAZones zones[MAX_ZONES];

class Cities {
public:
	void LoadCities();
	void AddCity(char*, double, double, double, double, double, double);
};

class Zones {
public:
	void LoadZones();
	void AddZone(char*, double, double, double, double, double, double);
};