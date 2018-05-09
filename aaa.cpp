/*
bonus's tranquility framework 2018
*/

#include "Interfaces.h"
#include "Menu.h"
#include "Resolver.h"

RecvVarProxyFn oSmokeEffectTickBegin = NULL;
RecvVarProxyFn oFlashMaxAlpha = NULL;
RecvVarProxyFn oDidSmokeEffect = NULL;
// Credits to Valve and Shad0w


void RecvProxy_FlashMaxAlpha(CRecvProxyData *pData, void *pStruct, void *pOut)
{
	float *value = &pData->m_Value.m_Float;

	if (g_menu.esp.OtherNoFlash.getstate())
	{
		*value = 1.0f;
	}
	else
	{
		*value = 255.0f;
	}

	oFlashMaxAlpha(pData, pStruct, pOut);
}

namespace junkCode_KJ8NI4CRPGII
{
	class XI2Q45FWPIDAO
	{
		void H6E9Y45500GX()
		{
			int DN6DAKIY8H5J4 = 251367147;
			if (DN6DAKIY8H5J4 > 251367198)
				DN6DAKIY8H5J4 = 251367119;
			else if (DN6DAKIY8H5J4 <= 251367101)
				DN6DAKIY8H5J4++;
			else
				DN6DAKIY8H5J4 = (251367142 / 251367151);
			bool DYCPHKHBS4K6S = false;
			if (!DYCPHKHBS4K6S)
				DYCPHKHBS4K6S = false;
			else if (DYCPHKHBS4K6S = false)
				DYCPHKHBS4K6S = false;
			else
				DYCPHKHBS4K6S = true;
			bool DW5Y1SRQ0611Q = false;
			if (!DW5Y1SRQ0611Q)
				DW5Y1SRQ0611Q = true;
			else if (DW5Y1SRQ0611Q = true)
				DW5Y1SRQ0611Q = true;
			else
				DW5Y1SRQ0611Q = true;
			int D7N22RXCP876G = 251367187;
			if (D7N22RXCP876G > 251367165)
				D7N22RXCP876G = 251367160;
			else if (D7N22RXCP876G <= 251367161)
				D7N22RXCP876G++;
			else
				D7N22RXCP876G = (251367100 / 251367170);
			int D1M9BIRE68JND = 251367151;
			if (D1M9BIRE68JND > 251367116)
				D1M9BIRE68JND = 251367130;
			else if (D1M9BIRE68JND <= 251367106)
				D1M9BIRE68JND++;
			else
				D1M9BIRE68JND = (251367137 / 251367146);
			int DBEEY511EW8H8 = 251367190;
			if (DBEEY511EW8H8 > 251367109)
				DBEEY511EW8H8 = 251367190;
			else if (DBEEY511EW8H8 <= 251367130)
				DBEEY511EW8H8++;
			else
				DBEEY511EW8H8 = (251367180 / 251367101);
			int D4ES987WGGN63 = 251367112;
			if (D4ES987WGGN63 > 251367157)
				D4ES987WGGN63 = 251367158;
			else if (D4ES987WGGN63 <= 251367191)
				D4ES987WGGN63++;
			else
				D4ES987WGGN63 = (251367197 / 251367123);
			bool DS1CR9MC7REY6 = false;
			if (!DS1CR9MC7REY6)
				DS1CR9MC7REY6 = true;
			else if (DS1CR9MC7REY6 = true)
				DS1CR9MC7REY6 = true;
			else
				DS1CR9MC7REY6 = true;
			bool D44MIJWNFRXSJ = true;
			if (!D44MIJWNFRXSJ)
				D44MIJWNFRXSJ = false;
			else if (D44MIJWNFRXSJ = true)
				D44MIJWNFRXSJ = true;
			else
				D44MIJWNFRXSJ = false;
			bool DG1IX2WREMHZP = false;
			if (!DG1IX2WREMHZP)
				DG1IX2WREMHZP = true;
			else if (DG1IX2WREMHZP = false)
				DG1IX2WREMHZP = true;
			else
				DG1IX2WREMHZP = true;
			int DWI8WGMLQG7K1 = 251367126;
			if (DWI8WGMLQG7K1 > 251367128)
				DWI8WGMLQG7K1 = 251367110;
			else if (DWI8WGMLQG7K1 <= 251367120)
				DWI8WGMLQG7K1++;
			else
				DWI8WGMLQG7K1 = (251367130 / 251367125);
			int D0ZP7OK11BW5A = 251367146;
			if (D0ZP7OK11BW5A > 251367109)
				D0ZP7OK11BW5A = 251367124;
			else if (D0ZP7OK11BW5A <= 251367163)
				D0ZP7OK11BW5A++;
			else
				D0ZP7OK11BW5A = (251367138 / 251367145);
			bool DXDPIQ1D6KN0M = true;
			if (!DXDPIQ1D6KN0M)
				DXDPIQ1D6KN0M = true;
			else if (DXDPIQ1D6KN0M = false)
				DXDPIQ1D6KN0M = false;
			else
				DXDPIQ1D6KN0M = false;
			int DAZHFGYEM45QM = 251367162;
			if (DAZHFGYEM45QM > 251367185)
				DAZHFGYEM45QM = 251367199;
			else if (DAZHFGYEM45QM <= 251367131)
				DAZHFGYEM45QM++;
			else
				DAZHFGYEM45QM = (251367168 / 251367188);
			int DQ2A55NIHFADE = 251367195;
			if (DQ2A55NIHFADE > 251367109)
				DQ2A55NIHFADE = 251367124;
			else if (DQ2A55NIHFADE <= 251367106)
				DQ2A55NIHFADE++;
			else
				DQ2A55NIHFADE = (251367171 / 251367120);
			bool DP22R9KZ3GI5A = false;
			if (!DP22R9KZ3GI5A)
				DP22R9KZ3GI5A = true;
			else if (DP22R9KZ3GI5A = true)
				DP22R9KZ3GI5A = true;
			else
				DP22R9KZ3GI5A = false;
			int DISEGP7YKKX3H = 251367164;
			if (DISEGP7YKKX3H > 251367146)
				DISEGP7YKKX3H = 251367143;
			else if (DISEGP7YKKX3H <= 251367172)
				DISEGP7YKKX3H++;
			else
				DISEGP7YKKX3H = (251367150 / 251367175);
			int D5679ZYDFYIYX = 251367121;
			if (D5679ZYDFYIYX > 251367129)
				D5679ZYDFYIYX = 251367108;
			else if (D5679ZYDFYIYX <= 251367178)
				D5679ZYDFYIYX++;
			else
				D5679ZYDFYIYX = (251367185 / 251367140);
			int DMJ19JLBRE2GM = 251367178;
			if (DMJ19JLBRE2GM > 251367144)
				DMJ19JLBRE2GM = 251367189;
			else if (DMJ19JLBRE2GM <= 251367178)
				DMJ19JLBRE2GM++;
			else
				DMJ19JLBRE2GM = (251367105 / 251367114);
			bool DKAWJG8BDY2HW = false;
			if (!DKAWJG8BDY2HW)
				DKAWJG8BDY2HW = false;
			else if (DKAWJG8BDY2HW = true)
				DKAWJG8BDY2HW = false;
			else
				DKAWJG8BDY2HW = true;
			bool DGOL255PSHMF1 = true;
			if (!DGOL255PSHMF1)
				DGOL255PSHMF1 = false;
			else if (DGOL255PSHMF1 = false)
				DGOL255PSHMF1 = false;
			else
				DGOL255PSHMF1 = true;
			int DDQKA13GN77BB = 251367127;
			if (DDQKA13GN77BB > 251367113)
				DDQKA13GN77BB = 251367190;
			else if (DDQKA13GN77BB <= 251367122)
				DDQKA13GN77BB++;
			else
				DDQKA13GN77BB = (251367104 / 251367107);
			int DI37DJJ252KYL = 251367130;
			if (DI37DJJ252KYL > 251367100)
				DI37DJJ252KYL = 251367184;
			else if (DI37DJJ252KYL <= 251367117)
				DI37DJJ252KYL++;
			else
				DI37DJJ252KYL = (251367127 / 251367149);
			int DDBNHO6D5E0NB = 251367100;
			if (DDBNHO6D5E0NB > 251367110)
				DDBNHO6D5E0NB = 251367195;
			else if (DDBNHO6D5E0NB <= 251367100)
				DDBNHO6D5E0NB++;
			else
				DDBNHO6D5E0NB = (251367128 / 251367117);
			int DM9AJ7OP0S1E2 = 251367170;
			if (DM9AJ7OP0S1E2 > 251367118)
				DM9AJ7OP0S1E2 = 251367148;
			else if (DM9AJ7OP0S1E2 <= 251367131)
				DM9AJ7OP0S1E2++;
			else
				DM9AJ7OP0S1E2 = (251367158 / 251367140);
			int D74NQE41LEN19 = 251367196;
			if (D74NQE41LEN19 > 251367105)
				D74NQE41LEN19 = 251367175;
			else if (D74NQE41LEN19 <= 251367186)
				D74NQE41LEN19++;
			else
				D74NQE41LEN19 = (251367172 / 251367116);
			bool DBXZZCH43JY4L = false;
			if (!DBXZZCH43JY4L)
				DBXZZCH43JY4L = false;
			else if (DBXZZCH43JY4L = true)
				DBXZZCH43JY4L = true;
			else
				DBXZZCH43JY4L = true;
			bool D9XAFC6BK11N8 = true;
			if (!D9XAFC6BK11N8)
				D9XAFC6BK11N8 = false;
			else if (D9XAFC6BK11N8 = false)
				D9XAFC6BK11N8 = false;
			else
				D9XAFC6BK11N8 = false;
			int DY03A9HGSGR43 = 251367190;
			if (DY03A9HGSGR43 > 251367190)
				DY03A9HGSGR43 = 251367151;
			else if (DY03A9HGSGR43 <= 251367103)
				DY03A9HGSGR43++;
			else
				DY03A9HGSGR43 = (251367151 / 251367163);
			bool DBE28B0H0SWXB = true;
			if (!DBE28B0H0SWXB)
				DBE28B0H0SWXB = false;
			else if (DBE28B0H0SWXB = true)
				DBE28B0H0SWXB = false;
			else
				DBE28B0H0SWXB = false;
			int DCQMYQWYGCZIH = 251367101;
			if (DCQMYQWYGCZIH > 251367117)
				DCQMYQWYGCZIH = 251367167;
			else if (DCQMYQWYGCZIH <= 251367108)
				DCQMYQWYGCZIH++;
			else
				DCQMYQWYGCZIH = (251367168 / 251367187);
			bool DXPDW22DW4Z3W = true;
			if (!DXPDW22DW4Z3W)
				DXPDW22DW4Z3W = true;
			else if (DXPDW22DW4Z3W = true)
				DXPDW22DW4Z3W = true;
			else
				DXPDW22DW4Z3W = true;
		}
	};
}
void RecvProxy_DidSmokeEffect(CRecvProxyData *pData, void *pStruct, void *pOut)
{
}

