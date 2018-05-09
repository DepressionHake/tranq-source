// General shit
#include "DLLMain.h"
#include "Utilities.h"

// Injection stuff
#include "INJ/ReflectiveLoader.h"

// Stuff to initialise
#include "Offsets.h"
#include "Interfaces.h"
#include "Hooks.h"
#include "RenderManager.h"
#include "Hacks.h"
#include "Menu.h"
#include "MiscHacks.h"
#include "Dumping.h"
#include "AntiLeak.h"
#include "AntiAntiAim.h"
#include <iostream>

//	#define Eddie -1634570121
//	#define Blank 1042304619
#define bobbo 1213810804
//	#define near 1213810804
//	#define a7las 310320754
#define bonus 1446480194
#define xanax 1590804032
#define max 1855585659
//#define fach -1765626592
//	#define wave 1213810804 //lifetime
#define mrbean -1409279184 //one month from 3/23
#define stevie -223997480  //this is stevie gave me csgo account 6 months 
//	#define Huddy -1128825389 //2 days from 3/28
#define eddie 1213810804 //weezo
#define mike 1213810804
#define synth -1875610336 //lifetime
#define GoldenHackUser -1092299461 //lifetime
#define GNF -1402304679
#define jake 1045183505
#define Jesse 1518069402
#define weirdnameguy 673786259
//#define curv3 1678080564 //one month from 2/4
//#define Cookie 1047031790 //making video started 2/17
//#define Womble -836981747 //making video started 2/20
//	#define hermes -459590222 //making video started 2/24
//	#define enpo 243804604 //making video started 2/24
//	#define Weerks 2117025276 //one month from 2/26
#define cbaz 1244856661 //lifetime
//#define Strain -194323508 //making video started 3/3
//  #define Sub 349527895 //one month from 3/4
#define SpitefulLox -1308326986 //one month from 3/18
//	#define Joao 205416094 //one month from 3/8
#define Justin09104 -800826623 //one month from 3/11
#define homicide 1213810804
#define Odysseas 1213810804
#define Wolfee -1013697163 //one month from 3/19
#define banana 249560360 //cause i trust this mans
#define ninelives 1553286926 //one month from 3/23
#define chriscurtis 339617762
#define grix -1096090042 //lifetime
#define ZDP 2085521108 //making video started 3/28
#define Kennyboiii -1643091536 //one month from 4/5
#define Dank 505461181 //lifetime
#define therussian 1658318589 //ont month from 4/8
#define Sparticus 1213810804
#define n7ckgakis -1369807748
#define jayy -199582547
#define desync 679772352

float lineRealAngle;
float testFloat1;
float testFloat2;
int resolverstage[64];
float testFloat3;
float enemyLBYTimer[65];
int hittedLogHits[65];
float autowalldmgtest[65];

float testFloat4;
int shotsfired;
int LBYBreakerTimer;
float lineFakeAngle;
float consoleProxyLbyLASTUpdateTime;
int antiAimSide;
float lineLBY;
float flipBool;

template <int XORSTART, int BUFLEN, int XREFKILLER>

class Xor
{
private:
	Xor();
public:
	char s[BUFLEN];

	Xor(const char* xs);
	~Xor()
	{
		for (int i = 0; i < BUFLEN; i++) s[i] = 0;
	}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>

Xor<XORSTART, BUFLEN, XREFKILLER>::Xor(const char* xs)
{
	int xvalue = XORSTART;
	int i = 0;
	for (; i < (BUFLEN - 1); i++)
	{
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN - 1] = (2 * 2 - 3) - 1;
}

extern HINSTANCE hAppInstance;

UCHAR szFileSys[255], szVolNameBuff[255];
DWORD dwMFL, dwSysFlags;
DWORD dwSerial;
LPCTSTR szHD = "C:\\";

bool ErasePEHeader(HMODULE hModule)
{
	hModule = GetModuleHandle(NULL);
	if ((DWORD)hModule == 0) return 0;
	DWORD IMAGE_NT_HEADER = *(int*)((DWORD)hModule + 60);
	for (int i = 0; i<0x108; i++)
		*(BYTE*)(IMAGE_NT_HEADER + i) = 0;
	for (int i = 0; i<120; i++)
		*(BYTE*)((DWORD)hModule + i) = 0;
	return 1;
}

HINSTANCE HThisModule;
bool DoUnload;

void CAntiLeak::ErasePE()
{
	char *pBaseAddr = (char*)GetModuleHandle(NULL);
	DWORD dwOldProtect = 0;
	VirtualProtect(pBaseAddr, 4096, PAGE_READWRITE, &dwOldProtect);
	ZeroMemory(pBaseAddr, 4096);
	VirtualProtect(pBaseAddr, 4096, dwOldProtect, &dwOldProtect);
}

int InitialThread()
{
	//Utilities::OpenConsole("Avoz");

	PrintMetaHeader();

	Offsets::Initialise();
	interfaces::Initialise();
	NetVar.RetrieveClasses();
	NetvarManager::Instance()->CreateDatabase();
	Render::Initialise();
	Hacks::SetupHacks();
	SetupMenu();
	Hooks::Initialise();
	ApplyAAAHooks();


	//Dump::DumpClassIds();


	Utilities::Log("Ready");

	while (DoUnload == false)
	{
		Sleep(1000);
	}

	Hooks::UndoHooks();
	Sleep(2000);
	FreeLibraryAndExitThread(HThisModule, 0);

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Beep(750, 800);
		GetVolumeInformation(szHD, (LPTSTR)szVolNameBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);

		if (dwSerial == bonus ||
			dwSerial == bobbo ||
			dwSerial == eddie ||
			dwSerial == grix ||
			dwSerial == banana ||
			dwSerial == Justin09104 ||
			dwSerial == Odysseas ||
			dwSerial == Dank ||
			dwSerial == ZDP ||
			dwSerial == Wolfee ||
			dwSerial == ninelives ||
			dwSerial == max ||
			dwSerial == xanax ||
			dwSerial == mrbean ||
			dwSerial == stevie ||
			dwSerial == mike ||
			dwSerial == jayy ||
			dwSerial == synth ||
			dwSerial == GoldenHackUser ||
			dwSerial == desync ||
			dwSerial == GNF ||
			dwSerial == jake ||
			dwSerial == Jesse ||
			dwSerial == weirdnameguy ||
			dwSerial == synth ||
			dwSerial == cbaz ||
			dwSerial == SpitefulLox ||
			dwSerial == chriscurtis ||
			dwSerial == Kennyboiii ||
			dwSerial == therussian ||
			dwSerial == Sparticus ||
			dwSerial == n7ckgakis)

		{
			Beep(750, 800);
			Sleep(100);
		}
		else
		{
			// when HWID rejected
			MessageBox(NULL, "Incorrect HWID!", "tranquility", MB_OK);
			exit(0);
			return TRUE;
		}

		{
			{
				DisableThreadLibraryCalls(hModule);

				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitialThread, NULL, NULL, NULL);

				return TRUE;
			}
		}
		return FALSE;
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
	}
	return TRUE;
}