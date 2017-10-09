#include "..\CheatInclude.h"

void CChams::Run( void * context, void * state, const ModelRenderInfo_t & info, matrix3x4_t * pCustomBoneToWorld )
{
	C_BasePlayer* pLocalPlayer = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	if ( !pLocalPlayer || !g_pEngine->IsInGame() || !info.pModel )
		return;


	std::string modelName = g_pVModelInfo->GetModelName( info.pModel );

	if ( Vars.Visuals.Chams.bEnabled && modelName.find( strenc( "models/player" ) ) != std::string::npos )
	{
		C_BasePlayer* pModelEntity = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( info.entity_index );
		if ( pModelEntity && pModelEntity->IsAlive() && !pModelEntity->IsDormant() )
		{
			Color render_color_hidden = !pModelEntity->IsEnemy() && Vars.Visuals.Chams.bTeamCheck ? Color( Vars.Visuals.Chams.Colors.flTeamHidden ) : Color( Vars.Visuals.Chams.Colors.flEnemyHidden );
			Color render_color_visible = !pModelEntity->IsEnemy() && Vars.Visuals.Chams.bTeamCheck ? Color( Vars.Visuals.Chams.Colors.flTeamVisible ) : Color( Vars.Visuals.Chams.Colors.flEnemyVisible );

			if ( Vars.Visuals.Chams.bXQZ && pModelEntity != pLocalPlayer )
			{
				ForceMaterial( T::matHidden, render_color_hidden );
				g_pVModelRender->DrawModelExecute( context, state, info, pCustomBoneToWorld );
			}

			T::matVisible->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
			ForceMaterial( T::matVisible, render_color_visible );
			g_pVModelRender->DrawModelExecute( context, state, info, pCustomBoneToWorld );
		}
	}


}

void CChams::ForceMaterial( IMaterial * material, Color color )
{
	if ( material != NULL )
	{
		g_pVRenderView->SetColorModulation( color.Base() );
		g_pVModelRender->ForcedMaterialOverride( material );
	}
}
