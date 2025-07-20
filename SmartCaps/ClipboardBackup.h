#pragma once

#include <Windows.h>
#include <map>
#include <vector>

class ClipboardBackup
{
public:
    ClipboardBackup();

    void Restore() const;

private:
    std::map<UINT, std::vector<BYTE>> Formats;
};