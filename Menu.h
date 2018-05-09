/*

*/

#pragma once

#include "GUI.h"
#include "Controls.h"

class Crage : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CSlider	  AimbotFov;
	CCheckBox AimbotSilentAim;
	CCheckBox AimbotPerfectSilentAim;
	CCheckBox AimbotAutoPistol;
	CCheckBox AimbotAutoRevolver;
	CCheckBox AimbotAimStep;
	CKeyBind SomeShit;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CKeyBind  AimbotStopKey;
	CCheckBox PitchCorrection;
	CKeyBind  AimbotBaimKey;
	CSlider   AimbotMultiPointIndexes;
	CCheckBox AimbotAwpAtBody;
	CCheckBox PreferBodyAim;


	CComboBox TargetSelection;
	CCheckBox TargetFriendlyFire;
	CComboBox TargetHitbox;
	CSliderValue TargetBaimHealth;
	CCheckBox TargetHitscan;
	CCheckBox TargetMultipoint;
	CSliderValue TargetSmartScan;
	CSlider   TargetPointscale;
	CSliderValue TargetSmart;

	// Target Selection Settings
	CGroupBox TargetGroup;
	/*CComboBox TargetSelection;
	CCheckBox TargetFriendlyFire;
	CComboBox TargetHitbox;
	CSlider TargetBaimHealth;
	CComboBox TargetHitscan;
	CCheckBox TargetMultipoint;
	CSlider   TargetSmartScan;
	CSlider   TargetPointscale;
	CSlider	  TargetSmart;*/

	// Accuracy Settings
	CGroupBox AccuracyGroup;
	CCheckBox AccuracyRecoil;
	CCheckBox AccuracyAutoWall;
	CSlider	  AccuracyMinimumDamage;
	CCheckBox Accuracylagcomp;
	CCheckBox AutoMinimumDamage;
	CCheckBox AccuracyAutoStop;
	CCheckBox OtherFreestanding;
	CComboBox AccuracyMovement;
	CCheckBox OtherGhettoEdge;
	CCheckBox AccuracyAutoCrouch;
	CCheckBox AccuracyAutoScope;
	CCheckBox TargetSecondaryHitbox;
	CCheckBox AutoHitChance;
	CComboBox AccuracyResolverYaw;
	CComboBox AccuracyResolverenable; //resolver from resolver.cpp kinda shit
	CCheckBox AccuracyResolverenable2; //secondary resolver from pAyyware idk might be good
	CCheckBox AccuracyResolver2; //test from UC thread super lby
	CCheckBox AccuracyResolverPitch;
	CCheckBox AccuracyResolverBeta3;
	CComboBox AccuracyResolver;
	CSlider AccuracyBruteforceAfterX;
	CCheckBox AccuracyBacktracking;
	CComboBox AccuracyDrop;
	CSlider   AccuracyHitchanceVal;
	CCheckBox AccuracyPositionAdjustment;
	CCheckBox AccuracyPrediction;
	CCheckBox AimbotBacktrack;
	CSlider   AimbotTickModulation;

	//Anti Aim Basics
	CLabel AntiAimActiveLabel;
	CCheckBox AntiAimActive;

	// Anti-Aim Settings
	CGroupBox AntiAimGroup;
	CCheckBox AntiAimEnable;
	CComboBox AntiAimPitch;
	CComboBox staticyaw;
	CComboBox movingyaw;
	CComboBox fakeyaw;
	CComboBox edgeyaw;
	CCheckBox AntiAimEdge;
	CSlider	  AntiAimOffset;
	CCheckBox AntiAimResolver2;
	CCheckBox FakeLagFix;
	CKeyBind AimbotResolverOverride;
	CCheckBox AccuracyResolverBeta2;
	CCheckBox AccuracyResolverBeta;
	CSlider fakeyawcustom;
	CCheckBox DynamicMultipoint;
	CSlider staticyawcustom;
	CSlider	  SpinSpeed;
	CSlider	  SpinSpeed2;
	CSlider	  AntiAimOffsetReal;
	CSlider	  AntiAimOffsetFake;
	CCheckBox AntiAimKnife;
	CCheckBox AntiAimTarget;
	CCheckBox AntiAimJitterLBY;
	CSlider	  AntiAimSpinspeed;
	CComboBox AntiAimAntiResolver;
	CSlider	  AddFakeYaw;
	CKeyBind  AntiAimFlipKey;
	CComboBox AntiAimEdge2;
	CSlider AntiAimBreakLBY;
	CComboBox FakeAngleChams;
};

