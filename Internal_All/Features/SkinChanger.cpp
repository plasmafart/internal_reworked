#include "..\CheatInclude.h"
#include <fstream>
#include <string.h>
#include "..\json.h"

Variables Vars;

void StickerSetting::UpdateValues()
{
	kit_vector_index = kit_vector_index < int( k_stickers.size() ) ? kit_vector_index : k_stickers.size() - 1;
	kit_index = k_stickers.at( kit_vector_index ).id;
}

void StickerSetting::UpdateIds()
{
	this->kit_vector_index = find_if( k_stickers.begin(), k_stickers.end(), [ this ] ( const Kit_t& x )
	{
		return this->kit_index == x.id;
	} ) - k_stickers.begin();
}

void EconomyItem_t::UpdateValues()
{

	definition_vector_index = definition_vector_index < int( k_weapon_names.size() ) ? definition_vector_index : k_weapon_names.size() - 1;
	definition_index = k_weapon_names.at( definition_vector_index ).definition_index;

	entity_quality_vector_index = entity_quality_vector_index < int( k_quality_names.size() ) ? entity_quality_vector_index : k_quality_names.size() - 1;
	entity_quality_index = k_quality_names.at( entity_quality_vector_index ).index;

	if ( definition_index == GLOVE_T_SIDE && !k_gloves.empty() )
	{
		paint_kit_vector_index = paint_kit_vector_index < int( k_gloves.size() ) ? paint_kit_vector_index : k_gloves.size() - 1;
		paint_kit_index = k_gloves.at( paint_kit_vector_index ).id;

		definition_override_vector_index = definition_override_vector_index < int( k_glove_names.size() ) ? definition_override_vector_index : k_glove_names.size() - 1;
		definition_override_index = k_glove_names.at( definition_override_vector_index ).definition_index;
	}
	else if ( !k_skins.empty() )
	{
		paint_kit_vector_index = paint_kit_vector_index < int( k_skins.size() ) ? paint_kit_vector_index : k_skins.size() - 1;
		paint_kit_index = k_skins.at( paint_kit_vector_index ).id;

		definition_override_vector_index = definition_override_vector_index < int( k_knife_names.size() ) ? definition_override_vector_index : k_knife_names.size() - 1;
		definition_override_index = k_knife_names.at( definition_override_vector_index ).definition_index;
	}

	/*for ( auto& sticker : stickers )
	sticker.UpdateValues();*/

}

void EconomyItem_t::UpdateIds()
{
	definition_vector_index = find_if( k_weapon_names.begin(), k_weapon_names.end(), [ this ] ( const WeaponName_t& x )
	{
		return this->definition_index == x.definition_index;
	} ) - k_weapon_names.begin();

	entity_quality_vector_index = find_if( k_quality_names.begin(), k_quality_names.end(), [ this ] ( const QualityName_t& x )
	{
		return this->entity_quality_index == x.index;
	} ) - k_quality_names.begin();

	const auto& skin_set = definition_index == GLOVE_T_SIDE ? k_gloves : k_skins;

	paint_kit_vector_index = find_if( skin_set.begin(), skin_set.end(), [ this ] ( const Kit_t& x )
	{
		return this->paint_kit_index == x.id;
	} ) - skin_set.begin();

	const auto& override_set = definition_index == GLOVE_T_SIDE ? k_glove_names : k_knife_names;

	definition_override_vector_index = find_if( override_set.begin(), override_set.end(), [ this ] ( const WeaponName_t& x )
	{
		return this->definition_override_index == x.definition_index;
	} ) - override_set.begin();

	/*for ( auto& sticker : stickers )
	sticker.UpdateIds();*/
}

static void EraseOverrideIfExistsByIndex( int definition_index )
{
	// We have info about the item not needed to be overridden
	if ( k_weapon_info.count( definition_index ) )
	{

		auto& icon_override_map = F::SkinChanger->GetIconOverrideMap();

		const auto& original_item = k_weapon_info.at( definition_index );

		// We are overriding its icon when not needed
		if ( original_item.icon && icon_override_map.count( original_item.icon ) )
			icon_override_map.erase( icon_override_map.at( original_item.icon ) ); // Remove the leftover override
	}
}

