

#include "Menu.h"
#include "Controls.h"
#include "Hooks.h"
#include "Interfaces.h"
#include "CRC32.h"
#include "RenderManager.h"
#include "GUI.h"

#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 600

AyyWareWindow g_menu;
void SaveCallback()
{
	switch (g_menu.OtherConfigBox.getindex())
	{
	case 0:
		GUI.SaveWindowState(&g_menu, "autoconfig.cfg");
		break;
	case 1:
		GUI.SaveWindowState(&g_menu, "scoutconfig.cfg");
		break;
	case 2:
		GUI.SaveWindowState(&g_menu, "pistolconfig.cfg");
		break;
	case 3:
		GUI.SaveWindowState(&g_menu, "legitconfig.cfg");
		break;
	case 4:
		GUI.SaveWindowState(&g_menu, "awpconfig.cfg");
		break;
	case 5:
		GUI.SaveWindowState(&g_menu, "otherconfig.cfg");
		break;
	}
}

void LoadCallback()
{
	switch (g_menu.OtherConfigBox.getindex())
	{
	case 0:
		GUI.LoadWindowState(&g_menu, "autoconfig.cfg");
		break;
	case 1:
		GUI.LoadWindowState(&g_menu, "scoutconfig.cfg");
		break;
	case 2:
		GUI.LoadWindowState(&g_menu, "pistolconfig.cfg");
		break;
	case 3:
		GUI.LoadWindowState(&g_menu, "legitconfig.cfg");
		break;
	case 4:
		GUI.LoadWindowState(&g_menu, "awpconfig.cfg");
		break;
	case 5:
		GUI.LoadWindowState(&g_menu, "otherconfig.cfg");
		break;
	}
}



void UnLoadCallbk()
{
	DoUnload = true;
}

void KnifeApplyCallbk()
{
	static ConVar* Meme = interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	interfaces::engine->ClientCmd_Unrestricted("cl_fullupdate");
}

void GlovesApplyCallbk()
{
	static ConVar* Meme = interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	interfaces::engine->ClientCmd_Unrestricted("cl_fullupdate");
}

void AyyWareWindow::Setup()
{
	SetPosition(350, 50);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTitle("tranquility");

	RegisterTab(&rage);
	RegisterTab(&legit);
	RegisterTab(&esp);
	RegisterTab(&misc);
	//RegisterTab(&AntiAimTab);
	RegisterTab(&ColorTab);
	RegisterTab(&SkinTab);
	//RegisterTab(&Playerlist);

	RECT Client = GetClientArea();
	Client.bottom -= 29;

	rage.Setup();
	legit.Setup();
	esp.Setup();
	misc.Setup();
	//AntiAimTab.Setup();
	ColorTab.Setup();
	SkinTab.Setup();
	//Playerlist.Setup();

#pragma region Bottom Buttons
	OtherConfigBox.SetFileId("cfg_box");
	OtherConfigBox.AddItem("Auto");
	OtherConfigBox.AddItem("Scout");
	OtherConfigBox.AddItem("Pistol");
	OtherConfigBox.AddItem("Legit");
	OtherConfigBox.AddItem("Awp");
	OtherConfigBox.AddItem("Other");
	OtherConfigBox.SetPosition(642, 295);
	OtherConfigBox.SetSize(95, 200);

	SaveButton.SetText("Save");
	SaveButton.SetCallback(SaveCallback);
	SaveButton.SetSize(95, 200);
	SaveButton.SetPosition(642, 235);

	LoadButton.SetText("Load");
	LoadButton.SetCallback(LoadCallback);
	LoadButton.SetSize(95, 200);
	LoadButton.SetPosition(642, 265);


	misc.RegisterControl(&SaveButton);
	misc.RegisterControl(&LoadButton);
	misc.RegisterControl(&OtherConfigBox);

	Radar->SetPosition(g_menu.esp.OtherRadarXPosition.getvalue(), g_menu.esp.OtherRadarYPosition.getvalue());
	Radar->SetSize(200, 200);

#pragma endregion Setting up the settings buttons
}

void Crage::Setup()
{
	SetTitle("Rage");

	ActiveLabel.SetPosition(32, 48);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(78, 48);
	RegisterControl(&Active);

#pragma region RageBot

	AimbotGroup.SetPosition(16, 48);
	AimbotGroup.SetText("");
	AimbotGroup.SetSize(376, 198);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Aimbot", this, &AimbotEnable);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl("Auto Fire", this, &AimbotAutoFire);

	AimbotFov.SetFileId("aim_fov");
	AimbotFov.SetBoundaries(0.f, 180.f);
	AimbotFov.SetValue(180.f);
	AimbotGroup.PlaceLabledControl("FOV", this, &AimbotFov);

	AimbotSilentAim.SetFileId("aim_silentmethod");
	AimbotGroup.PlaceLabledControl("Silent Aim", this, &AimbotSilentAim);

	//AimbotAutoPistol.SetFileId("aim_autopistol");
	//AimbotGroup.PlaceLabledControl("Auto Pistol", this, &AimbotAutoPistol);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl("On Key", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl("Key", this, &AimbotKeyBind);

	AimbotAutoRevolver.SetFileId("aim_acock");
	AimbotGroup.PlaceLabledControl("Auto Revolver", this, &AimbotAutoRevolver);

	TargetHitbox.SetFileId("tgt_hitbox");
	TargetHitbox.AddItem("Head");
	TargetHitbox.AddItem("Neck");
	TargetHitbox.AddItem("Chest");
	TargetHitbox.AddItem("Stomach");
	TargetHitbox.AddItem("Pelvis");
	AimbotGroup.PlaceLabledControl("Hitbox", this, &TargetHitbox);

	TargetSecondaryHitbox.SetFileId("tgt_multibox");
	AimbotGroup.PlaceLabledControl("Multi-Box", this, &TargetSecondaryHitbox);

	TargetHitscan.SetFileId("tgt_hitscan");
	AimbotGroup.PlaceLabledControl("Hitscan", this, &TargetHitscan);

	PreferBodyAim.SetFileId("tgt_preferbaim");
	AimbotGroup.PlaceLabledControl("Prefer Baim", this, &PreferBodyAim);

	TargetSmart.SetFileId("acc_smart");
	TargetSmart.SetBoundaries(0, 20);
	TargetSmart.SetValue(0);
	AimbotGroup.PlaceLabledControl("Body Aim After (X) Shots", this, &TargetSmart);

	TargetBaimHealth.SetFileId("acc_baimhealth");
	TargetBaimHealth.SetBoundaries(0, 100);
	TargetBaimHealth.SetValue(0);
	AimbotGroup.PlaceLabledControl("Body Aim If < (X) HP", this, &TargetBaimHealth);

	AimbotAwpAtBody.SetFileId("acc_bodyawp");
	AimbotGroup.PlaceLabledControl("Auto AWP Body", this, &AimbotAwpAtBody);

	TargetMultipoint.SetFileId("tgt_multipoint");
	AimbotGroup.PlaceLabledControl("Multipoint", this, &TargetMultipoint);

	AimbotMultiPointIndexes.SetFileId("aim_mpindexes");
	AimbotMultiPointIndexes.SetBoundaries(0.f, 1.f);
	AimbotMultiPointIndexes.SetValue(0.f);
	AimbotGroup.PlaceLabledControl("Point Scale", this, &AimbotMultiPointIndexes);

	AccuracyRecoil.SetFileId("acc_norecoil");
	AimbotGroup.PlaceLabledControl("No Recoil", this, &AccuracyRecoil);

	AccuracyAutoWall.SetFileId("acc_awall");
	AimbotGroup.PlaceLabledControl("Auto Wall", this, &AccuracyAutoWall);


#pragma endregion Targetting controls 

#pragma region Accuracy
	AccuracyGroup.SetPosition(408, 48);
	AccuracyGroup.SetText("");
	AccuracyGroup.SetSize(360, 360); //280
	RegisterControl(&AccuracyGroup);

	AccuracyMinimumDamage.SetFileId("acc_mindmg");
	AccuracyMinimumDamage.SetBoundaries(0.f, 100.f);
	AccuracyGroup.PlaceLabledControl("Min Damage", this, &AccuracyMinimumDamage);

	AccuracyMovement.SetFileId("acc_stop");
	AccuracyMovement.AddItem("Off");
	AccuracyMovement.AddItem("Auto-Stop");
	AccuracyMovement.AddItem("Auto-Crouch");
	AccuracyGroup.PlaceLabledControl("Auto Movement", this, &AccuracyMovement);

	AccuracyAutoScope.SetFileId("acc_scope");
	AccuracyGroup.PlaceLabledControl("Auto Scope", this, &AccuracyAutoScope);

	AccuracyHitchanceVal.SetFileId("acc_chance");
	AccuracyHitchanceVal.SetBoundaries(0, 100);
	AccuracyHitchanceVal.SetValue(0);
	AccuracyGroup.PlaceLabledControl("Hitchance", this, &AccuracyHitchanceVal);

	AccuracyBacktracking.SetFileId("aa_btrack");
	AccuracyGroup.PlaceLabledControl("Backtracking", this, &AccuracyBacktracking);

	AccuracyResolverBeta.SetFileId("aa_resolve");
	AccuracyGroup.PlaceLabledControl("Resolver", this, &AccuracyResolverBeta);

	AntiAimEnable.SetFileId("aa_enable");
	AccuracyGroup.PlaceLabledControl("AA Enable", this, &AntiAimEnable);

	AntiAimPitch.SetFileId("aa_pitch");
	AntiAimPitch.AddItem("Off");//0
	AntiAimPitch.AddItem("Emotion");//1
	AntiAimPitch.AddItem("Crooked Emotion");//2
	AntiAimPitch.AddItem("HalfDown");//3
	AntiAimPitch.AddItem("Up");//4
	AntiAimPitch.AddItem("Zero");//5
	AntiAimPitch.AddItem("No-Spread");//6
	AccuracyGroup.PlaceLabledControl("Pitch", this, &AntiAimPitch);

	staticyaw.SetFileId("aa_real");
	staticyaw.AddItem("None");//0
	staticyaw.AddItem("Backwards");//1
	staticyaw.AddItem("Sideways");//2
	staticyaw.AddItem("Adaptive");//3
	staticyaw.AddItem("Sideways Jitter");//4
	staticyaw.AddItem("Backwards Jitter");//5
	staticyaw.AddItem("Lowerbody");//6
	staticyaw.AddItem("Random");//7
	staticyaw.AddItem("Spin");//8
	staticyaw.AddItem("Backwards Z");//9
	staticyaw.AddItem("Jitter Z");//10
	staticyaw.AddItem("Custom");//11
	staticyaw.AddItem("Sideways Z");//12
	AccuracyGroup.PlaceLabledControl("Real Yaw", this, &staticyaw);

	fakeyaw.SetFileId("aa_fake");
	fakeyaw.AddItem("None");//0
	fakeyaw.AddItem("Backwards");//1
	fakeyaw.AddItem("Sideways");//2
	fakeyaw.AddItem("Adaptive");//3
	fakeyaw.AddItem("Sideways Jitter");//4
	fakeyaw.AddItem("Backwards Jitter");//5
	fakeyaw.AddItem("Lowerbody");//6
	fakeyaw.AddItem("Random");//7
	fakeyaw.AddItem("Spin");//8
	AccuracyGroup.PlaceLabledControl("Fake Yaw", this, &fakeyaw);

	movingyaw.SetFileId("aa_move");
	movingyaw.AddItem("None");//0
	movingyaw.AddItem("Sideways");//1
	movingyaw.AddItem("Backwards");//2
	movingyaw.AddItem("Adaptive");//3
	movingyaw.AddItem("Backwards Jitter");//4
	movingyaw.AddItem("Sideways Jitter");//5
	movingyaw.AddItem("Back Lowerbody");//6
	movingyaw.AddItem("Random");//7
	movingyaw.AddItem("Spin");//8
	movingyaw.AddItem("Sideways Z");//9
	movingyaw.AddItem("Jitter Z");//10
	movingyaw.AddItem("Forwards Z");//12
	AccuracyGroup.PlaceLabledControl("Move Yaw", this, &movingyaw);

	AntiAimFlipKey.SetFileId("aim_flipkey");
	AccuracyGroup.PlaceLabledControl("AA Flip", this, &AntiAimFlipKey);

	staticyawcustom.SetFileId("aim_custmr");
	staticyawcustom.SetBoundaries(0.f, 360.f);
	AccuracyGroup.PlaceLabledControl("Custom Yaw", this, &staticyawcustom);

	AntiAimEdge.SetFileId("aim_edge");
	AccuracyGroup.PlaceLabledControl("Wall DTC", this, &AntiAimEdge);

	AntiAimOffset.SetFileId("aa_offset");
	AntiAimOffset.SetBoundaries(0.f, 180.f);
	AntiAimOffset.SetValue(0.f);
	AccuracyGroup.PlaceLabledControl("Add Jitter", this, &AntiAimOffset);

	SpinSpeed.SetFileId("aa_AntiAimSpinspeed");
	SpinSpeed.SetBoundaries(0.f, 800.f);
	SpinSpeed.SetValue(0.f);
	AccuracyGroup.PlaceLabledControl("Spin Speed", this, &SpinSpeed);

	AntiAimBreakLBY.SetFileId("aa_break");
	AntiAimBreakLBY.SetBoundaries(0.f, 180.f);
	AccuracyGroup.PlaceLabledControl("LBY Break°", this, &AntiAimBreakLBY);

	AntiAimKnife.SetFileId("aa_knife");
	AccuracyGroup.PlaceLabledControl("Knife AA", this, &AntiAimKnife);

	//OtherFreestanding.SetFileId("aa_knife");
	//AccuracyGroup.PlaceLabledControl("Override Freestanding", this, &OtherFreestanding);

	FakeAngleChams.SetFileId("aa_fkechams");
	FakeAngleChams.AddItem("Off");
	FakeAngleChams.AddItem("Fake Angle");
	FakeAngleChams.AddItem("LBY Angle");
	AccuracyGroup.PlaceLabledControl("Draw Secondary Angles", this, &FakeAngleChams);

#pragma endregion  RageBot
}

