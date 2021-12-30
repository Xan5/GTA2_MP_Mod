// GTA2Dll.cpp : Defines the exported functions for the DLL application.

#define _WIN32_WINNT _WIN32_WINNT_WINXP
#include "stdafx.h"
#include "GTA2Dll.h"
#include <comdef.h> 

void EditMemory(DWORD dwAddress, BYTE bVal)
{
	DWORD dwOld;
	if (VirtualProtect((void*)dwAddress, 1, 0x40, &dwOld))
	{
		if (IsBadReadPtr((PDWORD)dwAddress, 1) == 0)
		{
			//memcpy((void*)dwAddress, (void*)&bVal, 1);
			*(PBYTE)dwAddress = bVal;
			VirtualProtect((void*)dwAddress, 1, dwOld, &dwOld);
		}
	}
}

void EditMemory(DWORD dwAddress, DWORD dwVal, DWORD type)
{
	DWORD dwOld;
	if (VirtualProtect((void*)dwAddress, 1, 0x40, &dwOld))
	{
		if (IsBadReadPtr((PDWORD)dwAddress, type) == 0)
		{
			memcpy((void*)dwAddress, (void*)&dwVal, type);
			VirtualProtect((void*)dwAddress, 1, dwOld, &dwOld);
		}
	}
}

//void __thiscall ShowBigOnScreenLabel(void* this, WCHAR* txt, int timeToShow);
typedef void(__fastcall ShowBigLabelLink)(void* ptr, DWORD edx, WCHAR* txt, int time);
static ShowBigLabelLink* fnShowBigOnScreenLabel = (ShowBigLabelLink*)0x004c6060;

typedef Ped* (__stdcall GetPedByIdLink)(int);
static GetPedByIdLink* fnGetPedByID = (GetPedByIdLink*)0x0043ae10;

void ShowBigLabel(const char* message) {
	_bstr_t castedMessage(message);
	S10* s10 = (S10*) * (DWORD*)0x00672f40;
	//s10-> ptrToSomeStructRelToBIG_LABEL - offset is +0x2854
	fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, castedMessage, 10);
}

Ped* GetPedById(int id) {
	return fnGetPedByID(id);
}

void SetShowCycleOn() {
	EditMemory((DWORD)0x005ead95, (BYTE)0x0001);
}



