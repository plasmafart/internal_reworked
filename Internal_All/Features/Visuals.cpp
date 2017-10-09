#include "..\CheatInclude.h"

void CVisuals::Run()
{
	if ( !g_pEngine->IsInGame() )
	{
		flHurtTime = 0.f; // for hitmarker
		return;
	}

	for ( int i = 0; i < g_pClientEntList->GetHighestEntityIndex(); i++ )
	{
		PlayerESP( i );
	}

	ThirdpersonScope();

	Hitmarker();
}

void CVisuals::SetHurtTime( float ht )
{
	flHurtTime = ht;
}

void CVisuals::PlayerESP( int index )
{
	if ( !Vars.Visuals.PlayerEsp.bEnabled )
		return;

	if ( index == g_pEngine->GetLocalPlayer() )
		return;

	C_BasePlayer* pLocalPlayer = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	C_BasePlayer* pPlayer = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( index );

	if ( !pPlayer || !pLocalPlayer )
		return;

	int iClassID = pPlayer->GetClientClass()->m_ClassID;

	if ( iClassID != 83 && iClassID != 35 )
		return;

	if ( pPlayer->IsDormant() || !pPlayer->IsAlive() )
		return;

	Vector max = pPlayer->GetCollideable()->OBBMaxs();

	Vector pos, pos3D;
	Vector top, top3D;
	pos3D = pPlayer->GetOrigin();
	top3D = pos3D + Vector( 0, 0, max.z );
	if ( !D::WorldToScreen( pos3D, pos ) || !D::WorldToScreen( top3D, top ) )
		return;
	float height = ( pos.y - top.y );
	float width = height / 4.f;


	if ( iClassID == 83 )
	{
		D::DrawString( Font::ESP, top.x, top.y + 3, Color::White(), FONT_CENTER, charenc( "Hostage" ) );
		return;
	}


	if ( Vars.Visuals.PlayerEsp.bSkeleton )
		Skeleton( pPlayer, Vars.Visuals.PlayerEsp.Colors.flTeamBones, Vars.Visuals.PlayerEsp.Colors.flEnemyBones );


	if ( Vars.Visuals.PlayerEsp.bBox )
		D::CornerBox( top.x, top.y, width, height, false, !pPlayer->IsEnemy() && Vars.Visuals.PlayerEsp.bTeamCheck ? Vars.Visuals.PlayerEsp.Colors.flTeamBoxes : Vars.Visuals.PlayerEsp.Colors.flEnemyBoxes, Color::Black() );

	D::DrawString( Font::ESP, top.x, top.y - 6, Color::White(), FONT_CENTER, "%s", pPlayer->GetName().c_str() );

	HealthBar( pos, top, pPlayer->GetHealth() );

	int bottom = 0;

	D::DrawString( Font::ESP, top.x, top.y + height + 8 + ( 10 * bottom++ ), Color::White(), FONT_CENTER, "%s", pPlayer->GetActiveWeapon()->GetWeaponName().c_str() );

}


void CVisuals::Skeleton( C_BasePlayer *pPlayer, Color color_team, Color color_enemy )
{
	studiohdr_t* pStudioModel = g_pVModelInfo->GetStudioModel( pPlayer->GetModel() );
	if ( !pStudioModel )
		return;

	static matrix3x4_t pBoneToWorldOut[ 128 ];
	if ( !pPlayer->SetupBones( pBoneToWorldOut, 128, 256, g_pGlobalVarsBase->curtime ) )
		return;

	for ( int i = 0; i < pStudioModel->numbones; i++ )
	{
		mstudiobone_t* pBone = pStudioModel->pBone( i );
		if ( !pBone || !( pBone->flags & 256 ) || pBone->parent == -1 )
			continue;

		Vector vBonePos1;
		if ( !D::WorldToScreen( Vector( pBoneToWorldOut[ i ][ 0 ][ 3 ], pBoneToWorldOut[ i ][ 1 ][ 3 ], pBoneToWorldOut[ i ][ 2 ][ 3 ] ), vBonePos1 ) )
			continue;

		Vector vBonePos2;
		if ( !D::WorldToScreen( Vector( pBoneToWorldOut[ pBone->parent ][ 0 ][ 3 ], pBoneToWorldOut[ pBone->parent ][ 1 ][ 3 ], pBoneToWorldOut[ pBone->parent ][ 2 ][ 3 ] ), vBonePos2 ) )
			continue;

		D::DrawLine( ( int ) vBonePos1.x, ( int ) vBonePos1.y, ( int ) vBonePos2.x, ( int ) vBonePos2.y, Vars.Visuals.PlayerEsp.bTeamCheck && !pPlayer->IsEnemy() ? color_team : color_enemy );

	}
}

