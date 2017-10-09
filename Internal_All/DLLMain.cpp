#pragma once 

#include "MainInclude.h"

DWORD __stdcall Memes( HMODULE hModule )
{
	bool signaled[ 32 ] = { 0 };
	bool success = false;

	std::uint32_t totalSlept = 0;

	const std::initializer_list<std::wstring>& modules = { L"client.dll", L"engine.dll", L"shaderapidx9.dll" };
	while ( true )
	{
		for ( auto i = 0u; i < modules.size(); ++i )
		{
			auto& module = *( modules.begin() + i );
			if ( !signaled[ i ] && GetModuleHandleW( std::data( module ) ) != NULL )
			{
				signaled[ i ] = true;

				//
				// Checks if all modules are signaled
				//
				bool done = true;
				for ( auto j = 0u; j < modules.size(); ++j )
				{
					if ( !signaled[ j ] )
					{
						done = false;
						break;
					}
				}
				if ( done )
				{
					success = true;
					goto exit;
				}
			}
		}
		if ( totalSlept > std::uint32_t( 10000 ) )
		{
			break;
		}
		Sleep( 10 );
		totalSlept += 10;
	}

exit: if ( !success ) return false;

	U::Startup();

	while ( !GetAsyncKeyState( VK_END ) )
		Sleep( 10 );

	Vars.Menu.bOpened = false;

	Sleep( 10 );

	Hook->HooksUnhook();

	FreeLibraryAndExitThread( hModule , NULL );

	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  dwReasonForCall, LPVOID lpReserved )
{
	switch ( dwReasonForCall )
	{
		case DLL_PROCESS_ATTACH:

			CreateThread( NULL, NULL, ( LPTHREAD_START_ROUTINE ) Memes, hModule, NULL, NULL );

			return true;

		case DLL_PROCESS_DETACH:
			if ( lpReserved == nullptr )
			{

			}
			return true;

		default:
			return true;
	}

	return TRUE;
}
