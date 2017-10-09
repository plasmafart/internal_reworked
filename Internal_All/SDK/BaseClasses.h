#pragma once
#include "..\Internal\NetVars.h"


enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

enum class LifeState
{
	ALIVE = 0,
	DYING,
	DEAD,
	RESPAWNABLE,
	DISCARDBODY,
};

class C_BaseEntity : public IClientEntity
{
public:
	char __pad[ 0x64 ];
	int index;
	NETVAR( GetModelIndex, unsigned, "CBaseEntity->m_nModelIndex" )
		NETVAR( GetTeam, int, "CBaseEntity->m_iTeamNum" )
		NETVAR( GetOrigin, Vector, "CBaseEntity->m_vecOrigin" )
		PNETVAR( GetCollideable, ICollideable, "CBaseEntity->m_Collision" )
		NETVAR( GetSpotted, bool, "CBaseEntity->m_bSpotted" )

		void SetModelIndex( int index );
};

class C_BaseCombatCharacter : public C_BaseEntity
{
public:
	PNETVAR( GetWeapons, CBaseHandle, "CBaseCombatCharacter->m_hMyWeapons" )
		PNETVAR( GetWearables, CBaseHandle, "CBaseCombatCharacter->m_hMyWearables" )
		PNETVAR( GetActiveWeaponHandle, CBaseHandle, "CBaseCombatCharacter->m_hActiveWeapon" )
};

struct model_t;
class C_BaseCombatWeapon;
class C_BasePlayer : public C_BaseCombatCharacter
{
public:
	NETVAR( GetLifeState, LifeState, "CBasePlayer->m_lifeState" )
		NETVAR( GetViewModel, CBaseHandle, "CBasePlayer->m_hViewModel[0]" )
		NETVAR( GetEyeAngles, QAngle, "CCSPlayer->m_angEyeAngles" )
		NETVAR( GetViewOffset, Vector, "CBasePlayer->m_vecViewOffset" )
		NETVAR( GetHealth, int, "CBasePlayer->m_iHealth" )
		NETVAR( GetFlags, int, "CBasePlayer->m_fFlags" )
		NETVAR( IsScoped, bool, "CCSPlayer->m_bIsScoped")


		Vector GetEyePosition();
	bool IsAlive();
	bool IsEnemy();
	player_info_t GetPlayerInfo();
	std::string GetName();
	model_t* GetModel();
	C_BaseCombatWeapon* GetActiveWeapon();
	bool SetupBones( matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime );
};

class CCSWeaponData;
class C_BaseWeaponWorldModel;
class C_BaseCombatWeapon : public C_BaseEntity
{
public:
	NETVAR( GetViewModelIndex, int, "CBaseCombatWeapon->m_iViewModelIndex" )
		NETVAR( GetWeaponWorldModelHandle, CBaseHandle, "CBaseCombatWeapon->m_hWeaponWorldModel" )
		NETVAR( GetWorldDroppedModelIndex, int, "CBaseCombatWeapon->m_iWorldDroppedModelIndex" )

		std::string GetWeaponName();
	int GetWeaponID();
	int GetWeaponType();
	CCSWeaponData* GetCSWpnData();
};

class C_BaseAttributableItem : public C_BaseCombatWeapon
{
private:
	using str_32 = char[ 32 ];
public:
	NETVAR( GetAccountID, int, "CBaseAttributableItem->m_iAccountID" )
		NETVAR( GetItemDefinitionIndex, int, "CBaseAttributableItem->m_iItemDefinitionIndex" )
		NETVAR( GetItemIDHigh, int, "CBaseAttributableItem->m_iItemIDHigh" )
		NETVAR( GetEntityQuality, int, "CBaseAttributableItem->m_iEntityQuality" )
		NETVAR( GetCustomName, str_32, "CBaseAttributableItem->m_szCustomName" )
		NETVAR( GetFallbackPaintKit, unsigned, "CBaseAttributableItem->m_nFallbackPaintKit" )
		NETVAR( GetFallbackSeed, unsigned, "CBaseAttributableItem->m_nFallbackSeed" )
		NETVAR( GetFallbackWear, float, "CBaseAttributableItem->m_flFallbackWear" )
		NETVAR( GetFallbackStatTrak, unsigned, "CBaseAttributableItem->m_nFallbackStatTrak" )
};

class C_BaseViewModel : public C_BaseEntity
{
public:
	NETVAR( GetOwner, CBaseHandle, "CBaseViewModel->m_hOwner" )
		NETVAR( GetWeapon, CBaseHandle, "CBaseViewModel->m_hWeapon" )
		NETPROP( GetSequenceProp, "CBaseViewModel->m_nSequence" )
};

class C_BaseWeaponWorldModel : public C_BaseEntity
{

};

class CCStrike15ItemDefinition
{
public:
	virtual int GetNumSupportedStickerSlots();
	virtual const char* GetStickerSlotMaterialBySlotIndex();
};


class CCSWeaponData
{
public:

	virtual ~CCSWeaponData() {};

