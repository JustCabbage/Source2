#include "Source2.hpp"

#include <thread>

#include "Console/Console.hpp"
#include "SDK/Interfaces.hpp"

namespace Source2
{
    void __stdcall Create(HMODULE Instance)
    {
        Console& Console = Console::Get();
        Console.AttachConsole();

        Interfaces& Interfaces = Interfaces::Get();
        Interfaces.Generate();

        // Interface analysis from generated map

        while (!(GetAsyncKeyState(VK_END) & 1)) std::this_thread::sleep_for(std::chrono::milliseconds(100));

        Console.DetachConsole();
        FreeLibraryAndExitThread(Instance, 0);
    }
} // namespace Source2