/*
Syn's AyyWare Framework
*/

#pragma once

// Includes
#include "CommonIncludes.h"
#include "SDK.h"
#include "IPrediction.h"
#include "igameventmanager.h"
// Namespace to contain all the valve interfaces
namespace interfaces
{
	// Gets handles to all the interfaces needed
	void Initialise();

	extern IBaseClientDLL* Client;
	extern IVEngineClient* engine;
	extern IPanel* Panels;
	extern IClientEntityList* g_entitylist;
	extern ISurface* Surface;
	extern IVDebugOverlay* DebugOverlay;
	extern IClientModeShared *ClientMode;
	extern CGlobalVarsBase *Globals;
	extern IViewRenderBeams* ViewRenderBeams;
	extern CGlobalVarsBase* g_Globals;
	extern DWORD *Prediction;
	extern IVEffects* Dlight;
	extern CMaterialSystem* MaterialSystem;
	extern IViewRenderBeams* g_pViewRenderBeams;
	//extern IInputSystem* InputSystem;
	extern CVRenderView* RenderView;
	extern IVModelRender* ModelRender;
	extern CModelInfo* ModelInfo;
	extern IEngineTrace* Trace;
	extern IPhysicsSurfaceProps* PhysProps;
	extern ICVar *CVar;
	extern CInput* pInput;
	extern IMoveHelper* MoveHelper;
	extern IGameMovement *GameMovement;
	extern IPrediction* GamePrediction;
	extern IGameEventManager2 *GameEventManager;
	extern IMDLCache* ModelCache;
	extern IClientMode* m_pClientMode;
};