void Clegit::Setup()
{
	SetTitle("Legit");

	ActiveLabel.SetPosition(32, 48);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(78, 48);
	RegisterControl(&Active);

#pragma region Aimbot
	AimbotGroup.SetPosition(16, 48);
	AimbotGroup.SetText("");
	AimbotGroup.SetSize(376, 250);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enable", this, &AimbotEnable);

	AimbotAutoPistol.SetFileId("aim_apistol");
	AimbotGroup.PlaceLabledControl("Auto Pistol", this, &AimbotAutoPistol);

	AimbotBacktrack.SetFileId("legit_backtrack");
	AimbotGroup.PlaceLabledControl("Backtrack Ticks", this, &AimbotBacktrack);

	LegitAA.SetFileId("other_legitaa");
	AimbotGroup.PlaceLabledControl("Legit AA", this, &LegitAA);

	AimbotFriendlyFire.SetFileId("aim_friendfire");
	AimbotGroup.PlaceLabledControl("Friendly Fire", this, &AimbotFriendlyFire);

	AimbotSmokeCheck.SetFileId("otr_smokecheck");
	AimbotGroup.PlaceLabledControl("Smoke Check", this, &AimbotSmokeCheck);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl("On Key", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl("Key Bind", this, &AimbotKeyBind);

	WeaponPistGroup.SetPosition(254, 48);
	WeaponPistGroup.SetText("");
	WeaponPistGroup.SetSize(240, 155);
	RegisterControl(&WeaponPistGroup);

	WeaponPistHitbox.SetFileId("pist_hitbox");
	WeaponPistHitbox.AddItem("Head");
	WeaponPistHitbox.AddItem("Neck");
	WeaponPistHitbox.AddItem("Chest");
	WeaponPistHitbox.AddItem("Stomach");
	WeaponPistHitbox.AddItem("Multihitbox");
	WeaponPistGroup.PlaceLabledControl("Hitbox", this, &WeaponPistHitbox);

	WeaponPistSpeed.SetFileId("pist_speed");
	WeaponPistSpeed.SetBoundaries(0.f, 100.f);
	WeaponPistSpeed.SetValue(1.0f);
	WeaponPistGroup.PlaceLabledControl("Max Speed", this, &WeaponPistSpeed);

	WeaponPistFoV.SetFileId("pist_fov");
	WeaponPistFoV.SetBoundaries(0.f, 10.f);
	WeaponPistFoV.SetValue(3.f);
	WeaponPistGroup.PlaceLabledControl("Field of View", this, &WeaponPistFoV);

	WeaponPistInacc.SetFileId("pist_inacc");
	WeaponPistInacc.SetBoundaries(0.f, 10.f);
	WeaponPistGroup.PlaceLabledControl("Humanize", this, &WeaponPistInacc);

	WeaponPistPSilent.SetFileId("pist_psi");
	WeaponPistGroup.PlaceLabledControl("pSilent", this, &WeaponPistPSilent);

	WeaponPistAimtime.SetValue(0);
	WeaoponPistStartAimtime.SetValue(0);
}

void Cesp::Setup()
{
	SetTitle("Visuals");

	ActiveLabel.SetPosition(32, 48);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(78, 48);
	RegisterControl(&Active);

#pragma region Options
	OptionsGroup.SetText("");
	OptionsGroup.SetPosition(16, 48);
	OptionsGroup.SetSize(376, 250);
	RegisterControl(&OptionsGroup);

	FiltersEnemiesOnly.SetFileId("ftr_enemyonly");
	OptionsGroup.PlaceLabledControl("Enemy Only", this, &FiltersEnemiesOnly);

	OptionsBox.SetFileId("otr_box");
	OptionsBox.AddItem("Off");
	OptionsBox.AddItem("Normal");
	OptionsBox.AddItem("Health Based");
	OptionsGroup.PlaceLabledControl("Box", this, &OptionsBox);

	OptionsFillBox.SetFileId("opt_Fill");
	OptionsGroup.PlaceLabledControl("Box Fill", this, &OptionsFillBox);

	OptionsName.SetFileId("opt_name");
	OptionsGroup.PlaceLabledControl("Name", this, &OptionsName);

	OptionsVitals.SetFileId("opt_hp");
	OptionsVitals.AddItem("Off");
	OptionsVitals.AddItem("Split");
	OptionsVitals.AddItem("Full");
	OptionsGroup.PlaceLabledControl("Health", this, &OptionsVitals);

	OptionsWeapon.SetFileId("opt_weapon");
	OptionsGroup.PlaceLabledControl("Weapon", this, &OptionsWeapon);

	//OptionsWeapon2.SetFileId("opt_weapon");
	//OptionsGroup.PlaceLabledControl("Weapon Icon", this, &OptionsWeapon2);

	OptionsInfo.SetFileId("opt_info");
	OptionsGroup.PlaceLabledControl("Info", this, &OptionsInfo);

	BacktrackingLol.SetFileId("opt_backdot");
	OptionsGroup.PlaceLabledControl("Backtracking Dot", this, &BacktrackingLol);

	OptionsHeadIndicator.SetFileId("opt_headarrow");
	OptionsGroup.PlaceLabledControl("Angle Indicator", this, &OptionsHeadIndicator);

	OtherChams.SetFileId("opt_chams");
	OtherChams.AddItem("Off");
	OtherChams.AddItem("Normal");
	OtherChams.AddItem("Wireframe");
	OptionsGroup.PlaceLabledControl("Chams", this, &OtherChams);

	LocalChams.SetFileId("opt_lcl");
	OptionsGroup.PlaceLabledControl("Local Chams", this, &LocalChams);

	OptionsChamsXQZ.SetFileId("opt_xqzcham");
	OptionsGroup.PlaceLabledControl("XQZ Chams", this, &OptionsChamsXQZ);

	OptionsSkeleton.SetFileId("opt_bone");
	OptionsGroup.PlaceLabledControl("Skeleton", this, &OptionsSkeleton);

	OtherGlow.SetFileId("otr_glo");
	OptionsGroup.PlaceLabledControl("Glow", this, &OtherGlow);

	OptionsAimSpot.SetFileId("opt_aimspot");
	OptionsGroup.PlaceLabledControl("Head Cross", this, &OptionsAimSpot);

	FiltersWeapons.SetFileId("ftr_weaps");
	OptionsGroup.PlaceLabledControl("Show Items", this, &FiltersWeapons);

	//ShowImpacts.SetFileId("opt_impacts");
	//OptionsGroup.PlaceLabledControl("Show Impacts", this, &ShowImpacts);

	IsScoped.SetFileId("opt_scoped");
	OptionsGroup.PlaceLabledControl("Show Scoped", this, &IsScoped);

	OptionsRadar.SetFileId("otr_radar");
	OptionsGroup.PlaceLabledControl("In-Game Radar", this, &OptionsRadar);

	OtherRadar.SetFileId("otr_drawnradar");
	OptionsGroup.PlaceLabledControl("Drawn Radar", this, &OtherRadar);

	OtherRadarEnemyOnly.SetFileId("otr_radar_enemy_only");
	OptionsGroup.PlaceLabledControl("    Enemy Only", this, &OtherRadarEnemyOnly);

	OtherRadarVisibleOnly.SetFileId("otr_radar_visible_only");
	OptionsGroup.PlaceLabledControl("    Visible Only", this, &OtherRadarVisibleOnly);

	OtherRadarXPosition.SetFileId("otr_radar_position_x");
	OtherRadarYPosition.SetFileId("otr_radar_position_y");

	OtherRadarScale.SetFileId("otr_radar_scale");
	OtherRadarScale.SetBoundaries(0, 10000);
	OtherRadarScale.SetValue(10000);
	OptionsGroup.PlaceLabledControl("    FOV Units", this, &OtherRadarScale);

	StaticProps.SetFileId("otr_staticprop");
	StaticProps.AddItem("Off");
	StaticProps.AddItem("Alpha");
	StaticProps.AddItem("Wireframe");
	OptionsGroup.PlaceLabledControl("Prop ESP", this, &StaticProps);

	/*	OptionsLBY.SetFileId("aa_LBY");
	OptionsGroup.PlaceLabledControl("LBY indicator", this, &OptionsLBY);*/

#pragma endregion Setting up the Options controls


#pragma region Other
	OtherGroup.SetText("");
	OtherGroup.SetPosition(408, 48);
	OtherGroup.SetSize(360, 360);
	RegisterControl(&OtherGroup);

	OtherSpreadCrosshair.SetFileId("otr_spreadhair");
	OtherGroup.PlaceLabledControl("Spread Crosshair", this, &OtherSpreadCrosshair);

	OtherSpreadCrosshairValue.SetFileId("otr_spreadhairo");
	OtherSpreadCrosshairValue.SetBoundaries(0.f, 255.f);
	OtherSpreadCrosshairValue.SetValue(120.f);
	OtherGroup.PlaceLabledControl("Spread Crosshair Opacity", this, &OtherSpreadCrosshairValue);

	//SniperCrosshair.SetFileId("otr_sniprhair");
	//OtherGroup.PlaceLabledControl("Sniper Crosshair", this, &SniperCrosshair);

	OtherRecoilCrosshair.SetFileId("otr_recoilhair");
	OtherGroup.PlaceLabledControl("Recoil Crosshair", this, &OtherRecoilCrosshair);

	OtherFoVCrosshair.SetFileId("otr_fovcross");
	OtherFoVCrosshair.AddItem("Off");
	OtherFoVCrosshair.AddItem("Legitbot");
	OtherFoVCrosshair.AddItem("Ragebot");
	OtherGroup.PlaceLabledControl("FOV Circle", this, &OtherFoVCrosshair);

	OtherNoVisualRecoil.SetFileId("otr_visrecoil");
	OtherGroup.PlaceLabledControl("No Visual Recoil", this, &OtherNoVisualRecoil);

	OtherNoFlash.SetFileId("otr_noflash");
	OtherGroup.PlaceLabledControl("No Flash", this, &OtherNoFlash);

	OtherNoFlash2.SetFileId("otr_noflash2");
	OtherNoFlash2.SetBoundaries(1, 255);
	OtherGroup.PlaceLabledControl("Flash Value", this, &OtherNoFlash2);

	OtherPlayerLine.SetFileId("otr_angllins");
	OtherGroup.PlaceLabledControl("Angle Lines", this, &OtherPlayerLine);

	OtherGlow2.SetFileId("otr_glo2");
	OtherGroup.PlaceLabledControl("Item Glow", this, &OtherGlow2);

	//OtherBulletBeam.SetFileId("otr_beam");
	//OtherGroup.PlaceLabledControl("Bullet Tracers", this, &OtherBulletBeam);

	//	OtherEnemyCircle.SetFileId("otr_enemccirc");
	//	OtherGroup.PlaceLabledControl("Enemy Circle", this, &OtherEnemyCircle);

	OtherFOV.SetFileId("otr_fov");
	OtherFOV.SetBoundaries(0.f, 180.f);
	OtherFOV.SetValue(90.f);
	OtherGroup.PlaceLabledControl("FOV", this, &OtherFOV);

	OtherViewmodelFOV.SetFileId("otr_viewfov");
	OtherViewmodelFOV.SetBoundaries(0.f, 180.f);
	OtherViewmodelFOV.SetValue(0.f);
	OtherGroup.PlaceLabledControl("Weapon FOV", this, &OtherViewmodelFOV);

	OtherCompRank.SetFileId("opt_comprank");
	OtherGroup.PlaceLabledControl("Reveal Ranks", this, &OtherCompRank);

	OtherBulletTracer2.SetFileId("otr_bulltrcr");
	OtherGroup.PlaceLabledControl("Aim Lines", this, &OtherBulletTracer2);

	OtherRemoveScope.SetFileId("otr_RemoveScope");
	OtherGroup.PlaceLabledControl("Remove Scope", this, &OtherRemoveScope);

	OtherNoSmoke.SetFileId("otr_nosmoke");
	OtherGroup.PlaceLabledControl("Remove Smoke", this, &OtherNoSmoke);

	OtherBarrel.SetFileId("otr_Barrel");
	OtherBarrel.AddItem("Off");
	OtherBarrel.AddItem("Normal");
	OtherBarrel.AddItem("Health Based");
	OtherGroup.PlaceLabledControl("Snap Lines", this, &OtherBarrel);

	OtherDrawNades.SetFileId("otr_nades");
	OtherGroup.PlaceLabledControl("Nade ESP", this, &OtherDrawNades);

	OtherBombShow.SetFileId("otr_bomb");
	OtherGroup.PlaceLabledControl("Bomb ESP", this, &OtherBombShow);

	OtherShowLBY.SetFileId("otr_angles");
	OtherGroup.PlaceLabledControl("Angle Display", this, &OtherShowLBY);

	OtherVelocityESP.SetFileId("otr_vlcty");
	OtherGroup.PlaceLabledControl("Velocity", this, &OtherVelocityESP);

	OptionsArmor.SetFileId("opt_arm");
	OptionsGroup.PlaceLabledControl("Armor ESP", this, &OptionsArmor);

	GrenadeTracer.SetFileId("opt_grndetrae");
	OtherGroup.PlaceLabledControl("Grenade Tracer", this, &GrenadeTracer);

	//WeaponR.SetFileId("weaponsr");
	//  WeaponR.SetBoundaries(0.f, 255.f);
	//WeaponR.SetValue(210.f);
	//	OtherGroup.PlaceLabledControl("Weapon Chams Red", this, &WeaponR);

	//	WeaponG.SetFileId("weapong");
	//	WeaponG.SetBoundaries(0.f, 255.f);
	//	WeaponG.SetValue(20.f);
	//	OtherGroup.PlaceLabledControl("Weapon Chams Green", this, &WeaponG);

	//	WeaponB.SetFileId("weaponb");
	//	WeaponB.SetBoundaries(0.f, 255.f);
	//	WeaponB.SetValue(70.f);
	//	OtherGroup.PlaceLabledControl("Weapon Chams Blue", this, &WeaponB);

	//OtherDamageIndicators.SetFileId("opt_dmgindc");
	//OtherGroup.PlaceLabledControl("Damage Indicators", this, &OtherDamageIndicators);

	OtherAutowallCrosshair.SetFileId("opt_autowallacrs");
	OtherGroup.PlaceLabledControl("Autowall Crosshair", this, &OtherAutowallCrosshair);

	MapESP.SetFileId("otr_mapesp");
	OtherGroup.PlaceLabledControl("Nightmode", this, &MapESP);


	//OtherLSDMode.SetFileId("otr_nigtmde");
	//OtherGroup.PlaceLabledControl("LSD Mode", this, &OtherLSDMode);

	//OtherChromeMode.SetFileId("otr_nigtmde");
	//OtherGroup.PlaceLabledControl("Chrome Mode", this, &OtherChromeMode);

	//OtherCrosshairAngle.SetFileId("otr_crsang");
	//OtherGroup.PlaceLabledControl("Angle Crosshair", this, &OtherCrosshairAngle);

	OtherShowResolverInfo.SetFileId("otr_reslvrinfo");
	OtherGroup.PlaceLabledControl("Resolver Info", this, &OtherShowResolverInfo);

	//DLight.SetFileId("opt_dlights");
	//OtherGroup.PlaceLabledControl("Direction Dot", this, &DLight);

	//OtherBombShow.SetFileId("bomb_showplntd");
	//OtherGroup.PlaceLabledControl("Show Planted Bomb", this, &OtherBombShow);

#pragma endregion Setting up the Other controls

#pragma region WorldOptions
	/*CvarGroup.SetText("World");
	CvarGroup.SetPosition(434, 320);
	CvarGroup.SetSize(334, 170);
	RegisterControl(&CvarGroup);


	AmbientExposure.SetFileId("otr_ambientexposure");
	AmbientExposure.SetBoundaries(0.f, 2.f);
	AmbientExposure.SetValue(2.f);
	CvarGroup.PlaceLabledControl("Ambient-Exposure", this, &AmbientExposure);

	AmbientRed.SetFileId("otr_ambientred");
	AmbientRed.SetBoundaries(0.f, .5f);
	AmbientRed.SetValue(0.f);
	CvarGroup.PlaceLabledControl("Ambient-Red", this, &AmbientRed);

	AmbientGreen.SetFileId("otr_ambientgreen");
	AmbientGreen.SetBoundaries(0.f, .5f);
	AmbientGreen.SetValue(0.f);
	CvarGroup.PlaceLabledControl("Ambient-Green", this, &AmbientGreen);

	AmbientBlue.SetFileId("otr_ambientblue");
	AmbientBlue.SetBoundaries(0.f, .5f);
	AmbientBlue.SetValue(0.f);
	CvarGroup.PlaceLabledControl("Ambient-Blue", this, &AmbientBlue);

	/*AmbientSkybox.SetFileId("otr_skyboxchanger");
	AmbientSkybox.AddItem("Disabled");
	AmbientSkybox.AddItem("Skybox 1");
	AmbientSkybox.AddItem("Skybox 2");
	AmbientSkybox.AddItem("Skybox 3");
	AmbientSkybox.AddItem("Skybox 4");
	CvarGroup.PlaceLabledControl("Change-Skybox", this, &AmbientSkybox);*/

#pragma endregion Setting up the Other controls
}

void Cmisc::Setup()
{
	SetTitle("Misc");

#pragma region Other
	OtherGroup.SetPosition(16, 48);
	OtherGroup.SetSize(376, 250);
	OtherGroup.SetText("");
	RegisterControl(&OtherGroup);

	OtherAutoJump.SetFileId("otr_autojump");
	OtherGroup.PlaceLabledControl("Bunnyhop", this, &OtherAutoJump);

	FakeLagEnable.SetFileId("fakelag_enable");
	OtherGroup.PlaceLabledControl("FakeLag Enable", this, &FakeLagEnable);

	FakeLagChoke.SetFileId("fakelag_choke");
	FakeLagChoke.SetBoundaries(0, 18);
	FakeLagChoke.SetValue(0);
	OtherGroup.PlaceLabledControl("Factor", this, &FakeLagChoke);

	FakeLagTyp.SetFileId("fakelag_typ");
	FakeLagTyp.AddItem("Off");
	FakeLagTyp.AddItem("Normal");
	OtherGroup.PlaceLabledControl("FakeLag Mode", this, &FakeLagTyp);


	//	OtherEdgeJump.SetFileId("otr_edgejump");
	//	OtherGroup.PlaceLabledControl("Edge Jump", this, &OtherEdgeJump);

	OtherAutoStrafe.SetFileId("otr_strafe");
	OtherAutoStrafe.AddItem("Off");
	OtherAutoStrafe.AddItem("Legit");
	OtherAutoStrafe.AddItem("Rage");
	OtherGroup.PlaceLabledControl("Autostrafer", this, &OtherAutoStrafe);

	OtherLogs.SetFileId("otr_logs");
	OtherGroup.PlaceLabledControl("Event Logs", this, &OtherLogs);

	OtherSafeMode.SetFileId("otr_safemode");
	OtherSafeMode.SetState(true);
	OtherGroup.PlaceLabledControl("Anti-Untrusted", this, &OtherSafeMode);

	OtherClantag.SetFileId("otr_clantag");
	OtherGroup.PlaceLabledControl("Clantag", this, &OtherClantag);

	//OtherKillSpamchat.SetFileId("opt_killmessahe");
	//OtherGroup.PlaceLabledControl("Headshot Message", this, &OtherKillSpamchat);

	//FPSClantag.SetFileId("FPSClantag");
	//OtherGroup.PlaceLabledControl("FPS Counter", this, &FPSClantag);

	OtherModelChanger.SetFileId("otr_crash");
	OtherModelChanger.AddItem("Off");
	OtherModelChanger.AddItem("AK-47 Beast");
	OtherModelChanger.AddItem("Knife Pickaxe");
	OtherModelChanger.AddItem("Black Candy Cane");
	//OtherModelChanger.AddItem("Deadpool Model");
	OtherGroup.PlaceLabledControl("Models", this, &OtherModelChanger);

	OtherFakeping.SetFileId("opt_fkepng");
	OtherGroup.PlaceLabledControl("Fake Ping", this, &OtherFakeping);

	//KnifeBot.SetFileId("opt_knfbt");
	//OtherGroup.PlaceLabledControl("KnifeBot", this, &KnifeBot);

	//OtherLastTickDefuse.SetFileId("opt_lsttkdfs");
	//OtherGroup.PlaceLabledControl("Last Tick Defuse", this, &OtherLastTickDefuse);

	//OtherAutoAccept.SetFileId("opt_autoacpt");
	//OtherGroup.PlaceLabledControl("Auto Accept MM", this, &OtherAutoAccept);

	//OtherModelEnable.SetFileId("otr_model?");
	//OtherGroup.PlaceLabledControl("model shit", this, &OtherModelEnable);

	//	OtherTeamChat.SetFileId("otr_teamchat");
	//	OtherGroup.PlaceLabledControl("Team Chat Only", this, &OtherTeamChat);

	//	OtherChatDelay.SetFileId("otr_chatdelay");
	//	OtherChatDelay.SetBoundaries(0.1, 3.0);
	//	OtherChatDelay.SetValue(0.5);
	//	OtherGroup.PlaceLabledControl("Spam Delay", this, &OtherChatDelay);

	//OtherCrasher.SetFileId("otr_crash");
	//OtherGroup.PlaceLabledControl("Ayyware Crasher", this, &OtherCrasher);

	OtherTranqChat.SetFileId("otr_chat");
	OtherGroup.PlaceLabledControl("Chat Spam", this, &OtherTranqChat);

	//OtherAirStuck.SetFileId("otr_astuck");
	//OtherGroup.PlaceLabledControl("Air Stuck", this, &OtherAirStuck);

	FakeWalk.SetFileId("otr_fakewalk");
	OtherGroup.PlaceLabledControl("Fake Walk", this, &FakeWalk);

	OtherCircleStrafeKey.SetFileId("otr_crclstrfe");
	OtherGroup.PlaceLabledControl("Circle Strafe Key", this, &OtherCircleStrafeKey);

	//OtherTextMenu.SetFileId("otr_astuck");
	//OtherGroup.PlaceLabledControl("Text Menu (BROKEN)", this, &OtherTextMenu);

	OtherSpecList.SetFileId("otr_speclist");
	OtherGroup.PlaceLabledControl("Spectators List", this, &OtherSpecList);

	//OtherThirdperson.SetFileId("aa_thirdpsr2");
	//OtherGroup.PlaceLabledControl("Thirdperson Beta", this, &OtherThirdperson);

	OtherHitmarker.SetFileId("otr_hitmarker");
	OtherGroup.PlaceLabledControl("Hitmarker", this, &OtherHitmarker);

	OtherThirdpersonKey.SetFileId("otr_tpkeylul");
	OtherGroup.PlaceLabledControl("Thirdperson", this, &OtherThirdpersonKey);

	//OtherThirdpersonKey2.SetFileId("otr_tpkeylul");
	//OtherGroup.PlaceLabledControl("Thirdperson Beta", this, &OtherThirdpersonKey2);

	OtherThirdpersonRange.SetFileId("aa_thirdpsrrge");
	OtherThirdpersonRange.SetBoundaries(0.f, 300.f);
	OtherGroup.PlaceLabledControl("Thirdperson Range", this, &OtherThirdpersonRange);

	//FakeWalk.SetFileId("otr_FakeWalk");
	//OtherGroup.PlaceLabledControl("Fake Walk", this, &FakeWalk);

	OtherMemewalk.SetFileId("otr_slidewalk");
	OtherGroup.PlaceLabledControl("Slidewalk", this, &OtherMemewalk);

#pragma endregion
}

void CColorTab::Setup()
{
	SetTitle("Colors");

#pragma region
	ColorsGroup.SetPosition(16, 48); //344
	ColorsGroup.SetText("");
	ColorsGroup.SetSize(376, 270);
	RegisterControl(&ColorsGroup);

	/*backR.SetFileId("menu_r");
	backR.SetBoundaries(0.f, 255.f);
	ColorsGroup.PlaceLabledControl("Menu Background R", this, &backR);

	backG.SetFileId("menu_g");
	backG.SetBoundaries(0.f, 255.f);
	ColorsGroup.PlaceLabledControl("Menu Background G", this, &backG);

	backB.SetFileId("menu_b");
	backB.SetBoundaries(0.f, 255.f);
	ColorsGroup.PlaceLabledControl("Menu Background B", this, &backB);*/

	SkeletonR.SetFileId("skel_r");
	SkeletonR.SetBoundaries(0.f, 255.f);
	SkeletonR.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Skeleton R", this, &SkeletonR);

	SkeletonG.SetFileId("skel_g");
	SkeletonG.SetBoundaries(0.f, 255.f);
	SkeletonG.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Skeleton G", this, &SkeletonG);

	SkeletonB.SetFileId("skel_b");
	SkeletonB.SetBoundaries(0.f, 255.f);
	SkeletonB.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Skeleton B", this, &SkeletonB);

	NameR.SetFileId("name_r");
	NameR.SetBoundaries(0.f, 255.f);
	NameR.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Name ESP R", this, &NameR);

	NameG.SetFileId("name_g");
	NameG.SetBoundaries(0.f, 255.f);
	NameG.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Name ESP G", this, &NameG);

	NameB.SetFileId("name_b");
	NameB.SetBoundaries(0.f, 255.f);
	NameB.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Name ESP B", this, &NameB);

	HitMarkerR.SetFileId("Hitmrk_r");
	HitMarkerR.SetBoundaries(0.f, 255.f);
	HitMarkerR.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Hitmarker R", this, &HitMarkerR);

	HitMarkerG.SetFileId("Hitmrk_g");
	HitMarkerG.SetBoundaries(0.f, 255.f);
	HitMarkerG.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Hitmarker G", this, &HitMarkerG);

	HitMarkerB.SetFileId("Hitmrk_b");
	HitMarkerB.SetBoundaries(0.f, 255.f);
	HitMarkerB.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Hitmarker B", this, &HitMarkerB);

	BoxR.SetFileId("box_r");
	BoxR.SetBoundaries(0.f, 255.f);
	ColorsGroup.PlaceLabledControl("Box R", this, &BoxR);

	BoxG.SetFileId("box_g");
	BoxG.SetBoundaries(0.f, 255.f);
	ColorsGroup.PlaceLabledControl("Box G", this, &BoxG);

	BoxB.SetFileId("box_b");
	BoxB.SetBoundaries(0.f, 255.f);
	ColorsGroup.PlaceLabledControl("Box B", this, &BoxB);

	TChamsR.SetFileId("t_color_vis_r");
	TChamsR.SetBoundaries(0.f, 255.f);
	TChamsR.SetValue(0.f);
	ColorsGroup.PlaceLabledControl("Chams R", this, &TChamsR);

	TChamsG.SetFileId("t_color_vis_g");
	TChamsG.SetBoundaries(0.f, 255.f);
	TChamsG.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Chams G", this, &TChamsG);

	TChamsB.SetFileId("t_color_vis_b");
	TChamsB.SetBoundaries(0.f, 255.f);
	TChamsB.SetValue(0.f);
	ColorsGroup.PlaceLabledControl("Chams B", this, &TChamsB);

	LocalTChamsR.SetFileId("t_color_lcl_r");
	LocalTChamsR.SetBoundaries(0.f, 255.f);
	LocalTChamsR.SetValue(0.f);
	ColorsGroup.PlaceLabledControl("Local Chams R", this, &LocalTChamsR);

	LocalTChamsG.SetFileId("t_color_lcl_g");
	LocalTChamsG.SetBoundaries(0.f, 255.f);
	LocalTChamsG.SetValue(255.f);
	ColorsGroup.PlaceLabledControl("Local Chams G", this, &LocalTChamsG);

	LocalTChamsB.SetFileId("t_color_lcl_b");
	LocalTChamsB.SetBoundaries(0.f, 255.f);
	LocalTChamsB.SetValue(0.f);
	ColorsGroup.PlaceLabledControl("Local Chams B", this, &LocalTChamsB);

#pragma endregion


#pragma region

	Color2Group.SetPosition(408, 48);
	Color2Group.SetText("");
	Color2Group.SetSize(376, 270); //280
	RegisterControl(&Color2Group);

	crossR.SetFileId("cross_r");
	crossR.SetBoundaries(0.f, 255.f);
	crossR.SetValue(255.f);
	Color2Group.PlaceLabledControl("Head Dot R", this, &crossR);

	crossG.SetFileId("cross_g");
	crossG.SetBoundaries(0.f, 255.f);
	crossG.SetValue(255.f);
	Color2Group.PlaceLabledControl("Head Dot G", this, &crossG);

	crossB.SetFileId("cross_b");
	crossB.SetBoundaries(0.f, 255.f);
	crossB.SetValue(255.f);
	Color2Group.PlaceLabledControl("Head Dot B", this, &crossB);

	FakeChamsR.SetFileId("fkchams_r");
	FakeChamsR.SetBoundaries(0.f, 255.f);
	Color2Group.PlaceLabledControl("Angle Chams R", this, &FakeChamsR);

	FakeChamsG.SetFileId("fkchams_g");
	FakeChamsG.SetBoundaries(0.f, 255.f);
	Color2Group.PlaceLabledControl("Angle Chams G", this, &FakeChamsG);

	FakeChamsB.SetFileId("fkchams_b");
	FakeChamsB.SetBoundaries(0.f, 255.f);
	Color2Group.PlaceLabledControl("Angle Chams B", this, &FakeChamsB);

	GlowR.SetFileId("glow_r");
	GlowR.SetBoundaries(0.f, 255.f);
	Color2Group.PlaceLabledControl("Glow R", this, &GlowR);

	GlowG.SetFileId("glow_g");
	GlowG.SetBoundaries(0.f, 255.f);
	Color2Group.PlaceLabledControl("Glow G", this, &GlowG);

	GlowB.SetFileId("glow_b");
	GlowB.SetBoundaries(0.f, 255.f);
	Color2Group.PlaceLabledControl("Glow B", this, &GlowB);

#pragma endregion
}

void CSkinTab::Setup()
{
	SetTitle("Skins");

	SkinActive.SetPosition(32, 48);
	SkinActive.SetText("Active");
	RegisterControl(&SkinActive);

	SkinEnable.SetFileId("skin_enable");
	SkinEnable.SetPosition(78, 48);
	RegisterControl(&SkinEnable);

	GlovesApply.SetText("Apply");
	GlovesApply.SetCallback(GlovesApplyCallbk);
	GlovesApply.SetPosition(16, 460);//400, 480
	GlovesApply.SetSize(371, 106);
	RegisterControl(&GlovesApply);

	KnifeGroup.SetPosition(16, 48);
	KnifeGroup.SetText("");
	KnifeGroup.SetSize(376, 80);
	RegisterControl(&KnifeGroup);

	KnifeModel.SetFileId("knife_model");
	KnifeModel.AddItem("Bayonet");
	KnifeModel.AddItem("Bowie Knife");
	KnifeModel.AddItem("Butterfly Knife");
	KnifeModel.AddItem("Falchion Knife");
	KnifeModel.AddItem("Flip Knife");
	KnifeModel.AddItem("Gut Knife");
	KnifeModel.AddItem("Huntsman Knife");
	KnifeModel.AddItem("Karambit");
	KnifeModel.AddItem("M9 Bayonet");
	KnifeModel.AddItem("Shadow Daggers");
	KnifeGroup.PlaceLabledControl("Knife", this, &KnifeModel);

	KnifeSkin.SetFileId("knife_skin");
	KnifeSkin.AddItem("Off");
	KnifeSkin.AddItem("Crimson Web");
	KnifeSkin.AddItem("Bone Mask");
	KnifeSkin.AddItem("Fade");
	KnifeSkin.AddItem("Night");
	KnifeSkin.AddItem("Blue Steel");
	KnifeSkin.AddItem("Stained");
	KnifeSkin.AddItem("Case Hardend");
	KnifeSkin.AddItem("Slaughter");
	KnifeSkin.AddItem("Safari Mesh");
	KnifeSkin.AddItem("Boreal Forest");
	KnifeSkin.AddItem("Ultraviolet");
	KnifeSkin.AddItem("Urban Masked");
	KnifeSkin.AddItem("Scorched");
	KnifeSkin.AddItem("Rust Coat");
	KnifeSkin.AddItem("Tiger Tooth");
	KnifeSkin.AddItem("Damascus Steel");
	KnifeSkin.AddItem("Damascus Steel");
	KnifeSkin.AddItem("Marble Fade");
	KnifeSkin.AddItem("Rust Coat");
	KnifeSkin.AddItem("Doppler Ruby");
	KnifeSkin.AddItem("Doppler Sapphire");
	KnifeSkin.AddItem("Lore");
	KnifeGroup.PlaceLabledControl("Knife", this, &KnifeSkin);

	MachinegunsGroup.SetPosition(408, 48);
	MachinegunsGroup.SetText("");
	MachinegunsGroup.SetSize(360, 80);
	RegisterControl(&MachinegunsGroup);

	MachinegunsM249Skin.SetFileId("m249_skin");
	MachinegunsM249Skin.AddItem("Contrast Spray");
	MachinegunsM249Skin.AddItem("Blizzard Marbleized");
	MachinegunsM249Skin.AddItem("Jungle DDPAT");
	MachinegunsM249Skin.AddItem("Gator Mesh");
	MachinegunsM249Skin.AddItem("Magma");
	MachinegunsM249Skin.AddItem("System Lock");
	MachinegunsM249Skin.AddItem("Shipping Forecast");
	MachinegunsM249Skin.AddItem("Impact Drill");
	MachinegunsM249Skin.AddItem("Nebula Crusader");
	MachinegunsM249Skin.AddItem("Spectre");
	MachinegunsM249Skin.AddItem("Emerald Poison Dart");
	MachinegunsGroup.PlaceLabledControl("M249", this, &MachinegunsM249Skin);

	MachinegunsNEGEVSkin.SetFileId("negev_skin");
	MachinegunsNEGEVSkin.AddItem("Anodized Navy");
	MachinegunsNEGEVSkin.AddItem("Man-o'-war");
	MachinegunsNEGEVSkin.AddItem("Palm");
	MachinegunsNEGEVSkin.AddItem("VariCamo");
	MachinegunsNEGEVSkin.AddItem("Palm");
	MachinegunsNEGEVSkin.AddItem("CaliCamo");
	MachinegunsNEGEVSkin.AddItem("Terrain");
	MachinegunsNEGEVSkin.AddItem("Army Sheen");
	MachinegunsNEGEVSkin.AddItem("Bratatat");
	MachinegunsNEGEVSkin.AddItem("Desert-Strike");
	MachinegunsNEGEVSkin.AddItem("Nuclear Waste");
	MachinegunsNEGEVSkin.AddItem("Loudmouth");
	MachinegunsNEGEVSkin.AddItem("Power Loader");
	MachinegunsGroup.PlaceLabledControl("Negev", this, &MachinegunsNEGEVSkin);

	SSG08Skin.SetFileId("sgg08_skin");
	SSG08Skin.AddItem("Lichen Dashed");
	SSG08Skin.AddItem("Dark Water");
	SSG08Skin.AddItem("Blue Spruce");
	SSG08Skin.AddItem("Sand Dune");
	SSG08Skin.AddItem("Palm");
	SSG08Skin.AddItem("Mayan Dreams");
	SSG08Skin.AddItem("Blood in the Water");
	SSG08Skin.AddItem("Tropical Storm");
	SSG08Skin.AddItem("Acid Fade");
	SSG08Skin.AddItem("Slashed");
	SSG08Skin.AddItem("Detour");
	SSG08Skin.AddItem("Abyss");
	SSG08Skin.AddItem("Big Iron");
	SSG08Skin.AddItem("Necropos");
	SSG08Skin.AddItem("Ghost Crusader");
	SSG08Skin.AddItem("Dragonfire");
	SSG08Skin.AddItem("Death's Head");
	KnifeGroup.PlaceLabledControl("SGG 08", this, &SSG08Skin);

	AWPSkin.SetFileId("awp_skin");
	AWPSkin.AddItem("BOOM");
	AWPSkin.AddItem("Dragon Lore");
	AWPSkin.AddItem("Pink DDPAT");
	AWPSkin.AddItem("Snake Camo");
	AWPSkin.AddItem("Lightning Strike");
	AWPSkin.AddItem("Safari Mesh");
	AWPSkin.AddItem("Corticera");
	AWPSkin.AddItem("Redline");
	AWPSkin.AddItem("Man-o'-war");
	AWPSkin.AddItem("Graphite");
	AWPSkin.AddItem("Electric Hive");
	AWPSkin.AddItem("Pit Viper");
	AWPSkin.AddItem("Asiimov");
	AWPSkin.AddItem("Worm God");
	AWPSkin.AddItem("Medusa");
	AWPSkin.AddItem("Sun in Leo");
	AWPSkin.AddItem("Hyper Beast");
	AWPSkin.AddItem("Elite Build");
	AWPSkin.AddItem("Fever Dream");
	AWPSkin.AddItem("Oni Taiji");
	KnifeGroup.PlaceLabledControl("AWP", this, &AWPSkin);

	G3SG1Skin.SetFileId("g3sg1_skin");
	G3SG1Skin.AddItem("Desert Storm");
	G3SG1Skin.AddItem("Arctic Camo");
	G3SG1Skin.AddItem("Bone Mask");
	G3SG1Skin.AddItem("Contractor");
	G3SG1Skin.AddItem("Safari Mesh");
	G3SG1Skin.AddItem("Polar Camo");
	G3SG1Skin.AddItem("Jungle Dashed");
	G3SG1Skin.AddItem("VariCamo");
	G3SG1Skin.AddItem("Predator");
	G3SG1Skin.AddItem("Demeter");
	G3SG1Skin.AddItem("Azure Zebra");
	G3SG1Skin.AddItem("Green Apple");
	G3SG1Skin.AddItem("Orange Kimono");
	G3SG1Skin.AddItem("Neon Kimono");
	G3SG1Skin.AddItem("Murky");
	G3SG1Skin.AddItem("Chronos");
	G3SG1Skin.AddItem("Flux");
	G3SG1Skin.AddItem("The Executioner");
	G3SG1Skin.AddItem("Orange Crash");
	KnifeGroup.PlaceLabledControl("G3SG1", this, &G3SG1Skin);

	SCAR20Skin.SetFileId("scar20_skin");
	SCAR20Skin.AddItem("Splash Jam");
	SCAR20Skin.AddItem("Storm");
	SCAR20Skin.AddItem("Contractor");
	SCAR20Skin.AddItem("Carbon Fiber");
	SCAR20Skin.AddItem("Sand Mesh");
	SCAR20Skin.AddItem("Palm");
	SCAR20Skin.AddItem("Emerald");
	SCAR20Skin.AddItem("Crimson Web");
	SCAR20Skin.AddItem("Cardiac");
	SCAR20Skin.AddItem("Army Sheen");
	SCAR20Skin.AddItem("Cyrex");
	SCAR20Skin.AddItem("Grotto");
	SCAR20Skin.AddItem("Emerald");
	SCAR20Skin.AddItem("Green Marine");
	SCAR20Skin.AddItem("Outbreak");
	SCAR20Skin.AddItem("Bloodsport");
	SCAR20Skin.AddItem("Blueprint");
	KnifeGroup.PlaceLabledControl("SCAR-20", this, &SCAR20Skin);

	GloveModel.SetFileId("glove_model");
	GloveModel.AddItem("Off");
	GloveModel.AddItem("Bloodhound");
	GloveModel.AddItem("Handwrap");
	GloveModel.AddItem("Driver");
	GloveModel.AddItem("Sport");
	GloveModel.AddItem("Motorcycle");
	GloveModel.AddItem("Specialist");
	KnifeGroup.PlaceLabledControl("Glove Model", this, &GloveModel);

	GloveSkin.SetFileId("glove_skin");
	GloveSkin.AddItem("Off");
	GloveSkin.AddItem("Snakebite");
	GloveSkin.AddItem("Charred");
	GloveSkin.AddItem("Guerrilla");
	GloveSkin.AddItem("Bronzed");
	GloveSkin.AddItem("Slaughter");
	GloveSkin.AddItem("Badlands");
	GloveSkin.AddItem("Leather");
	GloveSkin.AddItem("Spruce DDPAT");
	GloveSkin.AddItem("Crimson Weave");
	GloveSkin.AddItem("Lunar Weave");
	GloveSkin.AddItem("Diamondback");
	GloveSkin.AddItem("Convoy");
	GloveSkin.AddItem("Pandoras Box");
	GloveSkin.AddItem("Hedge Naze");
	GloveSkin.AddItem("Superconductor");
	GloveSkin.AddItem("Arid");
	GloveSkin.AddItem("Spearmint");
	GloveSkin.AddItem("Cool Mint");
	GloveSkin.AddItem("Boom");
	GloveSkin.AddItem("Eclipse");
	GloveSkin.AddItem("Crimson Kimono");
	GloveSkin.AddItem("Emerald Web");
	GloveSkin.AddItem("Foundation");
	GloveSkin.AddItem("Forest DDPAT");
	KnifeGroup.PlaceLabledControl("Glove Skin", this, &GloveSkin);

	MachinegunsXM1014Skin.SetFileId("xm1014_skin");
	MachinegunsXM1014Skin.AddItem("Blaze Orange");
	MachinegunsXM1014Skin.AddItem("VariCamo Blue");
	MachinegunsXM1014Skin.AddItem("Bone Mask");
	MachinegunsXM1014Skin.AddItem("Blue Steel");
	MachinegunsXM1014Skin.AddItem("Blue Spruce");
	MachinegunsXM1014Skin.AddItem("Grassland");
	MachinegunsXM1014Skin.AddItem("Urban Perforated");
	MachinegunsXM1014Skin.AddItem("Jungle");
	MachinegunsXM1014Skin.AddItem("VariCamo");
	MachinegunsXM1014Skin.AddItem("VariCamo");
	MachinegunsXM1014Skin.AddItem("Fallout Warning");
	MachinegunsXM1014Skin.AddItem("Jungle");
	MachinegunsXM1014Skin.AddItem("CaliCamo");
	MachinegunsXM1014Skin.AddItem("Pit Viper");
	MachinegunsXM1014Skin.AddItem("Tranquility");
	MachinegunsXM1014Skin.AddItem("Red Python");
	MachinegunsXM1014Skin.AddItem("Heaven Guard");
	MachinegunsXM1014Skin.AddItem("Red Leather");
	MachinegunsXM1014Skin.AddItem("Bone Machine");
	MachinegunsXM1014Skin.AddItem("Quicksilver");
	MachinegunsXM1014Skin.AddItem("Scumbria");
	MachinegunsXM1014Skin.AddItem("Teclu Burner");
	MachinegunsXM1014Skin.AddItem("Black Tie");
	MachinegunsXM1014Skin.AddItem("Seasons");
	MachinegunsGroup.PlaceLabledControl("XM1014", this, &MachinegunsXM1014Skin);

	MachinegunsMAG7Skin.SetFileId("mag7_skin");
	MachinegunsMAG7Skin.AddItem("Counter Terrace");
	MachinegunsMAG7Skin.AddItem("Metallic DDPAT");
	MachinegunsMAG7Skin.AddItem("Silver");
	MachinegunsMAG7Skin.AddItem("Storm");
	MachinegunsMAG7Skin.AddItem("Bulldozer");
	MachinegunsMAG7Skin.AddItem("Heat");
	MachinegunsMAG7Skin.AddItem("Sand Dune");
	MachinegunsMAG7Skin.AddItem("Irradiated Alert");
	MachinegunsMAG7Skin.AddItem("Memento");
	MachinegunsMAG7Skin.AddItem("Hazard");
	MachinegunsMAG7Skin.AddItem("Heaven Guard");
	MachinegunsMAG7Skin.AddItem("Firestarter");
	MachinegunsMAG7Skin.AddItem("Seabird");
	MachinegunsMAG7Skin.AddItem("Cobalt Core");
	MachinegunsMAG7Skin.AddItem("Praetorian");
	MachinegunsMAG7Skin.AddItem("Hard Water");
	MachinegunsGroup.PlaceLabledControl("Mag-7", this, &MachinegunsMAG7Skin);

	MachinegunsSAWEDOFFSkin.SetFileId("sawedoff_skin");
	MachinegunsSAWEDOFFSkin.AddItem("First Class");
	MachinegunsSAWEDOFFSkin.AddItem("Forest DDPAT");
	MachinegunsSAWEDOFFSkin.AddItem("Contrast Spray");
	MachinegunsSAWEDOFFSkin.AddItem("Snake Camo");
	MachinegunsSAWEDOFFSkin.AddItem("Orange DDPAT");
	MachinegunsSAWEDOFFSkin.AddItem("Fade");
	MachinegunsSAWEDOFFSkin.AddItem("Copper");
	MachinegunsSAWEDOFFSkin.AddItem("Origami");
	MachinegunsSAWEDOFFSkin.AddItem("Sage Spray");
	MachinegunsSAWEDOFFSkin.AddItem("VariCamo");
	MachinegunsSAWEDOFFSkin.AddItem("Irradiated Alert");
	MachinegunsSAWEDOFFSkin.AddItem("Mosaico");
	MachinegunsSAWEDOFFSkin.AddItem("Serenity");
	MachinegunsSAWEDOFFSkin.AddItem("Amber Fade");
	MachinegunsSAWEDOFFSkin.AddItem("Full Stop");
	MachinegunsSAWEDOFFSkin.AddItem("Highwayman");
	MachinegunsSAWEDOFFSkin.AddItem("The Kraken");
	MachinegunsSAWEDOFFSkin.AddItem("Rust Coat");
	MachinegunsSAWEDOFFSkin.AddItem("Bamboo Shadow");
	MachinegunsSAWEDOFFSkin.AddItem("Bamboo Forest");
	MachinegunsSAWEDOFFSkin.AddItem("Yorick");
	MachinegunsSAWEDOFFSkin.AddItem("Fubar");
	MachinegunsSAWEDOFFSkin.AddItem("Wasteland Princess");
	MachinegunsSAWEDOFFSkin.AddItem("Zander");
	MachinegunsGroup.PlaceLabledControl("Sawed-Off", this, &MachinegunsSAWEDOFFSkin);

	MachinegunsNOVASkin.SetFileId("nova_skin");
	MachinegunsNOVASkin.AddItem("Candy Apple");
	MachinegunsNOVASkin.AddItem("Blaze Orange");
	MachinegunsNOVASkin.AddItem("Modern Hunter");
	MachinegunsNOVASkin.AddItem("Forest Leaves");
	MachinegunsNOVASkin.AddItem("Bloomstick");
	MachinegunsNOVASkin.AddItem("Sand Dune");
	MachinegunsNOVASkin.AddItem("Polar Mesh");
	MachinegunsNOVASkin.AddItem("Walnut");
	MachinegunsNOVASkin.AddItem("Predator");
	MachinegunsNOVASkin.AddItem("Tempest");
	MachinegunsNOVASkin.AddItem("Graphite");
	MachinegunsNOVASkin.AddItem("Ghost Camo");
	MachinegunsNOVASkin.AddItem("Rising Skull");
	MachinegunsNOVASkin.AddItem("Antique");
	MachinegunsNOVASkin.AddItem("Green Apple");
	MachinegunsNOVASkin.AddItem("Caged Steel");
	MachinegunsNOVASkin.AddItem("Koi");
	MachinegunsNOVASkin.AddItem("Moon in Libra");
	MachinegunsNOVASkin.AddItem("Ranger");
	MachinegunsNOVASkin.AddItem("Hyper Beast");
	MachinegunsGroup.PlaceLabledControl("Nova", this, &MachinegunsNOVASkin);

	AK47Skin.SetFileId("ak47_skin");
	AK47Skin.AddItem("First Class");
	AK47Skin.AddItem("Red Laminate");
	AK47Skin.AddItem("Case Hardened");
	AK47Skin.AddItem("Black Laminate");
	AK47Skin.AddItem("Fire Serpent");
	AK47Skin.AddItem("Cartel");
	AK47Skin.AddItem("Emerald Pinstripe");
	AK47Skin.AddItem("Blue Laminate");
	AK47Skin.AddItem("Redline");
	AK47Skin.AddItem("Vulcan");
	AK47Skin.AddItem("Jaguar");
	AK47Skin.AddItem("Jet Set");
	AK47Skin.AddItem("Wasteland Rebel");
	AK47Skin.AddItem("Elite Build");
	AK47Skin.AddItem("Hydroponic");
	AK47Skin.AddItem("Aquamarine Revenge");
	AK47Skin.AddItem("Frontside Misty");
	AK47Skin.AddItem("Point Disarray");
	AK47Skin.AddItem("Fuel Injector");
	AK47Skin.AddItem("Neon Revolution");
	AK47Skin.AddItem("BloodSport");
	AK47Skin.AddItem("Orbit Mk01");
	KnifeGroup.PlaceLabledControl("AK-47", this, &AK47Skin);

	M41SSkin.SetFileId("m4a1s_skin");
	M41SSkin.AddItem("Dark Water");
	M41SSkin.AddItem("Hyper Beast");
	M41SSkin.AddItem("Boreal Forest");
	M41SSkin.AddItem("VariCamo");
	M41SSkin.AddItem("Nitro");
	M41SSkin.AddItem("Bright Water");
	M41SSkin.AddItem("Atomic Alloy");
	M41SSkin.AddItem("Blood Tiger");
	M41SSkin.AddItem("Guardian");
	M41SSkin.AddItem("Master Piece");
	M41SSkin.AddItem("Knight");
	M41SSkin.AddItem("Cyrex");
	M41SSkin.AddItem("Basilisk");
	M41SSkin.AddItem("Icarus Fell");
	M41SSkin.AddItem("Hot Rod");
	M41SSkin.AddItem("Golden Coi");
	M41SSkin.AddItem("Chantico's Fire");
	M41SSkin.AddItem("Mecha Industries");
	M41SSkin.AddItem("Flashback");
	M41SSkin.AddItem("Decimator");
	M41SSkin.AddItem("Briefing");
	KnifeGroup.PlaceLabledControl("M4A1-S", this, &M41SSkin);

	M4A4Skin.SetFileId("m4a4_skin");
	M4A4Skin.AddItem("Bullet Rain");
	M4A4Skin.AddItem("Zirka");
	M4A4Skin.AddItem("Asiimov");
	M4A4Skin.AddItem("Howl");
	M4A4Skin.AddItem("X-Ray");
	M4A4Skin.AddItem("Desert-Strike");
	M4A4Skin.AddItem("Griffin");
	M4A4Skin.AddItem("Dragon King");
	M4A4Skin.AddItem("Poseidon");
	M4A4Skin.AddItem("Daybreak");
	M4A4Skin.AddItem("Evil Daimyo");
	M4A4Skin.AddItem("Royal Paladin");
	M4A4Skin.AddItem("The BattleStar");
	M4A4Skin.AddItem("Desolate Space");
	M4A4Skin.AddItem("Buzz Kill");
	M4A4Skin.AddItem("Hell Fire");
	KnifeGroup.PlaceLabledControl("M4A4", this, &M4A4Skin);

	AUGSkin.SetFileId("aug_skin");
	AUGSkin.AddItem("Bengal Tiger");
	AUGSkin.AddItem("Hot Rod");
	AUGSkin.AddItem("Chameleon");
	AUGSkin.AddItem("Torque");
	AUGSkin.AddItem("Radiation Hazard");
	AUGSkin.AddItem("Asterion");
	AUGSkin.AddItem("Daedalus");
	AUGSkin.AddItem("Akihabara Accept");
	AUGSkin.AddItem("Ricochet");
	AUGSkin.AddItem("Fleet Flock");
	AUGSkin.AddItem("Syd Mead");
	KnifeGroup.PlaceLabledControl("AUG", this, &AUGSkin);

	GALILSkin.SetFileId("galil_skin");
	GALILSkin.AddItem("Forest DDPAT");
	GALILSkin.AddItem("Contrast Spray");
	GALILSkin.AddItem("Orange DDPAT");
	GALILSkin.AddItem("Eco");
	GALILSkin.AddItem("Winter Forest");
	GALILSkin.AddItem("Sage Spray");
	GALILSkin.AddItem("VariCamo");
	GALILSkin.AddItem("VariCamo");
	GALILSkin.AddItem("Chatterbox");
	GALILSkin.AddItem("Shattered");
	GALILSkin.AddItem("Kami");
	GALILSkin.AddItem("Blue Titanium");
	GALILSkin.AddItem("Urban Rubble");
	GALILSkin.AddItem("Hunting Blind");
	GALILSkin.AddItem("Sandstorm");
	GALILSkin.AddItem("Tuxedo");
	GALILSkin.AddItem("Cerberus");
	GALILSkin.AddItem("Aqua Terrace");
	GALILSkin.AddItem("Rocket Pop");
	GALILSkin.AddItem("Stone Cold");
	GALILSkin.AddItem("Firefight");
	GALILSkin.AddItem("Crimson Tsunami");
	GALILSkin.AddItem("Suger Rush");
	KnifeGroup.PlaceLabledControl("GALIL", this, &GALILSkin);

	FAMASSkin.SetFileId("famas_skin");
	FAMASSkin.AddItem("Contrast Spray");
	FAMASSkin.AddItem("Colony");
	FAMASSkin.AddItem("Cyanospatter");
	FAMASSkin.AddItem("Djinn");
	FAMASSkin.AddItem("Afterimage");
	FAMASSkin.AddItem("Doomkitty");
	FAMASSkin.AddItem("Spitfire");
	FAMASSkin.AddItem("Teardown");
	FAMASSkin.AddItem("Hexane");
	FAMASSkin.AddItem("Pulse");
	FAMASSkin.AddItem("Sergeant");
	FAMASSkin.AddItem("Styx");
	FAMASSkin.AddItem("Neural Net");
	FAMASSkin.AddItem("Survivor");
	FAMASSkin.AddItem("Valence");
	FAMASSkin.AddItem("Roll Cage");
	FAMASSkin.AddItem("Mecha Industries");
	FAMASSkin.AddItem("Macabre");
	KnifeGroup.PlaceLabledControl("FAMAS", this, &FAMASSkin);

	SG553Skin.SetFileId("sg552_skin");
	SG553Skin.AddItem("Bulldozer");
	SG553Skin.AddItem("Ultraviolet");
	SG553Skin.AddItem("Damascus Steel");
	SG553Skin.AddItem("Fallout Warning");
	SG553Skin.AddItem("Damascus Steel");
	SG553Skin.AddItem("Pulse");
	SG553Skin.AddItem("Army Sheen");
	SG553Skin.AddItem("Traveler");
	SG553Skin.AddItem("Fallout Warning");
	SG553Skin.AddItem("Cyrex");
	SG553Skin.AddItem("Tiger Moth");
	SG553Skin.AddItem("Atlas");
	KnifeGroup.PlaceLabledControl("SG552", this, &SG553Skin);

	GLOCKSkin.SetFileId("glock_skin");
	GLOCKSkin.AddItem("Groundwater");
	GLOCKSkin.AddItem("Candy Apple");
	GLOCKSkin.AddItem("Fade");
	GLOCKSkin.AddItem("Night");
	GLOCKSkin.AddItem("Dragon Tattoo");
	GLOCKSkin.AddItem("Twilight Galaxy");
	GLOCKSkin.AddItem("Sand Dune");
	GLOCKSkin.AddItem("Brass");
	GLOCKSkin.AddItem("Sand Dune");
	GLOCKSkin.AddItem("Steel Disruption");
	GLOCKSkin.AddItem("Blue Fissure");
	GLOCKSkin.AddItem("Water Elemental");
	GLOCKSkin.AddItem("Reactor");
	GLOCKSkin.AddItem("Grinder");
	GLOCKSkin.AddItem("Bunsen Burner");
	GLOCKSkin.AddItem("Wraith");
	GLOCKSkin.AddItem("Royal Legion");
	GLOCKSkin.AddItem("Weasel");
	GLOCKSkin.AddItem("Wasteland Rebel");
	MachinegunsGroup.PlaceLabledControl("Glock", this, &GLOCKSkin);

	USPSSkin.SetFileId("usps_skin");
	USPSSkin.AddItem("Forest Leaves");
	USPSSkin.AddItem("Dark Water");
	USPSSkin.AddItem("VariCamo");
	USPSSkin.AddItem("Overgrowth");
	USPSSkin.AddItem("Caiman");
	USPSSkin.AddItem("Blood Tiger");
	USPSSkin.AddItem("Serum");
	USPSSkin.AddItem("Night Ops");
	USPSSkin.AddItem("Stainless");
	USPSSkin.AddItem("Guardian");
	USPSSkin.AddItem("Orion");
	USPSSkin.AddItem("Road Rash");
	USPSSkin.AddItem("Royal Blue");
	USPSSkin.AddItem("Business Class");
	USPSSkin.AddItem("Para Green");
	USPSSkin.AddItem("Torque");
	USPSSkin.AddItem("Kill Confirmed");
	USPSSkin.AddItem("Lead Conduit");
	USPSSkin.AddItem("Cyrex");
	USPSSkin.AddItem("Neo-Noir");
	USPSSkin.AddItem("Blueprint");
	MachinegunsGroup.PlaceLabledControl("USP-S", this, &USPSSkin);

	DEAGLESkin.SetFileId("deagle_skin");
	DEAGLESkin.AddItem("Blaze");
	DEAGLESkin.AddItem("Pilot");
	DEAGLESkin.AddItem("Midnight Storm");
	DEAGLESkin.AddItem("Sunset Storm");
	DEAGLESkin.AddItem("Crimson Web");
	DEAGLESkin.AddItem("Night");
	DEAGLESkin.AddItem("Hypnotic");
	DEAGLESkin.AddItem("Mudder");
	DEAGLESkin.AddItem("Golden Koi");
	DEAGLESkin.AddItem("Cobalt Disruption");
	DEAGLESkin.AddItem("Urban Rubble");
	DEAGLESkin.AddItem("Naga");
	DEAGLESkin.AddItem("Hand Cannon");
	DEAGLESkin.AddItem("Heirloom");
	DEAGLESkin.AddItem("Meteorite");
	DEAGLESkin.AddItem("Conspiracy");
	DEAGLESkin.AddItem("Bronze Deco");
	DEAGLESkin.AddItem("Sunset Storm");
	DEAGLESkin.AddItem("Corinthian");
	DEAGLESkin.AddItem("Kumicho Dragon");
	DEAGLESkin.AddItem("Oxide Blaze");
	MachinegunsGroup.PlaceLabledControl("Deagle", this, &DEAGLESkin);

	DUALSSkin.SetFileId("duals_skin");
	DUALSSkin.AddItem("Anodized Navy");
	DUALSSkin.AddItem("Stained");
	DUALSSkin.AddItem("Contractor");
	DUALSSkin.AddItem("Colony");
	DUALSSkin.AddItem("Demolition");
	DUALSSkin.AddItem("Black Limba");
	DUALSSkin.AddItem("Cobalt Quartz");
	DUALSSkin.AddItem("Hemoglobin");
	DUALSSkin.AddItem("Urban Shock");
	DUALSSkin.AddItem("Marina");
	DUALSSkin.AddItem("Panther");
	DUALSSkin.AddItem("Retribution");
	DUALSSkin.AddItem("Briar");
	DUALSSkin.AddItem("Duelist");
	DUALSSkin.AddItem("Moon in Libra");
	DUALSSkin.AddItem("Dualing Dragons");
	DUALSSkin.AddItem("Cartel");
	DUALSSkin.AddItem("Ventilators");
	DUALSSkin.AddItem("Cobra Strike");
	MachinegunsGroup.PlaceLabledControl("Duals", this, &DUALSSkin);

	FIVESEVENSkin.SetFileId("fiveseven_skin");
	FIVESEVENSkin.AddItem("Case Hardened");
	FIVESEVENSkin.AddItem("Contractor");
	FIVESEVENSkin.AddItem("Jungle");
	FIVESEVENSkin.AddItem("Nitro");
	FIVESEVENSkin.AddItem("Red Quartz");
	FIVESEVENSkin.AddItem("Nightshade");
	FIVESEVENSkin.AddItem("Silver Quartz");
	FIVESEVENSkin.AddItem("Kami");
	FIVESEVENSkin.AddItem("Copper Galaxy");
	FIVESEVENSkin.AddItem("Neon Kimono");
	FIVESEVENSkin.AddItem("Fowl Play");
	FIVESEVENSkin.AddItem("Hot Shot");
	FIVESEVENSkin.AddItem("Urban Hazard");
	FIVESEVENSkin.AddItem("Monkey Business");
	FIVESEVENSkin.AddItem("Retrobution");
	FIVESEVENSkin.AddItem("Triumvirate");
	FIVESEVENSkin.AddItem("Capillary");
	FIVESEVENSkin.AddItem("Hyper Beast");
	MachinegunsGroup.PlaceLabledControl("Five-Seven", this, &FIVESEVENSkin);

	TECNINESkin.SetFileId("tec9_skin");
	TECNINESkin.AddItem("Terrace");
	TECNINESkin.AddItem("Urban DDPAT");
	TECNINESkin.AddItem("Ossified");
	TECNINESkin.AddItem("Hades");
	TECNINESkin.AddItem("VariCamo");
	TECNINESkin.AddItem("Nuclear Threat");
	TECNINESkin.AddItem("Red Quartz");
	TECNINESkin.AddItem("Tornado");
	TECNINESkin.AddItem("Isaac");
	TECNINESkin.AddItem("Toxic");
	TECNINESkin.AddItem("Bamboo Forest");
	TECNINESkin.AddItem("Avalanche");
	TECNINESkin.AddItem("Jambiya");
	TECNINESkin.AddItem("Re-Entry");
	TECNINESkin.AddItem("Fuel Injector");
	TECNINESkin.AddItem("Cut Out");
	MachinegunsGroup.PlaceLabledControl("Tec-9", this, &TECNINESkin);

	P2000Skin.SetFileId("p2000_skin");
	P2000Skin.AddItem("Grassland Leaves");
	P2000Skin.AddItem("Silver");
	P2000Skin.AddItem("Granite Marbleized");
	P2000Skin.AddItem("Forest Leaves");
	P2000Skin.AddItem("Ossified");
	P2000Skin.AddItem("Handgun");
	P2000Skin.AddItem("Fade");
	P2000Skin.AddItem("Scorpion");
	P2000Skin.AddItem("Grassland");
	P2000Skin.AddItem("Corticera");
	P2000Skin.AddItem("Ocean Foam");
	P2000Skin.AddItem("Pulse");
	P2000Skin.AddItem("Amber Fade");
	P2000Skin.AddItem("Red FragCam");
	P2000Skin.AddItem("Chainmail");
	P2000Skin.AddItem("Coach Class");
	P2000Skin.AddItem("Ivory");
	P2000Skin.AddItem("Fire Elemental");
	P2000Skin.AddItem("Asterion");
	P2000Skin.AddItem("Pathfinder");
	P2000Skin.AddItem("Imperial");
	P2000Skin.AddItem("Oceanic");
	P2000Skin.AddItem("Imperial Dragon");
	P2000Skin.AddItem("Woodsman");
	MachinegunsGroup.PlaceLabledControl("P2000", this, &P2000Skin);

	P250Skin.SetFileId("p250_skin");
	P250Skin.AddItem("Whiteout");
	P250Skin.AddItem("Metallic DDPAT");
	P250Skin.AddItem("Splash");
	P250Skin.AddItem("Gunsmoke");
	P250Skin.AddItem("Modern Hunter");
	P250Skin.AddItem("Bone Mask");
	P250Skin.AddItem("Boreal Forest");
	P250Skin.AddItem("Sand Dune");
	P250Skin.AddItem("Nuclear Threat");
	P250Skin.AddItem("Mehndi");
	P250Skin.AddItem("Facets");
	P250Skin.AddItem("Hive");
	P250Skin.AddItem("Muertos");
	P250Skin.AddItem("Steel Disruption");
	P250Skin.AddItem("Undertow");
	P250Skin.AddItem("Franklin");
	P250Skin.AddItem("Neon Kimono");
	P250Skin.AddItem("Supernova");
	P250Skin.AddItem("Contamination");
	P250Skin.AddItem("Cartel");
	P250Skin.AddItem("Valence");
	P250Skin.AddItem("Crimson Kimono");
	P250Skin.AddItem("Mint Kimono");
	P250Skin.AddItem("Wing Shot");
	P250Skin.AddItem("Asiimov");
	P250Skin.AddItem("Ripple");
	P250Skin.AddItem("Red Rock");
	MachinegunsGroup.PlaceLabledControl("P250", this, &P250Skin);

	CZSkin.SetFileId("cz_skin");
	CZSkin.AddItem("Victoria");
	CZSkin.AddItem("Crimson Web");
	CZSkin.AddItem("Yellow Jacket");
	CZSkin.AddItem("Fuschia");
	CZSkin.AddItem("Xiangliu");
	CZSkin.AddItem("Pole Position");
	CZSkin.AddItem("Tigris");
	CZSkin.AddItem("Red Astor");
	CZSkin.AddItem("Tread Plate");
	CZSkin.AddItem("Chalice");
	CZSkin.AddItem("Imprint");
	CZSkin.AddItem("Twist");
	CZSkin.AddItem("Polymer");
	CZSkin.AddItem("Hexane");
	CZSkin.AddItem("Tuxedo");
	CZSkin.AddItem("Nitro");
	CZSkin.AddItem("Emerald");
	CZSkin.AddItem("Poison Dart");
	MachinegunsGroup.PlaceLabledControl("CZ75", this, &CZSkin);
}

/*void CPlayersTab::Setup()
{
SetTitle("e");

#pragma region PList

pListGroup.SetPosition(16, 16);
pListGroup.SetSize(680, 200);
pListGroup.SetText("Player List");
pListGroup.SetColumns(2);
RegisterControl(&pListGroup);

pListPlayers.SetPosition(26, 46);
pListPlayers.SetSize(640, 50);
pListPlayers.SetHeightInItems(20);
RegisterControl(&pListPlayers);

#pragma endregion

#pragma region Options

OptionsGroup.SetPosition(16, 257);
OptionsGroup.SetSize(450, 120);
OptionsGroup.SetText("Player Options");
RegisterControl(&OptionsGroup);

OptionsFriendly.SetFileId("pl_friendly");
OptionsGroup.PlaceLabledControl("Friendly", this, &OptionsFriendly);

OptionsAimPrio.SetFileId("pl_priority");
OptionsGroup.PlaceLabledControl("Priority", this, &OptionsAimPrio);

OptionsCalloutSpam.SetFileId("pl_callout");
OptionsGroup.PlaceLabledControl("Callout Spam", this, &OptionsCalloutSpam);

#pragma endregion
}

DWORD GetPlayerListIndex(int EntId)
{
player_info_t pinfo;
interfaces::engine->GetPlayerInfo(EntId, &pinfo);

// Bot
if (pinfo.guid[0] == 'B' && pinfo.guid[1] == 'O')
{
char buf[64]; sprintf_s(buf, "BOT_420%sAY", pinfo.name);
return CRC32(buf, 64);
}
else
{
return CRC32(pinfo.guid, 32);
}
}

bool IsFriendly(int EntId)
{
DWORD plistId = GetPlayerListIndex(EntId);
if (PlayerList.find(plistId) != PlayerList.end())
{
return PlayerList[plistId].Friendly;
}

return false;
}

bool IsAimPrio(int EntId)
{
DWORD plistId = GetPlayerListIndex(EntId);
if (PlayerList.find(plistId) != PlayerList.end())
{
return PlayerList[plistId].AimPrio;
}

return false;
}

bool IsCalloutTarget(int EntId)
{
DWORD plistId = GetPlayerListIndex(EntId);
if (PlayerList.find(plistId) != PlayerList.end())
{
return PlayerList[plistId].Callout;
}

return false;
}

void UpdatePlayerList()
{
IClientEntity* localplayer = interfaces::g_entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
if (interfaces::engine->IsConnected() && interfaces::engine->IsInGame() && localplayer && localplayer->IsAlive())
{
g_menu.Playerlist.pListPlayers.ClearItems();

// Loop through all active entitys
for (int i = 0; i < interfaces::g_entitylist->GetHighestEntityIndex(); i++)
{
// Get the entity

player_info_t pinfo;
if (i != interfaces::engine->GetLocalPlayer() && interfaces::engine->GetPlayerInfo(i, &pinfo))
{
IClientEntity* m_entity = interfaces::g_entitylist->GetClientEntity(i);
int HP = 100; char* Location = "Unknown";
char *Friendly = " ", *AimPrio = " ";

DWORD plistId = GetPlayerListIndex(g_menu.Playerlist.pListPlayers.getvalue());
if (PlayerList.find(plistId) != PlayerList.end())
{
Friendly = PlayerList[plistId].Friendly ? "Friendly" : "";
AimPrio = PlayerList[plistId].AimPrio ? "AimPrio" : "";
}

if (m_entity && !m_entity->IsDormant())
{
HP = m_entity->GetHealth();
Location = m_entity->GetLastPlaceName();
}

char nameBuffer[512];
sprintf_s(nameBuffer, "%-24s %-10s %-10s [%d HP] [Last Seen At %s]", pinfo.name, IsFriendly(i) ? "Friend" : " ", IsAimPrio(i) ? "AimPrio" : " ", HP, Location);
g_menu.Playerlist.pListPlayers.AddItem(nameBuffer, i);

}

}

DWORD meme = GetPlayerListIndex(g_menu.Playerlist.pListPlayers.getvalue());

// Have we switched to a different player?
static int //PrevSelectedPlayer = 0;
if (PrevSelectedPlayer != g_menu.Playerlist.pListPlayers.getvalue())
{
if (PlayerList.find(meme) != PlayerList.end())
{
g_menu.Playerlist.OptionsFriendly.SetState(PlayerList[meme].Friendly);
g_menu.Playerlist.OptionsAimPrio.SetState(PlayerList[meme].AimPrio);
g_menu.Playerlist.OptionsCalloutSpam.SetState(PlayerList[meme].Callout);

}
else
{
g_menu.Playerlist.OptionsFriendly.SetState(false);
g_menu.Playerlist.OptionsAimPrio.SetState(false);
g_menu.Playerlist.OptionsCalloutSpam.SetState(false);

}
}
PrevSelectedPlayer = g_menu.Playerlist.pListPlayers.getvalue();

//PlayerList[meme].Friendly = g_menu.Playerlist.OptionsFriendly.getstate();
//PlayerList[meme].AimPrio = g_menu.Playerlist.OptionsAimPrio.getstate();
//PlayerList[meme].Callout = g_menu.Playerlist.OptionsCalloutSpam.getstate();
}
}*/

void SetupMenu()
{
	g_menu.Setup();

	GUI.RegisterWindow(&g_menu);
	GUI.BindWindow(VK_INSERT, &g_menu);
}

void DoUIFrame()
{
	// General Processing

	// If the "all filter is selected tick all the others
	if (g_menu.esp.FiltersAll.getstate())
	{
		g_menu.esp.FiltersC4.SetState(true);
		g_menu.esp.FiltersChickens.SetState(true);
		g_menu.esp.FiltersPlayers.SetState(true);
		g_menu.esp.FiltersWeapons.SetState(true);
	}

	GUI.Update();
	GUI.Draw();


}


/*TextMenu::TextMenu()
{
Enabled = true;
SelectedOption = 0;
MenuItems =

{ L"Resolver", &g_menu.rage.AccuracyResolverenable.getstate, 0 },
{ L"Box", &g_menu.esp.OptionsBox.getindex, 1 },
{ L"Bhop", &g_menu.misc.OtherAutoJump.getstate, 2 }
};

void TextMenu::OnPaintTraverse()
{
if (!Enabled) return;
HandleInput();
int i = 0;
for (int q = 0; q < MenuItems.size(); q++) DrawBool(20, 20 + (i++ * 13), MenuItems[q].name, *MenuItems[q].container, MenuItems[q].number, SelectedOption);
}
DWORD Testhhh;
void TextMenu::DrawBool(int x, int y, const wchar_t* name, bool container, int number, int selected_number)
{
interfaces::Surface->DrawSetTextFont(Testhhh);
interfaces::Surface->DrawSetTextColor(number == selected_number ? Color(255, 215, 0) : Color(255, 255, 255));
interfaces::Surface->DrawSetTextPos(x, y);
interfaces::Surface->DrawPrintText(name, wcslen(name));
interfaces::Surface->DrawSetTextColor(container ? Color(0, 255, 0) : Color(255, 0, 0));
interfaces::Surface->DrawSetTextPos(x + 120, y);
interfaces::Surface->DrawPrintText(container ? L"true" : L"false", container ? wcslen(L"true") : wcslen(L"false"));
}

void TextMenu::HandleInput() //ugly code warning
{
if (GetAsyncKeyState(VK_UP)) SelectedOption--;
else if (GetAsyncKeyState(VK_DOWN)) SelectedOption++;

if (SelectedOption < 0) SelectedOption = MenuItems.size() - 1; 	   //bit ghetto
else if (SelectedOption > MenuItems.size() - 1) SelectedOption = 0;//bit ghetto

if (GetAsyncKeyState(VK_LEFT)) *MenuItems[SelectedOption].container = false;
else if (GetAsyncKeyState(VK_RIGHT)) *MenuItems[SelectedOption].container = true;
}
void TextMenu::Toggle() { Enabled = !Enabled; }
bool TextMenu::IsVisible() { return Enabled; }*/