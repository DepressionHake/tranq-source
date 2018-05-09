/*
bonus's tranquility framework 2018
*/

#pragma once

#include "Hacks.h"
extern float lineLBY;

#define WHITE Color(255, 255, 255, 255)
// All misc visuals (Crosshairs etc) go in this class
struct BulletImpact_t
{
	float			flImpactTime;
	Vector			vecImpactPos;
	Color			color;
	IClientEntity*	pPlayer;

	__forceinline BulletImpact_t()
	{
		vecImpactPos = { 0.0f, 0.0f, 0.0f };
		flImpactTime = 0.0f;
		color = WHITE;
		pPlayer = nullptr;
	}

	__forceinline BulletImpact_t(IClientEntity* player, Vector pos, float time, Color col = WHITE)
	{
		pPlayer = player;
		flImpactTime = time;
		vecImpactPos = pos;
		color = col;
	}
};

class CEsp : public CHack
{
public:
	void Init();
	void BacktrackingCross(IClientEntity * m_entity);
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:
	static CEsp Instance()
	{
		static CEsp instance;
		return instance;
	}
	// Other shit
	IClientEntity *BombCarrier;

	struct ESPBox
	{
		int x, y, w, h;
	};
	// Draw a player
	void DrawPlayer(IClientEntity * m_entity, player_info_t pinfo, const Vector& origin, CUserCmd* pCmd);

	// Get player info
	Color GetPlayerColor(IClientEntity* m_entity);
	bool GetBox(IClientEntity* m_entity, ESPBox &result);

	// Draw shit about player
	void SpecList();
	void DrawGlow(IClientEntity *m_entity, int r, int g, int b, int a);
	void DLight(IClientEntity* local, IClientEntity* entity);
	//void DoEnemyCircle(IClientEntity* localplayerPlayer, const Vector &vecDelta, float *flRotation);
	void DrawWeaponESP(IClientEntity* m_entity, CEsp::ESPBox size);
	void DrawExtraInfo(IClientEntity* m_entity, CEsp::ESPBox size);
	void DrawArmor(IClientEntity* m_entity, CEsp::ESPBox size);
	void DrawFlash(IClientEntity* m_entity, ClientClass* cClass);
	void DamageIndicators(IGameEvent* pEvent, player_info_t pinfo, CEsp::ESPBox size);
	void DrawBox(ESPBox size, Color color, IClientEntity * m_entity);
	void DrawMolotov(IClientEntity * m_entity, ClientClass * cClass);
	void HitBones(IClientEntity* m_entity);
	void DrawLBY(IClientEntity* m_entity, CEsp::ESPBox size);
	void DoEnemyCircle(IClientEntity* localplayerPlayer, const Vector &vecDelta, float *flRotation);
	CEsp::ESPBox GetBOXX(IClientEntity * m_entity);
	void DirectionArrow(const Vector& origin, CUserCmd* pCmd);
	void DrawSmoke(IClientEntity * m_entity, ClientClass * cClass);
	void DrawBombCarrier(IClientEntity* m_entity, CEsp::ESPBox size);
	void DrawDecoy(IClientEntity * m_entity, ClientClass * cClass);
	void NIGGA(IClientEntity *m_entity, CEsp::ESPBox size);
	void AimLine(IClientEntity* m_entity);
	void BombCarrier1(player_info_t pinfo, ESPBox size, IClientEntity* m_entity);
	void DrawBombBar(IClientEntity* m_entity);
	void DrawWeapon(IClientEntity * m_entity, CEsp::ESPBox size);
	void DrawHE(IClientEntity * m_entity, ClientClass * cClass);
	void EntityGlow();
	void RemoveScope();
	void Fill(CEsp::ESPBox size, Color color);
	void Hitboxes(IClientEntity* Entity, Color color);
	void DrawIcon(IClientEntity * m_entity, CEsp::ESPBox size);
	void DrawName(player_info_t pinfo, ESPBox size);
	void BulletTrace(IClientEntity * m_entity);
	void DrawVitals(IClientEntity* m_entity, ESPBox size);
	void Barrel(CEsp::ESPBox size, Color color, IClientEntity* m_entity);
	void DrawLBY(IClientEntity* m_entity, CUserCmd* pCmd);
	void DrawInfo(IClientEntity* m_entity, ESPBox size, const Vector& origin);
	void BombTimer(IClientEntity * m_entity, ClientClass * cClass);
	void DrawHealth(IClientEntity* m_entity, ESPBox size);
	void DrawCross(IClientEntity* m_entity);
	void Indicator();
	void DrawGlow2(Color color);
	void DrawSkeleton(IClientEntity* m_entity);
	void DrawGlow();
	void Dildo(IClientEntity * m_entity, ClientClass * cClass);
	void DrawBombPlanted2(IClientEntity * m_entity, ClientClass * cClass);

	void GrenadeTrace();
	void GrenadeTraceOffMeme();
	void ShowImpacts();
	void ShowImpactsOffMeme();
	void DrawChicken(IClientEntity* m_entity, ClientClass* cClass);
	void DrawDrop(IClientEntity* m_entity, ClientClass* cClass);
	void DrawGrenades(IClientEntity* m_entity);
	void DrawBombPlanted(IClientEntity* m_entity, ClientClass* cClass);
	void DrawBomb(IClientEntity* m_entity, ClientClass* cClass);
	void* pSkip;
	class CGlow
	{
	public:
		void shutdown();
		void paint();
	};

	void antiaim_lines();
public:
	void paint();
	CGlow glow;
};

namespace Globals
{
	extern CUserCmd* UserCmd;
	extern IClientEntity* Target;
	extern int Shots;
	extern float userCMD;
	extern bool change;
	extern int TargetID;
	extern bool didhitHS;
	extern int missedshots;
	extern int missedshots1;
	extern std::map<int, QAngle> storedshit;
}

extern int resolverstage[64];
extern float autowalldmgtest[65];
extern CEsp esp;
extern CEsp* visuals;