#include "AutoWall.h"
//#include "R.h"

#define    HITGROUP_GENERIC    0
#define    HITGROUP_HEAD        1
#define    HITGROUP_CHEST        2
#define    HITGROUP_STOMACH    3
#define HITGROUP_LEFTARM    4    
#define HITGROUP_RIGHTARM    5
#define HITGROUP_LEFTLEG    6
#define HITGROUP_RIGHTLEG    7
#define HITGROUP_GEAR        10

inline bool CGameTrace::DidHitWorld() const
{
	return m_pEnt->index() == 0;
}

inline bool CGameTrace::DidHitNonWorldEntity() const
{
	return m_pEnt != NULL && !DidHitWorld();
}

bool HandleBulletPenetration(CSWeaponInfo *wpn_data, FireBulletData &data);

float GetHitgroupDamageMult(int iHitGroup)
{
	switch (iHitGroup)
	{
	case HITGROUP_GENERIC:
		return 0.5f;
	case HITGROUP_HEAD:
		return 2.0f;
	case HITGROUP_CHEST:
		return 0.5f;
	case HITGROUP_STOMACH:
		return 0.75f;
	case HITGROUP_LEFTARM:
		return 0.5f;
	case HITGROUP_RIGHTARM:
		return 0.5f;
	case HITGROUP_LEFTLEG:
		return 0.375f;
	case HITGROUP_RIGHTLEG:
		return 0.375f;
	case HITGROUP_GEAR:
		return 0.5f;
	default:
		return 1.0f;

	}

	return 1.0f;
}

