#Persistent
#NoEnv
     
hModule := DllCall("LoadLibrary", Str, A_ScriptDir . "\API.dll")
if (hModule == -1 || hModule == 0) {
	MsgBox, 16, API Fehler, Die API.dll konnte nicht gefunden werden.
    ExitApp
}

; SA:MP
GetServerName_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetServerName")
GetServerIP_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetServerIP")
CountOnlinePlayers_func := DllCall("GetProcAddress", UInt, hModule, Str, "CountOnlinePlayers")
GetPlayerName_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerName")
GetPlayerID_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerID")
GetPlayerScore_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerScore")
GetPlayerPing_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerPing_func")
IsPlayerConnected_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerConnected")
GetPlayerNameByID_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerNameByID")
GetPlayerScoreByID_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerScoreByID")
GetPlayerPingByID_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerPingByID")
SendChat_func := DllCall("GetProcAddress", UInt, hModule, Str, "SendChat")
AddChatMessage_func := DllCall("GetProcAddress", UInt, hModule, Str, "AddChatMessage")
ShowDialog_func := DllCall("GetProcAddress", UInt, hModule, Str, "ShowDialog")
GetChatLine_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetChatLine")
IsInChat_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsInChat")

; GTA
GetPlayerMoney_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerMoney")
GetPlayerHealth_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerHealth")
GetPlayerArmour_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerArmour")
GetPlayerPos_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerPos")
GetPlayerPosX_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerPosX")
GetPlayerPosY_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerPosY")
GetPlayerPosZ_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerPosZ")
IsPlayerInAnyInterior_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInAnyInterior")
GetPlayerInteriorID_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerInteriorID")
IsPlayerInRangeOfPoint_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInRangeOfPoint")
GetPlayerWeaponID_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerWeaponID")
GetPlayerWeaponSlot_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerWeaponSlot")
GetPlayerWeaponClipAmmo_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetPlayerWeaponClipAmmo")
IsPlayerInArea_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInArea")
GetCityName_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetCityName")
GetZoneName_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetZoneName")
GetWeaponName_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetWeaponName")
GetVehicleHealth_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetVehicleHealth")
IsPlayerInAnyVehicle_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInAnyVehicle")
VehicleSirenStateChange_func := DllCall("GetProcAddress", UInt, hModule, Str, "VehicleSirenStateChange")
GetVehicleSirenState_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetVehicleSirenState")
GetVehicleLockState_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetVehicleLockState")
GetVehicleEngineState_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetVehicleEngineState")
GetVehicleLightState_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetVehicleLightState")
GetVehicleModelID_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetVehicleModelID")
GetVehicleType_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetVehicleType")
IsPlayerInACar_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInACar")
IsPlayerInABoat_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInABoat")
IsPlayerInATrain_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInATrain")
IsPlayerInABike_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInABike")
IsPlayerInAPlane_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInAPlane")
IsPlayerInABicycle_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsPlayerInABicycle")

; Interface
SetInterfaceHealthColor_func := DllCall("GetProcAddress", UInt, hModule, Str, "SetInterfaceHealthColor")
SetInterfaceMoneyColor_func := DllCall("GetProcAddress", UInt, hModule, Str, "SetInterfaceMoneyColor")
SetInterfaceWantedLevelColor_func := DllCall("GetProcAddress", UInt, hModule, Str, "SetInterfaceWantedLevelColor")

; Randomshit
IsAPIUpdateAvailable_func := DllCall("GetProcAddress", UInt, hModule, Str, "IsAPIUpdateAvailable")
GetAPIVersion_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetAPIVersion")
GetTimestamp_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetTimestamp")
GetAPIRuntime_func := DllCall("GetProcAddress", UInt, hModule, Str, "GetAPIRuntime")

; SA:MP
GetServerName(ByRef servername) {
	global GetServerName_func
	VarSetCapacity(servername, 15)
    Result := DllCall(GetServerName_func, StrP, servername)
    return Result
}

GetServerIP(ByRef ipAddress) {
	global GetServerIP_func
	VarSetCapacity(ipAddress, 15)
    Result := DllCall(GetServerIP_func, StrP, ipAddress)
    return Result
}

CountOnlinePlayers() {
	global CountOnlinePlayers_func
    Result := DllCall(CountOnlinePlayers_func)
    return Result
}