void CVisuals::HealthBar( Vector bot, Vector top, int health )
{
	float h = ( bot.y - top.y );

	UINT hp = h - ( UINT ) ( ( h * health ) / 100 );

	float flBoxes = std::ceil( health / 10.f );
	float flX = top.x - 7 - h / 4.f;
	float flY = top.y - 1;
	float flHeight = h / 10.f;

	int Red = 255 - ( health*2.55 );
	int Green = health*2.55;

	D::DrawRect( flX, flY, 4, h + 2, Color( 80, 80, 80, 125 ) );
	D::DrawOutlinedRect( flX, flY, 4, h + 2, Color::Black() );
	D::DrawRect( flX + 1, flY, 2, flHeight * flBoxes + 1, Color( Red, Green, 0, 255 ) );

	for ( int i = 0; i < 10; i++ )
		D::DrawLine( flX, flY + i * flHeight, flX + 4, flY + i * flHeight, Color::Black() );
}

void CVisuals::ThirdpersonScope()
{
	if ( !Vars.Visuals.bSniperCrosshair )
		return;

	C_BasePlayer* pLocalPlayer = ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );

	if ( !pLocalPlayer || !pLocalPlayer->IsAlive() )
		return;

	int szWidth, szHeight;
	g_pEngine->GetScreenSize( szWidth, szHeight );

	if ( pLocalPlayer->GetActiveWeapon()->GetWeaponType() == WEAPONTYPE_SNIPER_RIFLE && !pLocalPlayer->IsScoped() )
	{
		D::DrawLine( szWidth / 2 - 4, szHeight / 2, szWidth / 2 + 5, szHeight / 2, Color::White() );
		D::DrawLine( szWidth / 2, szHeight / 2 - 4, szWidth / 2, szHeight / 2 + 5, Color::White() );
	}


	if ( !pLocalPlayer->IsScoped() )
		return;

	D::DrawLine( 0, szHeight / 2, szWidth, szHeight / 2, Color::Black() );
	D::DrawLine( szWidth / 2, 0, szWidth / 2, szHeight, Color::Black() );

	if ( !g_pInput->m_fCameraInThirdPerson )
		return;

	int length = 6;
	int gap = 4;

	Color cFinal = Color::Red();

	D::DrawLine( szWidth / 2 - gap, szHeight / 2 - gap, szWidth / 2 - gap, szHeight / 2 - gap - length, cFinal );
	D::DrawLine( szWidth / 2 + gap, szHeight / 2 + gap, szWidth / 2 + gap, szHeight / 2 + gap + length, cFinal );

	D::DrawLine( szWidth / 2 + gap, szHeight / 2 - gap, szWidth / 2 + gap, szHeight / 2 - gap - length, cFinal );
	D::DrawLine( szWidth / 2 - gap, szHeight / 2 + gap, szWidth / 2 - gap, szHeight / 2 + gap + length, cFinal );

	D::DrawLine( szWidth / 2 - gap, szHeight / 2 - gap, szWidth / 2 - gap - length, szHeight / 2 - gap, cFinal );
	D::DrawLine( szWidth / 2 + gap, szHeight / 2 + gap, szWidth / 2 + gap + length, szHeight / 2 + gap, cFinal );

	D::DrawLine( szWidth / 2 + gap, szHeight / 2 - gap, szWidth / 2 + gap + length, szHeight / 2 - gap, cFinal );
	D::DrawLine( szWidth / 2 - gap, szHeight / 2 + gap, szWidth / 2 - gap - length, szHeight / 2 + gap, cFinal );
}

void CVisuals::Hitmarker()
{
	if ( !Vars.Visuals.bHitmarker )
		return;

	float curtime = g_pGlobalVarsBase->curtime;
	int lineSize = 8;

	if ( flHurtTime + 0.25f >= curtime )
	{
		int screenSizeX, screenCenterX;
		int screenSizeY, screenCenterY;
		g_pEngine->GetScreenSize( screenSizeX, screenSizeY );

		screenCenterX = screenSizeX / 2;
		screenCenterY = screenSizeY / 2;

		D::DrawLine( screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - ( lineSize / 4 ), screenCenterY - ( lineSize / 4 ), Vars.Visuals.Colors.flHitmarker );
		D::DrawLine( screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - ( lineSize / 4 ), screenCenterY + ( lineSize / 4 ), Vars.Visuals.Colors.flHitmarker );
		D::DrawLine( screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + ( lineSize / 4 ), screenCenterY + ( lineSize / 4 ), Vars.Visuals.Colors.flHitmarker );
		D::DrawLine( screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + ( lineSize / 4 ), screenCenterY - ( lineSize / 4 ), Vars.Visuals.Colors.flHitmarker );
	}
}