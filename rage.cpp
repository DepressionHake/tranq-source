/*
bonus's tranquility framework 2018
*/

#include "RageBot.h"
#include "RenderManager.h"
#include "Resolver.h"
#include "Autowall.h"
#include <iostream>
#include "UTIL Functions.h"

#define TICK_INTERVAL			( interfaces::Globals->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t ) ( interfaces::Globals->interval_per_tick *( t ) )

void CRageBot::Init()
{
	IsAimStepping = false;
	IsLocked = false;
	TargetID = -1;
}

void CRageBot::Draw()
{

}

bool IsAbleToShoot(IClientEntity* localplayer)
{
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeaponHandle());

	if (!localplayer)
		return false;

	if (!pWeapon)
		return false;

	float flServerTime = localplayer->GetTickBase() * interfaces::Globals->interval_per_tick;

	return (!(pWeapon->GetNextPrimaryAttack() > flServerTime));
}


float hitchance(IClientEntity* localplayer, CBaseCombatWeapon* pWeapon)
{
	//	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeaponHandle());
	float hitchance = 101;
	if (!pWeapon) return 0;
	if (g_menu.rage.AccuracyHitchanceVal.getvalue() > 1)
	{//Inaccuracy method
		float inaccuracy = pWeapon->GetInaccuracy();
		if (inaccuracy == 0) inaccuracy = 0.0000001;
		inaccuracy = 1 / inaccuracy;
		hitchance = inaccuracy;

	}
	return hitchance;
}

bool spreadlimit(IClientEntity* localplayer, CBaseCombatWeapon* pWeapon)
{
	if (!pWeapon) return false;
	float inaccuracy = pWeapon->GetInaccuracy();
	return inaccuracy < (float)g_menu.rage.AccuracyHitchanceVal.getvalue() / 1000.f;
}

// (DWORD)g_pNetVars->GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
// You need something like this
bool CanOpenFire() // Creds to untrusted guy
{
	IClientEntity* localplayerEntity = (IClientEntity*)interfaces::g_entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (!localplayerEntity)
		return false;

	CBaseCombatWeapon* entwep = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(localplayerEntity->GetActiveWeaponHandle());

	float flServerTime = (float)localplayerEntity->GetTickBase() * interfaces::Globals->interval_per_tick;
	float flNextPrimaryAttack = entwep->GetNextPrimaryAttack();

	std::cout << flServerTime << " " << flNextPrimaryAttack << std::endl;

	return !(flNextPrimaryAttack > flServerTime);
}

void CRageBot::Move(CUserCmd *pCmd, bool &bSendPacket)
{
	IClientEntity* pEnt;
	IClientEntity* localplayerEntity = (IClientEntity*)interfaces::g_entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (!localplayerEntity)
		return;

	// Master switch
	if (!g_menu.rage.Active.getstate())
		return;

	// Anti Aim 
	if (g_menu.rage.AntiAimEnable.getstate())
	{
		static int ChokedPackets = -1;

		CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(hackManager.localplayer()->GetActiveWeaponHandle());
		if (!pWeapon)
			return;

		if (ChokedPackets < 1 && localplayerEntity->GetLifeState() == LIFE_ALIVE && pCmd->buttons & IN_ATTACK && CanOpenFire() && GameUtils::IsBallisticWeapon(pWeapon))
		{
			bSendPacket = false;
		}
		else
		{
			if (localplayerEntity->GetLifeState() == LIFE_ALIVE)
			{
				DoAntiAim(pCmd, bSendPacket, pEnt);
			}
			ChokedPackets = -1;
		}
	}

	// Aimbot
	if (g_menu.rage.AimbotEnable.getstate())
		DoAimbot(pCmd, bSendPacket);

	// Recoil
	if (g_menu.rage.AccuracyRecoil.getstate())
		DoNoRecoil(pCmd);

	LastAngle = pCmd->viewangles;
}

Vector BestPoint(IClientEntity *targetPlayer, Vector &final)
{
	IClientEntity* localplayer = hackManager.localplayer();

	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pHit = targetPlayer;
	ray.Init(final + Vector(0, 0, 10), final);
	interfaces::Trace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	final = tr.endpos;
	return final;
}


