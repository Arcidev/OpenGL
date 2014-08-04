#include <iostream>
#include "DebugLog.h"

void DebugLog::write(char const* log)
{
    #if defined(_DEBUG)

        std::cout << log;

    #endif
}

void DebugLog::writeLine(char const* log)
{
    #if defined(_DEBUG)

        std::cout << log << std::endl;

    #endif
}

void DebugLog::writeLine(wchar_t const* log)
{
    #if defined(_DEBUG)

        std::wcout << log << std::endl;

    #endif
}
