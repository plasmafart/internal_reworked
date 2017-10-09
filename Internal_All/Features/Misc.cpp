#include "..\CheatInclude.h"

void CMisc::FixPositionInaccuracy( ClientFrameStage_t stage )
{
	if ( stage != FRAME_RENDER_START )
		return;

	if ( !g_pEngine->IsInGame() )
		return;

	C_BasePlayer* pLocalPlayer = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );

	if ( !pLocalPlayer->IsAlive() )
		return;

	for ( int i = 1; i <= g_pGlobalVarsBase->maxClients; i++ )
	{
		if ( i == g_pEngine->GetLocalPlayer() )
			continue;

		C_BasePlayer* pPlayer = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( i );

		if ( !pPlayer )
			continue;

		*( int* ) ( ( uintptr_t ) pPlayer + 0xA30 ) = g_pGlobalVarsBase->framecount;	//skip occlusion checks
		*( int* ) ( ( uintptr_t ) pPlayer + 0xA28 ) = 0;								//clear occlusion flags
	}

}

void CMisc::Radar()
{
	if ( !Vars.Other.bRadar )
		return;

	for ( int i = 1; i <= g_pGlobalVarsBase->maxClients; i++ )
	{
		if ( i == g_pEngine->GetLocalPlayer() )
			continue;

		C_BasePlayer* pPlayer = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( i );

		if ( !pPlayer )
			continue;

		pPlayer->GetSpotted() = true;
	}
}

bool CMisc::FinishHalftimeFix( CUserCmd * cmd )
{
	C_BasePlayer* pLocalPlayer = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );

	if ( pLocalPlayer && pLocalPlayer->GetFlags() & FL_FROZEN )
	{
		// Don't stomp the first time we get frozen
		if ( m_bWasFrozen )
		{
			// Stomp the new viewangles with old ones
			cmd->viewangles = m_oldangles;
			return true;
		}
		else
		{
			m_bWasFrozen = true;
		}
	}
	else
	{
		m_bWasFrozen = false;
	}

	return false;
}

void CMisc::SetupHalftimeFix( CUserCmd * cmd )
{
	m_oldangles = cmd->viewangles;
}
