#include "ClipboardBackup.h"

ClipboardBackup::ClipboardBackup()
{
    if (OpenClipboard(nullptr))
    {
        UINT Format = 0;

        while ((Format = EnumClipboardFormats(Format)))
        {
            HANDLE hData = GetClipboardData(Format);

            if (hData)
            {
                SIZE_T Size = GlobalSize(hData);
                if (Size > 0)
                {
                    BYTE* Data = static_cast<BYTE*>(GlobalLock(hData));

                    if (Data)
                    {
                        std::vector<BYTE> Buffer(Size);

                        memcpy(Buffer.data(), Data, Size);

                        Formats[Format] = Buffer;

                        GlobalUnlock(hData);
                    }
                }
            }
        }

        CloseClipboard();
    }
}

void ClipboardBackup::Restore() const
{
    if (!OpenClipboard(nullptr))
        return;

    EmptyClipboard();

    for (const auto& Pair : Formats)
    {
        UINT Format = Pair.first;
        const std::vector<BYTE>& Data = Pair.second;
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, Data.size());

        if (hMem)
        {
            BYTE* Dest = static_cast<BYTE*>(GlobalLock(hMem));

            if (Dest)
            {
                memcpy(Dest, Data.data(), Data.size());
                GlobalUnlock(hMem);
                SetClipboardData(Format, hMem);
            }
        }
    }

    CloseClipboard();
}