void CRageBot::DoAimbot(CUserCmd *pCmd, bool &bSendPacket)
{
	IClientEntity* pTarget = nullptr;
	IClientEntity* localplayer = hackManager.localplayer();
	Vector Start = localplayer->GetViewOffset() + localplayer->GetOrigin();
	bool FindNewTarget = true;
	//IsLocked = false;

	CSWeaponInfo* weapInfo = ((CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeaponHandle()))->GetCSWpnData();

	// Don't aimbot with the knife..
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeaponHandle());

	if (GameUtils::IsRevolver(pWeapon) && g_menu.rage.AimbotAutoRevolver.getstate())
	{
		static int delay = 0; //shitty 
		delay++; //so bad

		if (delay <= 15) //shit
			pCmd->buttons |= IN_ATTACK; //why
		else
			delay = 0; //garbage
	}

	if (pWeapon)
	{
		if (pWeapon->GetAmmoInClip() == 0 || !GameUtils::IsBallisticWeapon(pWeapon))
		{
			TargetID = 0;
			pTarget = nullptr;
			HitBox = -1;
			return;
		}
	}
	else
		return;

	// Make sure we have a good target
	if (IsLocked && TargetID >= 0 && HitBox >= 0)
	{
		pTarget = interfaces::g_entitylist->GetClientEntity(TargetID);
		if (pTarget  && TargetMeetsRequirements(pTarget))
		{
			HitBox = HitScan(pTarget);
			if (HitBox >= 0)
			{
				Vector ViewOffset = localplayer->GetOrigin() + localplayer->GetViewOffset();
				Vector View;
				interfaces::engine->GetViewAngles(View);
				float FoV = FovToPlayer(ViewOffset, View, pTarget, HitBox);
				if (FoV < g_menu.rage.AimbotFov.getvalue())
					FindNewTarget = false;
			}
		}
	}

	// Find a new target, apparently we need to
	if (FindNewTarget)
	{
		TargetID = 0;
		pTarget = nullptr;
		HitBox = -1;

		// Target selection type
		TargetID = GetTargetHealth();

		// Memes
		if (TargetID >= 0)
		{
			pTarget = interfaces::g_entitylist->GetClientEntity(TargetID);
		}
		else
		{
			pTarget = nullptr;
			HitBox = -1;
		}
	}

	Globals::Target = pTarget;
	Globals::TargetID = TargetID;

	// If we finally have a good target
	if (TargetID >= 0 && pTarget)
	{
		// Get the hitbox to shoot at
		HitBox = HitScan(pTarget);

		if (!CanOpenFire())
			return;

		// Key
		if (g_menu.rage.AimbotKeyPress.getstate())
		{
			int Key = g_menu.rage.AimbotKeyBind.GetKey();
			if (Key >= 0 && !GUI.GetKeyState(Key))
			{
				TargetID = -1;
				pTarget = nullptr;
				HitBox = -1;
				return;
			}
		}

		float pointscale = g_menu.rage.TargetPointscale.getvalue() - 5.f;

		Vector Point;
		Vector AimPoint = GetHitboxPosition(pTarget, HitBox) + Vector(0, 0, pointscale);

		if (g_menu.rage.TargetMultipoint.getstate())
			Point = BestPoint(pTarget, AimPoint);
		else
			Point = AimPoint;

		if (GameUtils::IsScopedWeapon(pWeapon) && !pWeapon->IsScoped() && g_menu.rage.AccuracyAutoScope.getstate()) // Autoscope
		{
			pCmd->buttons |= IN_ATTACK2;
		}
		else
		{
			if ((g_menu.rage.AccuracyHitchanceVal.getvalue() * 1.5 <= hitchance(localplayer, pWeapon)) || g_menu.rage.AccuracyHitchanceVal.getvalue() == 0 || *pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() == 64)
			{
				if (AimAtPoint(localplayer, Point, pCmd, bSendPacket))
				{
					if (g_menu.rage.AimbotAutoFire.getstate() && !(pCmd->buttons & IN_ATTACK))
						pCmd->buttons |= IN_ATTACK;
					else
						return;
				}
				else if (g_menu.rage.AimbotAutoFire.getstate() && !(pCmd->buttons & IN_ATTACK))
				{
					pCmd->buttons |= IN_ATTACK;
				}
			}
		}

		if (IsAbleToShoot(localplayer) && pCmd->buttons & IN_ATTACK)
			Globals::Shots += 1;

		// Stop and Crouch
		if (TargetID >= 0 && pTarget)
		{
			switch (g_menu.rage.AccuracyMovement.getindex())
			{
			case 0:
				break;
			case 1:
				pCmd->forwardmove = 0.f;
				pCmd->sidemove = 0.f;
				break;
			case 2:
				pCmd->buttons |= IN_DUCK;
				break;
			}
		}
	}

	// Auto Pistol
	if (GameUtils::IsPistol(pWeapon) && g_menu.rage.AimbotAutoPistol.getstate())
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			static bool WasFiring = false;
			WasFiring = !WasFiring;

			if (WasFiring)
			{
				pCmd->buttons |= IN_ATTACK2;
			}
		}
	}
}