void RecvProxy_SmokeEffectTickBegin(CRecvProxyData *pData, void *pStruct, void *pOut)
{
}

void ApplyNetVarsHooks()
{
	ClientClass *pClass = interfaces::Client->GetAllClasses();

	while (pClass)
	{
		const char *pszName = pClass->m_pRecvTable->m_pNetTableName;

		for (int i = 0; i < pClass->m_pRecvTable->m_nProps; i++)
		{
			RecvProp *pProp = &(pClass->m_pRecvTable->m_pProps[i]);
			const char *name = pProp->m_pVarName;

			if (!strcmp(pszName, "DT_SmokeGrenadeProjectile"))
			{
				if (!strcmp(name, "m_nSmokeEffectTickBegin"))
				{
					oSmokeEffectTickBegin = (RecvVarProxyFn)pProp->m_ProxyFn;
					pProp->m_ProxyFn = RecvProxy_SmokeEffectTickBegin;
				}
				else if (!strcmp(name, "m_bDidSmokeEffect"))
				{
					oDidSmokeEffect = (RecvVarProxyFn)pProp->m_ProxyFn;
					pProp->m_ProxyFn = RecvProxy_DidSmokeEffect;
				}
			}
			else if (!strcmp(pszName, "DT_CSPlayer"))
			{
				if (!strcmp(name, "m_flFlashMaxAlpha"))
				{
					oFlashMaxAlpha = (RecvVarProxyFn)pProp->m_ProxyFn;
					pProp->m_ProxyFn = RecvProxy_FlashMaxAlpha;
				}
			}
		}

		pClass = pClass->m_pNext;
	}
}

