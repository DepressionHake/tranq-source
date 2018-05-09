#include "LegitBot.h"
#include "RenderManager.h"
#include "MathFunctions.h"
#include <iostream>

#define    HITGROUP_GENERIC    0
#define    HITGROUP_HEAD        1
#define    HITGROUP_CHEST        2
#define    HITGROUP_STOMACH    3
#define HITGROUP_LEFTARM    4    
#define HITGROUP_RIGHTARM    5
#define HITGROUP_LEFTLEG    6
#define HITGROUP_RIGHTLEG    7
#define HITGROUP_GEAR        10

void CLegitBot::Init()
{
	IsLocked = false;
	TargetID = -1;
	HitBox = -1;
}

void CLegitBot::Draw()
{

}

static int CustomDelay = 0;
static int CustomBreak = 0;

void CLegitBot::Move(CUserCmd *pCmd, bool& bSendPacket)
{
	if (!g_menu.legit.Active.getstate())
		return;

	IClientEntity* localplayer = hackManager.localplayer();
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeaponHandle());

	static int CustomAimTime = 0;
	static int CustomAimStart = 0;
	if (g_menu.legit.AimbotEnable.getstate())
	{
		if (StartAim > 0)
		{
			if (CustomAimStart < (StartAim * 333))
			{
				CustomAimStart++;
			}
			else
			{
				if (Aimtime > 0)
				{
					if (CustomAimTime < (Aimtime * 333))
					{
						DoAimbot(pCmd, bSendPacket);
						CustomAimTime++;
					}
					if (!GUI.GetKeyState(g_menu.legit.AimbotKeyBind.GetKey()) || g_menu.legit.AimbotAutoFire.getstate())
					{
						CustomAimTime = 0;
						CustomAimStart = 0;
					}
				}
				else
				{
					DoAimbot(pCmd, bSendPacket);
					CustomAimTime = 0;
					CustomAimStart = 0;
				}
			}

			if (!GUI.GetKeyState(g_menu.legit.AimbotKeyBind.GetKey()) || g_menu.legit.AimbotAutoFire.getstate())
			{
				CustomAimStart = 0;
				CustomAimTime = 0;
			}
		}
		else
		{
			if (Aimtime > 0)
			{
				if (CustomAimTime < (Aimtime * 333))
				{
					DoAimbot(pCmd, bSendPacket);
					CustomAimTime++;
				}
				if (!GUI.GetKeyState(g_menu.legit.AimbotKeyBind.GetKey()) || g_menu.legit.AimbotAutoFire.getstate())
				{
					CustomAimTime = 0;
					CustomAimStart = 0;
				}
			}
			else
			{
				DoAimbot(pCmd, bSendPacket);
				CustomAimTime = 0;
				CustomAimStart = 0;
			}
		}
	}
	if (g_menu.legit.TriggerEnable.getstate() && ((g_menu.legit.TriggerKeyPress.getstate() && GUI.GetKeyState(g_menu.legit.TriggerKeyBind.GetKey()) || !g_menu.legit.TriggerKeyPress.getstate())))
	{
		DoTrigger(pCmd);
	}

	SyncWeaponSettings();
}

void CLegitBot::SyncWeaponSettings()
{
	IClientEntity* localplayer = hackManager.localplayer();
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeaponHandle());

	if (!pWeapon)
		return;

	if (g_menu.legit.AimbotEnable.getstate())
	{
		Speed = g_menu.legit.WeaponPistSpeed.getvalue() / 100;
		FoV = g_menu.legit.WeaponPistFoV.getvalue() * 2;
		RecoilControl = g_menu.legit.WeaponPistRecoil.getstate();
		PSilent = g_menu.legit.WeaponPistPSilent.getstate();
		Inacc = g_menu.legit.WeaponPistInacc.getvalue();



		switch (g_menu.legit.WeaponPistHitbox.getindex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			Multihitbox = false;
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			Multihitbox = false;
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			Multihitbox = false;
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			Multihitbox = false;
			break;
		case 4:
			Multihitbox = true;
			break;
		}

		Aimtime = g_menu.legit.WeaponPistAimtime.getvalue() / 10;
		StartAim = g_menu.legit.WeaoponPistStartAimtime.getvalue() / 10;
	}
}

