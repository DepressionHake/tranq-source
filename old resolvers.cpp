#include "Hooks.h"
#include "Resolver.h"
#include "ESP.h"
#define TIME_TO_TICKS( dt )     ( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )


void resolveyaw::Init() {}

float tolerance = 10.f;

float Normalize(float delta) {

	while (delta <= -180) delta += 360;
	while (delta > 180) delta -= 360;

	return delta;
}

const inline float GetDelta(float a, float b) {
	return abs(Normalize(a - b));


}

const inline float LBYDelta(const CTickRecord& v) {
	return v.m_angEyeAngles.y - v.m_flLowerBodyYawTarget;
}

const inline bool IsDifferent(float a, float b, float tolerance = 10.f) {
	return (GetDelta(a, b) > tolerance);
}

void resolveyaw::StoreVars(IClientEntity * pPlayer) {

	if (m_arrInfos.at(pPlayer->index()).m_sRecords.size() >= 10) {
		m_arrInfos.at(pPlayer->index()).m_sRecords.pop_back();
	}

	m_arrInfos.at(pPlayer->index()).m_sRecords.push_front(CTickRecord(pPlayer));
}



bool resolveyaw::staticreal(const std::deque<CTickRecord>& l, float tolerance) {
	auto minmax = std::minmax_element(std::begin(l), std::end(l), [](const CTickRecord& t1, const CTickRecord& t2) { return t1.m_flLowerBodyYawTarget < t2.m_flLowerBodyYawTarget; });
	return (fabs(minmax.first->m_flLowerBodyYawTarget - minmax.second->m_flLowerBodyYawTarget) <= tolerance);
}

bool resolveyaw::staticrealdif(const std::deque<CTickRecord>& l, float tolerance) {
	for (auto i = l.begin(); i < l.end() - 1;)
	{
		if (GetDelta(LBYDelta(*i), LBYDelta(*++i)) > tolerance)
			return false;
	}
	return true;
}

bool resolveyaw::HasSteadyDifference(const std::deque<CTickRecord>& l, float tolerance, IClientEntity* pEnt) {
	size_t misses = 0;
	for (size_t i = 0; i < l.size() - 1; i++) {
		float tickdif = static_cast<float>(l.at(i).m_flSimulationTime - l.at(i + 1).tickcount);
		float lbydif = GetDelta(l.at(i).m_flLowerBodyYawTarget, l.at(i + 1).m_flLowerBodyYawTarget);
		float ntickdif = static_cast<float>(Interfaces::Globals->tickcount - l.at(i).tickcount);
		if (((lbydif / tickdif) * ntickdif) > tolerance)
			misses++;
	}
	return (misses <= (l.size() / 3));
}
int missedLogHits[65];
float saveLastHeadshotFloat[65];
float saveLastBaimFloat[65];
float saveLastBaim30Float[65];
float enemysLastProxyTimer[65];
bool shotFakeHeadOnce[65];
int fakeshotMissedLast[65];
int ResolverStage[65];
#define TICK_INTERVAL           ( Interfaces::Globals->interval_per_tick )
#define TICKS_TO_TIME( t )      ( TICK_INTERVAL *( t ) )
int resolveyaw::GetDifferentDeltas(const std::deque<CTickRecord>& l, float tolerance) {
	std::vector<float> vec;
	for (auto var : l) {
		float curdelta = LBYDelta(var);
		bool add = true;
		for (auto fl : vec) {
			if (!IsDifferent(curdelta, fl, tolerance))
				add = false;
		}
		if (add)
			vec.push_back(curdelta);
	}
	return vec.size();
}


int resolveyaw::GetDifferentLBYs(const std::deque<CTickRecord>& l, float tolerance) {
	std::vector<float> vec;
	for (auto var : l)
	{
		float curyaw = var.m_flLowerBodyYawTarget;
		bool add = true;
		for (auto fl : vec)
		{
			if (!IsDifferent(curyaw, fl, tolerance))
				add = false;
		}
		if (add)
			vec.push_back(curyaw);
	}
	return vec.size();
}

float resolveyaw::measureticklby(const std::deque<CTickRecord>& l, IClientEntity* pEnt)
{
	int modulo = 1;
	int difangles = GetDifferentLBYs(l, tolerance);
	int inc = modulo * difangles;
	for (auto var : l)
	{
		for (int lasttick = var.tickcount; lasttick < Interfaces::Globals->tickcount; lasttick += inc)
		{
			if (lasttick == Interfaces::Globals->tickcount)
				return var.m_flLowerBodyYawTarget;
		}
	}
	return 0.f;
}

float resolveyaw::GetDeltaByComparingTicks(const std::deque<CTickRecord>& l, IClientEntity* pEnt) {
	int modulo = 1;
	int difangles = GetDifferentDeltas(l, tolerance);
	int inc = modulo * difangles;
	for (auto var : l)
	{
		for (int lasttick = var.tickcount; lasttick < Interfaces::Globals->tickcount; lasttick += inc) {
			if (lasttick == Interfaces::Globals->tickcount)
				return LBYDelta(var);
		}
	}
	return 0.f;
}

bool resolveyaw::DeltaKeepsChanging(const std::deque<CTickRecord>& cur, float tolerance) {
	return (GetDifferentDeltas(cur, tolerance) >(int) cur.size() / 2);
}

bool resolveyaw::LBYKeepsChanging(const std::deque<CTickRecord>& cur, float tolerance) {
	return (GetDifferentLBYs(cur, tolerance) > (int)cur.size() / 2);
}








void resolveyaw::Resolver(IClientEntity* pEntity, float org_yaw, STickRecord &record, AnimationLayer *layer)
{
	if (Menu::Window.RageBotTab.AccuracyResolverBeta.GetState())
	{
		auto index = pEntity->index();		
		auto cur = this->m_arrInfos.at(index).m_sRecords;
		float tickdif = static_cast<float>(cur.front().tickcount - cur.at(1).tickcount);
		float lbydif = GetDelta(cur.front().m_flLowerBodyYawTarget, cur.at(1).m_flLowerBodyYawTarget);
		float ntickdif = static_cast<float>(TIME_TO_TICKS(Interfaces::Globals->curtime) - cur.front().tickcount);
		auto new_yaw = org_yaw;
		bool is_moving = pEntity->velocity().Length() > 0.1f;
		bool is_onground = pEntity->GetFlags() & FL_ONGROUND;

		if (pEntity->lowerbody() != LatestLowerBodyYaw[index] || (is_moving && is_onground))
		{
			LatestLowerBodyYaw[index] = pEntity->lowerbody();
			OldYawDifference[index] = YawDifference[index];
			aa_info[index] = "Lby Updated";
			LatestLowerBodyYawUpdateTime[index] = Interfaces::Globals->curtime;
			pEntity->GetEyeAnglesY()->y = pEntity->lowerbody();
		}
		else
		{
			if (((Interfaces::Globals->curtime - LatestLowerBodyYawUpdateTime[index]) >= 0.5))
			{
				new_yaw -= 180;
				aa_info[index] = "Inverse";
			}
			else
			{
				if (cur.size() > 1)
				{
					if (staticreal(cur, 5))
						new_yaw = (cur.front().m_flLowerBodyYawTarget);
					else if (staticrealdif(cur, 10))
						new_yaw -= (cur.front().m_angEyeAngles.y - cur.front().m_flLowerBodyYawTarget);
					else if (HasSteadyDifference(cur, 10, pEntity)) 
						new_yaw = (lbydif / tickdif) * ntickdif;

					else if (LBYKeepsChanging(cur, 70))
						new_yaw -= measureticklby(cur, pEntity);
					else if (DeltaKeepsChanging(cur, 10))
						new_yaw = GetDeltaByComparingTicks(cur, pEntity);
					aa_info[index] = "Database";
				}
			}
		}
		new_yaw;
	}
}

