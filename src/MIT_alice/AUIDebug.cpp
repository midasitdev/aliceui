#include "pch.h"
#include "AUIDebug.h"

void AUIDebugPrintImpl(const char* filename, int line, const char* fmt, ...)
{
    const auto pre = std::string(filename) + "(" + std::to_string(line) + ") > ";
#if defined(_WIN32)
    std::vector<char> buffer(3 * strlen(fmt));
    va_list va;
    va_start(va, fmt);

#   pragma warning(push)
#   pragma warning(disable: 4996)
    vsprintf(buffer.data(), fmt, va);
#   pragma warning(pop)

    va_end(va);

    ::OutputDebugStringA(pre.c_str());
    ::OutputDebugStringA(buffer.data());
#else
    printf(pre.c_str());
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
#endif
}

void AUIDebugPrintImpl(const char* filename, int line, const wchar_t* fmt, ...)
{
    const auto pre = std::string(filename) + "(" + std::to_string(line) + ") > ";
#if defined(_WIN32)
    std::vector<wchar_t> buffer(3 * wcslen(fmt));
    va_list va;
    va_start(va, fmt);

#   pragma warning(push)
#   pragma warning(disable: 4996)
    vswprintf(buffer.data(), fmt, va);
#   pragma warning(pop)

    va_end(va);

    ::OutputDebugStringA(pre.c_str());
    ::OutputDebugStringW(buffer.data());
#else
    printf(pre.c_str());
    va_list va;
    va_start(va, fmt);
    vwprintf(fmt, va);
    va_end(va);
#endif
}
