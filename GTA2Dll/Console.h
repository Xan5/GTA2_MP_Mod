#pragma once

void SetupLogger();
void Log(const char* message);
void Log(const char* message, int value);
void Log(int message);
void LogInHex(int message);