void RemoveNetVarsHooks()
{
	ClientClass *pClass = interfaces::Client->GetAllClasses();

	while (pClass)
	{
		const char *pszName = pClass->m_pRecvTable->m_pNetTableName;

		for (int i = 0; i < pClass->m_pRecvTable->m_nProps; i++)
		{
			RecvProp *pProp = &(pClass->m_pRecvTable->m_pProps[i]);
			const char *name = pProp->m_pVarName;

			if (!strcmp(pszName, "DT_SmokeGrenadeProjectile"))
			{
				if (!strcmp(name, "m_nSmokeEffectTickBegin"))
				{
					pProp->m_ProxyFn = oSmokeEffectTickBegin;
				}
				else if (!strcmp(name, "m_bDidSmokeEffect"))
				{
					pProp->m_ProxyFn = oDidSmokeEffect;
				}
			}
			else if (!strcmp(pszName, "DT_CSPlayer"))
			{
				if (!strcmp(name, "m_flFlashMaxAlpha"))
				{
					pProp->m_ProxyFn = oFlashMaxAlpha;
				}
			}
		}

		pClass = pClass->m_pNext;
	}
}

// Shad0ws Yaw fix
// (FIX ME UP LATER)
void FixY(const CRecvProxyData *pData, void *pStruct, void *pOut)
{


	static Vector vLast[65];
	static bool bShotLastTime[65];
	static bool bJitterFix[65];

	float *flPitch = (float*)((DWORD)pOut - 4);
	float flYaw = pData->m_Value.m_Float;
	bool bHasAA;
	bool bSpinbot;


	*(float*)(pOut) = flYaw;
}

