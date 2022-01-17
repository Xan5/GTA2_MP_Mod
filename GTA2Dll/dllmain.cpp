// dllmain.cpp : Defines the entry point for the DLL application.
#define _WIN32_WINNT _WIN32_WINNT_WINXP
#include "stdafx.h"
#include "GTA2Dll.h"
#include "Console.h"

HANDLE hThread;

void Start() {
    SetupLogger();
    Log("start");
    SetShowCycleOn();
	//WaitForSingleObject(hThread, INFINITE);
    while (true)
    {
        Log("cycle");
        Test();
        Sleep(1000);
    }
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



