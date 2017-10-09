#include "..\MainInclude.h"
#include <fstream>
#include "..\json.h"

CConfig* Config = new CConfig();

nlohmann::json preset;

template<typename T>
void assign( T &value, char* sz )
{
	if ( preset[ sz ].empty() )
		return;

	value = preset[ sz ].get<T>();
}

void assign_array( float value[ 3 ], char* sz )
{
	if ( preset[ sz ][ "0" ].empty() || preset[ sz ][ "1" ].empty() || preset[ sz ][ "2" ].empty() )
		return;

	value[ 0 ] = preset[ sz ][ "0" ].get<float>();
	value[ 1 ] = preset[ sz ][ "1" ].get<float>();
	value[ 2 ] = preset[ sz ][ "2" ].get<float>();
}

template<typename T>
void save( T value, char* sz )
{
	preset[ sz ] = value;
}

void save_array( float value[3], char* sz )
{
	preset[ sz ][ "0" ] = value[ 0 ];
	preset[ sz ][ "1" ] = value[ 1 ];
	preset[ sz ][ "2" ] = value[ 2 ];
}

template<typename T>
void reset( T value, char* sz )
{
	if ( preset[ sz ].empty() )
		return;

	preset[ sz ].clear();
}

void reset_array( float value[3], char* sz )
{
	if ( preset[ sz ][ "0" ].empty() || preset[ sz ][ "1" ].empty() || preset[ sz ][ "2" ].empty() )
		return;

	preset[ sz ][ "0" ].clear();
	preset[ sz ][ "1" ].clear();
	preset[ sz ][ "2" ].clear();
}

const bool CConfig::LoadPreset()
{
	std::ifstream input_file = std::ifstream( config_name );

	if ( !input_file.good() )
		return false;

	try
	{
		preset << input_file;
	}
	catch ( ... )
	{
		input_file.close();
		return false;
	}

	assign( Vars.SkinChanger.bEnabled, "Vars.SkinChanger.bEnabled" );

	assign( Vars.Other.bThirdperson, "Vars.Other.bThirdperson" );
	assign( Vars.Other.flThirdpersonDist, "Vars.Other.flThirdpersonDist" );
	assign( Vars.Other.bRadar, "Vars.Other.bRadar" );

	assign( Vars.Visuals.bSniperCrosshair, "Vars.Visuals.bSniperCrosshair" );
	assign( Vars.Visuals.bHitmarker, "Vars.Visuals.bHitmarker" );
	assign_array( Vars.Visuals.Colors.flHitmarker, "Vars.Visuals.Colors.flHitmarker" );

	assign( Vars.Visuals.PlayerEsp.bEnabled, "Vars.Visuals.PlayerEsp.bEnabled" );
	assign( Vars.Visuals.PlayerEsp.bSkeleton, "Vars.Visuals.PlayerEsp.bSkeleton" );
	assign( Vars.Visuals.PlayerEsp.bBox, "Vars.Visuals.PlayerEsp.bBox" );
	assign( Vars.Visuals.PlayerEsp.bTeamCheck, "Vars.Visuals.PlayerEsp.bTeamCheck" );
	assign_array( Vars.Visuals.PlayerEsp.Colors.flEnemyBoxes, "Vars.Visuals.PlayerEsp.Colors.flEnemyBoxes" );
	assign_array( Vars.Visuals.PlayerEsp.Colors.flEnemyBones, "Vars.Visuals.PlayerEsp.Colors.flEnemyBones" );
	assign_array( Vars.Visuals.PlayerEsp.Colors.flTeamBoxes, "Vars.Visuals.PlayerEsp.Colors.flTeamBoxes" );
	assign_array( Vars.Visuals.PlayerEsp.Colors.flTeamBones, "Vars.Visuals.PlayerEsp.Colors.flTeamBones" );

	assign( Vars.Visuals.Chams.bEnabled, "Vars.Visuals.Chams.bEnabled" );
	assign( Vars.Visuals.Chams.bTeamCheck, "Vars.Visuals.Chams.bTeamCheck" );
	assign( Vars.Visuals.Chams.bXQZ, "Vars.Visuals.Chams.bXQZ" );
	assign_array( Vars.Visuals.Chams.Colors.flEnemyVisible, "Vars.Visuals.Chams.Colors.flEnemyVisible" );
	assign_array( Vars.Visuals.Chams.Colors.flEnemyHidden, "Vars.Visuals.Chams.Colors.flEnemyHidden" );
	assign_array( Vars.Visuals.Chams.Colors.flTeamVisible, "Vars.Visuals.Chams.Colors.flTeamVisible" );
	assign_array( Vars.Visuals.Chams.Colors.flTeamHidden, "Vars.Visuals.Chams.Colors.flTeamHidden" );

	assign( Vars.Visuals.MaterialConfig.bEnabled, "Vars.Visuals.MaterialConfig.bEnabled" );
	assign( Vars.Visuals.MaterialConfig.bDrawGrey, "Vars.Visuals.MaterialConfig.bDrawGrey" );
	assign( Vars.Visuals.MaterialConfig.bFullbright, "Vars.Visuals.MaterialConfig.bFullbright" );
	assign( Vars.Visuals.MaterialConfig.bShowLowResImage, "Vars.Visuals.MaterialConfig.bShowLowResImage" );
	assign( Vars.Visuals.MaterialConfig.bShowMipLevels, "Vars.Visuals.MaterialConfig.bShowMipLevels" );

	input_file.close();

	return true;
}

