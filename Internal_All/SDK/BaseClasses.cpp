#include "..\CheatInclude.h"

Vector C_BasePlayer::GetEyePosition() { return this->GetOrigin() + this->GetViewOffset(); }
bool C_BasePlayer::IsAlive() { return this->GetLifeState() == LifeState::ALIVE; }
bool C_BasePlayer::IsEnemy() { return this->GetTeam() != ( ( C_BasePlayer* ) g_pClientEntList->GetClientEntity( g_pEngine->GetLocalPlayer() ) )->GetTeam(); }
player_info_t C_BasePlayer::GetPlayerInfo() { player_info_t pinfo; g_pEngine->GetPlayerInfo( this->index, &pinfo ); return pinfo; }
std::string C_BasePlayer::GetName() { return this->GetPlayerInfo().name; }
C_BaseCombatWeapon* C_BasePlayer::GetActiveWeapon() { return ( C_BaseCombatWeapon* ) g_pClientEntList->GetClientEntityFromHandle( *this->GetActiveWeaponHandle() ); }
int C_BaseCombatWeapon::GetWeaponID() { if ( !this ) return -1; return ( ( C_BaseAttributableItem* ) this )->GetItemDefinitionIndex(); }
int C_BaseCombatWeapon::GetWeaponType() { if ( !this ) return -1; return this->GetCSWpnData()->WeaponType; }
CCSWeaponData* C_BaseCombatWeapon::GetCSWpnData() { return U::GetVFunc<CCSWeaponData*( __thiscall* )( void* )>( this, 446 )( this ); }
void C_BaseEntity::SetModelIndex( int index ) { U::GetVFunc<void( __thiscall* )( C_BaseEntity*, int )>( this, 75 )( this, index ); }
model_t* C_BasePlayer::GetModel() { return *( model_t** ) ( ( DWORD )this + 0x6C ); }

bool C_BasePlayer::SetupBones( matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
{
	__asm
	{
		mov edi, this
		lea ecx, dword ptr ds : [edi + 0x4]
		mov edx, dword ptr ds : [ecx]
		push currentTime
		push boneMask
		push nMaxBones
		push pBoneToWorldOut
		call dword ptr ds : [edx + 0x34]
	}
}


std::string C_BaseCombatWeapon::GetWeaponName()
{
	if ( !this )
		return "";

	int id = this->GetWeaponID();

	switch ( id )
	{
		case WEAPON_DEAGLE:
			return strenc( "Desert Eagle" );
		case WEAPON_ELITE:
			return strenc( "Dual Berettas" );
		case WEAPON_FIVESEVEN:
			return strenc( "Five-SeveN" );
		case WEAPON_GLOCK:
			return strenc( "Glock-18" );
		case WEAPON_AK47:
			return strenc( "AK-47" );
		case WEAPON_AUG:
			return strenc( "AUG" );
		case WEAPON_AWP:
			return strenc( "AWP" );
		case WEAPON_FAMAS:
			return strenc( "FAMAS" );
		case WEAPON_G3SG1:
			return strenc( "G3SG1" );
		case WEAPON_GALILAR:
			return strenc( "Galil" );
		case WEAPON_M249:
			return strenc( "M249" );
		case WEAPON_M4A1:
			return strenc( "M4A1" );
		case WEAPON_MAC10:
			return strenc( "MAC-10" );
		case WEAPON_P90:
			return strenc( "P90" );
		case WEAPON_UMP45:
			return strenc( "UMP-45" );
		case WEAPON_XM1014:
			return strenc( "XM1014" );
		case WEAPON_BIZON:
			return strenc( "PP-Bizon" );
		case WEAPON_MAG7:
			return strenc( "MAG-7" );
		case WEAPON_NEGEV:
			return strenc( "Negev" );
		case WEAPON_SAWEDOFF:
			return strenc( "Sawed-Off" );
		case WEAPON_TEC9:
			return strenc( "Tec-9" );
		case WEAPON_TASER:
			return strenc( "Taser" );
		case WEAPON_HKP2000:
			return strenc( "P2000" );
		case WEAPON_MP7:
			return strenc( "MP7" );
		case WEAPON_MP9:
			return strenc( "MP9" );
		case WEAPON_NOVA:
			return strenc( "Nova" );
		case WEAPON_P250:
			return strenc( "P250" );
		case WEAPON_SCAR20:
			return strenc( "SCAR-20" );
		case WEAPON_SG556:
			return strenc( "SG 553" );
		case WEAPON_SSG08:
			return strenc( "SSG 08" );
		case WEAPON_KNIFE:
			return strenc( "Knife" );
		case WEAPON_FLASHBANG:
			return strenc( "Flashbang" );
		case WEAPON_HEGRENADE:
			return strenc( "HE Grenade" );
		case WEAPON_SMOKEGRENADE:
			return strenc( "Smoke Grenade" );
		case WEAPON_MOLOTOV:
			return strenc( "Molotov" );
		case WEAPON_DECOY:
			return strenc( "Decoy" );
		case WEAPON_INCGRENADE:
			return strenc( "Incendiary Grenade" );
		case WEAPON_C4:
			return strenc( "C4" );
		case WEAPON_KNIFE_T:
			return strenc( "Knife" );
		case WEAPON_M4A1_SILENCER:
			return strenc( "M4A1-S" );
		case WEAPON_USP_SILENCER:
			return strenc( "USP-S" );
		case WEAPON_CZ75A:
			return strenc( "CZ75-Auto" );
		case WEAPON_REVOLVER:
			return strenc( "R8 Revolver" );
		default:
			return strenc( "Knife" );
	}

	return "";
}