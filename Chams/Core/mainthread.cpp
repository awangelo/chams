#include "pch.h"
#include <cstdio>
#include "../OpenGL/hooks.h"

inline static VOID
Cleanup(HMODULE hModule, FILE* p_file, DWORD exitCode)
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    if (p_file) fclose(p_file);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, exitCode);
}

DWORD WINAPI
MainThread(HMODULE hModule)
{
    FILE* p_file = NULL;
    BOOL ok = AllocConsole();
    if (!ok) Cleanup(hModule, p_file, ok);

    // A thread ainda nao tem acesso a esse console
    freopen_s(&p_file, "CONOUT$", "w", stdout);

    PCSTR art = R"(
    _________ .__
    \_   ___ \|  |__ _____    _____   ______
    /    \  \/|  |  \\__  \  /     \ /  ___/
    \     \___|   Y  \/ __ \|  Y Y  \\___ \
     \______  /___|  (____  /__|_|  /____  >
            \/     \/     \/      \/     \/
)";
    puts(art);
    puts("  [+] Successfully injected.");
    puts("  [+] Press END to unload.");

    if (!InitializeHooks()) Cleanup(hModule, p_file, 1);

    while (!(GetAsyncKeyState(VK_END) & 1))
    {
        Sleep(1000);
    }

    Cleanup(hModule, p_file, 0);
}
