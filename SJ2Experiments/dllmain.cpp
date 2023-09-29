// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

/*
* Autor: ZRD
* 29.09.2023
* Nasze entry do dll, ktore jest naprawde eksperymentem co mozemy zrobic
* z SJ2 poprzez inzynierie wsteczna
*/

// glowny thread naszego dll
void MainThread(HMODULE hM)
{
    AllocConsole();

    // nie wiem czy gra jakos do debugowania uzywala konsoli i czy robila to ale na wszelki wypadek to dodalem
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    std::cout << "[+] Pomyslnie wczytano" << std::endl;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Tworzymy Thread
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

