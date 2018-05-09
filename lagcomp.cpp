#include "EdgyLagComp.h"
#include "RageBot.h"

#define TICK_INTERVAL			(interfaces::Globals->interval_per_tick)

#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

void BackTrack::legitBackTrack(CUserCmd* cmd, IClientEntity* localplayer)
{
	if (g_menu.legit.AimbotBacktrack.getstate())
	{
		int bestTargetIndex = -1;
		int tickxd = g_menu.legit.TickModulation.getvalue();
		float bestFov = FLT_MAX;
		player_info_t info;
		if (!localplayer->IsAlive())
			return;

		for (int i = 0; i < interfaces::engine->GetMaxClients(); i++)
		{
			auto entity = (IClientEntity*)interfaces::g_entitylist->GetClientEntity(i);

			if (!entity || !localplayer)
				continue;

			if (entity == localplayer)
				continue;

			if (!interfaces::engine->GetPlayerInfo(i, &info))
				continue;

			if (entity->IsDormant())
				continue;

			if (entity->GetTeamNum() == localplayer->GetTeamNum())
				continue;

			if (entity->IsAlive())
			{

				float simtime = entity->GetSimulationTime();
				Vector hitboxPos = GetHitboxPosition(entity, 0);

				//headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
				headPositions[i][cmd->command_number % 12] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = AngleVector(cmd->viewangles + (localplayer->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
				float FOVDistance = DistPointToLine(hitboxPos, localplayer->GetEyePosition(), ViewDir);

				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

		float bestTargetSimTime;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir = AngleVector(cmd->viewangles + (localplayer->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
			for (int t = 0; t < 12; ++t)
			{
				float tempFOVDistance = DistPointToLine(headPositions[bestTargetIndex][t].hitboxPos, localplayer->GetEyePosition(), ViewDir);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > localplayer->GetSimulationTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}
			if (cmd->buttons & IN_ATTACK)
			{
				cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
			}
		}
	}
}

void BackTrack::rageBackTrack(CUserCmd* cmd, IClientEntity* localplayer)
{
	if (g_menu.rage.AccuracyBacktracking.getstate())
	{
		int bestTargetIndex = -1;
		int tickxd = g_menu.legit.TickModulation.getvalue();
		float bestFov = FLT_MAX;
		player_info_t info;
		if (!localplayer->IsAlive())
			return;

		for (int i = 0; i < interfaces::engine->GetMaxClients(); i++)
		{
			auto entity = (IClientEntity*)interfaces::g_entitylist->GetClientEntity(i);

			if (!entity || !localplayer)
				continue;

			if (entity == localplayer)
				continue;

			if (!interfaces::engine->GetPlayerInfo(i, &info))
				continue;

			if (entity->IsDormant())
				continue;

			if (entity->GetTeamNum() == localplayer->GetTeamNum())
				continue;

			if (entity->IsAlive())
			{

				float simtime = entity->GetSimulationTime();
				Vector hitboxPos = GetHitboxPosition(entity, 0);

				headPositions[i][cmd->command_number % 12] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = AngleVector(cmd->viewangles + (localplayer->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
				float FOVDistance = DistPointToLine(hitboxPos, localplayer->GetEyePosition(), ViewDir);

				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

		float bestTargetSimTime;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir = AngleVector(cmd->viewangles + (localplayer->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
			for (int t = 0; t < 12; ++t)
			{
				float tempFOVDistance = DistPointToLine(headPositions[bestTargetIndex][t].hitboxPos, localplayer->GetEyePosition(), ViewDir);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > localplayer->GetSimulationTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}
			if (cmd->buttons & IN_ATTACK)
			{
				cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
			}
		}
	}
}

BackTrack* backtracking = new BackTrack();
backtrackData headPositions[64][12];