GetPlayerName(ByRef name) {
	global GetPlayerName_func
	VarSetCapacity(name, 24)
    Result := DllCall(GetPlayerName_func, StrP, name)
    return Result
}

GetPlayerID() {
	global GetPlayerID_func
    Result := DllCall(GetPlayerID_func)
    return Result
}

GetPlayerScore() {
	global GetPlayerScore_func
    Result := DllCall(GetPlayerScore_func)
    return Result
}

GetPlayerPing() {
	global GetPlayerPing_func
    Result := DllCall(GetPlayerPing_func)
    return Result
}

IsPlayerConnected(playerid) {
	global IsPlayerConnected_func
    Result := DllCall(IsPlayerConnected_func, Int, playerid)
    return Result
}

GetPlayerNameByID(playerid, ByRef name) {
	global GetPlayerNameByID_func
	VarSetCapacity(name, 24)
    Result := DllCall(GetPlayerNameByID_func, Int, playerid, StrP, name)
    return Result
}

GetPlayerScoreByID(playerid) {
	global GetPlayerScoreByID_func
    Result := DllCall(GetPlayerScoreByID_func, Int, playerid)
    return Result
}

GetPlayerPingByID(playerid) {
	global GetPlayerPingByID_func
    Result := DllCall(GetPlayerPingByID_func, Int, playerid)
    return Result
}

SendChat(text) {
	global SendChat_func
    Result := DllCall(SendChat_func, Str, text)
    return Result
}

AddChatMessage(text) {
	global AddChatMessage_func
    Result := DllCall(AddChatMessage_func, Str, text)
    return Result
}

ShowDialog(style, caption, info, button) {
	global ShowDialog_func
    Result := DllCall(ShowDialog_func, Int, style, Str, caption, Str, info, Str, button)
    return Result
}

GetChatLine(line, ByRef content) {
	global GetChatLine_func
	VarSetCapacity(content, 256)
    Result := DllCall(GetChatLine_func, Int, line, StrP, content)
    return Result
}

IsInChat() {
	global IsInChat_func
    Result := DllCall(IsInChat_func)
    return Result
}

; GTA
GetPlayerMoney() {
	global GetPlayerMoney_func
    Result := DllCall(GetPlayerMoney_func)
    return Result
}

GetPlayerHealth() {
	global GetPlayerHealth_func
    Result := DllCall(GetPlayerHealth_func)
    return Result
}
     
GetPlayerArmour() {
	global GetPlayerArmour_func
	Result := DllCall(GetPlayerArmour_func)
	return Result
}
     
GetPlayerPos(ByRef x, ByRef y, ByRef z) {
	global GetPlayerPos_func
	Result := DllCall(GetPlayerPos_func, FloatP, x, FloatP, y, FloatP, z)
	return Result
}

GetPlayerPosX(ByRef position) {
	global GetPlayerPosX_func
	Result := DllCall(GetPlayerPosX_func, FloatP, position)
	return Result
}

GetPlayerPosY(ByRef position) {
	global GetPlayerPosY_func
	Result := DllCall(GetPlayerPosY_func, FloatP, position)
	return Result
}

GetPlayerPosZ(ByRef position) {
	global GetPlayerPosZ_func
	Result := DllCall(GetPlayerPosZ_func, FloatP, position)
	return Result
}

IsPlayerInAnyInterior() {
	global IsPlayerInAnyInterior_func
	Result := DllCall(IsPlayerInAnyInterior_func)
	return Result
}

GetPlayerInteriorID() {
	global GetPlayerInteriorID_func
	Result := DllCall(GetPlayerInteriorID_func)
	return Result
}

IsPlayerInRangeOfPoint(radius, x, y, z) {
	global IsPlayerInRangeOfPoint_func
	Result := DllCall(IsPlayerInRangeOfPoint_func, Float, radius, Float, x, Float, y, Float, z)
	return Result
}

GetPlayerWeaponID() {
	global GetPlayerWeaponID_func
	Result := DllCall(GetPlayerWeaponID_func, Float, x, Float, y, Float, z, Float, radius)
	return Result
}

GetPlayerWeaponSlot() {
	global GetPlayerWeaponSlot_func
	Result := DllCall(GetPlayerWeaponSlot_func, Float, x, Float, y, Float, z, Float, radius)
	return Result
}

GetPlayerWeaponClipAmmo() {
	global GetPlayerWeaponClipAmmo_func
	Result := DllCall(GetPlayerWeaponClipAmmo_func)
	return Result
}