void CLegitBot::DoAimbot(CUserCmd *pCmd, bool &bSendPacket)
{
	IClientEntity* pTarget = nullptr;
	IClientEntity* localplayer = hackManager.localplayer();
	bool FindNewTarget = true;

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeaponHandle());
	if (pWeapon)
	{
		if (pWeapon->GetAmmoInClip() == 0 || !GameUtils::IsBallisticWeapon(pWeapon))
		{
			return;
		}
		SyncWeaponSettings();

	}
	else
		return;

	if (IsLocked && TargetID >= 0 && HitBox >= 0)
	{
		pTarget = interfaces::g_entitylist->GetClientEntity(TargetID);
		if (pTarget  && TargetMeetsRequirements(pTarget))
		{
			SyncWeaponSettings();
			if (HitBox >= 0)
			{
				Vector ViewOffset = localplayer->GetOrigin() + localplayer->GetViewOffset();
				Vector View; interfaces::engine->GetViewAngles(View);
				if (localplayer->velocity().Length() > 45.f);
				View += localplayer->localPlayerExclusive()->GetAimPunchAngle() * RecoilControl;
				float nFoV = FovToPlayer(ViewOffset, View, pTarget, HitBox);
				if (nFoV < FoV)
					FindNewTarget = false;
			}
		}
	}

	if (FindNewTarget)
	{
		TargetID = 0;
		pTarget = nullptr;
		HitBox = -1;

		TargetID = GetTargetCrosshair();

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

	SyncWeaponSettings();

	if (TargetID >= 0 && pTarget)
	{
		SyncWeaponSettings();

		if (g_menu.legit.AimbotKeyPress.getstate())
		{
			int Key = g_menu.legit.AimbotKeyBind.GetKey();
			if (Key >= 0 && !GUI.GetKeyState(Key))
			{
				TargetID = -1;
				pTarget = nullptr;
				HitBox = -1;
				return;
			}
		}

		Vector AimPoint;

		if (Multihitbox)
		{
			AimPoint = GetHitboxPosition(pTarget, besthitbox);
		}
		else
		{
			AimPoint = GetHitboxPosition(pTarget, HitBox);
		}

		if (AimAtPoint(localplayer, AimPoint, pCmd, bSendPacket))
		{
			if (g_menu.legit.AimbotAutoFire.getstate() && !(pCmd->buttons & IN_ATTACK))
			{
				pCmd->buttons |= IN_ATTACK;
			}
		}
	}

	// Auto Pistol
	static bool WasFiring = false;
	if (GameUtils::IsPistol(pWeapon) && g_menu.legit.AimbotAutoPistol.getstate())
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			static bool WasFiring = false;
			WasFiring = !WasFiring;

			if (WasFiring)
			{
				pCmd->buttons &= ~IN_ATTACK;
			}
		}
	}
}

bool CLegitBot::TargetMeetsTriggerRequirements(IClientEntity* m_entity)
{
	if (m_entity && m_entity->IsDormant() == false && m_entity->IsAlive() && m_entity->index() != hackManager.localplayer()->index() && m_entity->index() < 65)
	{
		if (m_entity->GetTeamNum() != hackManager.localplayer()->GetTeamNum() || g_menu.legit.AimbotFriendlyFire.getstate())
		{
			if (!m_entity->HasGunGameImmunity())
			{

				return true;
			}
		}

	}

	return false;
}

void CLegitBot::DoTrigger(CUserCmd *pCmd)
{
}

