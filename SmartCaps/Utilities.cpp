#include "Utilities.h"

void SendKey(WORD VkCode)
{
    INPUT ip = { 0 };
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = VkCode;
    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

void SendKeys(const std::vector<WORD>& VkCodes)
{
    for (WORD VkCode : VkCodes)
    {
        INPUT Input = {0};
        Input.type = INPUT_KEYBOARD;
        Input.ki.wVk = VkCode;

        SendInput(1, &Input, sizeof(INPUT));
    }

    for (WORD VkCode : VkCodes)
    {
        INPUT ip = {0};
        ip.type = INPUT_KEYBOARD;
        ip.ki.wVk = VkCode;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;

        SendInput(1, &ip, sizeof(INPUT));
    }
}
