#pragma once

#include "IAppSystem.h"

#include "CBaseClientState.h"
#include "ClientClass.h"
#include "IClientEntity.h"
#include "IClientModeShared.h"
#include "IInput.h"
#include "BaseClasses.h"
#include "IBaseClientDLL.h"
#include "IClientEntityList.h"
#include "ICvar.h"
#include "IEngineClient.h"
#include "IEngineTrace.h"
#include "IGameEvent.h"
#include "IInputSystem.h"
#include "Interfaces.h"
#include "IVModelInfo.h"
#include "ILocalize.h"
#include "IGlobalVarsBase.h"
#include "ISurface.h"
#include "IVPanel.h"
#include "IVModelRender.h"
#include "IVPanel.h"
#include "IVRenderView.h"
#include "IMaterialSystem.h"
#include "IMaterial.h"



extern CBaseClientState*		g_pClientState;
extern IBaseClientDll*			g_pClient;
extern IClientModeShared*		g_pClientMode;
extern IClientEntityList*		g_pClientEntList;
extern ICVar*					g_pCvar;
extern IInput*					g_pInput;
extern IInputSystem*			g_pInputSystem;
extern IEngineClient*			g_pEngine;
extern IEngineTrace*			g_pEngineTrace;
extern IGameEventManager2*		g_pGameEventManager;
extern IVModelInfo*				g_pVModelInfo;
extern ILocalize*				g_pLocalize;
extern IMaterialSystem*			g_pMaterialSystem;
extern IMaterial*				g_pMaterial;
extern IGlobalVarsBase*			g_pGlobalVarsBase;
extern ISurface*				g_pSurface;
extern IVPanel*					g_pVPanel;
extern IVModelRender*			g_pVModelRender;
extern IVRenderView*			g_pVRenderView;

