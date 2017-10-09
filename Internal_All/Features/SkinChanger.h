#pragma once
struct StickerSetting
{
	void UpdateValues();
	void UpdateIds();
	int kit_index = 0;
	int kit_vector_index = 0;
	float wear = FLT_MIN;
	float scale = 1.f;
	float rotation = 0.f;
};

struct EconomyItem_t
{
	void UpdateValues();
	void UpdateIds();

	char name[ 32 ] = "Default";
	bool enabled = false;
	int definition_vector_index = 0;
	int definition_index = 1;
	int entity_quality_vector_index = 0;
	int entity_quality_index = 0;
	int paint_kit_vector_index = 0;
	int paint_kit_index = 0;
	int definition_override_vector_index = 0;
	int definition_override_index = 0;
	int seed = 0;
	int stat_trak = 0;
	float wear = FLT_MIN;
	char custom_name[ 32 ] = "";
	//std::array<StickerSetting, 5> stickers;
}; 

class CSkinChanger
{
public:
	void Run( ClientFrameStage_t stage );

	void Save();
	void Load();
	EconomyItem_t* GetByDefinitionIndex( int definition_index );

	std::vector<EconomyItem_t>& GetItems() { return m_items; }

	std::unordered_map<std::string, std::string>& GetIconOverrideMap() { return m_icon_overrides; }
	const char* GetIconOverride( const std::string& original ) { return m_icon_overrides.count( original ) ? m_icon_overrides.at( original ).c_str() : nullptr; }

	
private:
	std::vector<EconomyItem_t> m_items;
	std::unordered_map<std::string, std::string> m_icon_overrides;

public:
	char* appdata = getenv( "APPDATA" );
	std::string ext = "\\noskinchanger\\";

};