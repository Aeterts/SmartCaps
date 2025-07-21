#include "CapsLockState.h"
#include "ClipboardBackup.h"
#include "Utilities.h"

bool bIgnoreNextCapsLock = false;

void HandleClipboardOperation()
{
    ClipboardBackup Backup;

    bool bHasSelection = false;
    std::wstring SelectedText;

    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        CloseClipboard();
    }

    SendKeys({ VK_CONTROL, 'C' });
    Sleep(30);

    if (OpenClipboard(nullptr))
    {
        if (IsClipboardFormatAvailable(CF_UNICODETEXT))
        {
            HANDLE hData = GetClipboardData(CF_UNICODETEXT);

            if (hData)
            {
                wchar_t* Text = static_cast<wchar_t*>(GlobalLock(hData));

                if (Text && Text[0] != L'\0')
                {
                    SelectedText = Text;
                    bHasSelection = true;

                    GlobalUnlock(hData);
                }
            }
        }

        CloseClipboard();
    }

    if (bHasSelection)
    {
        try
        {
            std::wstring NewText = InvertTextCase(SelectedText);

            if (OpenClipboard(nullptr))
            {
                EmptyClipboard();

                HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (NewText.length() + 1) * sizeof(wchar_t));

                if (hMem)
                {
                    wchar_t* Buffer = static_cast<wchar_t*>(GlobalLock(hMem));

                    if (Buffer)
                    {
                        wcscpy_s(Buffer, NewText.length() + 1, NewText.c_str());
                        GlobalUnlock(hMem);
                        SetClipboardData(CF_UNICODETEXT, hMem);
                    }
                }

                CloseClipboard();
            }

            SendKeys({ VK_CONTROL , 'V' });
            Sleep(30);
        }
        catch (...)
        {
            ToggleCapsLock();
        }
    }
    else
    {
        ToggleCapsLock();
    }

    Backup.Restore();
}

std::wstring InvertTextCase(const std::wstring& Text)
{
    std::wstring Result;

    for (wchar_t Char : Text)
    {
        wchar_t Buffer[2] = {Char, L'\0'};

        if (IsCharUpperW(Char))
        {
            CharLowerW(Buffer);

            Result += Buffer[0];
        }
        else if (IsCharLowerW(Char))
        {
            CharUpperW(Buffer);

            Result += Buffer[0];
        }
        else
        {
            Result += Char;
        }
    }

    return Result;
}

void ToggleCapsLock()
{
    bIgnoreNextCapsLock = true;

    SendKey(VK_CAPITAL);
}