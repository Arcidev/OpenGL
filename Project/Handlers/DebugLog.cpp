#include "DebugLog.h"

void DebugLog::write(const char* log)
{
    #if defined(_DEBUG)

        cout << log;

    #endif
}

void DebugLog::writeLine(const char* log)
{
    #if defined(_DEBUG)

        cout << log << endl;

    #endif
}

void DebugLog::writeLine(const wchar_t* log)
{
#if defined(_DEBUG)

    wcout << log << endl;

#endif
}
