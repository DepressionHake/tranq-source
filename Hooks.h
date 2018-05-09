/*
bonus's tranquility framework 2018
*/

#pragma once

// It's actually in DLLMain but w/e
extern bool DoUnload;
extern bool bGlovesNeedUpdate;
extern bool bGlovesNeedUpdate2;

#include "Utilities.h"
namespace Hooks
{
	void Initialise();
	void UndoHooks();

	// VMT Managers
	extern Utilities::Memory::VMTManager VMTPanel; // Hooking drawing functions
	extern Utilities::Memory::VMTManager VMTClient; // Maybe CreateMove
	extern Utilities::Memory::VMTManager VMTClientMode; // CreateMove for functionality
	extern Utilities::Memory::VMTManager VMTModelRender; // DrawModelEx for chams
	extern Utilities::Memory::VMTManager VMTPrediction; // InPrediction for no vis recoil
	extern Utilities::Memory::VMTManager VMTPlaySound; // Autoaccept shit
	extern Utilities::Memory::VMTManager VMTRenderView;
};


namespace Resolver
{
	extern bool didhitHS;
}

extern bool flipAA;
extern int antiAimSide;


extern float testFloat1;
extern float testFloat2;
extern float testFloat3;
extern float testFloat4;
extern bool islbyupdate;
extern float ProxyLBYtime;
extern int LBYBreakerTimer;
extern float enemysLastProxyTimer[65];
extern float consoleProxyLbyLASTUpdateTime; // This is in ProxyLBY AntiAim.cpp
extern float fsnLBY;
extern float enemyLBYTimer[65];
extern int hittedLogHits[65];
extern int missedLogHits[65];
extern bool switchAntiAimSide;



extern float lineRealAngle;
extern bool flip_bool;
extern float flipBool;
extern int shotsfired;
extern int ResolverStage[65];
extern int resolverstage[64];
extern float lineFakeAngle;
