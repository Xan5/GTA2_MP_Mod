// GTA2Dll.cpp : Defines the exported functions for the DLL application.

#define _WIN32_WINNT _WIN32_WINNT_WINXP
#include "stdafx.h"
#include "Structs.h"
#include "GTA2Dll.h"

//void __thiscall ShowBigOnScreenLabel(void* this, WCHAR* txt, int timeToShow);
typedef void(__fastcall ShowBigOnScreenLabel)(void* ptr, DWORD edx, WCHAR* txt, int time);
ShowBigOnScreenLabel* fnShowBigOnScreenLabel = (ShowBigOnScreenLabel*)0x004c6060;

int var1 = 69;

void ShowBigLabel() {
	S10* s10 = (S10*) * (DWORD*)0x00672f40;
	//s10-> ptrToSomeStructRelToBIG_LABEL - offset is +0x2854
	fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"qqqqqqqqqqQ", 10);
	Sleep(2000);

}
