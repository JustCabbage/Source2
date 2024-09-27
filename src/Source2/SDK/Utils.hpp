#pragma once
// clang-format off
#include <Windows.h>
#include <TlHelp32.h>
// clang-format on

#include <cstdint>
#include <string>
#include <vector>

namespace Source2
{
    class Utils
    {
    public:
        template <typename T = void*>
        static T RVA(std::uint8_t* Address, std::uintptr_t RVAOffset, std::uintptr_t RIPOffset)
        {
            const std::uint32_t RVAShift = *reinterpret_cast<std::uint32_t*>(Address + RVAOffset);
            const std::uint64_t RIPShift = reinterpret_cast<std::uint64_t>(Address) + RIPOffset;
            return reinterpret_cast<T>(RVAShift + RIPShift);
        }

        static std::vector<std::string> FetchModules()
        {
            std::vector<std::string> ModuleList = {};

            MODULEENTRY32 ModuleEntry;

            HANDLE ModuleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
            if (ModuleSnapshot == INVALID_HANDLE_VALUE)
                return ModuleList;

            ModuleEntry.dwSize = sizeof(MODULEENTRY32);

            if (!Module32First(ModuleSnapshot, &ModuleEntry))
            {
                CloseHandle(ModuleSnapshot);
                return ModuleList;
            }

            do {
                const std::uintptr_t CreateInterface = reinterpret_cast<std::uintptr_t>(GetProcAddress(ModuleEntry.hModule, "CreateInterface"));
                if (CreateInterface && strcmp(ModuleEntry.szModule, "crashhandler64.dll")) // Whitelist crashhandler64.dll, since it's export is formatted differently
                {
                    ModuleList.push_back(ModuleEntry.szModule);
                }
            } while (Module32Next(ModuleSnapshot, &ModuleEntry));

            CloseHandle(ModuleSnapshot);
            return ModuleList;
        };
    };
} // namespace Source2