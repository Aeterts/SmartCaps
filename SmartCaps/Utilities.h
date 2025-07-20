#pragma once

#include <Windows.h>
#include <vector>

void SendKey(WORD VkCode);
void SendKeys(const std::vector<WORD>& VkCodes);