class Clegit : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;

	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotFriendlyFire;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CCheckBox AimbotAutoPistol;
	CCheckBox AimbotSmokeCheck;
	CSlider   TickModulation;
	CCheckBox AimbotBacktrack;

	CGroupBox TriggerGroup;
	CCheckBox TriggerEnable;
	CCheckBox TriggerKeyPress;
	CKeyBind  TriggerKeyBind;
	CCheckBox TriggerHitChance;
	CSlider   TriggerHitChanceAmmount;
	CSlider   TriggerDelay;
	CSlider   TriggerBurst;
	CSlider   TriggerBreak;
	CCheckBox TriggerRecoil;

	CGroupBox TriggerFilterGroup;
	CCheckBox TriggerHead;
	CCheckBox TriggerChest;
	CCheckBox TriggerStomach;
	CCheckBox TriggerArms;
	CCheckBox TriggerLegs;
	CCheckBox TriggerTeammates;
	CCheckBox TriggerFlashCheck;
	CCheckBox TriggerSmokeCheck;

	CGroupBox WeaponMainGroup;
	CSlider   WeaponMainSpeed;
	CSlider   WeaponMainFoV;
	CCheckBox WeaponMainRecoil;
	CComboBox WeaponMainHitbox;
	CSlider WeaponMainAimtime;
	CSlider WeaoponMainStartAimtime;
	CCheckBox WeaponMainPsilent;
	CSlider   WeaponMainInacc;

	CGroupBox WeaponPistGroup;
	CSlider   WeaponPistSpeed;
	CSlider   WeaponPistFoV;
	CCheckBox WeaponPistRecoil;
	CComboBox WeaponPistHitbox;
	CSlider WeaponPistAimtime;
	CSlider WeaoponPistStartAimtime;
	CCheckBox WeaponPistPSilent;
	CSlider   WeaponPistInacc;

	CGroupBox WeaponSnipGroup;
	CSlider   WeaponSnipSpeed;
	CSlider   WeaponSnipFoV;
	CCheckBox WeaponSnipRecoil;
	CComboBox WeaponSnipHitbox;
	CSlider WeaponSnipAimtime;
	CSlider WeaoponSnipStartAimtime;
	CCheckBox WeaponSnipPSilent;
	CSlider   WeaponSnipInacc;

	CGroupBox WeaponMpGroup;
	CSlider   WeaponMpSpeed;
	CSlider   WeaponMpFoV;
	CCheckBox WeaponMpRecoil;
	CComboBox WeaponMpHitbox;
	CSlider WeaponMpAimtime;
	CSlider WeaoponMpStartAimtime;
	CCheckBox WeaponMpPsilent;
	CSlider   WeaponMpInacc;

	CGroupBox WeaponShotgunGroup;
	CSlider   WeaponShotgunSpeed;
	CSlider   WeaponShotgunFoV;
	CCheckBox WeaponShotgunRecoil;
	CComboBox WeaponShotgunHitbox;
	CSlider WeaponShotgunAimtime;
	CSlider WeaoponShotgunStartAimtime;
	CCheckBox WeaponShotgunPsilent;
	CSlider   WeaponShotgunInacc;

	CGroupBox WeaponMGGroup;
	CSlider   WeaponMGSpeed;
	CSlider   WeaponMGFoV;
	CCheckBox WeaponMGRecoil;
	CComboBox WeaponMGHitbox;
	CSlider WeaponMGAimtime;
	CSlider WeaoponMGStartAimtime;
	CCheckBox WeaponMGPsilent;
	CSlider   WeaponMGInacc;

	CGroupBox Other;
	CCheckBox LegitAA;
};

