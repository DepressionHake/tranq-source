#include "Hooks.h"
#include "Resolver.h"
#include "ESP.h"

SResolveInfo arr_infos[64];
static float lastmovinglby[64];
void resolveyaw::resolve(IClientEntity* m_entity)
{
	animation_layer curlayer, prevlayer;
	SResolveInfo &player_recs = arr_infos[m_entity->index()];
	IClientEntity* localplayer = interfaces::g_entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (m_entity->velocity().Length2D() > 0.01) //moving sets angles to lby
	{
		m_entity->eyeangles()->y = m_entity->lowerbody(); //lby
		lastmovinglby[m_entity->index()] = m_entity->lowerbody(); //setting the angle for lastmovinglby
	}
	else if (m_entity->velocity().Length2D() < 0.01) //standing
	{
		m_entity->eyeangles()->y = lastmovinglby[m_entity->index()]; //lastmovinglby
	}
	else if (BreakingLBY(m_entity, player_recs.prevtickrec, &prevlayer) && m_entity->velocity().Length() < 0.01)
	{
		if ((prevlayer.m_flCycle != curlayer.m_flCycle) || curlayer.m_flWeight == 1.f)
		{
			m_entity->eyeangles()->y = lastmovinglby[m_entity->index()]; //lastmovinglby
		}
	}
	else if (m_entity->velocity().Length2D() < 85 && m_entity->velocity().Length2D() > 1) //basic fakewalk check
	{
		m_entity->eyeangles()->y = lastmovinglby[m_entity->index()]; //we dont know what angle they are using so we set to lastmovinglby
	}
	m_entity->eyeangles()->x = 89.f;
}

bool resolveyaw::BreakingLBY(IClientEntity *player, STickRecord &record, animation_layer *layer)
{
	for (int i = 0; i < record.m_iLayerCount; i++)
	{
		const int activity = player->GetSequenceActivity(record.animationLayer[i].m_nSequence);
		if (activity == 979)
		{
			*layer = record.animationLayer[i];
			return true;
		}
	}
	return false;
}


void resolveyaw::framestage(IClientEntity* entity, ClientFrameStage_t stage)
{
	IClientEntity* localplayer = interfaces::g_entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (localplayer->IsAlive())
	{
		if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			for (int i = 1; i <= 64; i++)
			{
				entity = interfaces::g_entitylist->GetClientEntity(i);

				if (!entity
					|| entity == hackManager.localplayer()
					|| entity->IsDormant()
					|| !entity->IsAlive())
					continue;

				resolveyaw::resolve(entity);
			}
		}
	}
}

resolveyaw* resolver = new resolveyaw();