void resolveyaw::FSN(IClientEntity* pEntity, float org_yaw, STickRecord &record, AnimationLayer *layer, ClientFrameStage_t curStage)
{
	if (curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		for (int i = 1; i < Interfaces::Engine->GetMaxClients(); i++)
		{

			pEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(i);

			if (!pEntity
				|| pEntity == hackManager.pLocal()
				|| pEntity->IsDormant()
				|| !pEntity->IsAlive())
				continue;

			resolveyaw::Resolver(pEntity, org_yaw, record, layer);
		}
	}
}

/*float_t resolveyaw::Bruteforce(IClientEntity *player)
{
	auto getdst = [](int a, int b)
	{
		int x = abs(b - a) % 360;
		return x > 180 ? 360 - x : x;
	};
	SResolveInfo arr_infos[64];
	auto record = arr_infos[player->EntIndex()];

	int avg = 1;
	int count = 1;

	float prevlby = 0.f;

	for (auto &r : record.arr_tickRecords)
	{
		if (r.m_flLowerBodyYawTarget == prevlby)
			continue;

		prevlby = r.m_flLowerBodyYawTarget;

		avg += getdst(static_cast<int>(r.m_angEyeAngles.y), static_cast<int>(r.m_flLowerBodyYawTarget));

		count++;
	}

	avg /= count;

	float add = 0;

	if (avg > 145)
		add = 180;
	else if (avg > 110)
		add = 135;
	else if (avg > 75)
		add = 90;
	else if (avg > 40)
		add = 45;

	return 1;
}*/

/*bool resolveyaw::IsAdjustingBalance(IClientEntity *player, STickRecord &record, AnimationLayer *layer)
{
	for (int i = 0; i < record.m_iLayerCount; i++)
	{
		const int activity = record.animationLayer[i].m_nSequence;
		if (activity == 979)
		{
			*layer = record.animationLayer[i];
			return true;
		}
	}
	return false;
}*/

/*bool eqqual(float x, float y, float diff)
{
	return std::abs(x - y) <= std::abs(diff);
}

static int missedShots[65];
bool isPartOf(char *a, char *b)
{
	if (std::strstr(b, a) != NULL) 
	{  
		return true;
	}
	return false;
}*/

void resolveyaw::AnimResolver(IClientEntity* pEntity, IClientEntity *pLocal)
{
 /*int i = pEntity->index();
	static int shotsfired[65];
	static float MoveLBY[65];
	static float FirstDelta[65];
	static bool fakeWalking;
	if (!pLocal->IsAlive())
		missedShots[i] = 0;
	if (Menu::Window.RageBotTab.AccuracyResolverBeta3.GetState())
	{
		if (pEntity->GetFlags() & FL_ONGROUND)
		{
			if (fakeWalking)
			{
				pResolverData[i].resolvermode = "Inverse";
				pEntity->GetEyeAnglesPointer()->y = pEntity->GetEyeAnglesPointer()->y + 180.f;
			}
			else if (pEntity->velocity().Length2D() > 15)
			{
				shotsfired[i] = 0;
				FirstDelta[i] = 0;
				pResolverData[i].resolvermode = "Moving";
				MoveLBY[i] = pEntity->pelvisangs();
				pEntity->GetEyeAnglesPointer()->y = pEntity->pelvisangs();
			}
			else
			{
				if (MoveLBY[i] = 0)
					MoveLBY[i] = pEntity->pelvisangs();
				if (pEntity->GetSequenceActivity(pEntity->GetAnimOverlay(3).m_nSequence) ==979 && pEntity->GetAnimOverlay(3).m_flWeight == 0.f && pEntity->GetAnimOverlay(3).m_flCycle >= 0.970000)
				{
					pResolverData[i].resolvermode = "Break LBY";
					if (FirstDelta[i] < 110 && FirstDelta[i] > -110)
						pEntity->GetEyeAnglesPointer()->y = FirstDelta[i] - 120;
					else if (FirstDelta[i] < 35 && FirstDelta[i] > -35)
						pEntity->GetEyeAnglesPointer()->y = FirstDelta[i] + 180;
					else
						pEntity->GetEyeAnglesPointer()->y = FirstDelta[i];
				}
				else
				{
					if (eqqual(FirstDelta[i], 0, 40.f))
					{
						pResolverData[i].resolvermode = "Flip";
						pEntity->GetEyeAnglesPointer()->y = (Globals::UserCmd->command_number % 2 ? MoveLBY[i] : FirstDelta[i]);
					}
					else if (missedShots[i] >= 2 && missedShots[i] <= 4)
					{
						pResolverData[i].resolvermode = "Fix LBY";
						pEntity->GetEyeAnglesPointer()->y = FirstDelta[i] + 180;
					}
					else
					{
						pResolverData[i].resolvermode = "Restored LBY";
						pEntity->GetEyeAnglesPointer()->y = MoveLBY[i];
					}
				}
			}
		}
	}*/
}

/*	AnimationLayer curBalanceLayer, prevBalanceLayer;
SResolveInfo arr_infos[64];
bool is_moving = pEntity->GetVelocity().Length() > 0.00001f;
int idx = pEntity->EntIndex();
SResolveInfo &player_recs = arr_infos[idx];
auto new_yaw = org_yaw;
if (is_moving)
{
if (pEntity->m_vecVelocity().Length2D() > 6.0f && pEntity->m_vecVelocity().Length2D() < 45.f && !pEntity->m_fFlags() & FL_DUCKING)
new_yaw = player_recs.m_angDirectionFirstMoving.y + 180.f;
else
new_yaw = pEntity->m_flLowerBodyYawTarget();
}
else if (pEntity, player_recs.curTickRecord, &curBalanceLayer)
{
if (pEntity, player_recs.prevTickRecord, &prevBalanceLayer)
{
if ((prevBalanceLayer.m_flCycle != curBalanceLayer.m_flCycle) || curBalanceLayer.m_flWeight == 1.f)
{
float
flAnimTime = curBalanceLayer.m_flCycle,
flSimTime = pEntity->m_flSimulationTime();
}
}
if (curBalanceLayer.m_flWeight == 0.f && (prevBalanceLayer.m_flCycle > 0.92f && curBalanceLayer.m_flCycle > 0.92f))
{
new_yaw = pEntity->GetEyeAngles().y + Bruteforce(pEntity);
}
else
{
new_yaw = pEntity->m_flLowerBodyYawTarget();
new_yaw = pEntity->GetEyeAngles().y + Bruteforce(pEntity);
}
if (arr_infos[idx].arr_tickRecords.size() > 16)

arr_infos[idx].arr_tickRecords.pop_back();

arr_infos[idx].arr_tickRecords.emplace_back(arr_infos[idx].curTickRecord);

arr_infos[idx].prevTickRecord = arr_infos[idx].curTickRecord;
}
float movinglby[64];
float lbytomovinglbydelta[64]; // long name idk what else to put
bool is_onground = pEntity->GetFlags() & FL_ONGROUND;
lbytomovinglbydelta[pEntity->GetIndex()] = pEntity->GetLowerBodyYaw() - lbytomovinglbydelta[pEntity->GetIndex()];

if (pEntity->GetVelocity().Length2D() > 6 && pEntity->GetVelocity().Length2D() < 42) { // shitty ayyware fakewalk check better than nothing.
pEntity->GetEyeAngles3()->y = pEntity->GetLowerBodyYaw() + 180;
}
else if (pEntity->GetVelocity().Length2D() < 6 || pEntity->GetVelocity().Length2D() > 42) { // they are moving
pEntity->GetEyeAngles3()->y = pEntity->GetLowerBodyYaw();
movinglby[pEntity->GetIndex()] = pEntity->GetLowerBodyYaw();
}
else if (lbytomovinglbydelta[pEntity->GetIndex()] > 50 && lbytomovinglbydelta[pEntity->GetIndex()] < -50) {// the 50 will allow you to have a 30 degree margin of error (do the math :))
pEntity->GetEyeAngles3()->y = movinglby[pEntity->GetIndex()];
}
else
pEntity->GetEyeAngles3()->y = pEntity->GetLowerBodyYaw();*/