bool CRageBot::TargetMeetsRequirements(IClientEntity* m_entity)
{
	// Is a valid player
	if (m_entity && m_entity->IsDormant() == false && m_entity->IsAlive() && m_entity->index() != hackManager.localplayer()->index())
	{
		// Entity Type checks
		ClientClass *pClientClass = m_entity->GetClientClass();
		player_info_t pinfo;
		if (pClientClass->m_ClassID == (int)CSGOClassID::CCSPlayer && interfaces::engine->GetPlayerInfo(m_entity->index(), &pinfo))
		{
			// Team Check
			if (m_entity->GetTeamNum() != hackManager.localplayer()->GetTeamNum() || g_menu.rage.TargetFriendlyFire.getstate())
			{
				// Spawn Check
				if (!m_entity->HasGunGameImmunity())
				{
					return true;
				}
			}
		}
	}

	// They must have failed a requirement
	return false;
}

float CRageBot::FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* m_entity, int aHitBox)
{
	CONST FLOAT MaxDegrees = 180.0f;
	Vector Angles = View;
	Vector Origin = ViewOffSet;
	Vector Delta(0, 0, 0);
	Vector Forward(0, 0, 0);
	AngleVectors(Angles, &Forward);
	Vector AimPos = GetHitboxPosition(m_entity, aHitBox);
	VectorSubtract(AimPos, Origin, Delta);
	Normalize(Delta, Delta);
	FLOAT DotProduct = Forward.Dot(Delta);
	return (acos(DotProduct) * (MaxDegrees / PI));
}

int CRageBot::GetTargetCrosshair()
{
	// Target selection
	int target = -1;
	float minFoV = g_menu.rage.AimbotFov.getvalue();

	IClientEntity* localplayer = hackManager.localplayer();
	Vector ViewOffset = localplayer->GetOrigin() + localplayer->GetViewOffset();
	Vector View; interfaces::engine->GetViewAngles(View);

	for (int i = 0; i < interfaces::g_entitylist->GetMaxEntities(); i++) //GetHighestEntityIndex()
	{
		IClientEntity *m_entity = interfaces::g_entitylist->GetClientEntity(i);
		if (TargetMeetsRequirements(m_entity))
		{
			int NewHitBox = HitScan(m_entity);
			if (NewHitBox >= 0)
			{
				float fov = FovToPlayer(ViewOffset, View, m_entity, 0);
				if (fov < minFoV)
				{
					minFoV = fov;
					target = i;
				}
			}
		}
	}

	return target;
}

int CRageBot::GetTargetDistance()
{
	// New Distance Aimbot
	int target = -1;
	int minDist = 8192;

	IClientEntity* localplayer = hackManager.localplayer();
	Vector ViewOffset = localplayer->GetOrigin() + localplayer->GetViewOffset();
	Vector View; interfaces::engine->GetViewAngles(View);

	for (int i = 0; i < interfaces::g_entitylist->GetHighestEntityIndex(); i++)
	{
		IClientEntity *m_entity = interfaces::g_entitylist->GetClientEntity(i);
		if (TargetMeetsRequirements(m_entity))
		{
			int NewHitBox = HitScan(m_entity);
			if (NewHitBox >= 0)
			{
				Vector Difference = localplayer->GetOrigin() - m_entity->GetOrigin();
				int Distance = Difference.Length();
				float fov = FovToPlayer(ViewOffset, View, m_entity, 0);
				if (Distance < minDist && fov < g_menu.rage.AimbotFov.getvalue())
				{
					minDist = Distance;
					target = i;
				}
			}
		}
	}
	return target;
}


