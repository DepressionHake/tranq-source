#pragma once

#include "Hacks.h"
#include "RageBot.h"

class CAntiAim : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:
	// Targetting
	void aimAtPlayer(CUserCmd* pCmd);

	// AntiAim
	void DoAntiAim(CUserCmd *pCmd, bool&bSendPacket);
	//bool EdgeAntiAim(IClientEntity* localplayerBaseEntity, CUserCmd* cmd, float flWall, float flCornor);
	bool bEdge;

	// AimStep
	bool IsAimStepping;
	bool lby_update_in_this_tick;
	Vector LastAimstepAngle;
	Vector LastAngle;
};
