/*#include "dmginc.h"
DamageIndicators damage_indicators;
#include "RenderManager.h"
void DamageIndicators::paint() {
	int red = (rand() % (int)(254 + 1));
	int redg = (rand() % (int)(254 + 1));
	int redb = (rand() % (int)(254 + 1));
	IClientEntity* pLocal = hackManager.pLocal();
	float curtime = pLocal->GetTickBase() * Interfaces::Globals->interval_per_tick;
	for (int i = 0; i < data.size(); i++) {
		if (data[i].flEraseTime < curtime) {
			data.erase(data.begin() + i);
			continue;
		}
		if (!data[i].bInitialized) {
			data[i].Position = data[i].Player->GetHeadPos();
			data[i].bInitialized = true;
		}
		if (curtime - data[i].flLastUpdate > 0.0001f) {
			data[i].Position.z -= (0.1f * (curtime - data[i].flEraseTime));
			data[i].flLastUpdate = curtime;
		}
		Vector screen_pos;
		if (Render::WorldToScreen(data[i].Position, screen_pos))
			Render::text(screen_pos.x, screen_pos.y, std::to_string(data[i].iDamage).c_str(), Render::Fonts::ESP, Color(red, redg, redb, 255));
	}
}*/