/*else
{
pResolverData[i].resolvermode = "In Air";
if (shotsfired[i] > 7 || !pLocal->IsAlive())
shotsfired[i] = 0;

switch (shotsfired[i])
{
case 1: pEntity->GetEyeAnglesPointer()->y = pEntity->GetEyeAnglesPointer()->y + 180.f; break;
case 2: pEntity->GetEyeAnglesPointer()->y = pEntity->GetEyeAnglesPointer()->y - 120.f; break;
case 3: pEntity->GetEyeAnglesPointer()->y = pEntity->GetEyeAnglesPointer()->y + 90.f; break;
case 4: pEntity->GetEyeAnglesPointer()->y = pEntity->GetEyeAnglesPointer()->y - 45.f; break;
case 5: pEntity->GetEyeAnglesPointer()->y = pEntity->GetEyeAnglesPointer()->y + 15.f; break;
case 6: pEntity->GetEyeAnglesPointer()->y = pEntity->pelvisangs() - 120.f;

}

if (pEntity->GetEyeAnglesPointer()->x < -179.f) pEntity->GetEyeAnglesPointer()->x += 360.f;
else if (pEntity->GetEyeAnglesPointer()->x > 90.0 || pEntity->GetEyeAnglesPointer()->x < -90.0) pEntity->GetEyeAnglesPointer()->x = 89.f;
else if (pEntity->GetEyeAnglesPointer()->x > 89.0 && pEntity->GetEyeAnglesPointer()->x < 91.0) pEntity->GetEyeAnglesPointer()->x -= 90.f;
else if (pEntity->GetEyeAnglesPointer()->x > 179.0 && pEntity->GetEyeAnglesPointer()->x < 181.0) pEntity->GetEyeAnglesPointer()->x -= 180;
else if (pEntity->GetEyeAnglesPointer()->x > -179.0 && pEntity->GetEyeAnglesPointer()->x < -181.0) pEntity->GetEyeAnglesPointer()->x += 180;
else if (fabs(pEntity->GetEyeAnglesPointer()->x) == 0) pEntity->GetEyeAnglesPointer()->x = std::copysign(89.0f, pEntity->GetEyeAnglesPointer()->x);
}*/

/*Vector* pAngles = pEntity->GetEyeAnglesPointer();
		float_t m_flPrevCycle; //0x001C
		float_t m_flWeight; //0x0020
		float_t m_flWeightDeltaRate; //0x0024
		uint32_t m_nSequence; //0x0018
		float_t m_flPlaybackRate; //0x0028
		float_t m_flCycle;
		struct RageBackTrackData1
		{
			float simtime;
			float flcycle[13];
			float flprevcycle[13];
			float flweight[13];
			float flweightdatarate[13];
			float yaw;
			uint32_t norder[13];
			Vector hitboxPos;
			int tick;
			int balanceadjusttick;
			float balanceadjustsimtime;
			int activity[13];
			float damage;
		};
		RageBackTrackData1 RageBackData1[64][16];
		uint32_t m_nOrder; //0x0014
		int activity = pEntity->GetSequenceActivity(m_nSequence);
		float flcycle = m_flCycle, flprevcycle = m_flPrevCycle, flweightdatarate = m_flWeightDeltaRate;
		int flweight = m_flWeight;
		uint32_t norder = m_nOrder;
		float bodyeyedelta = pEntity->GetEyeAngles().y - m_flLowerBodyYawTarget;
		if (pEntity->GetVelocity().Length2D() >= 0.50 && norder == 6 && flweight >= 0.550000 || pEntity->GetVelocity().Length2D() >= 0.50 && norder == 5 && flweight >= 0.550000 || !pResolverData[pEntity->GetIndex()].bfakewalk && pEntity->GetVelocity().Length2D() >= 0.50)
		{
			float simtime = pEntity->GetSimulationTime();
			Hitbox box{};
			pResolverData[pEntity->GetIndex()].lastmovinglby = pEntity->pelvisangs();
			RageBackData1[pEntity->GetIndex()][Globals::UserCmd->command_number % 16].simtime = simtime;
			pResolverData[pEntity->GetIndex()].resolvermode = "LBY Move";
			pResolverData[pEntity->GetIndex()].fakewalk = "No Fake Walk";
			pAngles->y = pEntity->pelvisangs();
		}
		if (activity == ACT_CSGO_IDLE_TURN_BALANCEADJUST && flweight >= 0.05f)
		{
			pResolverData[pEntity->GetIndex()].resolvermode = "Less BA Brute";
			pResolverData[pEntity->GetIndex()].addyaw > 0.f ? pAngles->y = pEntity->pelvisangs() - pResolverData[pEntity->GetIndex()].addyaw - 77.5 : pAngles->y = pEntity->pelvisangs() - 77.5;
		}
		if (activity == ACT_CSGO_IDLE_ADJUST_STOPPEDMOVING || activity == ACT_CSGO_IDLE_TURN_BALANCEADJUST && flweight == 0.f && flcycle >= 0.970000)
		{
			pResolverData[pEntity->GetIndex()].resolvermode = "LBY Brute";
			pResolverData[pEntity->GetIndex()].addyaw > 0.f ? pAngles->y = pEntity->pelvisangs() - pResolverData[pEntity->GetIndex()].addyaw : pAngles->y = pEntity->pelvisangs() - 17.5;
		}*/



int IClientEntity::GetSequenceActivity(int sequence)
{
	auto hdr = Interfaces::ModelInfo->GetStudiomodel(this->GetModel());

	if (!hdr)
		return -1;

	// c_csplayer vfunc 242, follow calls to find the function.

	static auto client2 = GetModuleHandleW(L"client.dll");
	static auto getSequenceActivity = (DWORD)(Utilities::Memory::FindPatternV2("client.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74 3D"));
	static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(getSequenceActivity);

	return GetSequenceActivity(this, hdr, sequence);
}

