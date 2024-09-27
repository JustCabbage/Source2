#include "Console.hpp"

namespace Source2
{
    void Console::AttachConsole()
    {
        AllocConsole();
        freopen_s(&m_ConsoleBuffer, "CONOUT$", "w", stdout);
        SetConsoleTitle("Source2 - Debug Console");

        // Handle ANSI escape codes
        HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD ConsoleMode;
        GetConsoleMode(ConsoleHandle, &ConsoleMode);
        ConsoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        ConsoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
        SetConsoleMode(ConsoleHandle, ConsoleMode);
    }

    void Console::DetachConsole() noexcept
    {
        if (m_ConsoleBuffer)
        {
            fclose(m_ConsoleBuffer);
        }
        FreeConsole();
    }

    Console& Console::Get() noexcept
    {
        static Console Instance;
        return Instance;
    }
} // namespace Source2