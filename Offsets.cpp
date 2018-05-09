#include "Offsets.h"
#include "UTIL Functions.h"

#define strenc( s ) ( s )
void Offsets::Initialise()
{
	// Modules
	Modules::Client = Utilities::Memory::WaitOnModuleHandle("client.dll");
	Modules::Engine = Utilities::Memory::WaitOnModuleHandle("engine.dll");
	Modules::VGUI2 = Utilities::Memory::WaitOnModuleHandle("vgui2.dll");
	Modules::VGUISurface = Utilities::Memory::WaitOnModuleHandle("vguimatsurface.dll");
	Modules::Material = Utilities::Memory::WaitOnModuleHandle("materialsystem.dll");
	Modules::VPhysics = Utilities::Memory::WaitOnModuleHandle("vphysics.dll");
	Modules::Stdlib = Utilities::Memory::WaitOnModuleHandle("vstdlib.dll");
	Modules::DataCaches = Utilities::Memory::WaitOnModuleHandle("datacache.dll");

	//------------------------------------------------------------------------
	// VTables
#pragma region VTables
	VMT::CHL_GetAllClasses = 8;

	VMT::Engine_GetScreenSize = 5;
	VMT::Engine_GetPlayerInfo = 8;
	VMT::Engine_GetLocalPlayer = 12;
	VMT::Engine_Time = 14;
	VMT::Engine_GetViewAngles = 18;
	VMT::Engine_SetViewAngles = 19;
	VMT::Engine_GetMaxClients = 20;
	VMT::Engine_IsConnected = 27;
	VMT::Engine_IsInGame = 26;
	VMT::Engine_WorldToScreenMatrix = 37;
	VMT::Engine_ClientCmd_Unrestricted = 114;

	VMT::Panel_GetName = 36;
	VMT::Panel_PaintTraverse = 41;

	VMT::Surface_DrawSetColorA = 14;
	VMT::Surface_DrawSetColorB = 15;
	VMT::Surface_DrawFilledRect = 16;
	VMT::Surface_DrawOutlinedRect = 18;
	VMT::Surface_DrawLine = 19;
	VMT::Surface_DrawSetTextFont = 23;
	VMT::Surface_DrawSetTextColorA = 24;
	VMT::Surface_DrawSetTextColorB = 25;
	VMT::Surface_DrawSetTextPos = 26;
	VMT::Surface_DrawPrintText = 28;
	VMT::Surface_DrawSetTextureRGBA = 37;
	VMT::Surface_DrawSetTexture = 38;
	VMT::Surface_CreateNewTextureID  = 43;
	VMT::Surface_FontCreate = 71;
	VMT::Surface_SetFontGlyphSet = 72;
	VMT::Surface_GetTextSize = 79;
	VMT::Surface_DrawOutlinedCircle = 103;
	VMT::Surface_SurfaceGetCursorPos = 66;
	VMT::Surface_DrawTexturedPolygon = 106;

	VMT::Material_GetName = 0;
	VMT::Material_SetMaterialVarFlag = 30;
	VMT::Material_GetMaterialVarFlag = 31;
	VMT::Material_AlphaModulate = 28;
	VMT::Material_ColorModulate = 29;
	VMT::Material_IncrementReferenceCount = 14;
	
	VMT::MaterialSystem_FindMaterial = 84;
	VMT::MaterialSystem_CreateMaterial = 83;
	
	VMT::ModelRender_ForcedMaterialOverride = 1;
	VMT::ModelRender_DrawModelExecute = 21;
	
	VMT::ModelInfo_GetModelName = 3;
	VMT::ModelInfo_GetStudiomodel = 32;

	VMT::RenderView_SetBlend = 4;
	VMT::RenderView_SetColorModulation = 6;

#pragma endregion Contains the VTable Indexs

	// I cbf trying to get the KeyValues part of the SDK working solo, so we'll just
	// Do some dirty shit
	Functions::KeyValues_KeyValues = Utilities::Memory::FindPattern("client.dll", (PBYTE)"\x68\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x89\x45\xFC\xEB\x07\xC7\x45\x00\x00\x00\x00\x00\x8B\x03\x56", "x????xxx????xxxxxxx?????xxx");
	Functions::KeyValues_KeyValues += 7;
	Functions::KeyValues_KeyValues = Functions::KeyValues_KeyValues + *reinterpret_cast< PDWORD_PTR >(Functions::KeyValues_KeyValues + 1) + 5;

	Functions::KeyValues_LoadFromBuffer = Utilities::Memory::FindPattern("client.dll", (PBYTE)"\xE8\x00\x00\x00\x00\x80\x7D\xF8\x00\x00\x00\x85\xDB", "x????xxxx??xx");
	Functions::KeyValues_LoadFromBuffer = Functions::KeyValues_LoadFromBuffer + *reinterpret_cast< PDWORD_PTR >(Functions::KeyValues_LoadFromBuffer + 1) + 5;

	Functions::dwCalcPlayerView =  Utilities::Memory::FindPattern("client.dll", (PBYTE)"\x84\xC0\x75\x08\x57\x8B\xCE\xE8\x00\x00\x00\x00\x8B\x06", "xxxxxxxx????xx");

	Functions::dwGetPlayerCompRank = GameUtils::FindPattern1(strenc("client.dll"), strenc("55 8B EC 8B 0D ? ? ? ? 68 ? ? ? ? "));

	Functions::dwIsReady = GameUtils::FindPattern1(strenc("client.dll"), strenc("55 8B EC 51 56 8B 35 ? ? ? ? 80 7E 58 00"));

	Utilities::Log("Offsets/Indexes Up to Date");
}