class Cesp : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Options Settings
	CGroupBox OptionsGroup;
	CComboBox OptionsBox;
	CCheckBox OptionsFillBox;
	CCheckBox OptionsName;
	CComboBox OptionsVitals;
	CCheckBox OptionsWeapon;
	CCheckBox OptionsWeapon2;
	CCheckBox OptionsInfo;
	CCheckBox SniperCrosshair;
	CCheckBox OptionsHelmet;
	CCheckBox OtherSniperCrosshair;
	CCheckBox OptionsChams1;
	CCheckBox OtherBulletBeam;
	CCheckBox OtherSpreadCrosshair;
	CKeyBind OtherFreecam;
	CCheckBox OtherFakeCheck;
	CCheckBox OptionsKit;
	CSlider OtherSpreadCrosshairValue;
	CCheckBox OptionsDefuse;
	CCheckBox OptionsGlow;
	CComboBox OptionsChams;
	CCheckBox OptionsRankESP;
	CComboBox OtherChams;
	CComboBox OptionsChams2;
	CComboBox OptionsNoHands;
	CCheckBox OptionsSkeleton;
	CCheckBox NightMode;
	CCheckBox HandXQZ;
	CCheckBox EntityGlow;
	CCheckBox OptionsAimSpot;
	CCheckBox OptionsChamsXQZ;
	CCheckBox GrenadeTracer;
	CComboBox OtherNoHands;
	CCheckBox OptionsArmor;
	CCheckBox LocalChams;
	CComboBox OptionsPlayerESP;
	CCheckBox OtherVelocityESP;
	CCheckBox OtherAsusProps;
	CCheckBox ShowImpacts;
	CCheckBox IsScoped;
	CCheckBox HasDefuser;
	CCheckBox IsDefusing;
	CCheckBox BacktrackingLol;
	CCheckBox OptionsLBY;
	CCheckBox OtherGlow2;
	CCheckBox OtherGlow;
	CCheckBox Grenades;
	CSlider   BulletTraceLength;

	// Filters Settings
	CGroupBox FiltersGroup;
	CCheckBox FiltersAll;
	CCheckBox FiltersPlayers;
	CCheckBox FiltersEnemiesOnly;
	CCheckBox FilterSelf;
	CCheckBox FiltersWeapons;
	CCheckBox FiltersChickens;
	CCheckBox FiltersC4;

	// Other Settings
	CGroupBox OtherGroup;
	CCheckBox OtherCrosshair;
	CCheckBox OtherRecoilCrosshair;
	CCheckBox OtherLSDMode;
	CComboBox StaticProps;
	CCheckBox OtherBulletTracer2;
	CCheckBox OtherChromeMode;
	CCheckBox OptionsRadar;
	CCheckBox OptionsHeadIndicator;
	CCheckBox OtherNoVisualRecoil;
	CCheckBox OtherPlayerScopedOpacity;
	CCheckBox OtherNoSky;
	CCheckBox OtherNoFlash;
	CCheckBox OtherDamageIndicators;
	CSlider OtherNoFlash2;
	CCheckBox OtherPlayerLine;
	CCheckBox OtherShowLBY;
	CCheckBox OtherEnemyCircle;
	CCheckBox OtherNoSmoke;
	CCheckBox DLight;
	CComboBox OtherFoVCrosshair;
	CCheckBox OtherAsusWalls;
	CCheckBox OtherAutowallCrosshair;
	CCheckBox OtherCrosshairAngle;
	CCheckBox OtherAimSpot;
	CSlider OtherViewmodelFOV;
	CSlider OtherFOV;
	CCheckBox OtherBombShow;
	CCheckBox OtherDrawNades;
	CComboBox OtherHitmarker2;
	CComboBox OtherInfo;
	CCheckBox OtherNightMode;
	CCheckBox MapESP;
	CCheckBox OtherCompRank;
	CSlider OtherMyPremiumInteger;
	CComboBox OtherBarrel;
	CCheckBox OtherRemoveScope;
	CCheckBox OtherBulletTracer;
	CCheckBox OtherShowResolverInfo;
	CCheckBox OtherModelActive;
	CSlider Weapon;
	CComboBox LWeaponChams;
	CSlider WeaponR;
	CSlider WeaponG;
	CSlider WeaponB;


	//Radar and Such
	CCheckBox OtherRadar;
	CCheckBox OtherRadarEnemyOnly;
	CCheckBox OtherRadarVisibleOnly;
	CSlider	  OtherRadarScale;
	CSlider OtherRadarXPosition;
	CSlider OtherRadarYPosition;
};

