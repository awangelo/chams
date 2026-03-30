#include "pch.h"
#include "mainthread.h"

BOOL APIENTRY
DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule); // Nao precisa dessas notificacoes

        HANDLE hThread = CreateThread(
            NULL, 0,
            [](LPVOID lpParam) -> DWORD {
                HMODULE hMod = (HMODULE)lpParam;
                MainThread(hMod);
                return 0;
            },
            hModule, 0, NULL
        );

        if (hThread)
            CloseHandle(hThread);
        else
            return FALSE; // Falha ao criar a thread.
    }

    return TRUE;
}
