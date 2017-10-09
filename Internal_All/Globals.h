#pragma once

#include "CheatInclude.h"
#include "Features\Features.h"
#include <unordered_map>

namespace G
{
	extern HMODULE		Dll;
	extern HWND			Window;
	extern bool			PressedKeys[ 256 ];
	extern bool			d3dinit;
}

namespace F
{
	extern CSkinChanger*	SkinChanger;
	extern CVisuals*		Visuals;
	extern CThirdperson*	Thirdperson;
	extern CMisc*			Misc;
	extern CChams*			Chams;
	extern CMaterialConfig*	MaterialConfig;
}

namespace T
{
	extern IMaterial*		matVisible;
	extern IMaterial*		matHidden;
}