void resolveyaw::resolver(IClientEntity* pEntity)
{
	/*if (Menu::Window.RageBotTab.AccuracyResolver.GetState())
	{
		auto cur = m_arrInfos.at(pEntity->GetIndex()).m_sRecords;
		if (cur.size() < 2)
			return;
		if (pEntity->GetVelocity().Length() > 0.00001f)
			pEntity->GetEyeAngles3()->y = pEntity->GetLowerBodyYaw();
		else if (HasStaticRealAngle(cur, 5))
			pEntity->GetEyeAngles3()->y = (cur.front().m_flLowerBodyYawTarget) + (random_between_two_floats(0.f, 1.f) > 0.5f ? 10 : -10);
		else if (HasStaticYawDifference(cur, 10))
			pEntity->GetEyeAngles3()->y = pEntity->GetEyeAngles().y - (cur.front().m_angEyeAngles.y - cur.front().m_flLowerBodyYawTarget);
		else if (HasSteadyDifference(cur, 10, pEntity))
		{
			float tickdif = static_cast<float>(cur.front().tickcount - cur.at(1).tickcount);
			float lbydif = GetDelta(cur.front().m_flLowerBodyYawTarget, cur.at(1).m_flLowerBodyYawTarget);
			float ntickdif = static_cast<float>(Globals::UserCmd->tick_count - cur.front().tickcount);
			pEntity->GetEyeAngles3()->y = (lbydif / tickdif) * ntickdif;
		}
		else if (DeltaKeepsChanging(cur, 10))
			pEntity->GetEyeAngles3()->y = pEntity->GetEyeAngles().y - GetDeltaByComparingTicks(cur, pEntity);
		else if (LBYKeepsChanging(cur, 70))
			pEntity->GetEyeAngles3()->y = GetLBYByComparingTicks(cur, pEntity);
		else
			pEntity->GetEyeAngles3()->y = pEntity->GetEyeAngles3()->y + 180;
	}*/
}



