class Cmisc : public CTab
{
public:
	void Setup();

	// Knife Changer
	//CGroupBox KnifeGroup;
	//CCheckBox KnifeEnable;
	//CComboBox KnifeModel;
	//CComboBox KnifeSkin;
	//CButton   KnifeApply;

	// Other Settings
	CGroupBox OtherGroup;
	CCheckBox OtherAutoJump;
	CCheckBox OtherEdgeJump;
	CComboBox OtherAutoStrafe;
	CCheckBox OtherSafeMode;
	CComboBox OtherChatSpam;
	CCheckBox OtherTeamChat;
	CSlider	  OtherChatDelay;
	CCheckBox FPSClantag;
	CKeyBind  OtherAirStuck;
	CCheckBox OtherLogs;
	CKeyBind  OtherLagSwitch;
	CCheckBox OtherSpecList;
	CCheckBox OtherWaterMark;
	CCheckBox OtherKillSpam;
	CSlider OtherScopedOpacity;
	CCheckBox OtherKillSpamchat;
	CCheckBox OtherCrasher;
	CCheckBox OtherFakeMedia;
	CCheckBox OtherHitmarker;
	CCheckBox OtherMemewalk;
	CComboBox OtherNightmode2;
	CCheckBox KnifeBot;
	CCheckBox OtherAsuswalls;
	CCheckBox OtherShowMenuOptions;
	CCheckBox OtherFakeping;
	CCheckBox OtherTranqChat;
	CComboBox FakeLagTyp;
	CCheckBox OtherBombShow;
	CCheckBox OtherAutoAccept;
	CKeyBind OtherFakeWalk;
	CKeyBind OtherCircleStrafeKey;
	CCheckBox OtherCircleStrafe;
	CCheckBox OtherThirdperson;
	CCheckBox OtherLastTickDefuse;
	CComboBox OtherThirdpersonType;
	CCheckBox OtherThirdpersonType2;
	CKeyBind OtherThirdpersonKey;
	CKeyBind OtherThirdpersonKey2;
	CCheckBox OtherHitmarkers;
	CSlider OtherThirdpersonRange;
	CCheckBox OtherModelEnable;
	CComboBox OtherConfigBox;
	CCheckBox OtherTextMenu;
	CComboBox OtherModelChanger;
	CKeyBind OtherMenuKey;

	// Fake Lag Settings
	CGroupBox FakeLagGroup;
	CCheckBox FakeLagEnable2;
	CCheckBox FakeLagEnable;
	CSlider AmbientExposure;
	CSlider AmbientRed;
	CSlider AmbientGreen;
	CSlider AmbientBlue;
	CComboBox AmbientSkybox;
	CSlider   FakeLagChoke2;
	CSlider   FakeLagChoke;
	CGroupBox glovesGloves;
	CCheckBox glovesEnableGloves;
	CComboBox glovesGloveSkin;
	CComboBox glovesGloveModel;
	CButton glovesGlovesApply;
	//CCheckBox FakeLagWhileShooting;
	CKeyBind bindkey2;
	CKeyBind bindkey3;
	//CCheckBox OtherAutoAccept;
	CCheckBox OtherWalkbot;
	CCheckBox OtherClantag;
	CTextField CustomClan;


