#pragma once

class DebugLog
{
    public:
        static void write(char const* log);
        static void writeLine(char const* log);
        static void writeLine(wchar_t const* log);
};
