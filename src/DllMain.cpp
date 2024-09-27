#include <cstdint>

#include "Source2/Source2.hpp"


std::uint32_t __stdcall DllMain(HMODULE Instance, std::uint32_t Reason, std::uint32_t Reserved)
{
    switch (Reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(Instance);
        HANDLE Thread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Source2::Create), Instance, 0, 0);
        if (Thread)
        {
            CloseHandle(Thread);
        }
        break;
    }
    }

    return 1;
}