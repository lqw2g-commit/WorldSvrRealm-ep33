#include "Base.h"
#include "Game/Game.h"
#include "PacketManager/PacketManager.h"
#include "GameVersion/GameVersion.h"
#include "Basic/Basic.h"
#include "Discord/Discord.h"
#include "DLLSec/DLLSec.h"
#include "Screen/Screen.h"
#include "WndProc/WndProc.h"
#include "Proc/Proc.h"
#include "GameCustom/MacroBM3/BM3Macro.h"
#include "GameCustom/BattleMode/Battlemode.h"
#include <iostream>
#include <windows.h>

// Example exported function
extern "C" __declspec(dllexport) void Episode33()
{
    std::cout << "Exported function called!" << std::endl;
}

void InitAll()
{
    // Existing initialization logic
    VM_STARTU(__FUNCTION__);
    g_Procedures->SetHooks();
    g_pBM3Macro->Init();

    WindowProc::InitHooks();
    //Game::MemoryChecks::InitMemoryChanges();
    DirectX::InitHooks();
    GameVersion::SetHooks();
    PacketManager::SetHooks();
    Basic::SetHooks();
    Discord::SetHooks();
    DLLSec::SetHooks();
    Screen::InitHooks();
    BattleMode::SetHooks();



    VM_END;
}

#ifdef DEV_MODE
void allocConsole()
{
    AllocConsole();

    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();
}
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
#ifdef DEV_MODE
        allocConsole();
#endif
        InitAll();
        break;
    }
    return TRUE;
}
