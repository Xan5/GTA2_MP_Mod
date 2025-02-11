// dllmain.cpp : Defines the entry point for the DLL application.
/* #define _WIN32_WINNT _WIN32_WINNT_WINXP */
#include "console.h"
#include "dll.h"
#include <windows.h>

/* #define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from
 * Windows headers */

HANDLE hThread;

void Start() {
  MessageBox(0, "a", "Variable", 0);
  SetupLogger();
  Log("start");
  SetShowCycleOn();
  /* WaitForSingleObject(hThread, INFINITE); */
  while (true) {
    Log("cycle");
    Test();
    Sleep(1000);
  }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  switch (ul_reason_for_call) {
  case DLL_PROCESS_ATTACH:
    MessageBox(0, "a", "Variable", 0);
    hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