bool CLegitBot::TargetMeetsRequirements(IClientEntity* m_entity)
{
	if (m_entity && m_entity->IsDormant() == false && m_entity->IsAlive() && m_entity->index() != hackManager.localplayer()->index())
	{
		ClientClass *pClientClass = m_entity->GetClientClass();
		player_info_t pinfo;
		if (pClientClass->m_ClassID == (int)CSGOClassID::CCSPlayer && interfaces::engine->GetPlayerInfo(m_entity->index(), &pinfo))
		{
			if (m_entity->GetTeamNum() != hackManager.localplayer()->GetTeamNum() || g_menu.legit.AimbotFriendlyFire.getstate())
			{
				if (g_menu.legit.AimbotSmokeCheck.getstate()) {
					typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);

					static uint32_t GoesThroughSmokeOffset = (uint32_t)Utilities::Memory::FindPatternV2("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
					static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;

					if (GoesThroughSmokeFunction(hackManager.localplayer()->GetEyePosition(), m_entity->GetBonePos(8)))
						return false;
				}

				if (Multihitbox)
				{
					if (!m_entity->HasGunGameImmunity())
					{
						if (GameUtils::IsVisible(hackManager.localplayer(), m_entity, 0) || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 8) || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 4 || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 1 || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 2 || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 3 || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 5 || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 7 || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 9 || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 10 || GameUtils::IsVisible(hackManager.localplayer(), m_entity, 6))))))))))
							return true;
						else
							return false;
					}
				}
				else
				{
					if (!m_entity->HasGunGameImmunity() && GameUtils::IsVisible(hackManager.localplayer(), m_entity, HitBox))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

float Get3dDistance(Vector me, Vector ent)
{
	return sqrt(pow(double(ent.x - me.x), 2.0) + pow(double(ent.y - me.y), 2.0) + pow(double(ent.z - me.z), 2.0));
}

float CLegitBot::FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* m_entity, int aHitBox)
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

	float Distance = Get3dDistance(Origin, AimPos);

	float pitch = sin(Forward.x - Delta.x) * Distance;
	float yaw = sin(Forward.y - Delta.y) * Distance;
	float zaw = sin(Forward.z - Delta.z) * Distance;

	float mag = sqrt((pitch*pitch) + (yaw*yaw) + (zaw*zaw));
	return mag;
}
/*
float CLegitBot::FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* m_entity, int aHitBox)
{
Vector out[9];

// Anything past 180 degrees is just going to wrap around
CONST FLOAT MaxDegrees = 180.0f;

// Get local angles
Vector Angles = View;

// Get local view / eye position
Vector Origin = ViewOffSet;

// Create and intiialize vectors for calculations below
Vector Delta(0, 0, 0);
//Vector Origin(0, 0, 0);
Vector Forward(0, 0, 0);

// Convert angles to normalized directional forward vector
AngleVectors(Angles, &Forward);
Vector AimPos = GetHitboxPosition(m_entity, aHitBox);
// Get delta vector between our local eye position and passed vector
VectorSubtract(AimPos, Origin, Delta);
//Delta = AimPos - Origin;

// Normalize our delta vector
Normalize(Delta, Delta);

// Get dot product between delta position and directional forward vectors
FLOAT DotProduct = Forward.Dot(Delta);

// Time to calculate the field of view
return (acos(DotProduct) * (MaxDegrees / PI));
}
*/

