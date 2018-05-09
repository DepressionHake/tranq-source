/*
 
*/

#pragma once

#include "Hacks.h"

class CRageBot : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:
	// Targetting
	int GetTargetCrosshair();
	int GetTargetDistance();
	//int GetTargetDistance(CUserCmd* pCmd);
	int GetTargetHealth();
	bool TargetMeetsRequirements(IClientEntity* m_entity);
	void aimAtPlayer(CUserCmd* pCmd);
	void KnifeBot(CUserCmd *pCmd, IClientEntity* localplayer);
	float FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* m_entity, int HitBox);
	int HitScan(IClientEntity* m_entity);
	void Resolver(ClientFrameStage_t curStage);
	void DoMovingAA(CUserCmd* pCmd, bool& bSendPacket, IClientEntity* localplayer);
	bool AimAtPoint(IClientEntity* localplayer, Vector point, CUserCmd *pCmd, bool &bSendPacket);

	// Functionality
	void DoAimbot(CUserCmd *pCmd, bool &bSendPacket);
	void Freestanding();
	void StartLagCompensation(IClientEntity * m_entity, CUserCmd * pCmd);
	void DoNoRecoil(CUserCmd *pCmd);
	void AutoRevolver();
	//float InterpolationFix(CUserCmd* pCmd);

	// AntiAim
	void DoAntiAim(CUserCmd *pCmd, bool&bSendPacket, IClientEntity* pEnt);
	//bool EdgeAntiAim(IClientEntity* localplayerBaseEntity, CUserCmd* cmd, float flWall, float flCornor);
	bool bEdge;

	// AimStep
	bool IsAimStepping;
	Vector LastAimstepAngle;
	Vector LastAngle;

	// Aimbot
	bool IsLocked;
	int TargetID;
	int HitBox;
	Vector AimPoint;
};

extern float headPos;
extern int antiAimSide;
extern float autowalldmgtest[65];
extern float flipBool;