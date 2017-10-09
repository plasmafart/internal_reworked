#include "..\MainInclude.h"

int created = 0;

IMaterial* IMaterialSystem::CreateMaterial( bool flat, bool ignorez, bool wireframed )
{
	std::string type = ( flat ) ? strenc( "UnlitGeneric" ) : strenc( "VertexLitGeneric" );

	std::string matdata = strenc( "\"" ) + type + strenc( "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"  \"\"\n\t\"$model\" \"1\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"  \"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"  \"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"" ) + std::to_string( wireframed ) + strenc( "\"\n\t\"$ignorez\" \"" ) + std::to_string( ignorez ) + strenc( "\"\n\t\"$rimlight\" \"1\"\n\t\"$rimlightexponent\" \"2\"\n\t\"$rimlightboost\" \".4" ) + strenc( "\"\n}\n" );
	std::string matdataold = strenc( "\"" ) + type + strenc( "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"  \"\"\n\t\"$model\" \"1\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"  \"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"  \"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"" ) + std::to_string( wireframed ) + strenc( "\"\n\t\"$ignorez\" \"" ) + std::to_string( ignorez ) + strenc( "\"\n}\n" );

	std::string matname = strenc( "custom_" ) + std::to_string( created );
	++created;

	KeyValues* pKeyValues = new KeyValues( matname.c_str() );
	U::InitKeyValues( pKeyValues, type.c_str() );
	U::LoadFromBuffer( pKeyValues, matname.c_str(), matdata.c_str() );

	typedef IMaterial*( __thiscall* OriginalFn )( void*, const char *pMaterialName, KeyValues *pVMTKeyValues );
	IMaterial* createdMaterial = U::GetVFunc<OriginalFn>( this, 83 )( this, matname.c_str(), pKeyValues );

	createdMaterial->IncrementReferenceCount();

	return createdMaterial;
}

IMaterial* IMaterialSystem::FindMaterial( char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix )
{
	typedef IMaterial*( __thiscall* OriginalFn )( void*, char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix );
	return U::GetVFunc<OriginalFn>( this, 84 )( this, pMaterialName, pTextureGroupName, complain, pComplainPrefix );
}

MaterialHandle_t IMaterialSystem::FirstMaterial()
{
	typedef MaterialHandle_t( __thiscall* FirstMaterialFn )( void* );
	return U::GetVFunc<FirstMaterialFn>( this, 86 )( this );
}

MaterialHandle_t IMaterialSystem::NextMaterial( MaterialHandle_t h )
{
	typedef MaterialHandle_t( __thiscall* NextMaterialFn )( void*, MaterialHandle_t );
	return U::GetVFunc<NextMaterialFn>( this, 87 )( this, h );
}

MaterialHandle_t IMaterialSystem::InvalidMaterial()
{
	typedef MaterialHandle_t( __thiscall* InvalidMaterialFn )( void* );
	return U::GetVFunc<InvalidMaterialFn>( this, 88 )( this );
}

IMaterial* IMaterialSystem::GetMaterial( MaterialHandle_t h )
{
	typedef IMaterial*( __thiscall* GetMaterialFn )( void*, MaterialHandle_t );
	return U::GetVFunc<GetMaterialFn>( this, 89 )( this, h );
}

bool IMaterialSystem::OverrideConfig( MaterialSystem_Config_t const& cfg, bool b )
{
	typedef bool( __thiscall* OverrideConfigFn )( void*, MaterialSystem_Config_t const&, bool );
	return U::GetVFunc<OverrideConfigFn>( this, 21 )( this, cfg, b );
}