inline float get_distance(const Vector &start, const Vector &end)
{
	float distance = sqrt((start - end).Length());

	if (distance < 1.0f)
		distance = 1.0f;

	return distance;
}

bool InRange(float x, float one, float two)
{
	return x >= one && x <= two;
}

void CRageBot::KnifeBot(CUserCmd *pCmd, IClientEntity* m_local)
{
	if (!g_menu.misc.KnifeBot.getstate()) return;
	if (!(interfaces::engine->IsConnected() && interfaces::engine->IsInGame())) return;
	if (!m_local || !m_local->IsAlive()) return;
	auto weapInfo = ((CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(m_local->GetActiveWeaponHandle()))->GetCSWpnData();
	auto m_weapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(m_local->GetActiveWeaponHandle());
	if (!m_weapon) return;
	if (!GameUtils::IsBallisticWeapon) return;
	auto tar = GetTargetDistance();
	auto target = interfaces::g_entitylist->GetClientEntity(tar);
	if (!target) return;
	auto localRot = m_local->GetRotation();
	auto targetRot = target->GetRotation();
	auto localPos = m_local->GetOrigin();
	auto targetPos = target->GetOrigin();
	auto deltaPos = get_distance(localPos, targetPos);
	auto deltaRot = get_distance(localRot, targetRot);
	auto canKnifeable = deltaPos < 8;
	if (!canKnifeable) return;
	auto backstab = InRange(deltaRot, 0, 6) || InRange(deltaRot, 17, 22);
	if (backstab)
		pCmd->buttons |= IN_ATTACK2;
	else {
		auto hp = target->GetHealth();
		auto armor = target->ArmorValue() > 1;
		auto minDmgSol = armor ? 34 : 40;
		auto minDmgSag = armor ? 55 : 65;
		if (hp <= minDmgSag)
			pCmd->buttons |= IN_ATTACK2;
		else if (hp <= minDmgSol)
			pCmd->buttons |= IN_ATTACK;
		else
			pCmd->buttons |= IN_ATTACK;
	}
}

int CRageBot::GetTargetHealth()
{
	// Target selection
	int target = -1;
	int minHealth = 101;

	IClientEntity* localplayer = hackManager.localplayer();
	Vector ViewOffset = localplayer->GetOrigin() + localplayer->GetViewOffset();
	Vector View; interfaces::engine->GetViewAngles(View);

	for (int i = 0; i < interfaces::g_entitylist->GetMaxEntities(); i++)
	{
		IClientEntity *m_entity = interfaces::g_entitylist->GetClientEntity(i);
		if (TargetMeetsRequirements(m_entity))
		{
			int NewHitBox = HitScan(m_entity);
			if (NewHitBox >= 0)
			{
				int Health = m_entity->GetHealth();
				float fov = FovToPlayer(ViewOffset, View, m_entity, 0);
				if (Health < minHealth && fov < g_menu.rage.AimbotFov.getvalue())
				{
					minHealth = Health;
					target = i;
				}
			}
		}
	}

	return target;
}

int CRageBot::HitScan(IClientEntity* m_entity)
{
	std::vector<int> HitBoxesToScan;
	bool AWall = g_menu.rage.AccuracyAutoWall.getstate();

	// Get the hitboxes to scan
	int HitScanMode = g_menu.rage.TargetHitscan.getstate();
	int health = g_menu.rage.TargetBaimHealth.getvalue();
	int shots = g_menu.rage.TargetSmart.getvalue();
	IClientEntity* localplayer = hackManager.localplayer();
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeaponHandle());

	// No Hitscan, just a single hitbox
	switch (g_menu.rage.TargetHitbox.getindex())
	{
	case 0:
		HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
		break;
	case 1:
		HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
		break;
	case 2:
		HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
		break;
	case 3:
		HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
		break;
	case 4:
		HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
		break;
	}

	if (g_menu.rage.TargetSecondaryHitbox.getstate())
	{
		HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
		HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach); 
		HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
	}

	if (g_menu.rage.TargetHitscan.getstate())
	{
		if (g_menu.rage.TargetHitbox.getindex() == 1) //Head
		{
			HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
			HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
		}
		if (g_menu.rage.TargetHitbox.getindex() == 2) //Neck
		{
			HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
			HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
		}
		if (g_menu.rage.TargetHitbox.getindex() == 3) //Chest
		{
			HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
		}
		if (g_menu.rage.TargetHitbox.getindex() == 3) //Stomach
		{
			HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
		}
		if (g_menu.rage.TargetHitbox.getindex() == 3) //Pelvis
		{
			HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
		}
	}
	if (m_entity->GetHealth() < health);
	{
		HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
	}
	if (g_menu.rage.TargetSmart.getvalue() > 1);
	{
		if (Globals::Shots > shots)
		{
			HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
		}
	}
	if (GameUtils::IsAWP(pWeapon))
	{
		if (g_menu.rage.AimbotAwpAtBody.getstate())
		{
			HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
			HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
		}
	}

	if (g_menu.rage.PreferBodyAim.getstate())
	{
		HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
	}

	if (g_menu.rage.AimbotBaimKey.GetKey() > 0)
	{
		HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
	}

	for (auto HitBoxID : HitBoxesToScan)
	{
		if (AWall) {
			Vector Point = GetHitboxPosition(m_entity, HitBoxID);
			float dmg = 0.f;
			if (CanHit(Point, &dmg)) {
				if (dmg >= g_menu.rage.AccuracyMinimumDamage.getvalue()) {
					return HitBoxID;
				}
			}
		}
		else {
			if (GameUtils::IsVisible(hackManager.localplayer(), m_entity, HitBoxID))
				return HitBoxID;
		}
	}

	return -1;
}

