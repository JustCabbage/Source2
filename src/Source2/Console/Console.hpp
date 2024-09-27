#pragma once
#include <windows.h>

#include <cstdio>

namespace Source2
{
    class Console
    {
    public:
        Console() noexcept = default;
        void __stdcall AttachConsole();
        void __stdcall DetachConsole() noexcept;
        static Console& __stdcall Get() noexcept;

        template <typename... Args>
        void __stdcall Write(const char* Format, Args... args)
        {
            std::printf("[\33[38;2;%d;%d;%dm%c\33[m] ", 173, 66, 245, '+'); // Nice purple color
            std::printf(Format, args...);
            std::printf("\n");
        }

    private:
        FILE* m_ConsoleBuffer = nullptr;
    };
} // namespace Source2