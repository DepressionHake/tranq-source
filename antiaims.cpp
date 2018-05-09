#include "RageBot.h"
#include "RenderManager.h"
#include "Resolver.h"
#include "Autowall.h"
#include "ESP.h"
#include <iostream>
#include "UTIL Functions.h"

#define M_PI 3.14159265358979323846

void AngleVectors3(const Vector &angles, Vector *forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

template<class T, class U>
T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}

float RandomNumber(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

float GetOutgoingLatency()
{
	INetChannelInfo *nci = interfaces::engine->GetNetChannelInfo();
	if (nci)
	{
		float OutgoingLatency = nci->GetAvgLatency(FLOW_OUTGOING);
		return OutgoingLatency;
	}
	else
	{
		return 0.0f;
	}
}


float OldLBY;
float LBYBreakerTimer;
float LastLBYUpdateTime;
bool bSwitch;
float CurrentVelocity(IClientEntity* LocalPlayer)
{
	int vel = LocalPlayer->velocity().Length2D();
	return vel;
}

bool NextLBYUpdate()
{
	IClientEntity* LocalPlayer = hackManager.localplayer();

	float flServerTime = (float)(LocalPlayer->GetTickBase()  * interfaces::Globals->interval_per_tick);

	if (OldLBY != LocalPlayer->lowerbody())
	{
		LBYBreakerTimer++;
		OldLBY = LocalPlayer->lowerbody();
		bSwitch = !bSwitch;
		LastLBYUpdateTime = flServerTime;
	}

	if (CurrentVelocity(LocalPlayer) > 0.1)
	{
		LastLBYUpdateTime = flServerTime;
		return false;
	}


	if ((LastLBYUpdateTime + 1.1 - GetOutgoingLatency() < flServerTime) && (LocalPlayer->GetFlags() & FL_ONGROUND))
	{
		if (LastLBYUpdateTime + 0.9 - GetOutgoingLatency() < flServerTime)
		{
			LastLBYUpdateTime = flServerTime;
		}
		return true;
	}
	return false;
}

namespace AAYaw /*AA-Yaw*/
{

	void Backward(CUserCmd* pCmd)
	{
		pCmd->viewangles.y -= 180.00f;
	}

	void urmomaa(CUserCmd* pCmd)
	{
		static bool wilupdate;
		static float LastLBYUpdateTime = 0;
		IClientEntity* LocalCmd = hackManager.localplayer();
		float server_time = LocalCmd->GetTickBase() * interfaces::Globals->interval_per_tick;
		if (server_time >= LastLBYUpdateTime)
		{
			LastLBYUpdateTime = server_time + 0.75f;
			wilupdate = true;
			pCmd->viewangles.y -= 90.f;
		}
		else
		{
			wilupdate = false;
			pCmd->viewangles.y += 103.f;
		}
		if (server_time >= LastLBYUpdateTime)
		{
			LastLBYUpdateTime = server_time + 0.95f;
			wilupdate = true;
			pCmd->viewangles.y += 109.f;
		}
		else
		{
			wilupdate = false;
			pCmd->viewangles.y += 90.f;
		}
		if (server_time >= LastLBYUpdateTime)
		{
			LastLBYUpdateTime = server_time + 0.001f;
			wilupdate = true;
			pCmd->viewangles.x += 89;
		}
		else
		{
			wilupdate = false;
			pCmd->viewangles.x += -180;
		}
	}
	void AntiCorrection(CUserCmd* pCmd)
	{
		Vector newAngle = pCmd->viewangles;

		static int ChokedPackets = -1;
		ChokedPackets++;

		float yaw;
		static int state = 0;
		static bool LBYUpdated = false;

		float flCurTime = interfaces::Globals->curtime;
		static float flTimeUpdate = 1.09f;
		static float flNextTimeUpdate = flCurTime + flTimeUpdate;
		if (flCurTime >= flNextTimeUpdate) {
			LBYUpdated = !LBYUpdated;
			state = 0;
		}

		if (flNextTimeUpdate < flCurTime || flNextTimeUpdate - flCurTime > 10.f)
			flNextTimeUpdate = flCurTime + flTimeUpdate;

		if (LBYUpdated)
			yaw = 90;
		else
			yaw = -90;

		if (yaw)
			newAngle.y += yaw;

		pCmd->viewangles = newAngle;
	}

	void AntiCorrectionALT(CUserCmd* pCmd)
	{
		Vector newAngle = pCmd->viewangles;

		static int ChokedPackets = -1;
		ChokedPackets++;

		float yaw;
		static int state = 0;
		static bool LBYUpdated = false;

		float flCurTime = interfaces::Globals->curtime;
		static float flTimeUpdate = 1.09f;
		static float flNextTimeUpdate = flCurTime + flTimeUpdate;
		if (flCurTime >= flNextTimeUpdate) {
			LBYUpdated = !LBYUpdated;
			state = 0;
		}

		if (flNextTimeUpdate < flCurTime || flNextTimeUpdate - flCurTime > 10.f)
			flNextTimeUpdate = flCurTime + flTimeUpdate;

		if (LBYUpdated)
			yaw = -90;
		else
			yaw = 90;

		if (yaw)
			newAngle.y += yaw;

		pCmd->viewangles = newAngle;
	}
	void BackwardJitter(CUserCmd *pCmd)
	{
		int random = rand() % 100;

		if (random < 98)

			pCmd->viewangles.y -= 180;

		if (random < 15)
		{
			float change = -70 + (rand() % (int)(140 + 1));
			pCmd->viewangles.y += change;
		}
		if (random == 69)
		{
			float change = -90 + (rand() % (int)(180 + 1));
			pCmd->viewangles.y += change;
		}
	}
	void SidewaysZ(CUserCmd *pCmd)
	{
		int random = rand() % 100;

		if (random < 98)

			pCmd->viewangles.y -= 90;

		if (random < 15)
		{
			float change = -45 + (rand() % (int)(70 + 1));
			pCmd->viewangles.y += change;
		}
		if (random == 69)
		{
			float change = -45 + (rand() % (int)(90 + 1));
			pCmd->viewangles.y += change;
		}
	}
	void SidewaysZALT(CUserCmd *pCmd)
	{
		int random = rand() % 100;

		if (random < 98)

			pCmd->viewangles.y += 90;

		if (random < 15)
		{
			float change = 45 + (rand() % (int)(-70 + 1));
			pCmd->viewangles.y += change;
		}
		if (random == 69)
		{
			float change = 45 + (rand() % (int)(-90 + 1));
			pCmd->viewangles.y += change;
		}
	}
	void Up(CUserCmd *pCmd)
	{
		pCmd->viewangles.x = -89.0f;
	}

	void Zero(CUserCmd *pCmd)
	{
		pCmd->viewangles.x = 1080.f;
	}
	enum ADAPTIVE_SIDE {
		ADAPTIVE_UNKNOWN,
		ADAPTIVE_LEFT,
		ADAPTIVE_RIGHT
	};

	enum ADAPTIVE_SIDE2 {
		ADAPTIVE_UNKNOWN2,
		ADAPTIVE_LEFT2,
		ADAPTIVE_RIGHT2
	};

	void adaptive2(CUserCmd * pCmd, bool& bSendPacket) {
		auto fov_to_player = [](Vector view_offset, Vector view, IClientEntity* m_entity, int hitbox)
		{
			CONST FLOAT MaxDegrees = 180.0f;
			Vector Angles = view;
			Vector Origin = view_offset;
			Vector Delta(0, 0, 0);
			Vector Forward(0, 0, 0);
			AngleVectors3(Angles, &Forward);
			Vector AimPos = GetHitboxPosition(m_entity, hitbox);
			VectorSubtract(AimPos, Origin, Delta);
			Normalize(Delta, Delta);
			FLOAT DotProduct = Forward.Dot(Delta);
			return (acos(DotProduct) * (MaxDegrees / PI));
		};

		auto m_local = hackManager.localplayer();

		int target = -1;
		float mfov = 20;

		Vector viewoffset = m_local->GetOrigin() + m_local->GetViewOffset();
		Vector view; interfaces::engine->GetViewAngles(view);

		for (int i = 0; i < interfaces::engine->GetMaxClients(); i++) {
			IClientEntity* m_entity = interfaces::g_entitylist->GetClientEntity(i);

			if (m_entity && m_entity->IsDormant() == false && m_entity->IsAlive() && m_entity->index() != hackManager.localplayer()->index()) {

				float fov = fov_to_player(viewoffset, view, m_entity, 0);
				if (fov < mfov) {
					mfov = fov;
					target = i;
				}
			}
		}

		ADAPTIVE_SIDE2 side = ADAPTIVE_UNKNOWN2;

		Vector at_target_angle;

		if (target) {
			auto m_entity = interfaces::g_entitylist->GetClientEntity(target);

			if (m_entity && m_entity->IsDormant() == false && m_entity->IsAlive() && m_entity->index() != hackManager.localplayer()->index()) {
				Vector pos_enemy;
				if (Render::WorldToScreen(m_entity->GetOrigin(), pos_enemy)) {
					CalcAngle(m_local->GetOrigin(), m_entity->GetOrigin(), at_target_angle);

					POINT mouse = GUI.GetMouse();

					if (mouse.x > pos_enemy.x) side = ADAPTIVE_RIGHT2;
					else if (mouse.x < pos_enemy.x) side = ADAPTIVE_LEFT2;
					else side = ADAPTIVE_UNKNOWN2;
				}
			}
		}

		if (side == ADAPTIVE_RIGHT) {
			pCmd->viewangles.y = at_target_angle.y + 90;
		}
		else if (side == ADAPTIVE_LEFT) {
			pCmd->viewangles.y = at_target_angle.y - 90;
		}

		if (side == ADAPTIVE_UNKNOWN) {
			pCmd->viewangles.y -= 180;
		}
	}


	void adaptive(CUserCmd * pCmd, bool& bSendPacket) {
		auto fov_to_player = [](Vector view_offset, Vector view, IClientEntity* m_entity, int hitbox)
		{
			CONST FLOAT MaxDegrees = 180.0f;
			Vector Angles = view;
			Vector Origin = view_offset;
			Vector Delta(0, 0, 0);
			Vector Forward(0, 0, 0);
			AngleVectors3(Angles, &Forward);
			Vector AimPos = GetHitboxPosition(m_entity, hitbox);
			VectorSubtract(AimPos, Origin, Delta);
			Normalize(Delta, Delta);
			FLOAT DotProduct = Forward.Dot(Delta);
			return (acos(DotProduct) * (MaxDegrees / PI));
		};

		auto m_local = hackManager.localplayer();

		int target = -1;
		float mfov = 20;

		Vector viewoffset = m_local->GetOrigin() + m_local->GetViewOffset();
		Vector view; interfaces::engine->GetViewAngles(view);

		for (int i = 0; i < interfaces::engine->GetMaxClients(); i++) {
			IClientEntity* m_entity = interfaces::g_entitylist->GetClientEntity(i);

			if (m_entity && m_entity->IsDormant() == false && m_entity->IsAlive() && m_entity->index() != hackManager.localplayer()->index()) {

				float fov = fov_to_player(viewoffset, view, m_entity, 0);
				if (fov < mfov) {
					mfov = fov;
					target = i;
				}
			}
		}

		ADAPTIVE_SIDE side = ADAPTIVE_UNKNOWN;

		Vector at_target_angle;

		if (target) {
			auto m_entity = interfaces::g_entitylist->GetClientEntity(target);

			if (m_entity && m_entity->IsDormant() == false && m_entity->IsAlive() && m_entity->index() != hackManager.localplayer()->index()) {
				Vector pos_enemy;
				if (Render::WorldToScreen(m_entity->GetOrigin(), pos_enemy)) {
					CalcAngle(m_local->GetOrigin(), m_entity->GetOrigin(), at_target_angle);

					POINT mouse = GUI.GetMouse();

					if (mouse.x > pos_enemy.x) side = ADAPTIVE_RIGHT;
					else if (mouse.x < pos_enemy.x) side = ADAPTIVE_LEFT;
					else side = ADAPTIVE_UNKNOWN;
				}
			}
		}

		if (side == ADAPTIVE_RIGHT) {
			pCmd->viewangles.y = at_target_angle.y - 90;
		}
		else if (side == ADAPTIVE_LEFT) {
			pCmd->viewangles.y = at_target_angle.y + 90;
		}


		if (side == ADAPTIVE_UNKNOWN) {
			pCmd->viewangles.y -= 180;
		}
	}

	void SideJitterALT(CUserCmd *pCmd)
	{
		static bool Fast2 = false;
		if (Fast2)
		{
			pCmd->viewangles.y -= 75;
		}
		else
		{
			pCmd->viewangles.y -= 105;
		}
		Fast2 = !Fast2;
	}

	void SideJitter(CUserCmd *pCmd)
	{
		static bool Fast2 = false;
		if (Fast2)
		{
			pCmd->viewangles.y += 75;
		}
		else
		{
			pCmd->viewangles.y += 105;
		}
		Fast2 = !Fast2;
	}

	void NewBackJitter(CUserCmd *pCmd)
	{
		static bool Fast2 = false;
		if (Fast2)
		{
			pCmd->viewangles.y += 165;
		}
		else
		{
			pCmd->viewangles.y -= 165;
		}
		Fast2 = !Fast2;
	}

	void Spinbot(CUserCmd* pCmd) {

		int random = rand() % 100;
		int random2 = rand() % 1000;

		static bool dir;
		static float current_y = pCmd->viewangles.y;

		if (random == 1) dir = !dir;

		if (dir)
			current_y += 100.9;
		else
			current_y -= 100.9;

		pCmd->viewangles.y = current_y;

		if (random == random2)
			pCmd->viewangles.y += random;
	}
}
bool CanFire()
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

void CRageBot::aimAtPlayer(CUserCmd *pCmd)
{
	IClientEntity* localplayer = hackManager.localplayer();

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(hackManager.localplayer()->GetActiveWeaponHandle());

	if (!localplayer || !pWeapon)
		return;

	Vector eye_position = localplayer->GetEyePosition();

	float best_dist = pWeapon->GetCSWpnData()->flRange;

	IClientEntity* target = nullptr;

	for (int i = 0; i < interfaces::g_entitylist->GetHighestEntityIndex(); i++)
	{
		IClientEntity *m_entity = interfaces::g_entitylist->GetClientEntity(i);
		if (TargetMeetsRequirements(m_entity))
		{
			if (Globals::TargetID != -1)
				target = interfaces::g_entitylist->GetClientEntity(Globals::TargetID);
			else
				target = m_entity;

			Vector target_position = target->GetEyePosition();

			float temp_dist = eye_position.DistTo(target_position);

			if (best_dist > temp_dist)
			{
				best_dist = temp_dist;
				CalcAngle(eye_position, target_position, pCmd->viewangles);
			}
		}
	}
}

void VectorAngles2(const Vector &vecForward, Vector &vecAngles)
{
	Vector vecView;
	if (vecForward[1] == 0.f && vecForward[0] == 0.f)
	{
		vecView[0] = 0.f;
		vecView[1] = 0.f;
	}
	else
	{
		vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

		if (vecView[1] < 0.f)
			vecView[1] += 360.f;

		vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

		vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
	}

	vecAngles[0] = -vecView[0];
	vecAngles[1] = vecView[1];
	vecAngles[2] = 0.f;
}

void AngleVectors2(const Vector& qAngles, Vector& vecForward)
{
	float sp, sy, cp, cy;
	SinCos((float)(qAngles[1] * (M_PI / 180.f)), &sy, &cy);
	SinCos((float)(qAngles[0] * (M_PI / 180.f)), &sp, &cp);

	vecForward[0] = cp*cy;
	vecForward[1] = cp*sy;
	vecForward[2] = -sp;
}

bool EdgeAntiAim(IClientEntity* localplayerBaseEntity, CUserCmd* cmd, float flWall, float flCornor)
{
	Ray_t ray;
	trace_t tr;

	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayerBaseEntity;

	auto bRetVal = false;
	auto vecCurPos = localplayerBaseEntity->GetEyePosition();

	for (float i = 0; i < 360; i++)
	{
		Vector vecDummy(10.f, cmd->viewangles.y, 0.f);
		vecDummy.y += i;

		NormalizeVector(vecDummy);

		Vector vecForward;
		AngleVectors2(vecDummy, vecForward);

		auto flLength = ((16.f + 3.f) + ((16.f + 3.f) * sin(DEG2RAD(10.f)))) + 7.f;
		vecForward *= flLength;

		ray.Init(vecCurPos, (vecCurPos + vecForward));
		interfaces::Trace->TraceRay(ray, MASK_SHOT, (CTraceFilter *)&traceFilter, &tr);

		if (tr.fraction != 1.0f)
		{
			Vector qAngles;
			auto vecNegate = tr.plane.normal;

			vecNegate *= -1.f;
			VectorAngles2(vecNegate, qAngles);

			vecDummy.y = qAngles.y;

			NormalizeVector(vecDummy);
			trace_t leftTrace, rightTrace;

			Vector vecLeft;
			AngleVectors2(vecDummy + Vector(0.f, 30.f, 0.f), vecLeft);

			Vector vecRight;
			AngleVectors2(vecDummy - Vector(0.f, 30.f, 0.f), vecRight);

			vecLeft *= (flLength + (flLength * sin(DEG2RAD(30.f))));
			vecRight *= (flLength + (flLength * sin(DEG2RAD(30.f))));

			ray.Init(vecCurPos, (vecCurPos + vecLeft));
			interfaces::Trace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&traceFilter, &leftTrace);

			ray.Init(vecCurPos, (vecCurPos + vecRight));
			interfaces::Trace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&traceFilter, &rightTrace);

			if ((leftTrace.fraction == 1.f) && (rightTrace.fraction != 1.f))
				vecDummy.y -= flCornor; // left
			else if ((leftTrace.fraction != 1.f) && (rightTrace.fraction == 1.f))
				vecDummy.y += flCornor; // right            

			cmd->viewangles.y = vecDummy.y;
			cmd->viewangles.y -= flWall;
			cmd->viewangles.x = 89.f;
			bRetVal = true;
		}
	}
	return bRetVal;
}

