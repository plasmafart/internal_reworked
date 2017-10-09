#include "..\CheatInclude.h"

void CThirdperson::Run( ClientFrameStage_t stage )
{
	if ( stage != FRAME_RENDER_START )
		return;

	if ( !g_pEngine->IsInGame() )
		return;

	C_BasePlayer* pLocalPlayer = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	if ( !pLocalPlayer )
		return;

	static QAngle viewAngles;
	g_pEngine->GetViewAngles( viewAngles );

	if ( Vars.Other.bThirdperson && pLocalPlayer->IsAlive() )
	{
		g_pInput->m_fCameraInThirdPerson = true;
		g_pInput->m_vecCameraOffset = Vector( viewAngles.x, viewAngles.y, Vars.Other.flThirdpersonDist );
	}
	else
	{
		if ( g_pInput->m_fCameraInThirdPerson )
		{
			g_pInput->m_fCameraInThirdPerson = false;
			g_pInput->m_vecCameraOffset = Vector( viewAngles.x, viewAngles.y, 20.f );
		}
	}
}