const bool CConfig::SavePreset()
{
	std::ofstream output_file = std::ofstream( config_name );

	if ( !output_file.good() )
		return false;

	save( Vars.SkinChanger.bEnabled, "Vars.SkinChanger.bEnabled" );

	save( Vars.Other.bThirdperson, "Vars.Other.bThirdperson" );
	save( Vars.Other.flThirdpersonDist, "Vars.Other.flThirdpersonDist" );
	save( Vars.Other.bRadar, "Vars.Other.bRadar" );

	save( Vars.Visuals.bSniperCrosshair, "Vars.Visuals.bSniperCrosshair" );
	save( Vars.Visuals.bHitmarker, "Vars.Visuals.bHitmarker" );
	save_array( Vars.Visuals.Colors.flHitmarker, "Vars.Visuals.Colors.flHitmarker" );

	save( Vars.Visuals.PlayerEsp.bEnabled, "Vars.Visuals.PlayerEsp.bEnabled" );
	save( Vars.Visuals.PlayerEsp.bSkeleton, "Vars.Visuals.PlayerEsp.bSkeleton" );
	save( Vars.Visuals.PlayerEsp.bBox, "Vars.Visuals.PlayerEsp.bBox" );
	save( Vars.Visuals.PlayerEsp.bTeamCheck, "Vars.Visuals.PlayerEsp.bTeamCheck" );
	save_array( Vars.Visuals.PlayerEsp.Colors.flEnemyBoxes, "Vars.Visuals.PlayerEsp.Colors.flEnemyBoxes" );
	save_array( Vars.Visuals.PlayerEsp.Colors.flEnemyBones, "Vars.Visuals.PlayerEsp.Colors.flEnemyBones" );
	save_array( Vars.Visuals.PlayerEsp.Colors.flTeamBoxes, "Vars.Visuals.PlayerEsp.Colors.flTeamBoxes" );
	save_array( Vars.Visuals.PlayerEsp.Colors.flTeamBones, "Vars.Visuals.PlayerEsp.Colors.flTeamBones" );

	save( Vars.Visuals.Chams.bEnabled, "Vars.Visuals.Chams.bEnabled" );
	save( Vars.Visuals.Chams.bTeamCheck, "Vars.Visuals.Chams.bTeamCheck" );
	save( Vars.Visuals.Chams.bXQZ, "Vars.Visuals.Chams.bXQZ" );
	save_array( Vars.Visuals.Chams.Colors.flEnemyVisible, "Vars.Visuals.Chams.Colors.flEnemyVisible" );
	save_array( Vars.Visuals.Chams.Colors.flEnemyHidden, "Vars.Visuals.Chams.Colors.flEnemyHidden" );
	save_array( Vars.Visuals.Chams.Colors.flTeamVisible, "Vars.Visuals.Chams.Colors.flTeamVisible" );
	save_array( Vars.Visuals.Chams.Colors.flTeamHidden, "Vars.Visuals.Chams.Colors.flTeamHidden" );

	save( Vars.Visuals.MaterialConfig.bEnabled, "Vars.Visuals.MaterialConfig.bEnabled" );
	save( Vars.Visuals.MaterialConfig.bDrawGrey, "Vars.Visuals.MaterialConfig.bDrawGrey" );
	save( Vars.Visuals.MaterialConfig.bFullbright, "Vars.Visuals.MaterialConfig.bFullbright" );
	save( Vars.Visuals.MaterialConfig.bShowLowResImage, "Vars.Visuals.MaterialConfig.bShowLowResImage" );
	save( Vars.Visuals.MaterialConfig.bShowMipLevels, "Vars.Visuals.MaterialConfig.bShowMipLevels" );

	output_file << std::setw( 4 ) << preset << std::endl;
	output_file.close();

	return true;
}