	CLabel SkinActive;
	CCheckBox SkinEnable;
	CButton   SkinApply;

	CGroupBox KnifeGroup;
	CComboBox KnifeModel;
	CComboBox KnifeSkin;

	// Pistols
	CGroupBox PistolGroup;
	CComboBox GLOCKSkin;
	CComboBox USPSSkin;
	CComboBox DEAGLESkin;
	CComboBox MAGNUMSkin;
	CComboBox DUALSSkin;
	CComboBox FIVESEVENSkin;
	CComboBox TECNINESkin;
	CComboBox P2000Skin;
	CComboBox P250Skin;

	// MPs
	CGroupBox MPGroup;
	CComboBox MAC10Skin;
	CComboBox P90Skin;
	CComboBox UMP45Skin;
	CComboBox BIZONSkin;
	CComboBox MP7Skin;
	CComboBox MP9Skin;

	// Rifles
	CGroupBox Riflegroup;
	CComboBox M41SSkin;
	CComboBox M4A4Skin;
	CComboBox AK47Skin;
	CComboBox AUGSkin;
	CComboBox FAMASSkin;
	CComboBox GALILSkin;
	CComboBox SG553Skin;


	// Machineguns
	CGroupBox MachinegunsGroup;
	CComboBox MachinegunsNEGEVSkin;
	CComboBox MachinegunsM249Skin;

	// Snipers
	CGroupBox Snipergroup;
	CComboBox SCAR20Skin;
	CComboBox G3SG1Skin;
	CComboBox SSG08Skin;
	CComboBox AWPSkin;

	// Shotguns
	CGroupBox Shotgungroup;
	CComboBox MAG7Skin;
	CComboBox MachinegunsXM1014Skin;
	CComboBox SAWEDOFFSkin;
	CComboBox NOVASkin;

	// Fake Lag Settings
	CKeyBind FakeWalk;

	//CCheckBox FakeLagWhileShooting;

	// Teleport shit cause we're cool
	CGroupBox TeleportGroup;
	CCheckBox TeleportEnable;
	CKeyBind  TeleportKey;

};

class CAntiAimTab : public CTab
{
public:
	void Setup();

	//MASTER SWITCH
	CLabel AntiAimActiveLabel;
	CCheckBox AntiAimActive;

	// Anti-Aim Settings
	CGroupBox AntiAimGroup;
	/*CCheckBox AntiAimEnable;
	CComboBox AntiAimPitch;
	CComboBox staticyaw;*/
	CSlider AntiAimResolverAngle1;
	CSlider AntiAimResolverAngle2;
	CSlider AntiAimResolverAngle3;
	CSlider AntiAimResolverAngle4;
	/*CComboBox movingyaw;
	CComboBox fakeyaw;
	CComboBox edgeyaw;
	CCheckBox AntiAimEdge;
	CSlider	  AntiAimOffset;
	CSlider	  SpinSpeed;
	CSlider	  SpinSpeed2;
	CSlider	  AntiAimOffsetReal;
	CSlider	  AntiAimOffsetFake;
	CCheckBox AntiAimKnife;
	CCheckBox AntiAimTarget;
	CCheckBox AntiAimJitterLBY;
	CSlider	  AntiAimSpinspeed;*/
	CSliderR backR;
	CSliderG backG;
	CSliderB backB;
	CSliderR spreadR;
	CSliderG spreadG;
	CSliderB spreadB;
	CSliderR textR;
	CSliderG textG;
	CSliderB textB;
	CSliderR HitMarkerR;
	CSliderG HitMarkerG;
	CSliderB HitMarkerB;
	CSliderR BoxR;
	CSliderG BoxG;
	CSliderB BoxB;

