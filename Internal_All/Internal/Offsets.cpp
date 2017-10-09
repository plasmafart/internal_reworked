#pragma once

#include "..\MainInclude.h"

void COffsets::GrabOffsets()
{
	d3d9Device = **( DWORD** ) ( U::FindPattern( strenc( "shaderapidx9.dll" ), strenc( "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C" ) ) + 0x1 );
	dwCAM_Think = U::FindPattern( strenc( "client.dll" ), strenc( "85 C0 75 30 38 86" ) );
	LoadFromBufferEx = U::FindPattern( strenc( "Client.dll" ), strenc( "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04" ) );
	InitKeyValuesEx = U::FindPattern( strenc( "Client.dll" ), strenc( "55 8B EC 51 33 C0 C7 45 FC ? ? ? ? 56 8B F1" ) );
}

COffsets* Offsets = new COffsets;