#pragma once

struct Variables
{
	Variables()
	{

	}
	struct
	{
		bool	bThirdperson;
		float	flThirdpersonDist = 60.f;
		bool	bRadar;

	} Other;
	struct
	{
		bool	bOpened = false;
		int		iTab = 0;

	} Menu;
	struct
	{
		bool	bEnabled = true;

	} SkinChanger;
	struct
	{
		bool	bSniperCrosshair;
		bool	bHitmarker;
		struct
		{
			float   flHitmarker[ 3 ];
		} Colors;
		struct
		{
			bool	bEnabled;
			bool	bSkeleton;
			bool	bBox;
			bool	bTeamCheck;
			struct
			{
				float   flEnemyBoxes[ 3 ];
				float   flEnemyBones[ 3 ];

				float   flTeamBoxes[ 3 ];
				float   flTeamBones[ 3 ];
			} Colors;

		} PlayerEsp;
		struct
		{
			bool	bEnabled;
			bool	bTeamCheck;
			bool	bXQZ;
			struct
			{
				float   flEnemyVisible[ 3 ];
				float   flEnemyHidden[ 3 ];

				float   flTeamVisible[ 3 ];
				float   flTeamHidden[ 3 ];
			} Colors;
			
		} Chams;
		struct
		{
			bool	bEnabled;
			bool	bDrawGrey;
			bool	bFullbright;
			bool	bShowLowResImage;
			bool	bShowMipLevels;

		} MaterialConfig;
	} Visuals;

};

extern Variables Vars;