#include "..\MainInclude.h"
#include "..\Math.h"
#include "..\Globals.h"



void CHook::HooksInit()
{
	g_phkVPanel = new VMTHook( ( DWORD** ) g_pVPanel );
	g_phkClient = new VMTHook( ( DWORD** ) g_pClient );
	g_phkClientMode = new VMTHook( ( DWORD** ) g_pClientMode );
	g_phkD3D9 = new VMTHook( ( DWORD** ) Offsets->d3d9Device );
	g_phkVModelRender = new VMTHook( ( DWORD** ) g_pVModelRender );
	g_phkMaterialSystem = new VMTHook( ( DWORD** ) g_pMaterialSystem );

	ConVar* sv_cheats_cvar = g_pCvar->FindVar( "sv_cheats" );
	g_phkSvCheats = new VMTHook( ( DWORD** ) sv_cheats_cvar );

	RecvProp* sequence_prop = C_BaseViewModel::GetSequenceProp();
	g_phkSequence = new RecvPropHook( sequence_prop, g_hkSequence );

	oFrameStageNotify = ( FrameStageNotifyFn ) Hook->g_phkClient->HookFunction( ( DWORD ) g_hkFrameStageNotify, 36 );
	oReset = ( ResetFn ) Hook->g_phkD3D9->HookFunction( ( DWORD ) g_hkReset, 16 );
	oEndScene = ( EndSceneFn ) Hook->g_phkD3D9->HookFunction( ( DWORD ) g_hkEndScene, 42 );
	oOverrideView = ( OverrideViewFn ) Hook->g_phkClientMode->HookFunction( ( DWORD ) g_hkOverrideView, 18 );
	oSvCheatsGetBool = ( SvCheatsGetBoolFn ) Hook->g_phkSvCheats->HookFunction( ( DWORD ) g_hkSvCheatsGetBool, 13 );
	oPaintTraverse = ( PaintTraverseFn ) Hook->g_phkVPanel->HookFunction( ( DWORD ) g_hkPaintTraverse, 41 );
	oCreateMove = ( CreateMoveFn ) Hook->g_phkClientMode->HookFunction( ( DWORD ) g_hkCreateMove, 24 );
	oDrawModelExecute = ( DrawModelExecuteFn ) g_phkVModelRender->HookFunction( ( DWORD ) g_hkDrawModelExecute, 21 );
	oOverrideConfig = ( OverrideConfigFn ) g_phkMaterialSystem->HookFunction( ( DWORD ) g_hkOverrideConfig, 21 );
}

void CHook::HooksUnhook()
{
	ImGui_ImplDX9_Shutdown();
	SetWindowLongPtr( G::Window, GWL_WNDPROC, ( LONG_PTR ) oWndProc );

	Hook->g_phkClient->UnHook();
	Hook->g_phkClientMode->UnHook();
	Hook->g_phkD3D9->UnHook();
	Hook->g_phkVModelRender->UnHook();

	Hook->g_phkSvCheats->UnHook();

	delete g_phkClient;
	delete g_phkD3D9;

	delete g_phkSequence;

	delete F::Misc;
	delete F::SkinChanger;
	delete F::Thirdperson;
	delete F::Visuals;
}

CHook* Hook = new CHook;