/*namespace ResolverV2
{
	IClientEntity *lastShotEntity = NULL;
	Vector lastShotEyePosition = Vector(0, 0, 0);
	Vector lastShotPoint = Vector(0, 0, 0);
	int lastShotHitbox = 0;
	bool impactAcked = false;

	ResolverFlags lastShotResolverFlags;
	BruteforceInfo lastShotResolverBruteforce;

	RecvVarProxyFn oRecvLowerBodyYawTarget = NULL;
	RecvVarProxyFn oRecvEyeAnglesX = NULL;
	RecvVarProxyFn oRecvEyeAnglesY = NULL;
	RecvVarProxyFn oRecvEyeAnglesZ = NULL;

	void CResolver::Init(IClientEntity *entity)
	{
		Clear();
		initialized = true;
		this->entity = entity;
		lastResolverMethod = LBY_UPDATE;
	}

	void CResolver::Clear()
	{
		entity = nullptr;
		initialized = false;
		ClearFlags();
		ClearPerTickInfo();
		//aaRec.Clear();
	}

	void CResolver::ClearBruteforce()
	{
		for (int i = 0; i < BF_STEP_COUNT; i++)
		{
			bruteforce.step[i] = 0;
			bruteforce.changeStep[i] = false;
		}

		bruteforce.missedCount = 0;

		movingLby = 0.0f;
	}

	void CResolver::ClearFlags()
	{
		flags.fakeWalking = false;
		flags.standing = false;
		flags.moving = false;
		flags.crouchPicking = false;
		flags.fakingLby = false;
		flags.inAir = false;
		flags.onGround = false;
		flags.lbyUpdated = false;
		flags.lbyGoingUpdate = false;
		flags.fakingYaw = false;
		flags.unresolved = false;
		flags.legit = true;
		flags.ducking = false;
	}

	void CResolver::ClearPerTickInfo()
	{
		lastSimulationTime = 0;
		nextLbyUpdateTime = INFINITY;
		lastLby = 0;
		lastGroundMoveTime = 0;
		lastBalanceAdjust = INFINITY;

		oLby = INFINITY;
		lastPitch = INFINITY;
		fixingPitch = INFINITY;
		receivedFirstUpdate = false;
	}
	void CResolver::OnFrameRenderStart()
	{

	}

	void CResolver::OnEntityUpdate()
	{
		if (Menu::Window.RageBotTab.ResolverForceYaw.GetState())
		{
			auto records = aaRec.m_sRecords;

			if (aaRec.m_sRecords.size() == 0 || entity->GetSimulationTime() != aaRec.m_sRecords.front()->m_flSimulationTime)
			{
				aaRec.StoreVars(entity);
			}
		}

		oDuckAmmount = entity->GetDuckAmount();
		oVelocity = entity->GetVelocity();
		oAbsVelocity = entity->GetAbsVelocity();
		oOrigin = entity->GetOrigin();
		oAbsOrigin = entity->GetAbsOrigin();

		oLby = entity->GetLowerBodyYaw();

		ClearFlags();

		float speed = entity->GetVelocity().Length();
		float pitch = Math::NormalizeYawInPlace(oEyeAngles.x);

		flags.inAir = !entity->CheckOnGround();
		flags.onGround = !flags.inAir;
		flags.standing = flags.onGround && speed < 1.0f;
		flags.moving = speed > 34.0f;

		//TODO : CHECKED FOR CHOCKED - POSSIBLE LOGIC ERROR"!!!!!!!!!!!!!!
		CAnimationLayer *layer6 = entity->GetAnimOverlay(6);
		//int chockedticks;
		//Backtrack::RecordData *record = Backtrack::pRecordManager->GetLatestRecord(entity);
		//chockedticks = TIME_TO_TICKS(entity->GetSimulationTime() - record->GetSimulationTime());
		if (layer6 && layer6->m_flPlaybackRate > 0.0f && layer6->m_flPlaybackRate < 0.008f && speed <= 34.0f)
			flags.fakeWalking = true; // chockedticks ? true : false;
		else
			flags.fakeWalking = false;

		//fakeWalking = onGround && speed >= 1.0f && speed <= 34.0f && lastGroundMoveTime > TICKS_TO_TIME(1);
		flags.crouchPicking = entity->GetDuckAmount() > 0.1f && entity->GetDuckAmount() < 0.85f;
		flags.ducking = entity->GetDuckAmount() > 0 && flags.onGround;

		if (pitch != lastPitch)
		{
			fixPitch = lastPitch != INFINITY && lastPitch >= 35.0f && pitch < 35.0f;

			if (fixPitch)
			{
				fixingPitch = lastPitch;
			}
			else
			{
				fixingPitch = INFINITY;
			}
		}

		flags.fakingYaw = flags.inAir || fabsf(Math::NormalizeYawInPlace(oLby - entity->GetEyeAngles().y)) >= 35.0f;
		//fakingLby = inAir || fakeWalking || standing;

		if (Menu::Window.RageBotTab.NoSpreadMode.GetState() || Menu::Window.RageBotTab.ResolveLegits.GetState())
			flags.legit = false;
		else
			flags.legit = flags.onGround && !flags.fakingYaw && Math::NormalizeYawInPlace(entity->GetEyeAngles().x) < 35.0f;

		flags.lbyPredicted = false;

		float curtime = entity->GetSimulationTime(); //TICKS_TO_TIME(I::pEngineClient->GetServerTick());

		bool lbyChanged = receivedFirstUpdate && (lastLby != oLby); //(fabsf(Math::NormalizeYawInPlace(lastLby - oLby)) >= 35.0f));

		flags.lbyUpdated = false;

		if (flags.moving && flags.onGround)
			flags.lbyUpdated = true;

		if (flags.moving && flags.onGround || !flags.fakingYaw)
		{
			lastNonBreakedLby = oLby;
		}

		if (flags.moving && flags.onGround)
		{
			movingLby = oLby;
			lastGroundMoveTime = curtime;
		}

		if (fabsf(entity->GetSimulationTime() - lastGroundMoveTime) > 1000.0f)
			lastGroundMoveTime = entity->GetSimulationTime() - 200.0f;

		if (lbyChanged)
			lastLbyUpdateTime = entity->GetSimulationTime();

		lastLby = oLby;
		lastPitch = pitch;

		receivedFirstUpdate = true;
	}

	void CResolver::ProcessAngles()
	{
		if (flags.onGround && (flags.lbyUpdated || flags.legit))
		{
			flags.unresolved = false;
		}
		else
		{
			flags.unresolved = true;
		}

		bool missed = false;

		for (int i = 0; i < BF_STEP_COUNT; i++)
		{
			if (bruteforce.changeStep[i])
			{
				bruteforce.changeStep[i] = false;
				bruteforce.step[i]++;
				missed = true;
			}
		}

		if (missed)
			bruteforce.missedCount++;
	}

	void CResolver::ApplyAngles(IClientEntity *pLocal)
	{
		if (!flags.legit)
		{
			rEyeAngles = entity->GetEyeAngles();//oEyeAngles;

			if (Menu::Window.RageBotTab.lispCorrect.GetState())
			{
				rEyeAngles.y = oLby;
			}

			if (fixPitch)
			{
				rEyeAngles.x = fixingPitch;
			}

			if (Menu::Window.RageBotTab.ResolverForceYaw.GetState())
			{
				float lastMoveLby = movingLby != 0.0f ? movingLby : oLby + 180.0f;
				float atTarget = CalcAngle(entity->GetAbsOrigin(), pLocal->GetAbsOrigin()).y + 180.0f;

				AnimationLayer curBalanceLayer, prevBalanceLayer;
				auto cur = aaRec.m_sRecords;

				if (aaRec.m_sRecords.size() > 1 && aaRec.prevTickRecord && aaRec.curTickRecord)
				{
					///////////////////////////////////////////////////////////// DELTAS!!!!!!!!!  /////////////////////////////////////////////////////////////
					float bodyeyedelta = entity->GetEyeAngles().y - cur.front()->m_flLowerBodyYawTarget;
					float flLowerBodyYaw = entity->GetLowerBodyYaw();
					float flOriginalAngle = Math::NormalizeYawResolver(entity->GetEyeAngles().y);
					float lbydelta = flOriginalAngle - flLowerBodyYaw;
					float CurrentLowerbody = entity->GetLowerBodyYaw();
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					flags.fakingLby =
						aaRec.IsAdjustingBalance(entity, *aaRec.curTickRecord, &curBalanceLayer) &&
						aaRec.IsAdjustingBalance(entity, *aaRec.prevTickRecord, &prevBalanceLayer) &&
						prevBalanceLayer.m_flCycle != curBalanceLayer.m_flCycle || curBalanceLayer.m_flWeight == 1.f;

					bool doBruteForce = bruteforce.missedCount >= Menu::Window.RageBotTab.BruteforceAfterXShots.GetValue();

					if (flags.onGround)
					{
						if (aaRec.IsEntityMoving(entity))
						{
							// moving resolver

							if (flags.fakeWalking)
							{
								// fake walk resolver

								if (aaRec.DeltaKeepsChanging(cur, 10.f))
								{
									rEyeAngles.y = entity->GetEyeAngles().y - aaRec.GetDeltaByComparingTicks(cur);
									lastResolverMethod = DELTA_CHANGE;
								}
								else if (aaRec.LBYKeepsChanging(cur, 10.f))
								{
									rEyeAngles.y = aaRec.GetLBYByComparingTicks(cur);
									lastResolverMethod = LBY_CHANGE;
								}
								else
								{
									doBruteForce = true;
								}
							}
							else
							{
								// moving resolver

								lastResolverMethod = MOVING_LBY;
								rEyeAngles.y = entity->GetLowerBodyYaw();
							}
						}
						else
						{
							// standing resolver

							if (flags.fakingLby)
							{
								// fake lby resolver

								if (std::abs(lbydelta - aaRec.GetDeltaByComparingTicks(cur)) <= 10)
								{
									rEyeAngles.y = Math::NormalizeYawResolver(flOriginalAngle - lbydelta);
									lastResolverMethod = LBY_TICKS;
								}
								else if (lbydelta < 35 && lbydelta > -35)
								{
									rEyeAngles.y = aaRec.GetDeltaByComparingTicks(cur) + 180;
									lastResolverMethod = LBY_CALCULATE;
								}
								else if (fabsf(bodyeyedelta) < 35.0f && fabsf(bodyeyedelta) > 0.0f)
								{
									rEyeAngles.y = cur.front()->m_flLowerBodyYawTarget + bodyeyedelta;
									lastResolverMethod = BODYEYE_DELTA;
								}
								else
								{
									doBruteForce = true;
								}
							}
							else
							{
								// standing resolver

								if (std::abs(lbydelta - aaRec.GetDeltaByComparingTicks(cur)) <= 10)
								{
									rEyeAngles.y = Math::NormalizeYawInPlace(flOriginalAngle - lbydelta);
									lastResolverMethod = LBY_TICKS;
								}
								else if (lbydelta < 35 && lbydelta > -35)
								{
									rEyeAngles.y = aaRec.GetDeltaByComparingTicks(cur) + 180;
									lastResolverMethod = LBY_CALCULATE;
								}
								else if (fabsf(bodyeyedelta) < 35.0f && fabsf(bodyeyedelta) > 0.0f)
								{
									rEyeAngles.y = cur.front()->m_flLowerBodyYawTarget + bodyeyedelta;
									lastResolverMethod = BODYEYE_DELTA;
								}
								else if (aaRec.HasStaticRealAngle(cur, 15.f))
								{
									rEyeAngles.y = (cur.front()->m_flLowerBodyYawTarget) + (Math::RandomFloat(0.f, 1.f) > 0.5f ? 10 : -10);
									lastResolverMethod = STATIC_YAW;
								}
								else if (aaRec.HasStaticYawDifference(cur))
								{
									rEyeAngles.y = entity->GetEyeAngles().y - (cur.front()->m_angEyeAngless.y - cur.front()->m_flLowerBodyYawTarget);
									lastResolverMethod = STATIC_YAW_FAKE;
								}
								else if (aaRec.DeltaKeepsChanging(cur))
								{
									rEyeAngles.y = entity->GetEyeAngles().y - aaRec.GetDeltaByComparingTicks(cur);
									lastResolverMethod = DELTA_CHANGE;
								}
								else if (aaRec.LBYKeepsChanging(cur))
								{
									rEyeAngles.y = aaRec.GetLBYByComparingTicks(cur);
									lastResolverMethod = LBY_CHANGE;
								}
								else
								{
									doBruteForce = true;
								}
							}
						}
					}
					else
					{
						//TODO: air resolver
						doBruteForce = true;
					}

					// we can't resolve, do bruteforce
					if (doBruteForce)
					{
						std::vector<float> yaw;

						if (flags.fakeWalking)
						{
							QAngle velAngles;
							VectorAngles(oVelocity, velAngles);

							yaw.push_back(lastMoveLby);
							yaw.push_back(velAngles.y + 180.0f);
							yaw.push_back(lastMoveLby + 180.0f);
							yaw.push_back(oLby);

							lastResolverMethod = FAKE_WALK;
						}
						else
						{
							yaw.push_back(lastMoveLby);
							yaw.push_back(lastMoveLby + 180);
							yaw.push_back(lastMoveLby - 35);
							yaw.push_back(lastMoveLby + 90);
							yaw.push_back(lastMoveLby - 90);
							yaw.push_back(lastMoveLby + 35);

							lastResolverMethod = LBY_OVERRIDE;
						}

						if (flags.fakeWalking && flags.onGround)
							rEyeAngles.y = yaw[bruteforce.step[BF_STEP_YAW_FAKEWALK] % yaw.size()];
						else if (flags.ducking && flags.onGround)
							rEyeAngles.y = yaw[bruteforce.step[BF_STEP_YAW_DUCKED] % yaw.size()];
						else if (flags.onGround)
							rEyeAngles.y = yaw[bruteforce.step[BF_STEP_YAW_STANDING] % yaw.size()];
						else if (!flags.onGround)
							rEyeAngles.y = yaw[bruteforce.step[BF_STEP_YAW_AIR] % yaw.size()];
					}

					// if lby updatedd we can override the resolver, because we resolved
					if (flags.lbyUpdated)
					{
						rEyeAngles.y = entity->GetLowerBodyYaw();
						lastResolverMethod = LBY_UPDATE;
					}
				}
			}
			else
			{
				ClearBruteforce();
			}

			if (Menu::Window.RageBotTab.SynThsPitchCorrection.GetState())
			{
				bool fake0 = false;
				bool legit = false;
				{
					switch (bruteforce.step[BF_STEP_YAW_PITCH] % 8)
					{
					case 0: rEyeAngles.x = 89.0f; break;
					case 1: rEyeAngles.x = 89.0f; break;
					case 2: rEyeAngles.x = 89.0f; break;
					case 3: rEyeAngles.x = 0.0f; break;
					case 4: rEyeAngles.x = 89.0f; break;
					case 5: rEyeAngles.x = 89.0f; break;
					case 6: rEyeAngles.x = -89.0f; break;
					case 7: rEyeAngles.x = 89.0f; break;
					}
				}
			}

			if (Menu::Window.RageBotTab.inverseUnresolved.GetState())
			{
				if (!flags.lbyUpdated)
				{
					rEyeAngles.y += 180.0f;
				}
			}

			switch (plPitch)
			{
			case PLP_FORCE_DOWN: rEyeAngles.x = 89.0f; break;
			case PLP_FORCE_ZERO: rEyeAngles.x = 0.0f; break;
			case PLP_FORCE_UP: rEyeAngles.x = -89.0f; break;
			}

			switch (plYaw)
			{
			case PLY_INVERSE: rEyeAngles.y += 180.0f; break;
			case PLY_INVERSE_NO_MOVE: if (entity->GetVelocity().Length() < 1.0f) rEyeAngles.y += 180.0f; break;
			case PLY_LEFT: rEyeAngles.y += 90.0f; break;
			case PLY_RIGHT: rEyeAngles.y += -90.0f; break;
			}
			entity->SetEyeAngles(rEyeAngles);
		}
	}


	bool CResolver::IsValid()
	{
		if (!entity) return false;
		if (!initialized) return false;

		return true;
	}

	//std::array<ResolverV2::CResolver, 64> resolverInfo;
	CResolver dummyResolver;

	CResolver &GetResolver(int index)
	{
		if (index < 0 || index >= MAX_PLAYERS)
			return dummyResolver;
	}

	bool Filter(IClientEntity *entity, IClientEntity *pLocal)
	{
		if (!entity) return true;
		if (entity == pLocal) return true;
		if (entity->IsAlive() == false) return true;
		if (entity->GetTeamNum() != 2 && entity->GetTeamNum() != 3) return true;
		if (entity->IsDormant()) return true;
		if (entity->GetIndex() >= MAX_PLAYERS) return true;
		if (entity->GetIndex() < 0) return true;

		if (AimbotV2::Filter(entity)) return true;

		return false;
	}

	void FrameStageNotifyPreReal(ClientFrameStage_t stage)
	{
		if (!Menu::Window.RageBotTab.SynThsResolver.GetState())
			return;

		int max = Interfaces::Engine->GetMaxClients();

		for (int i = 0; i < max; i++)
		{
			IClientEntityList *BigDickoLarryo;
			IClientEntity *entity = BigDickoLarryo->GetClientEntity(i);

			if (Filter(entity))
			{
				CResolver& resolver = GetResolver(i);
				resolver.ClearPerTickInfo();

				if (entity && !entity->IsAlive())
				{
					resolver.Clear();
				}

				continue;
			}

			CResolver& resolver = GetResolver(i);

			entity->PVSFix();

			if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			{
				CResolver& resolver = GetResolver(i);

				// initialize resolver
				if (!resolver.initialized || resolver.entity != entity)
				{
					resolver.Init(entity);
				}

				resolver.entity = entity;

				// entity updated
				resolver.OnEntityUpdate();

				resolver.ProcessAngles();

				resolver.lastSimulationTime = entity->GetSimulationTime();
			}
			else if (stage == FRAME_RENDER_START)
			{
				if (resolver.initialized)
				{
					resolver.OnFrameRenderStart();
				}
			}
		}
	}

	void CreateMove(CUserCmd *pCmd)
	{
		dummyResolver.initialized = false;

		if (!Menu::Window.RageBotTab.SynThsResolver.GetState())
			return;
	}

	void FrameStageNotifyPostReal(ClientFrameStage_t stage)
	{
		dummyResolver.initialized = false;

		if (!Menu::Window.RageBotTab.SynThsResolver.GetState())
			return;

	}

	void OnShoot(Vector from, Vector to, IClientEntity *entity, IClientEntity *pLocal)
	{
		static float last = 0;
		CBaseCombatWeapon *pWeapon = pLocal->GetWeapon();

		if (pWeapon && pWeapon->GetNextPrimaryAttack() != last)
		{
			CResolver& resolver = GetResolver(entity->GetIndex());

			if (resolver.IsValid())
			{
				lastShotEntity = entity;
				lastShotEyePosition = from;
				lastShotPoint = to;
			}
		}

		last = pWeapon->GetNextPrimaryAttack();
	}

	void HandleGameEvent(IGameEvent *pEvent, FireBulletData &data)
	{
		if (!Menu::Window.RageBotTab.SynThsResolver.GetState())
			return;

		const char *name = pEvent->GetName();

		static uint8_t colorRed[3] = { 255, 100, 100 };
		static uint8_t colorGreen[3] = { 100, 255, 100 };

		if (strstr(name, xorstr("round_start")))
		{
			lastShotEntity = NULL;
			lastShotEyePosition = Vector(0, 0, 0);
			lastShotPoint = Vector(0, 0, 0);
			lastShotResolverFlags = ResolverFlags();
			lastShotResolverBruteforce = BruteforceInfo();

			for (int i = 0; i < Interfaces::Globals->maxClients; i++)
			{
				IClientEntity *entity = Interfaces::EntList->GetClientEntity(i);

				if (!Menu::Window.RageBotTab.NoSpreadMode.GetState())
				{
					CResolver& resolver = GetResolver(i);
					resolver.Clear();
					resolver.ClearBruteforce();
				}
			}
		}
		else if (!strcmp(name, xorstr("player_hurt")))
		{
			int userid = pEvent->GetInt(xorstr("userid"));
			int attackerid = pEvent->GetInt(xorstr("attacker"));
			int dmg_health = pEvent->GetInt(xorstr("dmg_health"));
			int hitgroup = pEvent->GetInt(xorstr("hitgroup"));

			IClientEntity *entity = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetPlayerForUserID(userid));
			IClientEntity *attacker = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetPlayerForUserID(attackerid));

			IClientEntity *pLocal;

			if (!entity || !attacker || attacker != pLocal || Filter(entity)) return;

			CResolver& resolver = GetResolver(entity->GetIndex());

			if (!resolver.IsValid())
				return;

			if (lastShotResolverFlags.fakeWalking)
				resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_FAKEWALK] = false;
			else if (lastShotResolverFlags.ducking)
				resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_DUCKED] = false;
			else if (lastShotResolverFlags.onGround)
				resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_STANDING] = false;
			else
				resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_AIR] = false;

			resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_PITCH] = false;

			player_info_t pinfo;
			if (Interfaces::Engine->GetPlayerInfo(resolver.entity->GetIndex(), &pinfo))
			{
				std::string hitboxName = "";

				switch (hitgroup)
				{
				case 1: hitboxName = std::string(xorstr("HS")); break;
				case 2: hitboxName = std::string(xorstr("UPPER TORSO")); break;
				case 3: hitboxName = std::string(xorstr("LOWER TORSO")); break;
				case 4: hitboxName = std::string(xorstr("LEFT ARM")); break;
				case 5: hitboxName = std::string(xorstr("RIGHT ARM")); break;
				case 6: hitboxName = std::string(xorstr("LEFT LEG")); break;
				case 7: hitboxName = std::string(xorstr("RIGHT LEG")); break;
				}

				Interfaces::CVar->ConsolePrintf("%s", xorstr("[flexhack] "));
				//I::pCVar->ConsoleColorPrintf(colorGreen, "%s", xorstr("[Luminus] "));
				Interfaces::CVar->ConsolePrintf("%s %s %s %d%s%s%s", xorstr("  HIT"), MenuV2::SanitizeName(pinfo.m_szPlayerName).c_str(), xorstr("damage given:"), dmg_health, xorstr(". ["), hitboxName.c_str(), xorstr("].\n"));
			}
		}
		else if (!strcmp(name, xorstr("bullet_impact")))
		{
			int userid = pEvent->GetInt(xorstr("userid"));

			IClientEntity *entity = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetPlayerForUserID(userid));
			IClientEntity *pLocal;
			if (!entity || entity != pLocal || Filter(lastShotEntity))
				return;

			CResolver& resolver = GetResolver(lastShotEntity->GetIndex());

			if (!resolver.IsValid())
				return;

			if (impactAcked)
				return;

			impactAcked = true;

			float x = pEvent->GetFloat(xorstr("x"));
			float y = pEvent->GetFloat(xorstr("y"));
			float z = pEvent->GetFloat(xorstr("z"));

			Vector point = Vector(x, y, z);

			bool fail = false;

			if (!Menu::Window.RageBotTab.NoSpreadMode.GetState())
			{
				QAngle anglesReal = Math::CalcAngle(lastShotEyePosition, point);

				float distance = (lastShotPoint - lastShotEyePosition).Length();

				Vector simulatedPoint;
				Math::AngleVectors(anglesReal, simulatedPoint);
				simulatedPoint.NormalizeInPlace();
				simulatedPoint = lastShotEyePosition + simulatedPoint * distance;

				float delta = (simulatedPoint - lastShotPoint).Length();
				float impactDist = (lastShotPoint - point).Length();

				float damage = AutoWall::GetDamageEx(simulatedPoint, lastShotEyePosition, lastShotEntity, pLocal, lastShotHitbox);


				AutoWall::GetDamageEx(simulatedPoint, lastShotEyePosition, lastShotEntity, pLocal, lastShotHitbox, &data);

				float delta2 = (data.enter_trace.endpos - lastShotPoint).Length();


				if (damage <= 0.0f || (delta >= 5.0f || delta2 > 32.0f))
				{
					lastShotResolverBruteforce.missedBySpread = true;

					player_info_t pinfo;
					if (Interfaces::Engine->GetPlayerInfo(resolver.entity->GetIndex(), &pinfo))
					{
						Interfaces::CVar->ConsolePrintf("%s", xorstr("[flexhack] "));
						//I::pCVar->ConsoleColorPrintf(colorRed, "%s", xorstr("[Luminus] "));
						Interfaces::CVar->ConsolePrintf("%s %s %s [#%0.f#%.0f#%.0f]\n", xorstr("Missed"), MenuV2::SanitizeName(pinfo.m_szPlayerName).c_str(), xorstr("due to spread."), delta, delta2, damage);
					}
				}
			}
			else
			{
				lastShotResolverBruteforce.missedBySpread = false;
			}

			if (!lastShotResolverBruteforce.missedBySpread)
			{
				if (!lastShotResolverFlags.lbyUpdated)
				{
					if (lastShotResolverFlags.fakeWalking)
						resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_FAKEWALK] = true;
					else if (lastShotResolverFlags.ducking)
						resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_DUCKED] = true;
					else if (lastShotResolverFlags.onGround)
						resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_STANDING] = true;
					else
						resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_AIR] = true;

					resolver.bruteforce.changeStep[ResolverV2::BF_STEP_YAW_PITCH] = true;
				}
			}
		}
		else if (!strcmp(name, xorstr("weapon_fire")))
		{
			int userid = pEvent->GetInt(xorstr("userid"));

			IClientEntity *entity = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetPlayerForUserID(userid));

			IClientEntity *pLocal;

			if (!entity || entity != pLocal || Filter(lastShotEntity))
				return;

			CResolver& resolver = GetResolver(lastShotEntity->GetIndex());

			if (!resolver.IsValid())
				return;

			impactAcked = false;

			lastShotResolverBruteforce.missedBySpread = false;

			Vector from = lastShotEyePosition;
			Vector to = lastShotPoint;

			player_info_t pinfo;
			if (Interfaces::Engine->GetPlayerInfo(resolver.entity->GetIndex(), &pinfo))
			{
				std::string rflag = "";
				static uint8_t color[3] = { 100, 100, 255 };

				pinfo.m_szPlayerName[127] = '\0';


				Interfaces::CVar->ConsolePrintf("%s", xorstr("[flexhack] "));
				//I::pCVar->ConsoleColorPrintf(color, "%s", xorstr("[Luminus] "));
				Interfaces::CVar->ConsolePrintf("%s %s%s %s%s", xorstr("Shoot"), MenuV2::SanitizeName(pinfo.m_szPlayerName).c_str(), ".", rflag.c_str(), "\n");

				Vector fw;
				Math::AngleVectors(Math::CalcAngle(from, to), fw);
				fw.NormalizeInPlace();
			}
		}
	}

	void RecvLowerBodyYawTarget(const CRecvProxyData *pData, IClientEntity *entity, void *pOut)
	{
		if (entity)
		{
			float value = pData->m_Value.m_Float;

			IClientEntity *pLocal;

			if (entity == pLocal)
			{
				static float last = 0;

				{
				}

				last = I::Globals->curtime;
			}
			else
			{
				if (Menu::Window.RageBotTab.SynThsResolver.GetState())
				{
					if (!Filter(entity))
					{
						CResolver& resolver = GetResolver(entity->GetIndex());

						if (resolver.IsValid())
						{
							resolver.oLby = Math::NormalizeYawInPlace(value);
						}
					}
				}
			}

			*(float*)pOut = value;
		}

		oRecvLowerBodyYawTarget(pData, entity, pOut);
	}

	void RecvEyeAnglesX(const CRecvProxyData *pData, IClientEntity *entity, void *pOut)
	{
		if (Menu::Window.RageBotTab.SynThsResolver.GetState())
		{
			if (entity)
			{
				CResolver& resolver = GetResolver(entity->GetIndex());

				if (resolver.IsValid())
				{
					float value = pData->m_Value.m_Float;

					resolver.oEyeAngles.x = value;

					*(float*)pOut = value;
				}
			}
		}

		oRecvEyeAnglesX(pData, entity, pOut);
	}

	void RecvEyeAnglesY(const CRecvProxyData *pData, IClientEntity *entity, void *pOut)
	{
		if (Menu::Window.RageBotTab.SynThsResolver.GetState())
		{
			if (entity && !Filter(entity))
			{
				CResolver& resolver = GetResolver(entity->GetIndex());

				if (resolver.IsValid())
				{
					float value = pData->m_Value.m_Float;

					resolver.oEyeAngles.y = value;

					*(float*)pOut = value;
				}
			}
		}

		oRecvEyeAnglesY(pData, entity, pOut);
	}

	void RecvEyeAnglesZ(const CRecvProxyData *pData, IClientEntity *entity, void *pOut)
	{
		if (Menu::Window.RageBotTab.SynThsResolver.GetState())
		{
			if (entity && !Filter(entity))
			{
				CResolver& resolver = GetResolver(entity->GetIndex());

				if (resolver.IsValid())
				{
					float value = pData->m_Value.m_Float;

					resolver.oEyeAngles.z = value;

					*(float*)pOut = value;
				}
			}
		}

		oRecvEyeAnglesZ(pData, entity, pOut);
	}

};*/