static void ApplyConfigOnAttributableItem( C_BaseAttributableItem* item, const EconomyItem_t* config, unsigned xuid_low )
{

	CBaseHandle world_model_handle = item->GetWeaponWorldModelHandle();

	if ( world_model_handle == INVALID_EHANDLE_INDEX )
		return;

	C_BaseWeaponWorldModel* view_model_weapon = ( C_BaseWeaponWorldModel* ) ( g_pClientEntList->GetClientEntityFromHandle( world_model_handle ) );

	if ( !view_model_weapon )
		return;

	view_model_weapon->GetModelIndex() = item->GetModelIndex() + 1;

	// Force fallback values to be used.
	item->GetItemIDHigh() = -1;

	// Set the owner of the weapon to our lower XUID. (fixes StatTrak)
	item->GetAccountID() = xuid_low;

	if ( config->entity_quality_index )
		item->GetEntityQuality() = config->entity_quality_index;

	if ( config->custom_name[ 0 ] )
		strcpy_s( item->GetCustomName(), config->custom_name );

	if ( config->paint_kit_index )
		item->GetFallbackPaintKit() = config->paint_kit_index;

	if ( config->seed )
		item->GetFallbackSeed() = config->seed;

	if ( config->stat_trak )
		item->GetFallbackStatTrak() = config->stat_trak;

	item->GetFallbackWear() = config->wear;

	auto& definition_index = item->GetItemDefinitionIndex();

	auto& icon_override_map = F::SkinChanger->GetIconOverrideMap();

	if ( config->definition_override_index // We need to override defindex
		 && config->definition_override_index != definition_index // It is not yet overridden
		 && k_weapon_info.count( config->definition_override_index ) ) // We have info about what we gonna override it to
	{
		unsigned old_definition_index = definition_index;

		definition_index = config->definition_override_index;

		const auto& replacement_item = k_weapon_info.at( config->definition_override_index );

		// Set the weapon model index -- required for paint kits to work on replacement items after the 29/11/2016 update.
		//item->GetModelIndex() = g_model_info->GetModelIndex(k_weapon_info.at(config->definition_override_index).model);
		item->SetModelIndex( g_pVModelInfo->GetModelIndex( replacement_item.model ) );
		item->GetClientNetworkable()->PreDataUpdate( 0 );

		// We didn't override 0, but some actual weapon, that we have data for
		if ( old_definition_index && k_weapon_info.count( old_definition_index ) )
		{
			const auto& original_item = k_weapon_info.at( old_definition_index );

			if ( original_item.icon && replacement_item.icon )
				icon_override_map[ original_item.icon ] = replacement_item.icon;
		}
	}
	else
	{
		EraseOverrideIfExistsByIndex( definition_index );
	}

}

static CreateClientClassFn GetWearableCreateFn()
{
	auto clazz = g_pClient->GetAllClasses();

	while ( strcmp( clazz->m_pNetworkName, "CEconWearable" ) )
		clazz = clazz->m_pNext;

	return clazz->m_pCreateFn;
}

void CSkinChanger::Run( ClientFrameStage_t stage )
{
	if ( stage != FRAME_NET_UPDATE_POSTDATAUPDATE_START )
		return;

	if ( !Vars.SkinChanger.bEnabled )
		return;

	auto local_index = g_pEngine->GetLocalPlayer();
	auto local = static_cast< C_BasePlayer* >( g_pClientEntList->GetClientEntity( local_index ) );

	if ( !local )
		return;

	player_info_t player_info;

	if ( !g_pEngine->GetPlayerInfo( local_index, &player_info ) )
		return;

	// Handle glove config
	{
		auto wearables = local->GetWearables();

		auto glove_config = F::SkinChanger->GetByDefinitionIndex( GLOVE_T_SIDE );

		static DWORD glove_handle = 0;

		auto glove = reinterpret_cast< C_BaseAttributableItem* >( g_pClientEntList->GetClientEntityFromHandle( wearables[ 0 ] ) );

		if ( !glove ) // There is no glove
		{
			// Try to get our last created glove
			auto our_glove = reinterpret_cast< C_BaseAttributableItem* >( g_pClientEntList->GetClientEntityFromHandle( glove_handle ) );

			if ( our_glove ) // Our glove still exists
			{
				wearables[ 0 ] = glove_handle;
				glove = our_glove;
			}
		}

		if ( local->GetLifeState() != LifeState::ALIVE )
		{
			// We are dead but we have a glove, destroy it
			if ( glove )
			{
				glove->GetClientNetworkable()->SetDestroyedOnRecreateEntities();
				glove->GetClientNetworkable()->Release();
			}

			return;
		}

		if ( glove_config && glove_config->definition_override_index )
		{
			// We don't have a glove, but we should
			if ( !glove )
			{
				static auto create_wearable_fn = GetWearableCreateFn();

				auto entry = g_pClientEntList->GetHighestEntityIndex() + 1;
				auto serial = rand() % 0x1000;

				create_wearable_fn( entry, serial );
				glove = reinterpret_cast< C_BaseAttributableItem* >( g_pClientEntList->GetClientEntity( entry ) );

				// He he
				{
					static auto set_abs_origin_fn = reinterpret_cast< void( __thiscall* )( void*, const Vector& ) >
						( U::FindPattern( strenc( "client.dll" ), strenc( "55 8B EC 83 E4 F8 51 53 56 57 8B F1" ) ) );

					static const Vector new_pos = { 10000.f, 10000.f, 10000.f };

					set_abs_origin_fn( glove, new_pos );
				}

				wearables[ 0 ] = entry | serial << 16;

				// Let's store it in case we somehow lose it.
				glove_handle = wearables[ 0 ];
			}

			// Thanks, Beakers
			*reinterpret_cast< int* >( uintptr_t( glove ) + 0x64 ) = -1;

			ApplyConfigOnAttributableItem( glove, glove_config, player_info.xuidlow );
		}
	}

	// Handle weapon configs
	{
		auto weapons = local->GetWeapons();

		for ( size_t i = 0; weapons[ i ] != INVALID_EHANDLE_INDEX; i++ )
		{
			auto weapon = static_cast< C_BaseAttributableItem* >( g_pClientEntList->GetClientEntityFromHandle( weapons[ i ] ) );

			if ( !weapon )
				continue;

			auto& definition_index = weapon->GetItemDefinitionIndex();

			// All knives are terrorist knives.
			if ( auto active_conf = F::SkinChanger->GetByDefinitionIndex( IsKnife( definition_index ) ? WEAPON_KNIFE : definition_index ) )
				ApplyConfigOnAttributableItem( weapon, active_conf, player_info.xuidlow );
			else
				EraseOverrideIfExistsByIndex( definition_index );


		}
	}

	CBaseHandle view_model_handle = local->GetViewModel();

	if ( view_model_handle == INVALID_EHANDLE_INDEX )
		return;

	C_BaseViewModel* view_model = static_cast< C_BaseViewModel* >( g_pClientEntList->GetClientEntityFromHandle( view_model_handle ) );

	if ( !view_model )
		return;

	CBaseHandle view_model_weapon_handle = view_model->GetWeapon();

	if ( view_model_weapon_handle == INVALID_EHANDLE_INDEX )
		return;

	auto view_model_weapon = static_cast< C_BaseAttributableItem* >( g_pClientEntList->GetClientEntityFromHandle( view_model_weapon_handle ) );

	if ( !view_model_weapon )
		return;

	if ( k_weapon_info.count( view_model_weapon->GetItemDefinitionIndex() ) )
	{
		auto& override_model = k_weapon_info.at( view_model_weapon->GetItemDefinitionIndex() ).model;
		view_model->GetModelIndex() = g_pVModelInfo->GetModelIndex( override_model );
	}

}



