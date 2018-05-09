#pragma once
#pragma once


#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

#include "MiscClasses.h"
#include "Interfaces.h"
#include "Menu.h"

class hitmarker
{
	class player_hurt_listener : public IGameEventListener3
	{
	public:
		void start()
		{
			if (!interfaces::GameEventManager->AddListener(this, "player_hurt", false)) {
				throw std::exception("Failed to register the event");
			}
		}
		void stop()
		{
			interfaces::GameEventManager->RemoveListener(this);
		}
	};
public:
	static hitmarker* singleton()
	{
		static hitmarker* instance = new hitmarker;
		return instance;
	}

	void on_fire_event(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "player_hurt")) {
			int attacker = event->GetInt("attacker");
			if (interfaces::engine->GetPlayerForUserID(attacker) == interfaces::engine->GetLocalPlayer() && g_menu.esp.OptionsGlow.getstate())
			{
				_flHurtTime = interfaces::Globals->curtime;
			}
			if (interfaces::engine->GetPlayerForUserID(attacker) == interfaces::engine->GetLocalPlayer() && g_menu.esp.OptionsGlow.getstate())
			{
				PlaySoundA(_soundFileName, NULL, SND_ASYNC);
			}
		}
	}

	void on_paint()
	{
		auto curtime = interfaces::Globals->curtime;
		auto lineSize = 8;
		if (_flHurtTime + 0.25f >= curtime)
		{
			int screenSizeX, screenCenterX;
			int screenSizeY, screenCenterY;
			interfaces::engine->GetScreenSize(screenSizeX, screenSizeY);

			screenCenterX = screenSizeX / 2;
			screenCenterY = screenSizeY / 2;

#define g_pSurface interfaces::Surface
			g_pSurface->DrawSetColor(200, 200, 200, 255);
			g_pSurface->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4));
			g_pSurface->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4));
			g_pSurface->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4));
			g_pSurface->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4));
		}
	}

private:
	const char*             _soundFileName = "csgo\\sound\\hitsound.wav";
	float                   _flHurtTime;
};

