#pragma once

class DebugLog
{
    public:
        static void write(const char* log);
        static void writeLine(const char* log);
        static void writeLine(const wchar_t* log);
};
