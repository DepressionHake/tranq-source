#pragma once

#include "Interfaces.h"
#include "Hacks.h"
#include <deque>
#include "Singleton.h"

struct STickRecord
{
	bool operator==(STickRecord &other)
	{
		return other.m_flSimulationTime == m_flSimulationTime;
	}

	float m_flVelocity = 0.f;
	Vector m_vecVelocity = Vector(0, 0, 0);
	float m_flSimulationTime = 0.f;
	float m_flLowerBodyYawTarget = 0.f;
	QAngle m_angEyeAngles = QAngle(0, 0, 0);
	std::array<float, 24> m_flPoseParameter = {};
	float m_flCurTime = 0.f;
	int m_nFlags = 0;

	int m_iLayerCount = 0;
	animation_layer animationLayer[15];
};

class resolveyaw
{
public:
	void Init();
	void resolve(IClientEntity* entity);
	bool BreakingLBY(IClientEntity *player, STickRecord &record, animation_layer *layer);
	void framestage(IClientEntity* m_entity, ClientFrameStage_t stage);
	static resolveyaw GetInst()
	{
		static resolveyaw instance;
		return instance;
	}
};
extern resolveyaw* resolver;


namespace Globals
{
	extern CUserCmd* UserCmd;
	extern IClientEntity* Target;
	extern int Shots;
	extern bool change;
	extern int TargetID;
	extern bool didhitHS;
	extern int missedshots;
	extern std::map<int, QAngle> storedshit;
}

struct SResolveInfo
{
	std::deque<STickRecord> arr_tickRecords;

	STickRecord curTickRecord;
	STickRecord prevtickrec;

	float m_flLastLbyTime = 0.f;

	QAngle m_angDirectionFirstMoving = QAngle(0, 0, 0);
};