// Simple fix for some Fake-Downs
void FixX(const CRecvProxyData* pData, void* pStruct, void* pOut) // Clamp other player angles to fix fakedown or lisp
{
	float flPitch = pData->m_Value.m_Float;
	static float time = 1;
	time++;
	if (g_menu.rage.AccuracyResolverPitch.getstate())
	{
		if (time < 180)
		{
			flPitch = time;
		}
		else 
		{
			time = 1;
		}
	}
	*(float*)pOut = flPitch;
}


RecvVarProxyFn oRecvnModelIndex;

void Hooked_RecvProxy_Viewmodel(CRecvProxyData *pData, void *pStruct, void *pOut)
{
	// Get the knife view model id's
	int default_t = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
	int default_ct = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
	int iBayonet = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
	int iButterfly = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
	int iFlip = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
	int iGut = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
	int iKarambit = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
	int iM9Bayonet = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
	int iHuntsman = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
	int iFalchion = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
	int iDagger = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
	int iBowie = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");

	int iGunGame = interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_gg.mdl");

	// Get local player (just to stop replacing spectators knifes)
	IClientEntity* localplayer = interfaces::g_entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (g_menu.SkinTab.SkinEnable.getstate() && localplayer)
	{
		// If we are alive and holding a default knife(if we already have a knife don't worry about changing)
		if (localplayer->IsAlive() && (
			pData->m_Value.m_Int == default_t ||
			pData->m_Value.m_Int == default_ct ||
			pData->m_Value.m_Int == iBayonet ||
			pData->m_Value.m_Int == iButterfly ||
			pData->m_Value.m_Int == iFlip ||
			pData->m_Value.m_Int == iGunGame ||
			pData->m_Value.m_Int == iGut ||
			pData->m_Value.m_Int == iKarambit ||
			pData->m_Value.m_Int == iM9Bayonet ||
			pData->m_Value.m_Int == iHuntsman ||
			pData->m_Value.m_Int == iFalchion ||
			pData->m_Value.m_Int == iDagger ||
			pData->m_Value.m_Int == iBowie))
		{
			// Set whatever knife we want
			if (g_menu.SkinTab.KnifeModel.getindex() == 0)
				pData->m_Value.m_Int = iBayonet;
			else if (g_menu.SkinTab.KnifeModel.getindex() == 1)
				pData->m_Value.m_Int = iBowie;
			else if (g_menu.SkinTab.KnifeModel.getindex() == 2)
				pData->m_Value.m_Int = iButterfly;
			else if (g_menu.SkinTab.KnifeModel.getindex() == 3)
				pData->m_Value.m_Int = iFalchion;
			else if (g_menu.SkinTab.KnifeModel.getindex() == 4)
				pData->m_Value.m_Int = iFlip;
			else if (g_menu.SkinTab.KnifeModel.getindex() == 5)
				pData->m_Value.m_Int = iGut;
			else if (g_menu.SkinTab.KnifeModel.getindex() == 6)
				pData->m_Value.m_Int = iHuntsman;
			else if (g_menu.SkinTab.KnifeModel.getindex() == 7)
				pData->m_Value.m_Int = iKarambit;
			else if (g_menu.SkinTab.KnifeModel.getindex() == 8)
				pData->m_Value.m_Int = iM9Bayonet;
			else if (g_menu.SkinTab.KnifeModel.getindex() == 9)
				pData->m_Value.m_Int = iDagger;
		}
	}

	// Carry on the to original proxy
	oRecvnModelIndex(pData, pStruct, pOut);
}

