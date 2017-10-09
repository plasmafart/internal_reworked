#include "..\CheatInclude.h"

DrawModelExecuteFn oDrawModelExecute;

void __stdcall g_hkDrawModelExecute( void* context, void* state, const ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld )
{
	Hook->g_phkVModelRender->UnHook();

	F::Chams->Run( context, state, info, pCustomBoneToWorld );

	g_pVModelRender->DrawModelExecute( context, state, info, pCustomBoneToWorld );
	g_pVModelRender->ForcedMaterialOverride( NULL );
	Hook->g_phkVModelRender->ReHook();
}