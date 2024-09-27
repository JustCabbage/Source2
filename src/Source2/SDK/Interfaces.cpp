#include "Interfaces.hpp"

#include "../Console/Console.hpp"
#include "Utils.hpp"

namespace Source2
{
    Interfaces& Interfaces::Get()
    {
        static Interfaces Instance;
        return Instance;
    }

    InterfaceMap Interfaces::Generate()
    {
        const auto& Modules = Utils::FetchModules();
        for (const auto& Module : Modules)
        {
            const InterfaceEntries& Entries = Generate(Module.c_str());
            if (Entries.size())
            {
                this->m_Interfaces[Module] = Entries;
            }
        }

        return this->m_Interfaces;
    }

    InterfaceEntries Interfaces::Generate(const char* HostModule) const
    {
        Console& Console = Console::Get();
        InterfaceEntries Entries = {};

        const HMODULE Module = GetModuleHandleA(HostModule);

        if (!Module)
            return Entries;

        const std::uintptr_t InterfaceExport = reinterpret_cast<std::uintptr_t>(GetProcAddress(Module, "CreateInterface"));

        if (!InterfaceExport)
            return Entries;

        InterfaceEntry** InterfaceEntries = Utils::RVA<InterfaceEntry**>(reinterpret_cast<std::uint8_t*>(InterfaceExport), 3, 7);
        for (InterfaceEntry* Entry = *InterfaceEntries; Entry; Entry = Entry->Next)
        {
            const std::uintptr_t Interface = Entry->InterfaceCallback();
            Entries[Entry->InterfaceName] = Interface;
            Console.Write("%s -> %s ~ %p", HostModule, Entry->InterfaceName, Interface);
        }

        return Entries;
    }
} // namespace Source2