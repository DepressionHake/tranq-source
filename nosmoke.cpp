/*#include "nosmoke.h"
#include "Interfaces.h"


std::vector<const char*> smoke_materials = 
{
"particle/vistasmokev1/vistasmokev1_fire",
"particle/vistasmokev1/vistasmokev1_smokegrenade",
"particle/vistasmokev1/vistasmokev1_emods",
"particle/vistasmokev1/vistasmokev1_emods_impactdust",
};

bool NoSmoke::RenderSmokePostViewmodel()
{
	return Menu::Window.VisualsTab.Active.GetState && Menu::Window.VisualsTab.OtherNoSmoke.GetState;
}

void NoSmoke::FrameStageNotify(ClientFrameStage_t stage)
{
	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
	return;

	for (auto material_name : smoke_materials)
	{
		IMaterial* mat = material->SetMaterialVarFlag(material_name, TEXTURE_GROUP_OTHER);
		mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, Menu::Window.VisualsTab.Active.GetState && Menu::Window.VisualsTab.OtherNoSmoke.GetState);
	}
}

void NoSmoke::AimTuxShutdown()
{
	for (auto material_name : smoke_materials)
	{
		IMaterial* mat = material->SetMaterialVarFlag(material_name, TEXTURE_GROUP_OTHER);
		mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
	}
}*/