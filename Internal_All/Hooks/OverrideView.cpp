#include "..\CheatInclude.h"
#include "..\Math.h"

OverrideViewFn oOverrideView;
void __stdcall g_hkOverrideView( CViewSetup* vsView )
{
	/*if ( g_pEngine->IsInGame() )
	{
		if ( Vars.Visuals.FovChanger && !G::LocalPlayer->InScope() )
			vsView->fov = Vars.Visuals.flFOV;

	}*/

	oOverrideView( vsView );
}