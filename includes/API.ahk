#Persistent
#NoEnv
     
hModule := DllCall("LoadLibrary", Str, A_ScriptDir . "\API.dll")
if (hModule == -1 || hModule == 0) {
	MsgBox, 16, API Fehler, Die API.dll konnte nicht gefunden werden.
    ExitApp
}

; SA:MP Functions
GetPlayerName_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerName")
SendChat_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_SendChat")
GetServerIP_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetServerIP")

; GTA Functions
GetPlayerHealth_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerHealth")
GetPlayerArmour_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerArmour")
GetPlayerPos_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerPos")
GetPlayerPosX_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerPosX")
GetPlayerPosY_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerPosY")
GetPlayerPosZ_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerPosZ")
IsPlayerInAnyInterior_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_IsPlayerInAnyInterior")
GetPlayerInteriorID_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetPlayerInteriorID")
IsPlayerInRangeOfPoint_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_IsPlayerInRangeOfPoint")
GetRadioStationID_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetRadioStationID")
GetRadioStationName_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetRadioStationName")

; Vehicle Functions
GetVehicleHealth_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetVehicleHealth")
IsPlayerInAnyVehicle_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_IsPlayerInAnyVehicle")
GetVehicleModelID_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetVehicleModelID")
VehicleSirenStateChange_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_VehicleSirenStateChange")
GetVehicleSirenState_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetVehicleSirenState")
GetGasPedalState_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetGasPedalState")
GetVehicleLockState_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetVehicleLockState")
GetVehicleEngineState_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetVehicleEngineState")

; Interface Functions
SetInterfaceHealthColor_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_SetInterfaceHealthColor")
SetInterfaceMoneyColor_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_SetInterfaceMoneyColor")
SetInterfaceWantedLevelColor_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_SetInterfaceWantedLevelColor")

; Random Shit Functions
GetVersion_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetVersion")
GetTimestamp_func := DllCall("GetProcAddress", UInt, hModule, Str, "API_GetTimestamp")

; SA:MP Functions
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

GetServerIP(ByRef ipAddress) {
	global GetServerIP_func
	VarSetCapacity(ipAddress, 15)
    Result := DllCall(GetServerIP_func, StrP, ipAddress)
    return Result
}

; GTA Functions
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

GetRadioStationID() {
	global GetRadioStationID_func
	Result := DllCall(GetRadioStationID_func)
	return Result
}

GetRadioStationName(ByRef name) {
	global GetRadioStationName_func
	VarSetCapacity(name, 20)
    Result := DllCall(GetRadioStationName_func, StrP, name)
    return Result
}

; Vehicle Functions
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

GetVehicleModelID() {
	global GetVehicleModelID_func
    Result := DllCall(GetVehicleModelID_func)
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

GetGasPedalState() {
	global GetGasPedalState_func
    Result := DllCall(GetGasPedalState_func)
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

; Interface Functions
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

; Random Shit Functions
GetVersion(ByRef version) {
	global GetVersion_func
	VarSetCapacity(version, 24)
    Result := DllCall(GetVersion_func, StrP, version)
	return Result
}

GetTimestamp() {
	global GetTimestamp_func
    Result := DllCall(GetTimestamp_func)
    return Result
}