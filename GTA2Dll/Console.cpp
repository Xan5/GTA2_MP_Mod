// Console.cpp : Defines logging functions

#define _WIN32_WINNT _WIN32_WINNT_WINXP
#include "stdafx.h"
#include "Console.h"

void Log(const char* message) {
    std::cout << message << std::endl;
}
void Log(const char* message, int value) {
    std::cout << message << value << std::endl;
}

void Log(int message) {
    std::cout << message << std::endl;
}

void LogInHex(int message) {
    std::cout << std::hex << message << std::endl;
}

void Log(std::string message) {
    std::cout << message << std::endl;
}

void SetupConsoleLogger() {
    HWND window = GetForegroundWindow();
    FILE* streams[] = { stdout };
    AllocConsole();
    freopen_s(streams, "CONOUT$", "w", stdout);
    SetForegroundWindow(window);
}

void SetupFileLogger() {
    FILE* pFile = new FILE;
    errno_t err = fopen_s(&pFile, "log.txt", "w");
    if (err != -1) perror("Error opening file");
    freopen_s(&pFile, "log.txt", "w", stdout);
}

void SetupLogger() {
    SetupConsoleLogger();
    //SetupFileLogger();
}