	CGroupBox ColorsGroup;
	CSliderR SkeletonR;
	CSliderG SkeletonG;
	CSliderB SkeletonB;
	CSliderR NameR;
	CSliderG NameG;
	CSliderB NameB;
	CSliderR  FillBoxRed;
	CSliderG  FillBoxGreen;
	CSliderB  FillBoxBlue;
	CSlider	  FillBoxAlpha;
	CSliderR crossR;
	CSliderG crossG;
	CSliderB crossB;

	CComboBox AntiResolver;
	CComboBox AntiAimEdge2;
	CCheckBox BreakLBY;

	//skin pGroup

	CLabel SkinActive;
	CCheckBox SkinEnable;
	CButton   SkinApply;

	CGroupBox KnifeGroup;
	CComboBox KnifeModel;
	CComboBox KnifeSkin;

	// Pistols
	CGroupBox PistolGroup;
	CComboBox GLOCKSkin;
	CComboBox USPSSkin;
	CComboBox DEAGLESkin;
	CComboBox MAGNUMSkin;
	CComboBox DUALSSkin;
	CComboBox FIVESEVENSkin;
	CComboBox TECNINESkin;
	CComboBox P2000Skin;
	CComboBox P250Skin;

	// MPs
	CGroupBox MPGroup;
	CComboBox MAC10Skin;
	CComboBox P90Skin;
	CComboBox UMP45Skin;
	CComboBox BIZONSkin;
	CComboBox MP7Skin;
	CComboBox MP9Skin;

	// Rifles
	CGroupBox Riflegroup;
	CComboBox M41SSkin;
	CComboBox M4A4Skin;
	CComboBox AK47Skin;
	CComboBox AUGSkin;
	CComboBox FAMASSkin;
	CComboBox GALILSkin;
	CComboBox SG553Skin;


	// Machineguns
	CGroupBox MachinegunsGroup;
	CComboBox MachinegunsNEGEVSkin;
	CComboBox MachinegunsM249Skin;

	// Snipers
	CGroupBox Snipergroup;
	CComboBox SCAR20Skin;
	CComboBox G3SG1Skin;
	CComboBox SSG08Skin;
	CComboBox AWPSkin;

	// Shotguns
	CGroupBox Shotgungroup;
	CComboBox MAG7Skin;
	CComboBox MachinegunsXM1014Skin;
	CComboBox SAWEDOFFSkin;
	CComboBox NOVASkin;


};

class CColorTab : public CTab
{
public:
	void Setup();

	CGroupBox ColorGroup;
	CGroupBox CTColorGroup;
	CGroupBox TerroristColorGroup;
	CLabel  PlayerEsp;


	//Box esp visble
	CSlider	  VisBoxRed;
	CSlider	  VisBoxGreen;
	CSlider	  VisBoxBlue;
	CSlider	  VisBoxAlpha;

	CSlider	  VisBoxRed2;
	CSlider	  VisBoxGreen2;
	CSlider	  VisBoxBlue2;
	CSlider	  VisBoxAlpha2;

	//Box esp 
	CSlider	  BoxRed;
	CSlider	  BoxGreen;
	CSlider	  BoxBlue;
	CSlider	  BoxAlpha;

	CSlider	  BoxRed2;
	CSlider	  BoxGreen2;
	CSlider	  BoxBlue2;
	CSlider	  BoxAlpha2;

	//Chams 
	CSlider	  CTChamsRed;
	CSlider	  CTChamsGreen;
	CSlider	  CTChamsBlue;
	CSliderR CTChamsR;
	CSliderG CTChamsG;
	CSliderB CTChamsB;
	CSlider	  CTVisChamsRed;
	CSlider	  CTVisChamsGreen;
	CSlider	  CTVisChamsBlue;

