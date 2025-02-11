#include <comdef.h> 
#include "dll.h"
#include "console.h"

GameV2* game = (GameV2*)*(DWORD*)0x005eb4fc;
S8* s8 = (S8*)*(DWORD*)0x006644bc;
S10* s10 = (S10*)*(DWORD*)0x00672f40;


//void __thiscall ShowBigOnScreenLabel(void* this, WCHAR* txt, int timeToShow);
typedef void(__fastcall _ShowBigLabelLink)(void* ptr, DWORD edx, WCHAR* txt, int time);
static _ShowBigLabelLink* ShowBigOnScreenLabel = (_ShowBigLabelLink*)0x004c6060;

typedef Ped* (__stdcall _GetPedByIdLink)(int);
static _GetPedByIdLink* GetPedByIdLink = (_GetPedByIdLink*)0x0043ae10;

typedef int* (__stdcall _GetPlayersPedsLink)(int);
static _GetPlayersPedsLink* GetPlayersPedsLink = (_GetPlayersPedsLink*)0x004a5150;

typedef void(__fastcall _WarpPed)(PedS1* ptr, DWORD edx, int x, int y, int z);
static _WarpPed* WarpPed = (_WarpPed*)0x00491e00;

typedef void(__fastcall _FUN_00476e50)(void* ptr, DWORD edx, int z);
static _FUN_00476e50* FUN_00476e50 = (_FUN_00476e50*)0x00476e50;

void ShowBigLabel(const char* message) {
	_bstr_t castedMessage(message);
	//fnShowBigOnScreenLabel((void*)((int)s10 + 0x2854), 0, castedMessage, 10);
	ShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, castedMessage, 10);
}

void SetShowCycleOn() {
	*(bool*)0x005ead95 = true;
	/*BYTE val = 1;
	memcpy((void*)0x005ead95, (void*)&val, size_t(val));*/
}

void SetShowCycleOff() {
	*(bool*)0x005ead95 = false;
}

void SetPlayersCamera(Player_S4* player, int x, int y, int z) {
	player->cameraXtype1 = x;
	player->cameraYtype1 = y;
	player->cameraZtype1 = z;

	player->cameraXtype2 = x;
	player->cameraYtype2 = y;
	player->cameraZtype2 = z;

	player->cameraXtype3 = x;
	player->cameraYtype3 = y;
	player->cameraZtype3 = z;

	player->cameraXtype4 = x;
	player->cameraYtype4 = y;
	player->cameraZtype4 = z;
}

void WarpPlayer(Player_S4* player, int x, int y, int z, short rotation) {
	PedV2* ped = player->ped;
	SetPlayersCamera(player, x, y ,z);
	ped->pedS1->rotation = rotation;
	WarpPed(ped->pedS1, 0, x, y, z);
}

void WarpPlayerAndSetCamera(Player_S4* player, int x, int y, int z, short rotation) {
	PedV2* ped = player->ped;
	ped->pedS1->rotation = rotation;
	WarpPed(ped->pedS1, 0, x, y, z);
}

void Test() {
}