const bool CConfig::Reset()
{
	std::ofstream output_file = std::ofstream( config_name );

	if ( !output_file.good() )
		return false;

	reset( Vars.SkinChanger.bEnabled, "Vars.SkinChanger.bEnabled" );

	reset( Vars.Other.bThirdperson, "Vars.Other.bThirdperson" );
	reset( Vars.Other.flThirdpersonDist, "Vars.Other.flThirdpersonDist" );
	reset( Vars.Other.bRadar, "Vars.Other.bRadar" );

	reset( Vars.Visuals.bSniperCrosshair, "Vars.Visuals.bSniperCrosshair" );
	reset( Vars.Visuals.bHitmarker, "Vars.Visuals.bHitmarker" );
	reset_array( Vars.Visuals.Colors.flHitmarker, "Vars.Visuals.Colors.flHitmarker" );

	reset( Vars.Visuals.PlayerEsp.bEnabled, "Vars.Visuals.PlayerEsp.bEnabled" );
	reset( Vars.Visuals.PlayerEsp.bSkeleton, "Vars.Visuals.PlayerEsp.bSkeleton" );
	reset( Vars.Visuals.PlayerEsp.bBox, "Vars.Visuals.PlayerEsp.bBox" );
	reset( Vars.Visuals.PlayerEsp.bTeamCheck, "Vars.Visuals.PlayerEsp.bTeamCheck" );
	reset_array( Vars.Visuals.PlayerEsp.Colors.flEnemyBoxes, "Vars.Visuals.PlayerEsp.Colors.flEnemyBoxes" );
	reset_array( Vars.Visuals.PlayerEsp.Colors.flEnemyBones, "Vars.Visuals.PlayerEsp.Colors.flEnemyBones" );
	reset_array( Vars.Visuals.PlayerEsp.Colors.flTeamBoxes, "Vars.Visuals.PlayerEsp.Colors.flTeamBoxes" );
	reset_array( Vars.Visuals.PlayerEsp.Colors.flTeamBones, "Vars.Visuals.PlayerEsp.Colors.flTeamBones" );

	reset( Vars.Visuals.Chams.bEnabled, "Vars.Visuals.Chams.bEnabled" );
	reset( Vars.Visuals.Chams.bTeamCheck, "Vars.Visuals.Chams.bTeamCheck" );
	reset( Vars.Visuals.Chams.bXQZ, "Vars.Visuals.Chams.bXQZ" );
	reset_array( Vars.Visuals.Chams.Colors.flEnemyVisible, "Vars.Visuals.Chams.Colors.flEnemyVisible" );
	reset_array( Vars.Visuals.Chams.Colors.flEnemyHidden, "Vars.Visuals.Chams.Colors.flEnemyHidden" );
	reset_array( Vars.Visuals.Chams.Colors.flTeamVisible, "Vars.Visuals.Chams.Colors.flTeamVisible" );
	reset_array( Vars.Visuals.Chams.Colors.flTeamHidden, "Vars.Visuals.Chams.Colors.flTeamHidden" );

	reset( Vars.Visuals.MaterialConfig.bEnabled, "Vars.Visuals.MaterialConfig.bEnabled" );
	reset( Vars.Visuals.MaterialConfig.bDrawGrey, "Vars.Visuals.MaterialConfig.bDrawGrey" );
	reset( Vars.Visuals.MaterialConfig.bFullbright, "Vars.Visuals.MaterialConfig.bFullbright" );
	reset( Vars.Visuals.MaterialConfig.bShowLowResImage, "Vars.Visuals.MaterialConfig.bShowLowResImage" );
	reset( Vars.Visuals.MaterialConfig.bShowMipLevels, "Vars.Visuals.MaterialConfig.bShowMipLevels" );

	output_file << std::setw( 4 ) << preset << std::endl;
	output_file.close();

	return true;
}