	CSlider	 TerroristChamsRed;
	CSlider	 TerroristChamsGreen;
	CSlider	TerroristChamsBlue;

	CSlider	 TerroristVisChamsRed;
	CSlider	 TerroristVisChamsGreen;
	CSlider	TerroristVisChamsBlue;

	//color 1
	CGroupBox ColorsGroup;
	CSliderR SkeletonR;
	CSliderG SkeletonG;
	CSliderB SkeletonB;
	CSliderR NameR;
	CSliderG NameG;
	CSliderB NameB;
	CSliderR  FillBoxRed;
	CSliderG  FillBoxGreen;
	CSliderB  FillBoxBlue;
	CSlider	  FillBoxAlpha;
	CSliderR backR;
	CSliderG backG;
	CSliderB backB;
	CSliderR spreadR;
	CSliderG spreadG;
	CSliderB spreadB;
	CSliderR textR;
	CSliderG textG;
	CSliderB textB;
	CSliderR chamsR;
	CSliderG chamsG;
	CSliderB chamsB;
	CSliderR vischamsR;
	CSliderG vischamsG;
	CSliderB vischamsB;
	CSliderR WeaponR;
	CSliderG WeaponG;
	CSliderB WeaponB;

	//color 2
	CGroupBox Color2Group;
	CSliderR HitMarkerR;
	CSliderG HitMarkerG;
	CSliderB HitMarkerB;
	CSliderR BoxR;
	CSliderG BoxG;
	CSliderB BoxB;
	CSliderR crossR;
	CSliderG crossG;
	CSliderB crossB;
	CSliderR handR;
	CSliderG handG;
	CSliderB handB;
	CSliderR GlowR;
	CSliderG GlowG;
	CSliderB GlowB;
	CSliderR TChamsR;
	CSliderG TChamsG;
	CSliderB TChamsB;
	CSliderR FakeChamsR;
	CSliderG FakeChamsG;
	CSliderB FakeChamsB;



	CSliderR CTColorVisR;
	CSliderG CTColorVisG;
	CSliderB CTColorVisB;

	CSliderR CTColorNoVisR;
	CSliderG CTColorNoVisG;
	CSliderB CTColorNoVisB;

	CSliderR TColorVisR;
	CSliderG TColorVisG;
	CSliderB TColorVisB;

	CSliderR TColorNoVisR;
	CSliderG TColorNoVisG;
	CSliderB TColorNoVisB;

	CSliderR LocalTChamsR;
	CSliderG LocalTChamsG;
	CSliderB LocalTChamsB;
};



class CSkinTab : public CTab
{
public:
	void Setup();

	// Knife Changer/Skin Changer
	CLabel SkinActive;
	CCheckBox SkinEnable;
	CButton   SkinApply;

	// Knife

	// MPs


	// Machineguns
	CGroupBox MachinegunsGroup;
	CComboBox MachinegunsNEGEVSkin;
	CComboBox MachinegunsM249Skin;
	// Shotguns
	CComboBox MachinegunsMAG7Skin;
	CComboBox MachinegunsXM1014Skin;
	CComboBox MachinegunsSAWEDOFFSkin;
	CComboBox MachinegunsNOVASkin;
	// Pistols
	CComboBox GLOCKSkin;
	CComboBox USPSSkin;
	CComboBox DEAGLESkin;
	CComboBox MAGNUMSkin;
	CComboBox DUALSSkin;
	CComboBox FIVESEVENSkin;
	CComboBox TECNINESkin;
	CComboBox P2000Skin;
	CComboBox P250Skin;
	CComboBox CZSkin;

