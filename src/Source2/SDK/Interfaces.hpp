#pragma once
#include <map>
#include <string>
#include <windows.h>

namespace Source2
{
    using InterfaceEntries = std::map<std::string, std::uintptr_t>;
    using InterfaceMap = std::map<std::string, InterfaceEntries>;
    
    struct InterfaceEntry
    {
        std::uintptr_t(*InterfaceCallback)(); //0x0000
        char* InterfaceName; //0x0008
        struct InterfaceEntry* Next; //0x0010
    }; //Size: 0x0018

    class Interfaces
    {
    public:
        static Interfaces& Get();
        InterfaceMap Generate();
        InterfaceEntries Generate(const char* HostModule) const;

        template<typename T>
        T* GetInterface(const char* Module, const char* Interface)
        {
            const auto& Interfaces = this->m_Interfaces.at(Module);
            const auto& Entry = Interfaces.find(Interface);
            if(Entry == Interfaces.end())
                return nullptr;

            return reinterpret_cast<T*>(Entry->second);
        }
    private:
        InterfaceMap m_Interfaces;
    };
}