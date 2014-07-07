#include "DebugLog.h"
#include <iostream>

void DebugLog::write(const char* log)
{
    #if defined(_DEBUG)

        std::cout << log;

    #endif
}

void DebugLog::writeLine(const char* log)
{
    #if defined(_DEBUG)

        std::cout << log << std::endl;

    #endif
}

void DebugLog::writeLine(const wchar_t* log)
{
    #if defined(_DEBUG)

        std::wcout << log << std::endl;

    #endif
}