	// Snipers
	CGroupBox KnifeGroup;
	CComboBox SCAR20Skin;
	CComboBox G3SG1Skin;
	CComboBox SSG08Skin;
	CComboBox AWPSkin;
	CComboBox KnifeModel;
	CComboBox KnifeSkin;
	// Rifles
	CComboBox M41SSkin;
	CComboBox M4A4Skin;
	CComboBox AK47Skin;
	CComboBox AUGSkin;
	CComboBox FAMASSkin;
	CComboBox GALILSkin;
	CComboBox SG553Skin;
	//Gloves
	CCheckBox EnableGloves;
	CComboBox GloveSkin;
	CComboBox GloveModel;
	CButton GlovesApply;

	// Skinsettings
	CGroupBox SkinsettingsGroup;
	CCheckBox StatTrakEnable;
	/*
	*/

};

class SkinTab2 : public CTab
{
public:
	void Setup();

	// Knife Changer/Skin Changer
	CLabel SkinActive;
	CCheckBox SkinEnable;
	CButton   SkinApply;

	// Knife
	CGroupBox KnifeGroup;
	CComboBox KnifeModel;
	CComboBox KnifeSkin;

	// Pistols
	CGroupBox PistolGroup;
	CComboBox GLOCKSkin;
	CComboBox USPSSkin;
	CComboBox DEAGLESkin;
	CComboBox MAGNUMSkin;
	CComboBox DUALSSkin;
	CComboBox FIVESEVENSkin;
	CComboBox TECNINESkin;
	CComboBox P2000Skin;
	CComboBox P250Skin;

	// MPs
	CGroupBox MPGroup;
	CComboBox MAC10Skin;
	CComboBox P90Skin;
	CComboBox UMP45Skin;
	CComboBox BIZONSkin;
	CComboBox MP7Skin;
	CComboBox MP9Skin;

	// Rifles
	CGroupBox Riflegroup;
	CComboBox M41SSkin;
	CComboBox M4A4Skin;
	CComboBox AK47Skin;
	CComboBox AUGSkin;
	CComboBox FAMASSkin;
	CComboBox GALILSkin;
	CComboBox SG553Skin;


	// Machineguns
	CGroupBox MachinegunsGroup;
	CComboBox MachinegunsNEGEVSkin;
	CComboBox MachinegunsM249Skin;

	// Snipers
	CGroupBox Snipergroup;
	CComboBox SCAR20Skin;
	CComboBox G3SG1Skin;
	CComboBox SSG08Skin;
	CComboBox AWPSkin;

	// Shotguns
	CGroupBox Shotgungroup;
	CComboBox MAG7Skin;
	CComboBox MachinegunsXM1014Skin;
	CComboBox SAWEDOFFSkin;
	CComboBox NOVASkin;
};



class CPlayersTab : public CTab
{
public:
	void Setup();

	CGroupBox pListGroup;

	CGroupBox pListPlayers;

	CGroupBox OptionsGroup;

	CSlider OptionsFriendly;

	CSlider OptionsAimPrio;

	CSlider OptionsCalloutSpam;

	CLabel SetColumns;

};

class AyyWareWindow : public CWindow
{
public:
	void Setup();

	Crage rage;
	Clegit legit;
	Cesp esp;
	Cmisc misc;
	CAntiAimTab AntiAimTab;
	CColorTab ColorTab;
	CSkinTab SkinTab;
	SkinTab2 SkinTab2;
	CPlayersTab Playerlist;

	CButton SaveButton;
	CButton LoadButton;
	CButton UnloadButton;
	CComboBox OtherConfigBox;
};

	void SetupMenu();
	void DoUIFrame();

	extern AyyWareWindow g_menu;


struct Item
{
	const wchar_t* name;
	bool* container;
	int number;
};

class TextMenu : public CSingleton
{
public:
	TextMenu();
	void OnPaintTraverse();
	void Toggle();
	bool IsVisible();
private:
	void HandleInput();
	void DrawBool(int x, int y, const wchar_t* name, bool container, int number, int selected_number);
	bool Enabled;
	int SelectedOption;
	std::vector<Item> MenuItems;
};