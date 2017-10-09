#pragma once

class CVisuals
{
public:
	void Run();
	void SetHurtTime( float ht );
private:
	void PlayerESP( int index );
	void Skeleton( C_BasePlayer* Entity, Color color_team, Color color_enemy );
	void HealthBar( Vector bot, Vector top, int health );
	void ThirdpersonScope();
	void Hitmarker();
	float flHurtTime;
};