void DoRealAA(CUserCmd* pCmd, IClientEntity* localplayer, bool& bSendPacket, IClientEntity* pEnt)
{
	static bool switch2;
	Vector oldAngle = pCmd->viewangles;
	float oldForward = pCmd->forwardmove;
	float oldSideMove = pCmd->sidemove;
	int custom = g_menu.rage.staticyawcustom.getvalue();
	switch (g_menu.rage.staticyaw.getindex())
	{
	case 0:
		break;
	case 1:
		pCmd->viewangles.y += 180;
		antiAimSide = 3;
		break;
	case 2:
		if (flipBool)
		{
			pCmd->viewangles.y += 90;
			antiAimSide = 1; // RIGHT HEAD
		}
		else if (!flipBool)
		{
			pCmd->viewangles.y -= 90;
			antiAimSide = 2; // LEFT HEAD
		}
		break;
	case 3:
		AAYaw::adaptive(pCmd, bSendPacket);
		break;
	case 4:
		if (flipBool)
		{
			AAYaw::SideJitter(pCmd);
			antiAimSide = 1; // RIGHT HEAD
		}
		else if (!flipBool)
		{
			AAYaw::SideJitterALT(pCmd);
			antiAimSide = 2; // LEFT HEAD
		}
		break;
	case 5:
		// 180 Jitter
		AAYaw::NewBackJitter(pCmd);
		antiAimSide = 3;
		break;
	case 6:
		if (flipBool)
		{
			AAYaw::AntiCorrectionALT(pCmd);
			antiAimSide = 1; // RIGHT HEAD
		}
		else if (!flipBool)
		{
			AAYaw::AntiCorrection(pCmd);
			antiAimSide = 2; // LEFT HEAD
		}
		break;	case 7:
			pCmd->viewangles.y += RandomNumber(-180, 180);
			break;
		case 8:
			pCmd->viewangles.y += (g_menu.rage.SpinSpeed.getvalue() * 3) * interfaces::Globals->curtime;
			break;
		case 9:
			AAYaw::BackwardJitter(pCmd);
			antiAimSide = 3;
			break;
		case 10:
			pCmd->viewangles.y = localplayer->lowerbody() + rand() % 130 - rand() % 50;
			break;
		case 11:
			if (flipBool)
			{
				pCmd->viewangles.y += custom;
				antiAimSide = 1; // RIGHT HEAD
			}
			else if (!flipBool)
			{
				pCmd->viewangles.y -= custom;
				antiAimSide = 2; // LEFT HEAD
			}
		case 12:
			if (flipBool)
			{
				AAYaw::SidewaysZ(pCmd);
				antiAimSide = 2; // RIGHT HEAD
			}
			else if (!flipBool)
			{
				AAYaw::SidewaysZALT(pCmd); //AAYaw::SidewaysZ(pCmd);
				antiAimSide = 1; // LEFT HEAD
			}
			break;
	}


	static auto RandomReal = false;
	if (RandomReal)
		pCmd->viewangles.y += g_menu.rage.AntiAimOffset.getvalue();
	else
		pCmd->viewangles.y -= g_menu.rage.AntiAimOffset.getvalue();
	RandomReal = !RandomReal;
}