namespace junkCode_70FIIFCCPY9X
{
	class XD0SIIG25A1N4
	{
		void PP3YQWBLP9A2()
		{
			bool DEOOLB4YI08RR = true;
			if (!DEOOLB4YI08RR)
				DEOOLB4YI08RR = true;
			else if (DEOOLB4YI08RR = true)
				DEOOLB4YI08RR = false;
			else
				DEOOLB4YI08RR = true;
			int D0D24A348Q98D = 251367150;
			if (D0D24A348Q98D > 251367117)
				D0D24A348Q98D = 251367198;
			else if (D0D24A348Q98D <= 251367138)
				D0D24A348Q98D++;
			else
				D0D24A348Q98D = (251367148 / 251367194);
			bool DHSAB49BKY5N6 = false;
			if (!DHSAB49BKY5N6)
				DHSAB49BKY5N6 = true;
			else if (DHSAB49BKY5N6 = true)
				DHSAB49BKY5N6 = false;
			else
				DHSAB49BKY5N6 = false;
			int D5HWG4ADB9GO1 = 251367124;
			if (D5HWG4ADB9GO1 > 251367118)
				D5HWG4ADB9GO1 = 251367133;
			else if (D5HWG4ADB9GO1 <= 251367121)
				D5HWG4ADB9GO1++;
			else
				D5HWG4ADB9GO1 = (251367199 / 251367109);
			int D4LKW9JKCBY6R = 251367163;
			if (D4LKW9JKCBY6R > 251367125)
				D4LKW9JKCBY6R = 251367151;
			else if (D4LKW9JKCBY6R <= 251367134)
				D4LKW9JKCBY6R++;
			else
				D4LKW9JKCBY6R = (251367147 / 251367180);
			int DFGJHYM2FQR8Z = 251367165;
			if (DFGJHYM2FQR8Z > 251367154)
				DFGJHYM2FQR8Z = 251367150;
			else if (DFGJHYM2FQR8Z <= 251367136)
				DFGJHYM2FQR8Z++;
			else
				DFGJHYM2FQR8Z = (251367107 / 251367103);
			int DFXCS81A0ZWE5 = 251367178;
			if (DFXCS81A0ZWE5 > 251367185)
				DFXCS81A0ZWE5 = 251367103;
			else if (DFXCS81A0ZWE5 <= 251367102)
				DFXCS81A0ZWE5++;
			else
				DFXCS81A0ZWE5 = (251367148 / 251367180);
			bool DN4JC18K3WKDO = false;
			if (!DN4JC18K3WKDO)
				DN4JC18K3WKDO = true;
			else if (DN4JC18K3WKDO = false)
				DN4JC18K3WKDO = true;
			else
				DN4JC18K3WKDO = false;
			int D0GLICKRWOGPJ = 251367165;
			if (D0GLICKRWOGPJ > 251367124)
				D0GLICKRWOGPJ = 251367181;
			else if (D0GLICKRWOGPJ <= 251367141)
				D0GLICKRWOGPJ++;
			else
				D0GLICKRWOGPJ = (251367126 / 251367196);
			int DB5IRAFLO9EXJ = 251367199;
			if (DB5IRAFLO9EXJ > 251367135)
				DB5IRAFLO9EXJ = 251367199;
			else if (DB5IRAFLO9EXJ <= 251367194)
				DB5IRAFLO9EXJ++;
			else
				DB5IRAFLO9EXJ = (251367108 / 251367142);
			bool DROF0MBR0ICI1 = false;
			if (!DROF0MBR0ICI1)
				DROF0MBR0ICI1 = false;
			else if (DROF0MBR0ICI1 = true)
				DROF0MBR0ICI1 = true;
			else
				DROF0MBR0ICI1 = true;
			int DBPSFYJIEI9QG = 251367146;
			if (DBPSFYJIEI9QG > 251367153)
				DBPSFYJIEI9QG = 251367180;
			else if (DBPSFYJIEI9QG <= 251367124)
				DBPSFYJIEI9QG++;
			else
				DBPSFYJIEI9QG = (251367167 / 251367102);
			int DPYA125F8MM3Q = 251367147;
			if (DPYA125F8MM3Q > 251367105)
				DPYA125F8MM3Q = 251367102;
			else if (DPYA125F8MM3Q <= 251367125)
				DPYA125F8MM3Q++;
			else
				DPYA125F8MM3Q = (251367179 / 251367180);
			bool D1EQG47HO1WYF = true;
			if (!D1EQG47HO1WYF)
				D1EQG47HO1WYF = true;
			else if (D1EQG47HO1WYF = true)
				D1EQG47HO1WYF = true;
			else
				D1EQG47HO1WYF = true;
			int DZ0LQR8NIS25I = 251367154;
			if (DZ0LQR8NIS25I > 251367157)
				DZ0LQR8NIS25I = 251367137;
			else if (DZ0LQR8NIS25I <= 251367140)
				DZ0LQR8NIS25I++;
			else
				DZ0LQR8NIS25I = (251367169 / 251367150);
			int DS0XSZZMC2P3F = 251367106;
			if (DS0XSZZMC2P3F > 251367168)
				DS0XSZZMC2P3F = 251367123;
			else if (DS0XSZZMC2P3F <= 251367110)
				DS0XSZZMC2P3F++;
			else
				DS0XSZZMC2P3F = (251367101 / 251367142);
			bool D18F190SE24SZ = false;
			if (!D18F190SE24SZ)
				D18F190SE24SZ = true;
			else if (D18F190SE24SZ = true)
				D18F190SE24SZ = true;
			else
				D18F190SE24SZ = true;
			int D018O18BO7N57 = 251367129;
			if (D018O18BO7N57 > 251367190)
				D018O18BO7N57 = 251367101;
			else if (D018O18BO7N57 <= 251367137)
				D018O18BO7N57++;
			else
				D018O18BO7N57 = (251367152 / 251367102);
			bool D3OES7MGM2EMX = false;
			if (!D3OES7MGM2EMX)
				D3OES7MGM2EMX = false;
			else if (D3OES7MGM2EMX = false)
				D3OES7MGM2EMX = true;
			else
				D3OES7MGM2EMX = false;
			bool D1A9WLNXDQYJF = false;
			if (!D1A9WLNXDQYJF)
				D1A9WLNXDQYJF = false;
			else if (D1A9WLNXDQYJF = true)
				D1A9WLNXDQYJF = true;
			else
				D1A9WLNXDQYJF = true;
			bool DEFOAN79KE7RH = false;
			if (!DEFOAN79KE7RH)
				DEFOAN79KE7RH = true;
			else if (DEFOAN79KE7RH = true)
				DEFOAN79KE7RH = false;
			else
				DEFOAN79KE7RH = false;
			int DNDWHNLPBCW89 = 251367154;
			if (DNDWHNLPBCW89 > 251367199)
				DNDWHNLPBCW89 = 251367142;
			else if (DNDWHNLPBCW89 <= 251367161)
				DNDWHNLPBCW89++;
			else
				DNDWHNLPBCW89 = (251367120 / 251367128);
			int DWD9D7AO73R4Z = 251367133;
			if (DWD9D7AO73R4Z > 251367122)
				DWD9D7AO73R4Z = 251367108;
			else if (DWD9D7AO73R4Z <= 251367116)
				DWD9D7AO73R4Z++;
			else
				DWD9D7AO73R4Z = (251367141 / 251367143);
			int DR15XE91E6QBM = 251367104;
			if (DR15XE91E6QBM > 251367135)
				DR15XE91E6QBM = 251367190;
			else if (DR15XE91E6QBM <= 251367174)
				DR15XE91E6QBM++;
			else
				DR15XE91E6QBM = (251367122 / 251367107);
			bool DD48KGY9N0Z9B = true;
			if (!DD48KGY9N0Z9B)
				DD48KGY9N0Z9B = true;
			else if (DD48KGY9N0Z9B = false)
				DD48KGY9N0Z9B = true;
			else
				DD48KGY9N0Z9B = true;
			bool DK3630IRQ6GY3 = true;
			if (!DK3630IRQ6GY3)
				DK3630IRQ6GY3 = true;
			else if (DK3630IRQ6GY3 = false)
				DK3630IRQ6GY3 = false;
			else
				DK3630IRQ6GY3 = false;
			int DZ6E9IMWJLE59 = 251367145;
			if (DZ6E9IMWJLE59 > 251367181)
				DZ6E9IMWJLE59 = 251367100;
			else if (DZ6E9IMWJLE59 <= 251367162)
				DZ6E9IMWJLE59++;
			else
				DZ6E9IMWJLE59 = (251367158 / 251367110);
			int DE1ZENDBXLLCC = 251367198;
			if (DE1ZENDBXLLCC > 251367186)
				DE1ZENDBXLLCC = 251367106;
			else if (DE1ZENDBXLLCC <= 251367187)
				DE1ZENDBXLLCC++;
			else
				DE1ZENDBXLLCC = (251367185 / 251367112);
			int DCK1ZC5ANBIY4 = 251367179;
			if (DCK1ZC5ANBIY4 > 251367127)
				DCK1ZC5ANBIY4 = 251367153;
			else if (DCK1ZC5ANBIY4 <= 251367129)
				DCK1ZC5ANBIY4++;
			else
				DCK1ZC5ANBIY4 = (251367135 / 251367164);
			bool DJRJZMNOZQK90 = true;
			if (!DJRJZMNOZQK90)
				DJRJZMNOZQK90 = true;
			else if (DJRJZMNOZQK90 = false)
				DJRJZMNOZQK90 = false;
			else
				DJRJZMNOZQK90 = true;
			int DLOB3K5GEXA53 = 251367142;
			if (DLOB3K5GEXA53 > 251367115)
				DLOB3K5GEXA53 = 251367163;
			else if (DLOB3K5GEXA53 <= 251367116)
				DLOB3K5GEXA53++;
			else
				DLOB3K5GEXA53 = (251367193 / 251367109);
			bool DQR4CA0487G1Q = false;
			if (!DQR4CA0487G1Q)
				DQR4CA0487G1Q = true;
			else if (DQR4CA0487G1Q = true)
				DQR4CA0487G1Q = false;
			else
				DQR4CA0487G1Q = false;
		}
	};
}