using json = nlohmann::json;

void to_json( json& j, const StickerSetting& sticker )
{
	j = json
	{
		{ "kit", sticker.kit_index },
		{ "wear", sticker.wear },
		{ "scale", sticker.scale },
		{ "rotation", sticker.rotation }
	};
}

void from_json( const json& j, StickerSetting& sticker )
{
	sticker.kit_index = j.at( "kit" ).get<int>();
	sticker.wear = j.at( "wear" ).get<float>();
	sticker.scale = j.at( "scale" ).get<float>();
	sticker.rotation = j.at( "rotation" ).get<float>();
	sticker.UpdateIds();
}

void to_json( json& j, const EconomyItem_t& item )
{
	j = json
	{
		{ "name", item.name },
		{ "enabled", item.enabled },
		{ "definition_index", item.definition_index },
		{ "entity_quality_index", item.entity_quality_index },
		{ "paint_kit_index", item.paint_kit_index },
		{ "definition_override_index", item.definition_override_index },
		{ "seed", item.seed },
		{ "stat_trak", item.stat_trak },
		{ "wear", item.wear },
		{ "custom_name", item.custom_name },
	};
}

void from_json( const json& j, EconomyItem_t& item )
{
	strcpy_s( item.name, j.at( "name" ).get<std::string>().c_str() );
	item.enabled = j.at( "enabled" ).get<bool>();
	item.definition_index = j.at( "definition_index" ).get<int>();
	item.entity_quality_index = j.at( "entity_quality_index" ).get<int>();
	item.paint_kit_index = j.at( "paint_kit_index" ).get<int>();
	item.definition_override_index = j.at( "definition_override_index" ).get<int>();
	item.seed = j.at( "seed" ).get<int>();
	item.stat_trak = j.at( "stat_trak" ).get<int>();
	item.wear = j.at( "wear" ).get<float>();
	strcpy_s( item.custom_name, j.at( "custom_name" ).get<std::string>().c_str() );

	item.UpdateIds();
}

void CSkinChanger::Save()
{
	std::ofstream( "skinchanger.json" ) << json( m_items );
}
bool compareFunction( const EconomyItem_t& a, const EconomyItem_t& b ) { return std::string( a.name ) < std::string( b.name ); }

void CSkinChanger::Load()
{
	try
	{
		m_items = json::parse( std::ifstream( "skinchanger.json" ) ).get<std::vector<EconomyItem_t>>();
		std::sort( m_items.begin(), m_items.end(), compareFunction );
		g_pClientState->ForceFullUpdate();
	}
	catch ( const std::exception& )
	{
		// Config file doesn't exists or is malformed, just ignore it
	}
}

EconomyItem_t* CSkinChanger::GetByDefinitionIndex( int definition_index )
{
	for ( auto& x : m_items )
		if ( x.enabled && x.definition_index == definition_index )
			return &x;

	return nullptr;
}