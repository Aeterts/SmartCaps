#include "Utilities.h"

void SendKey(WORD VkCode)
{
    SendKeyState(VkCode, INPUT_KEYBOARD, 0);
    SendKeyState(VkCode, INPUT_KEYBOARD, KEYEVENTF_KEYUP);
}

void SendKeys(const std::vector<WORD>& VkCodes)
{
    for (WORD VkCode : VkCodes)
        SendKeyState(VkCode, INPUT_KEYBOARD, 0);

    for (WORD VkCode : VkCodes)
        SendKeyState(VkCode, INPUT_KEYBOARD, KEYEVENTF_KEYUP);
}

void SendKeyState(WORD VkCode, DWORD KeyType, DWORD KeyFlags)
{
    INPUT Input = { 0 };
    Input.type = KeyType;
    Input.ki.wVk = VkCode;

    if (KeyFlags > 0)
        Input.ki.dwFlags = KeyFlags;

    SendInput(1, &Input, sizeof(INPUT));
}