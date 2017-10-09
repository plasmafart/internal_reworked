#include "..\MainInclude.h"

void U::InitKeyValues( KeyValues* pKeyValues, const char* name )
{
	static InitKeyValuesFn InitKeyValuesEx = ( InitKeyValuesFn ) ( Offsets->InitKeyValuesEx );
	InitKeyValuesEx( pKeyValues, name );
}

void U::LoadFromBuffer( KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc )
{
	static LoadFromBufferFn LoadFromBufferEx = ( LoadFromBufferFn ) ( Offsets->LoadFromBufferEx );
	LoadFromBufferEx( pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc );
}

DWORD U::FindPattern( std::string moduleName, std::string pattern )
{
	const char* daPattern = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD moduleBase = ( DWORD ) GetModuleHandleA( moduleName.c_str() );
	MODULEINFO miModInfo; GetModuleInformation( GetCurrentProcess(), ( HMODULE ) moduleBase, &miModInfo, sizeof( MODULEINFO ) );
	DWORD moduleEnd = moduleBase + miModInfo.SizeOfImage;
	for ( DWORD pCur = moduleBase; pCur < moduleEnd; pCur++ )
	{
		if ( !*daPattern )
			return firstMatch;

		if ( *( PBYTE ) daPattern == '\?' || *( BYTE* ) pCur == getByte( daPattern ) )
		{
			if ( !firstMatch )
				firstMatch = pCur;

			if ( !daPattern[ 2 ] )
				return firstMatch;

			if ( *( PWORD ) daPattern == '\?\?' || *( PBYTE ) daPattern != '\?' )
				daPattern += 3;

			else
				daPattern += 2;
		}
		else
		{
			daPattern = pattern.c_str();
			firstMatch = 0;
		}
	}
	return 0;
}

void InitializeInterfaces()
{

	g_pClient = U::GetInterface<IBaseClientDll>( strenc( "Client.dll" ), strenc( "VClient018" ) );
	g_pClientEntList = U::GetInterface<IClientEntityList>( strenc( "Client.dll" ), strenc( "VClientEntityList003" ) );
	g_pCvar = U::GetInterface<ICVar>( strenc( "vstdlib.dll" ), strenc( "VEngineCvar007" ) );
	g_pClientMode = **( IClientModeShared*** ) ( ( *( DWORD** ) g_pClient )[ 10 ] + 0x5 );
	g_pEngine = U::GetInterface<IEngineClient>( strenc( "engine.dll" ), strenc( "VEngineClient014" ) );
	g_pEngineTrace = U::GetInterface<IEngineTrace>( strenc( "engine.dll" ), strenc( "EngineTraceClient004" ) );
	g_pClientState = **( CBaseClientState*** ) ( ( *( DWORD** ) g_pEngine )[ 12 ] + 0x10 );

	g_pInput = *( IInput** ) ( ( *( DWORD** ) g_pClient )[ 15 ] + 0x1 );
	g_pInputSystem = U::GetInterface<IInputSystem>( strenc( "inputsystem.dll" ), strenc( "InputSystemVersion001" ) );
	g_pGameEventManager = U::GetInterface<IGameEventManager2>( strenc( "engine.dll" ), strenc( "GAMEEVENTSMANAGER002" ) );
	g_pVModelInfo = U::GetInterface<IVModelInfo>( strenc( "engine.dll" ), strenc( "VModelInfoClient004" ) );
	g_pLocalize = U::GetInterface<ILocalize>( strenc( "localize.dll" ), strenc( "Localize_001" ) );

	g_pGlobalVarsBase = **( IGlobalVarsBase*** ) ( ( *( DWORD** ) g_pClient )[ 0 ] + 0x1B );
	g_pSurface = U::GetInterface<ISurface>( strenc( "vguimatsurface.dll" ), strenc( "VGUI_Surface031" ) );
	g_pVPanel = U::GetInterface<IVPanel>( strenc( "vgui2.dll" ), strenc( "VGUI_Panel009" ) );
	g_pVModelRender = U::GetInterface<IVModelRender>( strenc( "engine.dll" ), strenc( "VEngineModel016" ) );
	g_pVRenderView = U::GetInterface<IVRenderView>( strenc( "engine.dll" ), strenc( "VEngineRenderView014" ) );
	g_pMaterialSystem = U::GetInterface<IMaterialSystem>( strenc( "materialsystem.dll" ), strenc( "VMaterialSystem080" ) );
}

void U::SetupTextures()
{
	T::matVisible = g_pMaterialSystem->CreateMaterial( false, false, false );
	T::matHidden = g_pMaterialSystem->CreateMaterial( false, true, false );
}

void U::ReleaseTextures()
{
	if ( T::matVisible )
	{
		T::matVisible->Release();
		T::matVisible->DeleteIfUnreferenced();
	}
	if ( T::matHidden )
	{
		T::matHidden->Release();
		T::matHidden->DeleteIfUnreferenced();
	}
}


void U::Startup()
{
	InitializeInterfaces();
	Offsets->GrabOffsets();
	D::SetupFonts();
	U::SetupTextures();

	while ( !( G::Window = FindWindowA( charenc( "Valve001" ), NULL ) ) )
		Sleep( 200 );

	oWndProc = ( WNDPROC ) SetWindowLongPtr( G::Window, GWL_WNDPROC, ( LONG_PTR ) g_hkWndProc );

	Hook->HooksInit();

	while ( !GetModuleHandleA( "serverbrowser.dll" ) )
		Sleep( 100 );

	InitializeKits();
	F::SkinChanger->Load();
	Config->LoadPreset();
}


void *KeyValues::operator new( size_t iAllocSize )
{
	static PVOID pKeyValuesSystem;
	if ( !pKeyValuesSystem )
	{
		typedef PVOID( __cdecl* oKeyValuesSystem )( );
		oKeyValuesSystem KeyValuesSystem = ( oKeyValuesSystem ) GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "KeyValuesSystem" );

		pKeyValuesSystem = KeyValuesSystem();
	}

	typedef PVOID( __thiscall* oAllocKeyValuesMemory )( PVOID, size_t );
	return U::GetVFunc<oAllocKeyValuesMemory>( pKeyValuesSystem, 1 )( pKeyValuesSystem, iAllocSize );
}

void KeyValues::operator delete( PVOID pMem )
{
	static PVOID pKeyValuesSystem;
	if ( !pKeyValuesSystem )
	{
		typedef PVOID( __cdecl* oKeyValuesSystem )( );
		oKeyValuesSystem KeyValuesSystem = ( oKeyValuesSystem ) GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "KeyValuesSystem" );

		pKeyValuesSystem = KeyValuesSystem();
	}

	typedef void( __thiscall* oFreeKeyValuesMemory )( PVOID, PVOID );
	U::GetVFunc<oFreeKeyValuesMemory>( pKeyValuesSystem, 2 )( pKeyValuesSystem, pMem );
}