//Utilities::Log("APPLY SKIN APPLY SKIN");
/*
IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
INetChannelInfo *nci = Interfaces::Engine->GetNetChannelInfo();

static float myOldLby;
static float myoldTime;
testtimeToTick = TIME_TO_TICKS(0.1);
testServerTick = TIME_TO_TICKS(1);
//testTickCount64 = Interfaces::Globals->tickcount;

static int timerino;

static float oneTickMinues;
if (testServerTick == 128) {
	oneTickMinues = testServerTick / 128;
}
else {
	oneTickMinues = testServerTick / 64;
}

static float nextLBYUpdate;
float serverTime = pLocal->GetTickBase() * Interfaces::Globals->interval_per_tick;
static float oldtime[65];
static bool isPredicted[65];
static int startRound;

// 1. Time on Server LBY Update Predicten
if (consoleProxyLbyLASTUpdateTime <= 0 || startRound != roundStartTest) { // Everytime on each Server its at the Start 0
																		  // Predict each Round LBY NEW... 

	std::fill(begin_(enemyLBYTimer), end_(enemyLBYTimer), 0);
	std::fill(begin_(saveLastHeadshotFloat), end_(saveLastHeadshotFloat), 0);
	std::fill(begin_(saveLastBaimFloat), end_(saveLastBaimFloat), 0);
	std::fill(begin_(saveLastBaim30Float), end_(saveLastBaim30Float), 0);
	std::fill(begin_(saveLastBaim10Float), end_(saveLastBaim10Float), 0);

}
else
{
	if (pLocal->IsAlive()) {

		if (pLocal->velocity().Length2D() > 0.1f && pLocal->GetFlags() & FL_ONGROUND) {

			if (Interfaces::Globals->curtime >= nextLBYUpdate) {
				nextLBYUpdate = Interfaces::Globals->curtime + 0.22;

			}
		}
		else {

			if (Interfaces::Globals->curtime >= nextLBYUpdate && pLocal->GetFlags() & FL_ONGROUND) {

				nextLBYUpdate = Interfaces::Globals->curtime + 1.125;
				LBYBreakerTimer++;

				// TEST LBY PREDICT.... 
				//consoleFsnMyPredictTime = nextLBYUpdate;

				// BreakingLBY
				//testFloat4 = (int)floorf(TIME_TO_TICKS(nextLBYUpdate));
			}
		}
	}
}
myLBYTimer = nextLBYUpdate;

static int startTickBase;
static int timerxd;
static float oldlbyyy[65];
bool fake = pEnt->GetEyeAnglesY()->y;
bool real = pEnt->lowerbody();
static float oldtimer[65];
static bool isLBYPredictited[65];
if (Menu::Window.RageBotTab.AccuracyResolver.GetState())
{
	for (int i = 0; i < Interfaces::Engine->GetMaxClients(); ++i)
	{
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		if (!pEntity || pEntity->IsDormant() || !pEntity->IsAlive())
			continue;
		if (pEntity->GetTeamNum() == pLocal->GetTeamNum() || !pLocal->IsAlive())
			continue;
		Vector* eyeAngles = pEntity->GetEyeAnglesPointer();
		player_info_t pTemp;

		if (!Interfaces::Engine->GetPlayerInfo(i, &pTemp))
			continue;

		if (abs(shotsfired - hittedLogHits[pEntity->index()]) > 0) {
			missedLogHits[pEntity->index()] = abs(shotsfired - hittedLogHits[pEntity->index()]);
		}
		float deltadif = abs(pEntity->GetEyeAngles().y - pEntity->lowerbody());

		static float oldlowerbodyyaw;
		static float lbyproxytime;
		static int bullets;

		if (pEntity->velocity().Length2D() > 0.1f) {

			ResolverStage[pEntity->index()] = 1;
			eyeAngles->y = pEntity->lowerbody();
		}
		else
		{

			if (missedLogHits[pEntity->index()] >= 3 && missedLogHits[pEntity->index()] <= 4)
			{
				if (saveLastHeadshotFloat[pEntity->index()] != 0)
				{
					ResolverStage[pEntity->index()] = 5;
					eyeAngles->y = saveLastHeadshotFloat[pEntity->index()];

				}
				else if (saveLastBaimFloat[pEntity->index()] != 0)
				{
					ResolverStage[pEntity->index()] = 5;

					eyeAngles->y = saveLastBaimFloat[pEntity->index()];
				}
				else if (saveLastBaim30Float[pEntity->index()] != 0)
				{
					ResolverStage[pEntity->index()] = 5;
					eyeAngles->y = saveLastBaim30Float[pEntity->index()];
				}
				else {
					// Just aimbot kek
					ResolverStage[pEntity->index()] = 6;
				}
			}
			else
			{

				lbyproxytime = enemysLastProxyTimer[pEntity->index()] + 0.06f;
				if (lbyproxytime != enemyLBYTimer[pEntity->index()] && abs(lbyproxytime - enemyLBYTimer[pEntity->index()]) > 0.8f) {

					ResolverStage[pEntity->index()] = 2;
					enemyLBYTimer[pEntity->index()] = lbyproxytime;
					eyeAngles->y = pEntity->lowerbody();
					oldlowerbodyyaw = pEntity->lowerbody();
				}
				else
				{

					ResolverStage[pEntity->index()] = 6;
					eyeAngles->y = oldlowerbodyyaw + deltadif;

				}
			}
		}
	}
}*/