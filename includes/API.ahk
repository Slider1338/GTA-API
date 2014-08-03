#Persistent
#NoEnv
     
hModule := DllCall("LoadLibrary", Str, A_ScriptDir . "\API.dll")
if (hModule == -1 || hModule == 0) {
	MsgBox, 16, API Fehler, Die API.dll konnte nicht gefunden werden.
    ExitApp
}

; SA:MP
GetServerIP_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetServerIP")
GetPlayerName_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerName")
SendChat_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_SendChat")

; GTA
GetPlayerHealth_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerHealth")
GetPlayerArmour_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerArmour")
GetPlayerPos_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerPos")
GetPlayerPosX_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerPosX")
GetPlayerPosY_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerPosY")
GetPlayerPosZ_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerPosZ")
IsPlayerInAnyInterior_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_IsPlayerInAnyInterior")
GetPlayerInteriorID_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerInteriorID")
IsPlayerInRangeOfPoint_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_IsPlayerInRangeOfPoint")
GetPlayerWeaponID_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerWeaponID")
GetPlayerWeaponSlot_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerWeaponSlot")
GetVehicleHealth_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetVehicleHealth")
IsPlayerInAnyVehicle_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_IsPlayerInAnyVehicle")
VehicleSirenStateChange_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_VehicleSirenStateChange")
GetVehicleSirenState_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetVehicleSirenState")

; Interface
SetInterfaceHealthColor_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_SetInterfaceHealthColor")
SetInterfaceMoneyColor_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_SetInterfaceMoneyColor")
SetInterfaceWantedLevelColor_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_SetInterfaceWantedLevelColor")

; Randomshit
GetTimestamp_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetTimestamp")

; SA:MP
GetServerIP(ByRef ipAddress) {
	global GetServerIP_func
	VarSetCapacity(ipAddress, 15)
    Result := DllCall(GetServerIP_func, StrP, ipAddress)
    return Result
}

GetPlayerName(ByRef name) {
	global GetPlayerName_func
	VarSetCapacity(name, 24)
    Result := DllCall(GetPlayerName_func, StrP, name)
    return Result
}

SendChat(text) {
	global SendChat_func
    Result := DllCall(SendChat_func, Str, text)
    return Result
}

; GTA
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

IsPlayerInRangeOfPoint(x, y, z, radius) {
	global IsPlayerInRangeOfPoint_func
	Result := DllCall(IsPlayerInRangeOfPoint_func, Float, x, Float, y, Float, z, Float, radius)
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

; Randomshit
GetTimestamp() {
	global GetTimestamp_func
    Result := DllCall(GetTimestamp_func)
    return Result
}