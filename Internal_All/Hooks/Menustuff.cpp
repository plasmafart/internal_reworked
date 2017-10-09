#include "..\CheatInclude.h"

#include <functional>

void GUI_Init( IDirect3DDevice9* pDevice );

namespace ImGui
{
	// ImGui ListBox lambda binder
	static bool ListBox( const char* label, int* current_item, std::function<const char*( int )> lambda, int items_count, int height_in_items )
	{
		return ImGui::ListBox( label, current_item, [] ( void* data, int idx, const char** out_text )
		{
			*out_text = ( *reinterpret_cast< std::function<const char*( int )>* >( data ) )( idx );
			return true;
		}, &lambda, items_count, height_in_items );
	}
}

ImVec4 accent = ImVec4( 1.f, 0.26f, 0.f, 1.f );

void AccentText( const char* text )
{
	ImGui::PushStyleColor( ImGuiCol_Text, accent );
	ImGui::Text( text );
	ImGui::PopStyleColor();
}


void DrawGUI()
{
	Hook->g_phkD3D9->ReHook();

	ImGui::GetIO().MouseDrawCursor = Vars.Menu.bOpened;

	ImGui_ImplDX9_NewFrame();

	static float rainbow;
	rainbow += 0.00035f;
	if ( rainbow > 1.f ) rainbow = 0.f;
	static Color rba;
	rba = Color::FromHSB( rainbow, 1.f, 1.f );
	static ImVec4 rb;
	rb = ImVec4( rba.rBase(), rba.gBase(), rba.bBase(), 1.f );

	if ( Vars.Menu.bOpened )
	{
		int pX, pY;
		g_pInputSystem->GetCursorPosition( &pX, &pY );
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos.x = ( float ) ( pX );
		io.MousePos.y = ( float ) ( pY );
		ImGui::PushItemWidth( 150 );

		static char szCurrtooltip[ 128 ] = "";

		ImGui::Begin( charenc( "whatever" ), &Vars.Menu.bOpened, ImVec2( 803, 458 ), 1.0f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_ShowBorders );
		{
			if ( ImGui::Button( charenc( "Config" ), ImVec2( 151, 40 ) ) )
				Vars.Menu.iTab = 0;
			ImGui::SameLine();
			if ( ImGui::Button( charenc( "Visuals" ), ImVec2( 151, 40 ) ) )
				Vars.Menu.iTab = 1;
			ImGui::SameLine();
			if ( ImGui::Button( charenc( "Legit" ), ImVec2( 151, 40 ) ) )
				Vars.Menu.iTab = 2;
			ImGui::SameLine();
			if ( ImGui::Button( charenc( "Rage" ), ImVec2( 151, 40 ) ) )
				Vars.Menu.iTab = 3;
			ImGui::SameLine();
			if ( ImGui::Button( charenc( "Skinchanger" ), ImVec2( 151, 40 ) ) )
				Vars.Menu.iTab = 4;

			ImGui::PushStyleColor( ImGuiCol_Separator, rb );
			ImGui::Separator();
			ImGui::PopStyleColor();

			ImGui::BeginChildFrame( 0, ImVec2( 389, 21 ), ImGuiWindowFlags_ShowBorders );
			{

			}
			ImGui::EndChildFrame();

			if ( Vars.Menu.iTab == 0 )
			{

				ImGui::BeginChildFrame( 1, ImVec2( 389, 405 ), ImGuiWindowFlags_ShowBorders );
				{

					AccentText( "Config" );
					if ( ImGui::Button( "Load##3" ) )
					{
						ImGui::SetTooltip( "Load saved settings" );
						Config->LoadPreset();
					}
					ImGui::SameLine();
					if ( ImGui::Button( "Save##3" ) )
					{
						Config->SavePreset();
					}
					ImGui::SameLine();
					if ( ImGui::Button( "Reset##3" ) )
					{
						Config->Reset();
					}

				}
				ImGui::EndChildFrame();
				ImGui::SameLine();
				ImGui::BeginChildFrame( 2, ImVec2( 389, 405 ), ImGuiWindowFlags_ShowBorders );
				{
					ImGui::SetColorEditOptions( ImGuiColorEditFlags_NoInputs | ImGuiWindowFlags_ShowBorders | ImGuiColorEditFlags_PickerHueWheel );


					AccentText( "Chams" );
					ImGui::Dummy( ImVec2( 10, 1 ) ); ImGui::SameLine(); AccentText( "Team" );
					ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::Text( "Visible " ); ImGui::SameLine(); ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::ColorEdit3( "##Visible", Vars.Visuals.Chams.Colors.flTeamVisible );
					ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::Text( "Hidden" ); ImGui::SameLine(); ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::ColorEdit3( "##Hidden", Vars.Visuals.Chams.Colors.flTeamHidden );
					ImGui::Dummy( ImVec2( 1, 5 ) );

					ImGui::Dummy( ImVec2( 10, 1 ) ); ImGui::SameLine(); AccentText( "Enemy" );
					ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::Text( "Visible " ); ImGui::SameLine(); ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::ColorEdit3( "##Visible2", Vars.Visuals.Chams.Colors.flEnemyVisible );
					ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::Text( "Hidden" ); ImGui::SameLine(); ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::ColorEdit3( "##Hidden2", Vars.Visuals.Chams.Colors.flEnemyHidden );

					ImGui::Dummy( ImVec2( 1, 10 ) );
					AccentText( "Player Esp" );
					ImGui::Dummy( ImVec2( 10, 1 ) ); ImGui::SameLine(); AccentText( "Team" );
					ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::Text( "Boxes " ); ImGui::SameLine(); ImGui::Dummy( ImVec2( 22, 1 ) ); ImGui::SameLine(); ImGui::ColorEdit3( "##Boxes", Vars.Visuals.PlayerEsp.Colors.flTeamBoxes );
					ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::Text( "Bones " ); ImGui::SameLine(); ImGui::Dummy( ImVec2( 21, 1 ) ); ImGui::SameLine(); ImGui::ColorEdit3( "##Bones", Vars.Visuals.PlayerEsp.Colors.flTeamBones );
					ImGui::Dummy( ImVec2( 1, 5 ) );

					ImGui::Dummy( ImVec2( 10, 1 ) ); ImGui::SameLine(); AccentText( "Enemy" );
					ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::Text( "Boxes " ); ImGui::SameLine(); ImGui::Dummy( ImVec2( 22, 1 ) ); ImGui::SameLine(); ImGui::ColorEdit3( "##Boxes2", Vars.Visuals.PlayerEsp.Colors.flEnemyBoxes );
					ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::Text( "Bones " ); ImGui::SameLine(); ImGui::Dummy( ImVec2( 21, 1 ) ); ImGui::SameLine(); ImGui::ColorEdit3( "##Bones2", Vars.Visuals.PlayerEsp.Colors.flEnemyBones );

					ImGui::Dummy( ImVec2( 1, 10 ) );
					AccentText( "Misc" );
					ImGui::Dummy( ImVec2( 10, 1 ) ); ImGui::SameLine(); ImGui::Text( "Hitmarker" ); ImGui::SameLine(); ImGui::Dummy( ImVec2( 20, 1 ) ); ImGui::SameLine(); ImGui::ColorEdit3( "##Hitmarker", Vars.Visuals.Colors.flHitmarker );
				}
				ImGui::EndChildFrame();

			}
			//Visuals
			if ( Vars.Menu.iTab == 1 )
			{
				ImGui::BeginChildFrame( 3, ImVec2( 389, 405 ), ImGuiWindowFlags_ShowBorders );
				{

					AccentText( "Other" );
					ImGui::Checkbox( "Radar", &Vars.Other.bRadar );
					ImGui::Checkbox( "Thirdperson", &Vars.Other.bThirdperson );
					ImGui::PushItemWidth( 170 );
					ImGui::SliderFloat( "##Thirdperson Distance", &Vars.Other.flThirdpersonDist, 0.f, 300.f, "%.0f" );
					ImGui::PopItemWidth();

					AccentText( "Misc" );
					ImGui::Checkbox( "Hitmarkers", &Vars.Visuals.bHitmarker );
					ImGui::Checkbox( "Sniper Crosshair", &Vars.Visuals.bSniperCrosshair );

					AccentText( "Player ESP" );
					ImGui::Checkbox( "Enabled##Player ESP", &Vars.Visuals.PlayerEsp.bEnabled );
					ImGui::Checkbox( "Team check", &Vars.Visuals.PlayerEsp.bTeamCheck );
					ImGui::Checkbox( "Box", &Vars.Visuals.PlayerEsp.bBox );
					ImGui::Checkbox( "Sekeleton", &Vars.Visuals.PlayerEsp.bSkeleton );


				}
				ImGui::EndChildFrame();
				ImGui::SameLine();
				ImGui::BeginChildFrame( 4, ImVec2( 389, 405 ), ImGuiWindowFlags_ShowBorders );
				{
					AccentText( "Chams" );
					ImGui::Checkbox( "Enabled##Chams", &Vars.Visuals.Chams.bEnabled );
					ImGui::Checkbox( "Team check", &Vars.Visuals.Chams.bTeamCheck );
					ImGui::Checkbox( "XQZ", &Vars.Visuals.Chams.bXQZ );

					AccentText( "Material Config" );
					ImGui::Checkbox( "Enabled##MaterialConfig", &Vars.Visuals.MaterialConfig.bEnabled );
					ImGui::Checkbox( "Draw Grey", &Vars.Visuals.MaterialConfig.bDrawGrey );
					ImGui::Checkbox( "Fullbright", &Vars.Visuals.MaterialConfig.bFullbright );
					ImGui::Checkbox( "Show lowres-image", &Vars.Visuals.MaterialConfig.bShowLowResImage );
					ImGui::Checkbox( "Show mip-levels", &Vars.Visuals.MaterialConfig.bShowMipLevels );

				}
				ImGui::EndChildFrame();

			}
			//Skinchanger
			if ( Vars.Menu.iTab == 4 )
			{

				ImGui::Checkbox( "Enabled##skinchanger", &Vars.SkinChanger.bEnabled );

				std::vector<EconomyItem_t>& entries = F::SkinChanger->GetItems();

				// If the user deleted the only config let's add one
				if ( entries.size() == 0 )
					entries.push_back( EconomyItem_t() );


				static int selected_id = 0;

				ImGui::Columns( 2, nullptr, false );

				// Config selection
				{
					ImGui::PushItemWidth( -1 );

					char element_name[ 64 ];

					ImGui::ListBox( "##config", &selected_id, [ &element_name, &entries ] ( int idx )
					{
						sprintf_s( element_name, "%s (%s)", entries.at( idx ).name, k_weapon_names.at( entries.at( idx ).definition_vector_index ).name );
						return element_name;
					}, entries.size(), 15 );

					ImVec2 button_size = ImVec2( ImGui::GetColumnWidth() / 2 - 12.8f, 25 );

					if ( ImGui::Button( "Add", button_size ) )
					{
						entries.push_back( EconomyItem_t() );
						selected_id = entries.size() - 1;
					}
					ImGui::SameLine();

					if ( ImGui::Button( "Remove", button_size ) )
						entries.erase( entries.begin() + selected_id );

					ImGui::PopItemWidth();
				}

				ImGui::NextColumn();

				selected_id = selected_id < int( entries.size() ) ? selected_id : entries.size() - 1;

				EconomyItem_t& selected_entry = entries[ selected_id ];

				{
					// Name
					ImGui::InputText( "Name", selected_entry.name, 32 );
					ImGui::Dummy( ImVec2( 1, 4 ) );

					// Item to change skins for
					ImGui::Combo( "Item", &selected_entry.definition_vector_index, [] ( void* data, int idx, const char** out_text )
					{
						*out_text = k_weapon_names[ idx ].name;
						return true;
					}, nullptr, k_weapon_names.size(), 5 );
					ImGui::Dummy( ImVec2( 1, 3 ) );

					// Enabled
					ImGui::Checkbox( "Enabled", &selected_entry.enabled );
					ImGui::Dummy( ImVec2( 1, 3 ) );

					// Pattern Seed
					ImGui::InputInt( "Seed", &selected_entry.seed );
					ImGui::Dummy( ImVec2( 1, 4 ) );

					// Custom StatTrak number
					ImGui::InputInt( "StatTrak", &selected_entry.stat_trak );
					ImGui::Dummy( ImVec2( 1, 4 ) );

					// Wear Float
					ImGui::SliderFloat( "Wear", &selected_entry.wear, FLT_MIN, 1.f, "%.10f", 5 );
					ImGui::Dummy( ImVec2( 1, 4 ) );

					// Paint kit
					if ( selected_entry.definition_index != GLOVE_T_SIDE )
					{
						ImGui::Combo( "Paint Kit", &selected_entry.paint_kit_vector_index, [] ( void* data, int idx, const char** out_text )
						{
							*out_text = k_skins[ idx ].name.c_str();
							return true;
						}, nullptr, k_skins.size(), 10 );
					}
					else
					{
						ImGui::Combo( "Paint Kit", &selected_entry.paint_kit_vector_index, [] ( void* data, int idx, const char** out_text )
						{
							*out_text = k_gloves[ idx ].name.c_str();
							return true;
						}, nullptr, k_gloves.size(), 10 );
					}
					ImGui::Dummy( ImVec2( 1, 4 ) );

					// Quality
					ImGui::Combo( "Quality", &selected_entry.entity_quality_vector_index, [] ( void* data, int idx, const char** out_text )
					{
						*out_text = k_quality_names[ idx ].name;
						return true;
					}, nullptr, k_quality_names.size(), 5 );
					ImGui::Dummy( ImVec2( 1, 4 ) );

					// Yes we do it twice to decide knifes
					selected_entry.UpdateValues();

					// Item defindex override
					if ( selected_entry.definition_index == WEAPON_KNIFE )
					{
						ImGui::Combo( "Knife", &selected_entry.definition_override_vector_index, [] ( void* data, int idx, const char** out_text )
						{
							*out_text = k_knife_names.at( idx ).name;
							return true;
						}, nullptr, k_knife_names.size(), 5 );
					}
					else if ( selected_entry.definition_index == GLOVE_T_SIDE )
					{
						ImGui::Combo( "Glove", &selected_entry.definition_override_vector_index, [] ( void* data, int idx, const char** out_text )
						{
							*out_text = k_glove_names.at( idx ).name;
							return true;
						}, nullptr, k_glove_names.size(), 5 );
					}
					else
					{
						// We don't want to override weapons other than knives or gloves
						static auto unused_value = 0;
						selected_entry.definition_override_vector_index = 0;
						ImGui::Combo( "Unavailable", &unused_value, "For knives or gloves\0" );
					}
					ImGui::Dummy( ImVec2( 1, 4 ) );

					selected_entry.UpdateValues();

					// Custom Name tag
					ImGui::InputText( "Name Tag", selected_entry.custom_name, 32 );
					ImGui::Dummy( ImVec2( 1, 4 ) );
				}

				ImGui::NextColumn();

				ImGui::Columns( 1, nullptr, false );

				ImGui::Separator();



				ImGui::Dummy( ImVec2( 1, 10 ) );

				ImGui::Columns( 3, nullptr, false );

				ImGui::PushItemWidth( -1 );

				// Lower buttons for modifying items and saving
				{
					ImVec2 button_size = ImVec2( ImGui::GetColumnWidth() - 17.f, 25 );

					if ( ImGui::Button( "Update", button_size ) )
						g_pClientState->ForceFullUpdate();
					ImGui::NextColumn();

					if ( ImGui::Button( "Save", button_size ) )
						F::SkinChanger->Save();
					ImGui::NextColumn();

					if ( ImGui::Button( "Load", button_size ) )
						F::SkinChanger->Load();
					ImGui::NextColumn();
				}
				ImGui::Dummy( ImVec2( 1, 5 ) );

				ImGui::PopItemWidth();
				ImGui::Columns( 1 );

			}

		}
		ImGui::End();
	}
	else
	{
		ImGui::CloseCurrentPopup();
	}

	ImGui::Render();
}