namespace Offsets
{
	// Addresses of loaded game modules
	namespace Modules
	{
		DWORD Client;
		DWORD Engine;
		DWORD VGUI2;
		DWORD VGUISurface;
		DWORD Material;
		DWORD VPhysics;
		DWORD Stdlib;
		DWORD DataCaches;
	};

	// Virtual Method Table Indexes
	namespace VMT
	{
		//CHL Client
		DWORD CHL_GetAllClasses;

		//Engine Client
		DWORD Engine_GetScreenSize;
		DWORD Engine_GetPlayerInfo;
		DWORD Engine_GetLocalPlayer;
		DWORD Engine_Time;
		DWORD Engine_GetViewAngles;
		DWORD Engine_SetViewAngles;
		DWORD Engine_GetMaxClients;
		DWORD Engine_IsConnected;
		DWORD Engine_IsInGame;
		DWORD Engine_WorldToScreenMatrix;
		DWORD Engine_GetNetChannelInfo;
		DWORD Engine_ClientCmd_Unrestricted;

		// Panels
		DWORD Panel_GetName;
		DWORD Panel_PaintTraverse;

		// Surface
		DWORD Surface_DrawSetColorA;
		DWORD Surface_DrawSetColorB;
		DWORD Surface_DrawFilledRect;
		DWORD Surface_DrawOutlinedRect;
		DWORD Surface_DrawLine;
		DWORD Surface_DrawSetTextFont;
		DWORD Surface_DrawSetTextColorA;
		DWORD Surface_DrawSetTextColorB;
		DWORD Surface_DrawSetTextPos;
		DWORD Surface_DrawPrintText;
		DWORD Surface_DrawSetTextureRGBA;
		DWORD Surface_DrawSetTexture;
		DWORD Surface_CreateNewTextureID;
		DWORD Surface_FontCreate;
		DWORD Surface_SetFontGlyphSet;
		DWORD Surface_GetTextSize;
		DWORD Surface_DrawOutlinedCircle;
		DWORD Surface_SurfaceGetCursorPos;
		DWORD Surface_DrawTexturedPolygon;

		DWORD Material_GetName;
		DWORD Material_SetMaterialVarFlag;
		DWORD Material_GetMaterialVarFlag;
		DWORD Material_AlphaModulate;
		DWORD Material_ColorModulate;
		DWORD Material_IncrementReferenceCount;

		DWORD MaterialSystem_FindMaterial;
		DWORD MaterialSystem_CreateMaterial;

		DWORD ModelRender_ForcedMaterialOverride;
		DWORD ModelRender_DrawModelExecute;

		DWORD ModelInfo_GetModelName;
		DWORD ModelInfo_GetStudiomodel;

		DWORD RenderView_SetBlend;
		DWORD RenderView_SetColorModulation;

		// Weapon entities
		DWORD Weapon_GetSpread;
	};

	// Addresses of engine functions to call
	namespace Functions
	{
		DWORD KeyValues_KeyValues;
		DWORD KeyValues_LoadFromBuffer;
		DWORD dwCalcPlayerView;
		DWORD dwGetPlayerCompRank;
		DWORD dwIsReady;
	};

}; namespace junkCode_KJ8NI4CRPGII
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