void CRageBot::DoNoRecoil(CUserCmd *pCmd)
{
	// Ghetto rcs shit, implement properly later
	IClientEntity* localplayer = hackManager.localplayer();
	if (localplayer)
	{
		Vector AimPunch = localplayer->localPlayerExclusive()->GetAimPunchAngle();
		if (AimPunch.Length2D() > 0 && AimPunch.Length2D() < 150)
		{
			pCmd->viewangles -= AimPunch * 2;
			GameUtils::NormaliseViewAngle(pCmd->viewangles);
		}
	}
}

bool CRageBot::AimAtPoint(IClientEntity* localplayer, Vector point, CUserCmd *pCmd, bool &bSendPacket)
{
	bool ReturnValue = false;
	// Get the full angles
	if (point.Length() == 0) return ReturnValue;
	IClientEntity* Pent;
	Vector angles;
	Vector src = localplayer->GetEyePosition();
	Vector delta = point - localplayer->GetEyePosition();

	VectorAngles(point - src, angles);
	if (g_menu.misc.OtherSafeMode.getstate()) {
		GameUtils::NormaliseViewAngle(angles);
	}
	if (angles[0] != angles[0] || angles[1] != angles[1])
	{
		return ReturnValue;
	}


	IsLocked = true;
	//-----------------------------------------------

	// Aim Step Calcs
	Vector ViewOffset = localplayer->GetOrigin() + localplayer->GetViewOffset();
	if (!IsAimStepping)
		LastAimstepAngle = LastAngle; // Don't just use the viewangs because you need to consider aa

	float fovLeft = FovToPlayer(ViewOffset, LastAimstepAngle, interfaces::g_entitylist->GetClientEntity(TargetID), 0);

	if (fovLeft > 25.0f && g_menu.rage.AimbotAimStep.getstate())
	{
		Vector AddAngs = angles - LastAimstepAngle;
		Normalize(AddAngs, AddAngs);
		AddAngs *= 39;
		LastAimstepAngle += AddAngs;
		GameUtils::NormaliseViewAngle(LastAimstepAngle);
		angles = LastAimstepAngle;
	}
	else
	{
		ReturnValue = true;
	}


	if (g_menu.rage.AimbotSilentAim.getstate())
	{
		pCmd->viewangles = angles;
	}

	return ReturnValue;
}