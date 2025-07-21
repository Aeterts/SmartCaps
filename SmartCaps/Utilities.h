#pragma once

#include <Windows.h>
#include <vector>

void SendKey(WORD VkCode);
void SendKeys(const std::vector<WORD>& VkCodes);
void SendKeyState(WORD VkCode, DWORD KeyType, DWORD KeyFlags);