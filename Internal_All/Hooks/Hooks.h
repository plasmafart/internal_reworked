#pragma once

extern WNDPROC oWndProc;

using FrameStageNotifyFn = void( __stdcall* )( ClientFrameStage_t );
extern FrameStageNotifyFn oFrameStageNotify;

using EndSceneFn = long( __stdcall* )( IDirect3DDevice9* device );
extern EndSceneFn oEndScene;

using ResetFn = long( __stdcall* )( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp );
extern ResetFn oReset;

using OverrideViewFn = void( __stdcall* )( CViewSetup* );
extern OverrideViewFn oOverrideView;

using SvCheatsGetBoolFn = bool( __thiscall * )( void* );
extern SvCheatsGetBoolFn oSvCheatsGetBool;

using PaintTraverseFn = void( __thiscall* )( void*, unsigned int, bool, bool );
extern PaintTraverseFn oPaintTraverse;

using CreateMoveFn = bool( __stdcall* )( float, CUserCmd* );
extern CreateMoveFn oCreateMove;

using DrawModelExecuteFn = void*( __stdcall* )( void*, void*, const ModelRenderInfo_t&, matrix3x4_t* );
extern DrawModelExecuteFn oDrawModelExecute;

using OverrideConfigFn = bool( __thiscall* )( IMaterialSystem*, MaterialSystem_Config_t*, bool );
extern OverrideConfigFn oOverrideConfig;


extern LRESULT __stdcall g_hkWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

extern void __stdcall g_hkFrameStageNotify( ClientFrameStage_t stage );
extern long __stdcall g_hkEndScene( IDirect3DDevice9* pDevice );
extern long __stdcall g_hkReset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters );
extern void __stdcall g_hkOverrideView( CViewSetup* vsView );
extern bool __fastcall g_hkSvCheatsGetBool( void* pConVar, void* edx );
extern void __fastcall g_hkPaintTraverse( void* pPanels, int edx, unsigned int panel, bool forceRepaint, bool allowForce );
extern bool __stdcall g_hkCreateMove( float flInputSampleTime, CUserCmd* cmd );
extern void __stdcall g_hkDrawModelExecute( void* context, void* state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld );
extern bool __fastcall g_hkOverrideConfig( IMaterialSystem* this0, int edx, MaterialSystem_Config_t* config, bool forceUpdate );


//Netvar
extern void __cdecl g_hkSequence( const CRecvProxyData* proxy_data_const, void* entity, void* output );