void DoFakeAA(CUserCmd* pCmd, bool& bSendPacket, IClientEntity* localplayer)
{
	static bool switch2;
	Vector oldAngle = pCmd->viewangles;
	float oldForward = pCmd->forwardmove;
	float oldSideMove = pCmd->sidemove;

	switch (g_menu.rage.fakeyaw.getindex())
	{
	case 0:
		break;
	case 1:
		// Fast Spin
		pCmd->viewangles.y += 180;
		break;
	case 2:
		if (flipBool)
		{
			pCmd->viewangles.y -= 90;
		}
		else if (!flipBool)
		{
			pCmd->viewangles.y += 90;
		}
		break;
	case 3:
		AAYaw::adaptive2(pCmd, bSendPacket);
		break;
	case 4:
		if (flipBool)
		{
			AAYaw::SideJitterALT(pCmd);
		}
		else if (!flipBool)
		{
			AAYaw::SideJitter(pCmd);
		}
		break;
	case 5:
		// 180 Jitter
		AAYaw::NewBackJitter(pCmd);
		break;
	case 6:
		if (flipBool)
		{
			//AAYaw::LowerbodyNew(pCmd);
			AAYaw::AntiCorrection(pCmd);
		}
		else if (!flipBool)
		{
			AAYaw::AntiCorrectionALT(pCmd);
			//AAYaw::LowerbodyNewALT(pCmd);
		}
		break;
	case 7:
		pCmd->viewangles.y += RandomNumber(-180, 180);
		break;
	case 8:
		pCmd->viewangles.y += (g_menu.rage.SpinSpeed.getvalue() * 3) * interfaces::Globals->curtime;
		break;
	}
}

