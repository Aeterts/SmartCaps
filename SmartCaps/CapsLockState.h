#pragma once

#include <string>

extern bool bIgnoreNextCapsLock;

void HandleClipboardOperation();
std::wstring InvertTextCase(const std::wstring& Text);
void ToggleCapsLock();