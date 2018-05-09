#pragma once
#include "Hooks.h"
#include "Hacks.h"
#include "Chams.h"
#include "Menu.h"
#include "AntiAntiAim.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "MiscHacks.h"
#include "CRC32.h"
#include "BulletTracers.h"
#include "Materials.h"
#include <math.h>
#include <ctime>
#include <intrin.h>
#include "backtrackers.h"
#include "EdgyLagComp.h"
#include "igameventmanager.h"
#include <Windows.h>
#include "hitmarker.h"
#include "MemePredict.h"
#include "bullettracer.h"
#include "MiscClasses.h"
#include "Entities.h"
#include "GlowManager.h"
#include "Autowall.h"
#include "Resolver.h"
#include "DamageIndicators.h"
namespace Globals
{
	extern CUserCmd* UserCmd;
	extern IClientEntity* Target;
	extern int Shots;
	extern bool change;
	extern int TargetID;
	extern int missedshots;
	extern int HitboxID;
	extern std::map<int, QAngle> storedshit;
}