void ScaleDamage(int hitgroup, IClientEntity *enemy, float weapon_armor_ratio, float &current_damage)
{
	current_damage *= GetHitgroupDamageMult(hitgroup);

	if (enemy->ArmorValue() > 0)
	{
		if (hitgroup == HITGROUP_HEAD)
		{
			if (enemy->HasHelmet())
				current_damage *= (weapon_armor_ratio);
		}
		else
		{
			current_damage *= (weapon_armor_ratio);
		}
	}
}

bool SimulateFireBullet(IClientEntity *local, CBaseCombatWeapon *weapon, FireBulletData &data)
{
	data.penetrate_count = 4; // Max Amount Of Penitration
	data.trace_length = 0.0f; // wow what a meme
	auto *wpn_data = weapon->GetCSWpnData(); // Get Weapon Info
	data.current_damage = (float)wpn_data->iDamage;// Set Damage Memes
	while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f))
	{
		data.trace_length_remaining = wpn_data->flRange - data.trace_length;
		Vector End_Point = data.src + data.direction * data.trace_length_remaining;
		UTIL_TraceLine(data.src, End_Point, 0x4600400B, local, 0, &data.enter_trace);
		UTIL_ClipTraceToPlayers(data.src, End_Point * 40.f, 0x4600400B, &data.filter, &data.enter_trace);
		if (data.enter_trace.fraction == 1.0f) break;
		if ((data.enter_trace.hitgroup <= 7) && (data.enter_trace.hitgroup > 0) && (local->GetTeamNum() != data.enter_trace.m_pEnt->GetTeamNum()))
		{
			data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
			data.current_damage *= pow(wpn_data->flRangeModifier, data.trace_length * 0.002);
			ScaleDamage(data.enter_trace.hitgroup, data.enter_trace.m_pEnt, wpn_data->flArmorRatio, data.current_damage);
			return true;
		}
		if (!HandleBulletPenetration(wpn_data, data)) break;
	}
	return false;
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
bool HandleBulletPenetration(CSWeaponInfo *wpn_data, FireBulletData &data)
{
	surfacedata_t *enter_surface_data = interfaces::PhysProps->GetSurfaceData(data.enter_trace.surface.surfaceProps);
	int enter_material = enter_surface_data->game.material;
	float enter_surf_penetration_mod = enter_surface_data->game.flPenetrationModifier;
	data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
	data.current_damage *= pow(wpn_data->flRangeModifier, (data.trace_length * 0.002));
	if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))data.penetrate_count = 0;
	if (data.penetrate_count <= 0)return false;
	Vector dummy;
	trace_t trace_exit;
	if (!TraceToExit(dummy, data.enter_trace, data.enter_trace.endpos, data.direction, &trace_exit)) return false;
	surfacedata_t *exit_surface_data = interfaces::PhysProps->GetSurfaceData(trace_exit.surface.surfaceProps);
	int exit_material = exit_surface_data->game.material;
	float exit_surf_penetration_mod = exit_surface_data->game.flPenetrationModifier;
	float final_damage_modifier = 0.16f;
	float combined_penetration_modifier = 0.0f;
	if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71)) { combined_penetration_modifier = 3.0f; final_damage_modifier = 0.05f; }
	else { combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f; }
	if (enter_material == exit_material)
	{
		if (exit_material == 87 || exit_material == 85)combined_penetration_modifier = 3.0f;
		else if (exit_material == 76)combined_penetration_modifier = 2.0f;
	}
	float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
	float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data->flPenetration) * 1.25f);
	float thickness = VectorLength(trace_exit.endpos - data.enter_trace.endpos);
	thickness *= thickness;
	thickness *= v34;
	thickness /= 24.0f;
	float lost_damage = fmaxf(0.0f, v35 + thickness);
	if (lost_damage > data.current_damage)return false;
	if (lost_damage >= 0.0f)data.current_damage -= lost_damage;
	if (data.current_damage < 1.0f) return false;
	data.src = trace_exit.endpos;
	data.penetrate_count--;

	return true;
}


