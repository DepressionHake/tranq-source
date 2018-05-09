/*
bonus's tranquility framework 2018
*/

#pragma once

#include "Hacks.h"

Vector GetAutostrafeView();

class CMiscHacks : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:
	void AutoJump(CUserCmd *pCmd);
	void Telehop(CUserCmd *pCmd);
	void AutoJumpSMAC(CUserCmd *pCmd);
	void EdgeJump(CUserCmd *pCmd);
	void Walkbot(CUserCmd *pCmd);
	void PerfectStrafe(CUserCmd *pCmd);
	void LegitStrafe(CUserCmd *pCmd);
	void Fakelag(CUserCmd *pCmd, bool &bSendPacket);
	void RageStrafe(CUserCmd *pCmd);
	void RotateMovement(CUserCmd * pCmd, float rotation);
	void doCircularStrafe(CUserCmd * pCmd, Vector & Originalview);
	void xGodWalk(CUserCmd *pCmd);
	void xGodWalk2(CUserCmd *pCmd);
	void ChatSpamInterwebz();
	void ChatSpamName();
	void ayyware100(CUserCmd* localplayer, CBaseCombatWeapon *pWeapon);
	void ChatSpamDisperseName();
	void ChatSpamRegular();
	void SkyModes();
	void ChatSpamReports();
	void ChatSpamCallout();
//	void Fakelag(CUserCmd *pCmd, bool &bSendPacket);
//	void FakelagInAir(CUserCmd *pCmd, bool &bSendPacket);
	void Crasher();
	void AmbientLighting();
	void AmbientExposure();
	void SpoofPostProcessing();
	void AmbientSkybox();
	void RemoveScope();
	void headshotthemnigga();
	void FakeWalk(CUserCmd * pCmd, bool & bSendPacket);
	void OnRenderSpectatorList();

	//std::string GetNameChange();

	/*void ChatSpam();
	void Namechanger();

	std::string GetRegularSpam();
	std::string GetCustomSpam();
	std::string GetPlayerSpam();
	std::string GetSinglePlayerSpam();

	std::string GetNameChange();
	std::string GetNameCalloutChange();*/
};

namespace SDK
{
	class PlayerInfo {
	private:
		DWORD __pad0[2];
	public:
		int m_nXuidLow;
		int m_nXuidHigh;
		char m_szPlayerName[128];
		int m_nUserID;
		char m_szSteamID[33];
		UINT m_nSteam3ID;
		char m_szFriendsName[128];
		bool m_bIsFakePlayer;
		bool m_bIsHLTV;
		DWORD m_dwCustomFiles[4];
		BYTE m_FilesDownloaded;
	private:
		int __pad1;
	};
}