	char*		consoleName;			// 0x0004
	char		pad_0008[ 12 ];			// 0x0008
	int			iMaxClip1;				// 0x0014
	int			iMaxClip2;				// 0x0018
	int			iDefaultClip1;			// 0x001C
	int			iDefaultClip2;			// 0x0020
	char		pad_0024[ 8 ];			// 0x0024
	char*		szWorldModel;			// 0x002C
	char*		szViewModel;			// 0x0030
	char*		szDroppedModel;			// 0x0034
	char		pad_0038[ 4 ];			// 0x0038
	char*		N0000023E;				// 0x003C
	char		pad_0040[ 56 ];			// 0x0040
	char*		szEmptySound;			// 0x0078
	char		pad_007C[ 4 ];			// 0x007C
	char*		szBulletType;			// 0x0080
	char		pad_0084[ 4 ];			// 0x0084
	char*		szHudName;				// 0x0088
	char*		szWeaponName;			// 0x008C
	char		pad_0090[ 56 ];			// 0x0090
	int 		WeaponType;				// 0x00C8
	int			iWeaponPrice;			// 0x00CC
	int			iKillAward;				// 0x00D0
	char*		szAnimationPrefix;		// 0x00D4
	float		flCycleTime;			// 0x00D8
	float		flCycleTimeAlt;			// 0x00DC
	float		flTimeToIdle;			// 0x00E0
	float		flIdleInterval;			// 0x00E4
	bool		bFullAuto;				// 0x00E8
	char		pad_0x00E5[ 3 ];			// 0x00E9
	int			iDamage;				// 0x00EC
	float		flArmorRatio;			// 0x00F0
	int			iBullets;				// 0x00F4
	float		flPenetration;			// 0x00F8
	float		flFlinchVelocityModifierLarge;	// 0x00FC
	float		flFlinchVelocityModifierSmall;	// 0x0100
	float		flRange;				// 0x0104
	float		flRangeModifier;		// 0x0108
	float		flThrowVelocity;		// 0x010C
	char		pad_0x010C[ 12 ];			// 0x0110
	bool		bHasSilencer;			// 0x011C
	char		pad_0x0119[ 3 ];			// 0x011D
	char*		pSilencerModel;			// 0x0120
	int			iCrosshairMinDistance;	// 0x0124
	int			iCrosshairDeltaDistance;// 0x0128 - iTeam?
	float		flMaxPlayerSpeed;		// 0x012C
	float		flMaxPlayerSpeedAlt;	// 0x0130
	float		flSpread;				// 0x0134
	float		flSpreadAlt;			// 0x0138
	float		flInaccuracyCrouch;		// 0x013C
	float		flInaccuracyCrouchAlt;	// 0x0140
	float		flInaccuracyStand;		// 0x0144
	float		flInaccuracyStandAlt;	// 0x0148
	float		flInaccuracyJumpInitial;// 0x014C
	float		flInaccuracyJump;		// 0x0150
	float		flInaccuracyJumpAlt;	// 0x0154
	float		flInaccuracyLand;		// 0x0158
	float		flInaccuracyLandAlt;	// 0x015C
	float		flInaccuracyLadder;		// 0x0160
	float		flInaccuracyLadderAlt;	// 0x0164
	float		flInaccuracyFire;		// 0x0168
	float		flInaccuracyFireAlt;	// 0x016C
	float		flInaccuracyMove;		// 0x0170
	float		flInaccuracyMoveAlt;	// 0x0174
	float		flInaccuracyReload;		// 0x0178
	int			iRecoilSeed;			// 0x017C
	float		flRecoilAngle;			// 0x0180
	float		flRecoilAngleAlt;		// 0x0184
	float		flRecoilAngleVariance;	// 0x0188
	float		flRecoilAngleVarianceAlt;	// 0x018C
	float		flRecoilMagnitude;		// 0x0190
	float		flRecoilMagnitudeAlt;	// 0x0194
	float		flRecoilMagnitudeVariance;	// 0x0198
	float		flRecoilMagnitudeVarianceAlt;	// 0x019C
	float		flRecoveryTimeCrouch;	// 0x01A0
	float		flRecoveryTimeStand;	// 0x01A4
	float		flRecoveryTimeCrouchFinal;	// 0x01A8
	float		flRecoveryTimeStandFinal;	// 0x01AC
	int			iRecoveryTransitionStartBullet;// 0x01B0 
	int			iRecoveryTransitionEndBullet;	// 0x01B4
	bool		bUnzoomAfterShot;		// 0x01B8
	bool		bHideViewModelZoomed;	// 0x01B9
	char		pad_0x01B5[ 2 ];			// 0x01BA
	char		iZoomLevels[ 3 ];			// 0x01BC
	int			iZoomFOV[ 2 ];			// 0x01C0
	float		fZoomTime[ 3 ];			// 0x01C4
	char*		szWeaponClass;			// 0x01D4
	float		flAddonScale;			// 0x01D8
	char		pad_0x01DC[ 4 ];			// 0x01DC
	char*		szEjectBrassEffect;		// 0x01E0
	char*		szTracerEffect;			// 0x01E4
	int			iTracerFrequency;		// 0x01E8
	int			iTracerFrequencyAlt;	// 0x01EC
	char*		szMuzzleFlashEffect_1stPerson; // 0x01F0
	char		pad_0x01F4[ 4 ];			 // 0x01F4
	char*		szMuzzleFlashEffect_3rdPerson; // 0x01F8
	char		pad_0x01FC[ 4 ];			// 0x01FC
	char*		szMuzzleSmokeEffect;	// 0x0200
	float		flHeatPerShot;			// 0x0204
	char*		szZoomInSound;			// 0x0208
	char*		szZoomOutSound;			// 0x020C
	float		flInaccuracyPitchShift;	// 0x0210
	float		flInaccuracySoundThreshold;	// 0x0214
	float		flBotAudibleRange;		// 0x0218
	char		pad_0x0218[ 8 ];			// 0x0220
	char*		pWrongTeamMsg;			// 0x0224
	bool		bHasBurstMode;			// 0x0228
	char		pad_0x0225[ 3 ];			// 0x0229
	bool		bIsRevolver;			// 0x022C
	bool		bCannotShootUnderwater;	// 0x0230
};

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF

