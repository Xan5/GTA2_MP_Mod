#include <comdef.h>
#include <io.h>
#include <shellapi.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <windows.h>
#define F_OK 0
#define access _access

using namespace std;

HANDLE findProcess(WCHAR *processName);
BOOL loadRemoteDLL(HANDLE hProcess, const char *dllPath);
bool fileExist(const char *fname);

int main() {
  /* ShellExecuteA(NULL, "open", "gta2.exe", NULL, "...\\GTA2", SW_SHOWDEFAULT);
   */

  _bstr_t exeName("gta2.exe");
  char dllPath[] =
      "C:\\Users\\Xan\\source\\GTA2_MP_Mod\\zig-out\\bin\\GTA2MP.dll";
  if (!fileExist(dllPath)) {
    printf("[-] DLL not found! \n");
    Sleep(1000);
    exit(0);
  }

  while (true) {
    HANDLE hProcess = findProcess(exeName);
    if (hProcess != NULL) {
      BOOL injectSuccessful = loadRemoteDLL(hProcess, dllPath);
      if (injectSuccessful) {
        printf("[+] DLL injection successful! \n");
        Sleep(1000);
        exit(0);
      } else {
        printf("[-] DLL injection failed. \n");
        getchar();
      }
    }
  }
}

HANDLE findProcess(WCHAR *processName) {
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  DWORD dwPriorityClass;

  // Take a snapshot of all processes in the system.
  hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    printf("[-] Could not create snapshot.\n");
  }

  // Set the size of the structure before using it.
  pe32.dwSize = sizeof(PROCESSENTRY32);

  // Retrieve information about the first process,
  // and exit if unsuccessful
  if (!Process32First(hProcessSnap, &pe32)) {
    printf("[-] Process32First");
    CloseHandle(hProcessSnap);
    return FALSE;
  }

  // Now walk the snapshot of processes, and
  // display information about each process in turn
  do {
    if (!wcscmp(_bstr_t(pe32.szExeFile), processName)) {
      printf("The process %s was found in memory.\n", pe32.szExeFile);

      hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
      if (hProcess != NULL) {
        return hProcess;
      } else {
        printf("[-] Failed to open process %s.\n", pe32.szExeFile);
        return NULL;
      }
    }

  } while (Process32Next(hProcessSnap, &pe32));

  printf("[-] %ls has not been loaded into memory, aborting.\n", processName);
  return NULL;
}

BOOL loadRemoteDLL(HANDLE hProcess, const char *dllPath) {
  // printf("Enter any key to attempt DLL injection.");
  // getchar();

  // Allocate memory for DLL's path name to remote process
  LPVOID dllPathAddressInRemoteMemory =
      VirtualAllocEx(hProcess, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT,
                     PAGE_EXECUTE_READWRITE);
  if (dllPathAddressInRemoteMemory == NULL) {
    printf("[-] VirtualAllocEx unsuccessful.\n");
    getchar();

    return FALSE;
  }

  // Write DLL's path name to remote process
  BOOL succeededWriting = WriteProcessMemory(
      hProcess, dllPathAddressInRemoteMemory, dllPath, strlen(dllPath), NULL);

  if (!succeededWriting) {
    printf("[-] WriteProcessMemory unsuccessful.\n");
    getchar();
    return FALSE;
  } else {
    // Returns a pointer to the LoadLibrary address. This will be the same on
    // the remote process as in our current process.
    LPVOID loadLibraryAddress =
        (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if (loadLibraryAddress == NULL) {
      printf("[-] LoadLibrary not found in process.\n");
      getchar();
      return FALSE;
    } else {
      HANDLE remoteThread = CreateRemoteThread(
          hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryAddress,
          dllPathAddressInRemoteMemory, NULL, NULL);
      if (remoteThread == NULL) {
        printf("[-] CreateRemoteThread unsuccessful.\n");
        getchar();
        return FALSE;
      }
    }
  }

  CloseHandle(hProcess);
  return TRUE;
}

bool fileExist(const char *fname) {
  if (access(fname, F_OK) == 0) {
    return true;
  }
  return false;
}
