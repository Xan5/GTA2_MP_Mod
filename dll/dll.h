#pragma once

#include "Structs.h"

void ShowBigLabel(const char* message);
Ped* GetPedById(int id);

void SetShowCycleOn();
void SetShowCycleOff();

void WarpPlayer(Player_S4* player, int x, int y, int z, short rotation);
void WarpPlayerAndSetCamera(Player_S4* player, int x, int y, int z, short rotation);

void Test();