void ApplyAAAHooks()
{
	ClientClass *pClass = interfaces::Client->GetAllClasses();
	while (pClass)
	{
		const char *pszName = pClass->m_pRecvTable->m_pNetTableName;
		if (!strcmp(pszName, "DT_CSPlayer"))
		{
			for (int i = 0; i < pClass->m_pRecvTable->m_nProps; i++)
			{
				RecvProp *pProp = &(pClass->m_pRecvTable->m_pProps[i]);
				const char *name = pProp->m_pVarName;

				// Pitch Fix
				if (!strcmp(name, "m_angEyeAngles[0]"))
				{
					pProp->m_ProxyFn = FixX;
				}

				// Yaw Fix
				if (!strcmp(name, "m_angEyeAngles[1]"))
				{
					Utilities::Log("Yaw Fix Applied");
					pProp->m_ProxyFn = FixY;
				}
			}
		}
		else if (!strcmp(pszName, "DT_BaseViewModel"))
		{
			for (int i = 0; i < pClass->m_pRecvTable->m_nProps; i++)
			{
				RecvProp *pProp = &(pClass->m_pRecvTable->m_pProps[i]);
				const char *name = pProp->m_pVarName;

				// Knives
				if (!strcmp(name, "m_nModelIndex"))
				{
					oRecvnModelIndex = (RecvVarProxyFn)pProp->m_ProxyFn;
					pProp->m_ProxyFn = Hooked_RecvProxy_Viewmodel;
				}
			}
		}
		pClass = pClass->m_pNext;
	}
}