void CRageBot::DoAntiAim(CUserCmd *pCmd, bool &bSendPacket, IClientEntity* pEnt)
{
	IClientEntity* localplayer = hackManager.localplayer();

	if ((pCmd->buttons & IN_USE) || localplayer->GetMoveType() == MOVETYPE_LADDER)
		return;

	if (IsAimStepping || pCmd->buttons & IN_ATTACK)
		return;

	CBaseCombatWeapon* CSWeapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle(hackManager.localplayer()->GetActiveWeaponHandle());
	if (CSWeapon)
	{
		CSWeaponInfo* pWeaponInfo = CSWeapon->GetCSWpnData();
		if (!GameUtils::IsBallisticWeapon(CSWeapon))
		{
			if (g_menu.rage.AntiAimKnife.getstate())
			{
				if (!CanFire() || pCmd->buttons & IN_ATTACK2)
					return;
			}
			else
			{
				return;
			}
		}

	}

	if (g_menu.rage.AntiAimEdge.getstate()) {
		auto bEdge = EdgeAntiAim(hackManager.localplayer(), pCmd, 360.f, 45.f);
		if (bEdge)
			return;
	}

	int breaker = g_menu.rage.AntiAimBreakLBY.getvalue();

	if (g_menu.rage.AntiAimBreakLBY.getvalue() > 0.1);
	{
		if (NextLBYUpdate())
		{
			pCmd->viewangles.y += breaker;
			pCmd->viewangles.y -= breaker;
			{
				pCmd->viewangles.y += breaker;
			}
		}
	}
	int custom = g_menu.rage.staticyawcustom.getvalue();
	if (localplayer->velocity().Length2D() > 100)
	{
		switch (g_menu.rage.movingyaw.getindex())
		{
		case 0:
			break;
		case 1:
			pCmd->viewangles.y += 180;
			antiAimSide = 3;
			break;
		case 2:
			if (flipBool)
			{
				pCmd->viewangles.y += 90;
				antiAimSide = 1; // RIGHT HEAD
			}
			else if (!flipBool)
			{
				pCmd->viewangles.y -= 90;
				antiAimSide = 2; // LEFT HEAD
			}
			break;
		case 3:
			AAYaw::adaptive(pCmd, bSendPacket);
			break;
		case 4:
			if (flipBool)
			{
				AAYaw::SideJitter(pCmd);
				antiAimSide = 1; // RIGHT HEAD
			}
			else if (!flipBool)
			{
				AAYaw::SideJitterALT(pCmd);
				antiAimSide = 2; // LEFT HEAD
			}
			break;
		case 5:
			// 180 Jitter
			AAYaw::NewBackJitter(pCmd);
			antiAimSide = 3;
			break;
		case 6:
			if (flipBool)
			{
				AAYaw::AntiCorrectionALT(pCmd);
				antiAimSide = 1; // RIGHT HEAD
			}
			else if (!flipBool)
			{
				AAYaw::AntiCorrection(pCmd);
				antiAimSide = 2; // LEFT HEAD
			}
			break;
		case 7:
			pCmd->viewangles.y += RandomNumber(-180, 180);
			break;
		case 8:
			pCmd->viewangles.y += (g_menu.rage.SpinSpeed.getvalue() * 3) * interfaces::Globals->curtime;
			break;
		case 9:
			AAYaw::BackwardJitter(pCmd);
			antiAimSide = 3;
			break;
		case 10:
			pCmd->viewangles.y = localplayer->lowerbody() + rand() % 130 - rand() % 50;
			break;
		case 11:
			if (flipBool)
			{
				AAYaw::SidewaysZ(pCmd);
				antiAimSide = 2; // RIGHT HEAD
			}
			else if (!flipBool)
			{
				AAYaw::SidewaysZALT(pCmd); //AAYaw::SidewaysZ(pCmd);
				antiAimSide = 1; // LEFT HEAD
			}
			break;
		}
	}

	if (localplayer->GetFlags() & FL_FROZEN)
		return;
	switch (g_menu.rage.AntiAimPitch.getindex())
	{
	case 0:
		break;
	case 1:
		pCmd->viewangles.x = 87.000000;
		break;
	case 2:
		pCmd->viewangles.x = 79.1f;
		break;
	case 3:
		pCmd->viewangles.x = 45.f;
		break;
	case 4:
		AAYaw::Up(pCmd);
		break;
	case 5:
		AAYaw::Zero(pCmd);
		break;
	case 6: //NO SPREAD 
		if (!g_menu.misc.OtherSafeMode.getstate())
		{
			pCmd->viewangles.z -= 180;
			pCmd->viewangles.x -= 15;
		}
		break;
	}

	static int ChokedPackets = -1;
	ChokedPackets++;
	if (g_menu.misc.FakeLagEnable.getstate() && g_menu.rage.AntiAimEnable.getstate())
	{
		if (bSendPacket)
		{
			DoFakeAA(pCmd, bSendPacket, localplayer);
		}
		else
		{
			DoRealAA(pCmd, localplayer, bSendPacket, pEnt);
		}
	}
	else if (!g_menu.misc.FakeLagEnable.getstate() && g_menu.rage.AntiAimEnable.getstate())
	{
		if (ChokedPackets < 1)
		{
			bSendPacket = true;
			DoFakeAA(pCmd, bSendPacket, localplayer);
		}
		else
		{
			bSendPacket = false;
			DoRealAA(pCmd, localplayer, bSendPacket, pEnt);
			ChokedPackets = -1;
		}
	}
}