GetWeaponName(weaponid, ByRef weaponname) {
	global GetWeaponName_func
	VarSetCapacity(weaponname, 25)
    Result := DllCall(GetWeaponName_func, Int, weaponid, StrP, weaponname)
    return Result
}

IsPlayerInArea(x1, y1, x2, y2) {
	global IsPlayerInArea_func
    Result := DllCall(IsPlayerInArea_func, Float, x1, Float, y1, Float, x2, Float, y2)
    return Result
}

GetCityName(ByRef city) {
	global GetCityName_func
	VarSetCapacity(city, 20)
    Result := DllCall(GetCityName_func, StrP, city)
    return Result
}

GetZoneName(ByRef zone) {
	global GetZoneName_func
	VarSetCapacity(zone, 40)
    Result := DllCall(GetZoneName_func, StrP, zone)
    return Result
}

GetVehicleHealth() {
	global GetVehicleHealth_func
    Result := DllCall(GetVehicleHealth_func)
    return Result
}

IsPlayerInAnyVehicle() {
	global IsPlayerInAnyVehicle_func
    Result := DllCall(IsPlayerInAnyVehicle_func)
    return Result
}

VehicleSirenStateChange() {
	global VehicleSirenStateChange_func
    Result := DllCall(VehicleSirenStateChange_func)
    return Result
}

GetVehicleSirenState() {
	global GetVehicleSirenState_func
    Result := DllCall(GetVehicleSirenState_func)
    return Result
}

GetVehicleLockState() {
	global GetVehicleLockState_func
    Result := DllCall(GetVehicleLockState_func)
    return Result
}

GetVehicleEngineState() {
	global GetVehicleEngineState_func
    Result := DllCall(GetVehicleEngineState_func)
    return Result
}

GetVehicleLightState() {
	global GetVehicleLightState_func
    Result := DllCall(GetVehicleLightState_func)
    return Result
}

GetVehicleModelID() {
	global GetVehicleModelID_func
    Result := DllCall(GetVehicleModelID_func)
    return Result
}

GetVehicleType() {
	global GetVehicleLightState_func
    Result := DllCall(GetVehicleLightState_func)
    return Result
}

IsPlayerInACar() {
	global IsPlayerInACar_func
    Result := DllCall(IsPlayerInACar_func)
    return Result
}

IsPlayerInABoat() {
	global IsPlayerInABoat_func
    Result := DllCall(IsPlayerInABoat_func)
    return Result
}

IsPlayerInATrain() {
	global IsPlayerInATrain_func
    Result := DllCall(IsPlayerInATrain_func)
    return Result
}

IsPlayerInABike() {
	global IsPlayerInABike_func
    Result := DllCall(IsPlayerInABike_func)
    return Result
}

IsPlayerInAPlane() {
	global IsPlayerInAPlane_func
    Result := DllCall(IsPlayerInAPlane_func)
    return Result
}

IsPlayerInABicycle() {
	global IsPlayerInABicycle_func
    Result := DllCall(IsPlayerInABicycle_func)
    return Result
}

; Interface
SetInterfaceHealthColor(color) {
	global SetInterfaceHealthColor_func
    Result := DllCall(SetInterfaceHealthColor_func, Int, color)
    return Result
}

SetInterfaceMoneyColor(color) {
	global SetInterfaceMoneyColor_func
    Result := DllCall(SetInterfaceMoneyColor_func, Int, color)
    return Result
}

SetInterfaceWantedLevelColor(color) {
	global SetInterfaceWantedLevelColor_func
    Result := DllCall(SetInterfaceWantedLevelColor_func, Int, color)
    return Result
}

; Utilities
IsAPIUpdateAvailable() {
	global IsAPIUpdateAvailable_func
    Result := DllCall(IsAPIUpdateAvailable_func)
    return Result
}

GetAPIVersion(ByRef version) {
	global GetAPIVersion_func
	VarSetCapacity(version, 15)
    Result := DllCall(GetAPIVersion_func, StrP, version)
    return Result
}

GetTimestamp() {
	global GetTimestamp_func
    Result := DllCall(GetTimestamp_func)
    return Result
}

GetAPIRuntime() {
	global GetAPIRuntime_func
    Result := DllCall(GetAPIRuntime_func)
    return Result	
}