int CLegitBot::GetTargetCrosshair()
{
	// Target selection
	SyncWeaponSettings();
	int target = -1;
	float minFoV = FoV;

	IClientEntity* localplayer = hackManager.localplayer();
	Vector ViewOffset = localplayer->GetOrigin() + localplayer->GetViewOffset();
	Vector View; interfaces::engine->GetViewAngles(View);
	View += localplayer->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

	for (int i = 0; i < interfaces::g_entitylist->GetHighestEntityIndex(); i++)
	{
		IClientEntity *m_entity = interfaces::g_entitylist->GetClientEntity(i);
		if (TargetMeetsRequirements(m_entity))
		{
			if (Multihitbox)
			{

				float fov1 = FovToPlayer(ViewOffset, View, m_entity, 0);
				float fov2 = FovToPlayer(ViewOffset, View, m_entity, 4);
				float fov3 = FovToPlayer(ViewOffset, View, m_entity, 6);

				if (fov1 < FoV || fov2 < FoV && fov1 < FoV || fov3 < FoV)
				{
					FoV = fov1;
					target = i;
					besthitbox = 0;
				}

				if (fov2 < FoV || fov1 < FoV && fov2 < FoV || fov3 < FoV)
				{
					FoV = fov2;
					target = i;
					besthitbox = 4;
				}

				if (fov3 < FoV || fov1 < FoV && fov3 < FoV || fov2 < FoV)
				{
					FoV = fov3;
					target = i;
					besthitbox = 6;
				}

			}
			else
			{

				int NewHitBox = HitBox;
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
	}

	return target;
}

bool ShouldFire()
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

bool CLegitBot::AimAtPoint(IClientEntity* localplayer, Vector point, CUserCmd *pCmd, bool &bSendPacket)
{
	// Get the full angles
	if (point.Length() == 0) return false;

	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	static Vector Inaccuracy;

	if (timeSoFar > 0.2)
	{
		Inaccuracy.Init(-50 + rand() % 100, -50 + rand() % 100, -50 + rand() % 100);
		Inaccuracy.NormalizeInPlace();
		Inaccuracy *= Inacc;
		start_t = clock();
	}

	point += Inaccuracy;
	Vector angles;
	Vector src = localplayer->GetOrigin() + localplayer->GetViewOffset();

	CalcAngle(src, point, angles);
	GameUtils::NormaliseViewAngle(angles);

	if (angles[0] != angles[0] || angles[1] != angles[1])
	{
		return false;
	}

	if (RecoilControl)
	{
		Vector AimPunch = localplayer->localPlayerExclusive()->GetAimPunchAngle();
		if (AimPunch.Length2D() > 0 && AimPunch.Length2D() < 150)
		{
			angles -= AimPunch * 2;
			GameUtils::NormaliseViewAngle(angles);
		}
	}


	IsLocked = true;

	Vector shit = angles - pCmd->viewangles;
	bool v = false;
	GameUtils::NormaliseViewAngle(shit);
	if (shit.Length() > Speed)
	{
		Normalize(shit, shit);
		shit *= Speed;
	}
	else
	{
		v = true;
	}

	Vector ang = angles - pCmd->viewangles;
	bool f = false;

	if (ang.Length() > Speed)
	{
		Normalize(ang, ang);
		ang *= Speed;
	}
	else
	{
		f = true;
	}

	if (PSilent)
	{
		Vector Oldview = pCmd->viewangles;
		Vector qAimAngles = pCmd->viewangles;
		float Oldsidemove = pCmd->sidemove;
		float Oldforwardmove = pCmd->forwardmove;

		static int ChokedPackets = -1;

		if (ShouldFire() && ChokedPackets < 6)
		{
			bSendPacket = false;
			pCmd->viewangles += ang;
			pCmd->viewangles = angles;
			ChokedPackets++;
		}
		else
		{
			bSendPacket = true;
			pCmd->viewangles = Oldview;
			pCmd->sidemove = Oldsidemove;
			pCmd->forwardmove = Oldforwardmove;
			ChokedPackets = -1;
		}

		pCmd->viewangles.z = 0;
	}
	else
	{
		pCmd->viewangles += ang;
		interfaces::engine->SetViewAngles(pCmd->viewangles);
	}
	return f;

	pCmd->viewangles += shit;
	interfaces::engine->SetViewAngles(pCmd->viewangles);

	return f;
}

void CLegitBot::LegitAA(CUserCmd *pCmd, bool& bSendPacket)
{
	IClientEntity* localplayer = hackManager.localplayer();
	if ((pCmd->buttons & IN_USE) || localplayer->GetMoveType() == MOVETYPE_LADDER)
		return;
	if (g_menu.legit.LegitAA.getstate())
	{
		//for the memes
		Vector oldAngle = pCmd->viewangles;
		float oldForward = pCmd->forwardmove;
		float oldSideMove = pCmd->sidemove;
		if (g_menu.legit.LegitAA.getstate() && !pCmd->buttons & IN_ATTACK)
		{
			static int ChokedPackets = -1;
			ChokedPackets++;
			static bool yFlip;
			if (ChokedPackets < 1)
			{
				bSendPacket = true;
			}
			else
			{
				bSendPacket = false;
				yFlip ? pCmd->viewangles.y += 90.f : pCmd->viewangles.y -= 90.f;
				ChokedPackets = -1;
			}
			yFlip != yFlip;
		}
	}
}