/*
*    CanHit() - example of how to use the code
*     @in  point: target hitbox vector
*     @out damage_given: amount of damage the shot would do
*/
bool CanHit(const Vector &point, float *damage_given)
{
	auto *local = interfaces::g_entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	auto data = FireBulletData(local->GetOrigin() + local->GetViewOffset());
	data.filter = CTraceFilter();
	data.filter.pSkip = local;

	Vector angles;
	CalcAngle(data.src, point, angles);
	AngleVectors(angles, &data.direction);
	VectorNormalize(data.direction);

	if (SimulateFireBullet(local, (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle((HANDLE)local->GetActiveWeaponHandle()), data))
	{
		*damage_given = data.current_damage;
		return true;
	}

	return false;
}

bool CanWallbang(float &dmg) //all ok
{
	IClientEntity *localplayer = interfaces::g_entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (!localplayer)
		return false;
	FireBulletData data = FireBulletData(localplayer->GetEyePosition());
	data.filter = CTraceFilter();
	data.filter.pSkip = localplayer;

	Vector EyeAng;
	interfaces::engine->GetViewAngles(EyeAng);

	Vector dst, forward;

	AngleVectors(EyeAng, &forward);
	dst = data.src + (forward * 8196.f);

	Vector angles;
	CalcAngle(data.src, dst, angles);
	AngleVectors(angles, &data.direction);
	VectorNormalize(data.direction);

	CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle((HANDLE)localplayer->GetActiveWeaponHandle());

	if (!weapon)
		return false;

	data.penetrate_count = 1;
	data.trace_length = 0.0f;

	CSWeaponInfo *weaponData = weapon->GetCSWpnData();

	if (!weaponData)
		return false;

	data.current_damage = (float)weaponData->iDamage;

	data.trace_length_remaining = weaponData->flRange - data.trace_length;

	Vector end = data.src + data.direction * data.trace_length_remaining;

	UTIL_TraceLine(data.src, end, MASK_SHOT | CONTENTS_GRATE, localplayer, 0, &data.enter_trace);

	if (data.enter_trace.fraction == 1.0f)
		return false;

	if (HandleBulletPenetration(weaponData, data))
	{
		dmg = data.current_damage;
		return true;
	}

	return false;
}

bool canhitfreestanding(const Vector &point, float *damage_given, IClientEntity* m_entity)
{
	if (m_entity && m_entity->IsAlive())
	{
		auto data = FireBulletData(m_entity->GetEyePosition());

		data.filter = CTraceFilter();

		Vector angles;

		CalcAngle(data.src, point, angles);

		AngleVectors(angles, &data.direction);

		VectorNormalize(data.direction);

		if (SimulateFireBullet(m_entity, (CBaseCombatWeapon*)interfaces::g_entitylist->GetClientEntityFromHandle((HANDLE)m_entity->GetActiveWeaponHandle()), data))
		{
			*damage_given = data.current_damage;
			//enemy can hit
			return true;
		}
	}
	return false;
}