EndSceneFn oEndScene;
long __stdcall g_hkEndScene( IDirect3DDevice9* pDevice )
{
	if ( !G::d3dinit )
		GUI_Init( pDevice );

	DrawGUI();

	return oEndScene( pDevice );
}

ResetFn oReset;
long __stdcall g_hkReset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters )
{
	if ( !G::d3dinit )
		return oReset( pDevice, pPresentationParameters );

	ImGui_ImplDX9_InvalidateDeviceObjects();

	auto hr = oReset( pDevice, pPresentationParameters );

	ImGui_ImplDX9_CreateDeviceObjects();

	return hr;
}

void GUI_Init( IDirect3DDevice9* pDevice )
{
	ImGui_ImplDX9_Init( G::Window, pDevice );

	ImVec4 bg = ImVec4( 1.f, 1.f, 1.f, 0.008f );
	ImVec4 hovered = ImVec4( 1.f, 1.f, 1.f, 0.04f );
	ImVec4 active = ImVec4( 1.f, 1.f, 1.f, 0.07f );

	ImGuiIO& io = ImGui::GetIO();

	io.Fonts->Clear();
	io.Fonts->AddFontFromFileTTF( "C:/Windows/Fonts/Ubuntu-R.ttf", 15.0f );
	io.Fonts->Build();


	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ ImGuiCol_Text ] = ImVec4( 0.78f, 0.78f, 0.78f, 1.00f );
	style.Colors[ ImGuiCol_TextDisabled ] = ImVec4( 0.59f, 0.59f, 0.59f, 1.00f );
	style.Colors[ ImGuiCol_WindowBg ] = ImVec4( 0.02f, 0.02f, 0.02f, 1.0f );
	style.Colors[ ImGuiCol_ChildWindowBg ] = ImVec4( 0.03f, 0.03f, 0.03f, 1.0f );
	style.Colors[ ImGuiCol_Border ] = ImVec4( 0.10f, 0.10f, 0.10f, 1.0f );
	style.Colors[ ImGuiCol_FrameBg ] = ImVec4( 0.02f, 0.02f, 0.02f, 1.0f );
	style.Colors[ ImGuiCol_FrameBgHovered ] = ImVec4( 0.02f, 0.02f, 0.02f, 1.0f );
	style.Colors[ ImGuiCol_FrameBgActive ] = ImVec4( 0.02f, 0.02f, 0.02f, 1.0f );
	style.Colors[ ImGuiCol_TitleBg ] = bg;
	style.Colors[ ImGuiCol_TitleBgCollapsed ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.0f );
	style.Colors[ ImGuiCol_TitleBgActive ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.0f );
	style.Colors[ ImGuiCol_MenuBarBg ] = bg;
	style.Colors[ ImGuiCol_ScrollbarBg ] = bg;
	style.Colors[ ImGuiCol_ScrollbarGrab ] = accent;
	style.Colors[ ImGuiCol_ScrollbarGrabHovered ] = hovered;
	style.Colors[ ImGuiCol_ScrollbarGrabActive ] = active;
	style.Colors[ ImGuiCol_Separator ] = accent;
	style.Colors[ ImGuiCol_SliderGrab ] = accent;
	style.Colors[ ImGuiCol_SliderGrabActive ] = ImVec4( 1.f, 0.36f, 12.f, 1.f );
	style.Colors[ ImGuiCol_Button ] = ImVec4( 1.f, 1.f, 1.f, 0.01f );
	style.Colors[ ImGuiCol_ButtonHovered ] = hovered;
	style.Colors[ ImGuiCol_ButtonActive ] = accent;
	style.Colors[ ImGuiCol_Header ] = ImVec4( 1.f, 1.f, 1.f, 0.02f );
	style.Colors[ ImGuiCol_HeaderHovered ] = ImVec4( 6.f, 1.f, 1.f, 0.5f );;
	style.Colors[ ImGuiCol_HeaderActive ] = ImVec4( 6.f, 1.f, 1.f, 0.5f );;
	style.Colors[ ImGuiCol_CloseButton ] = ImVec4( 0.02f, 0.02f, 0.02f, 1.0f );
	style.Colors[ ImGuiCol_CloseButtonActive ] = ImVec4( 0.02f, 0.02f, 0.02f, 1.0f );
	style.Colors[ ImGuiCol_CloseButtonHovered ] = ImVec4( 0.02f, 0.02f, 0.02f, 1.0f );
	style.Colors[ ImGuiCol_ModalWindowDarkening ] = ImVec4( 0.02f, 0.02f, 0.02f, 1.0f );
	style.Colors[ ImGuiCol_ComboBg ] = bg;
	style.Colors[ ImGuiCol_PopupBg ] = ImVec4( 1.f, 1.f, 1.f, 0.03f );

	style.WindowRounding = 0.f;
	style.WindowPadding = ImVec2( 8, 8 );
	style.FramePadding = ImVec2( 5, 2 );
	style.ItemInnerSpacing = ImVec2( 4, 4 );
	style.DisplayWindowPadding = ImVec2( 805, 472 );
	style.DisplaySafeAreaPadding = ImVec2( 4, 4 );
	style.FrameRounding = 0.f;
	style.ScrollbarSize = 2.f;
	style.ScrollbarRounding = 0.f;
	style.GrabRounding = 0.f;
	style.GrabMinSize = 8.f;
	style.AntiAliasedShapes = true;
	style.ChildWindowRounding = 0.f;

	G::d3dinit = true;
}