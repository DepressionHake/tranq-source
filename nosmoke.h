#pragma once
#include "Hooks.h"
#include "Resolver.h"
#include "ESP.h"

namespace NoSmoke
{
	bool RenderSmokePostViewmodel();
	void FrameStageNotify(ClientFrameStage_t stage);
};